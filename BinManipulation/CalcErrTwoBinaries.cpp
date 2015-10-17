/*
 * This program reads two binary files, and calculates the 
 * statistical errors between them.
 *
 * This program splits files into layers to perform calculation,
 * so it supports evaluation on very large files.
 *
 * The outputs are min, max, RMS and L-Infinity.
 *
 * Programmer: Samuel Li
 * Date: 7/3/2015
 *
 * Modified: 8/5/2015
 *      FLOAT macro defines single or double precision.
 */


#include "stats.h"
#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define FLOAT float

using namespace std;

/* 
 * Opens a file to read and returns the length of the file in byte.
 */
long int OpenFileRead( FILE* &file, char* filename )
{
    file = fopen( filename, "rb" );
    if( file == NULL ) {
        cerr << "File open error: " << filename << endl;
        exit(1);
    }
    fseek( file, 0, SEEK_END );
    long size = ftell( file );
    fseek( file, 0, SEEK_SET );

    return size;
}

/*
 * Read a data chunk from the binary file.
 * Both offset and count are in the number of FLOATs (not bytes).
 */
void ReadChunk( FILE* &file, long offset, long count, FLOAT* buf )
{
    long rt = fseek( file, sizeof(FLOAT) * offset, SEEK_SET );
    if( rt != 0 ){
        cerr << "File seek error! " << endl;
        exit(1);
    }
    rt = fread( buf, sizeof(FLOAT), count, file ); 
    if( rt != count ) {
        cerr << "File read error! " << endl;
        exit(1);
    }
}

int main( int argc, char* argv[] )
{
    if( argc != 4 ) {
        if( sizeof(FLOAT) == 8 )
            cerr << "\tUsage: DOUBLE_filename1, DOUBLE_filename2, Z_dimension" << endl;
        else if( sizeof(FLOAT) == 4 )
            cerr << "\tUsage: FLOAT_filename1, FLOAT_filename2, Z_dimension" << endl;
        exit(1);
    }

    FILE* file1 = NULL;
    FILE* file2 = NULL;
    long size1 = OpenFileRead( file1, argv[1] );
    long size2 = OpenFileRead( file2, argv[2] );
    if( size1 != size2 ) {
        cerr << "Input file sizes don't align..." << endl;
        exit(1);
    }
    int z = atoi( argv[3] );
    if( size1 % z != 0 ) {
        cerr << "Z dimension error!" << endl;
        exit(1);
    }
    long planeSize = size1 / z / sizeof(FLOAT);
    FLOAT min1 , max1 , min2 , max2;
    min1 = max1 = min2 = max2 = 0.0;
    double* rmse_arr   = new double[ z ];   
    double*  linfy_arr = new double[ z ];
    FLOAT minmax1[2], minmax2[2];

    FLOAT*  buf1      = new FLOAT[ planeSize ];
    FLOAT*  buf2      = new FLOAT[ planeSize ];

    for( int i = 0; i < z; i++ ) {
        ReadChunk( file1, i * planeSize, planeSize, buf1 );
        ReadChunk( file2, i * planeSize, planeSize, buf2 );
        Stats::GetMinMax( buf1, minmax1, planeSize );
        Stats::GetMinMax( buf2, minmax2, planeSize );
        if( i == 0 ) {
            min1 = minmax1[0];      max1 = minmax1[1];
            min2 = minmax2[0];      max2 = minmax2[1];
        }
        else {
            min1 = min( min1, minmax1[0] );
            max1 = max( max1, minmax1[1] );
            min2 = min( min2, minmax2[0] );
            max2 = max( max2, minmax2[1] );
        }
        rmse_arr[i] = Stats::GetRMSE2( buf1, buf2, planeSize );
        linfy_arr[i] = Stats::GetLInfNorm( buf1, buf2, planeSize );    
    }

    double rmse = sqrt( Stats::GetMean( rmse_arr, z ));
    double linfy = linfy_arr[0];
    for( int i = 1; i < z; i++ )
        if( linfy_arr[i] > linfy )      
            linfy = linfy_arr[i];

    printf( "\t%s: min=%e, max=%e\n", argv[1], min1, max1 );
    printf( "\t%s: min=%e, max=%e\n", argv[2], min2, max2 );
    printf( "\trmse=%e, L-infy=%e\n", rmse, linfy );

    delete[] buf1; 
    delete[] buf2; 
    delete[] linfy_arr; 
    delete[] rmse_arr;
    fclose( file1 );
    fclose( file2 );

    return 0;
}

