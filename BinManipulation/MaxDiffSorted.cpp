/*
 * This program reads two binary files, sorts all numbers, 
 * and finds the max difference between the two arrays.
 *
 * The outputs are:
 *   1) the max difference: max_diff
 *   2) the total number of differences that are > (max_diff / 10)
 *
 * Programmer: Samuel Li
 * Date: 7/8/2015
 */


#include "stats.h"
#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

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
 * Both offset and count are in the number of floats (not bytes).
 */
void ReadChunk( FILE* &file, long offset, long count, float* buf )
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
    if( argc != 3 ) {
        cerr << "Please provide two file names as arguments." << endl;
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
    long planeSize = size1 / 4;
    float*  buf1      = new float[ planeSize ];
    float*  buf2      = new float[ planeSize ];

    ReadChunk( file1, 0, planeSize, buf1 );
    ReadChunk( file2, 0, planeSize, buf2 );
    fclose( file1 );
    fclose( file2 );

    vector<float> vec1( buf1, buf1 + planeSize );
    vector<float> vec2( buf2, buf2 + planeSize );
    sort( vec1.begin(), vec1.end() );
    sort( vec2.begin(), vec2.end() );

    float max_diff = 0.0;
    for( long i = 0; i < planeSize; i++ )
        if( fabs( vec1[i] - vec2[i] ) > max_diff )
            max_diff = fabs( vec1[i] - vec2[i] );

    float threshold = max_diff / 10.0;
    int count = 0;
    for( long i = 0; i < planeSize; i++ )
        if( fabs( vec1[i] - vec2[i] ) > threshold )
            count++;
    

    printf( "\t%s: min=%f, max=%f\n", argv[1], vec1.front(), vec1.back() );
    printf( "\t%s: min=%f, max=%f\n", argv[2], vec2.front(), vec2.back() );
    printf( "\tmax_diff=%e, %d elements have differences greater than (max_diff / 10)\n", max_diff, count);

    delete[] buf1; 
    delete[] buf2; 


    return 0;
}

