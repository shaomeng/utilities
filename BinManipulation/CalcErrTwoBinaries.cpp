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
 */


#include "stats.h"
#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

/* 
 * Opens a file and returns the length of the file in byte.
 */
long int OpenFile( FILE* &file, char* filename )
{
    file = fopen( filename, "rb" );
    if( file == NULL ) {
        cerr << "File open error: " << filename << endl;
        exit(1);
    }
    fseek( file, 0, SEEK_END );
    long size = ftell( file );

    return size;
}

/*
 * Read a data plane from the binary file.
 * Both offset and count are in the number of floats (not bytes).
 */
void ReadPlane( FILE* &file, long offset, long count, float* buf )
{
    long rt = fseek( file, sizeof(float) * offset, SEEK_SET );
    if( rt != 0 ){
        cerr << "File seek error! " << endl;
        exit(1);
    }
    rt = fread( buf, sizeof(float), count, file ); 
    if( rt != count ) {
        cerr << "File read error! " << endl;
        exit(1);
    }
}

int main( int argc, char* argv[] )
{
    if( argc != 4 ) {
        cerr << "Please input Z dimension and two files." << endl;
        exit(1);
    }

    FILE* file1 = NULL;
    FILE* file2 = NULL;
    long size1 = OpenFile( file1, argv[2] );
    long size2 = OpenFile( file2, argv[3] );
    if( size1 != size2 ) {
        cerr << "Input file sizes don't align..." << endl;
        exit(1);
    }
    int z = atoi( argv[1] );
    if( size1 % z != 0 ) {
        cerr << "Z dimension error!" << endl;
        exit(1);
    }
    long planeSize = size1 / z / 4;
    float min1, max1, min2, max2;
    double* rmse_arr   = new double[ z ];   
    float*  linfy_arr = new float[ z ];
    float*  buf1      = new float[ planeSize ];
    float*  buf2      = new float[ planeSize ];
    float minmax1[2], minmax2[2];


    for( int i = 0; i < z; i++ ) {
        ReadPlane( file1, i * planeSize, planeSize, buf1 );
        ReadPlane( file2, i * planeSize, planeSize, buf2 );
        Stats::GetMinMax( buf1, minmax1, planeSize );
        Stats::GetMinMax( buf2, minmax2, planeSize );
        if( i == 0 ) {
            min1 = minmax1[0];      max1 = minmax1[1];
            min2 = minmax2[0];      max2 = minmax2[2];
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

    printf( "\t%s: min=%f, max=%f\n", argv[2], min1, max1 );
    printf( "\t%s: min=%f, max=%f\n", argv[3], min2, max2 );
    printf( "\trmse=%e, L-infy=%e\n", rmse, linfy );

    delete[] buf1; 
    delete[] buf2; 
    delete[] linfy_arr; 
    delete[] rmse_arr;
    fclose( file1 );
    fclose( file2 );

    return 0;
}

