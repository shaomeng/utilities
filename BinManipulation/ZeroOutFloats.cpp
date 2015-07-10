/*
 * This program reads in a block of values (BOV), and a compression ratio.
 * It calculates the nth largest element,
 * and zero out all values smaller than the nth largest one.
 *
 * The values after zeroing out are written back in BOV, at their original locations. 
 *
 * Programmer: Samuel Li
 * Date: 7/9/2015
 *
 */

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

/* 
 * Opens a file to read and returns the length of the file in byte.
 */
long int OpenFileRead( FILE* &file, const char* filename )
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
 * Opens a file to write.
 */
int OpenFileWrite( FILE* &file, const char* filename )
{
    file = fopen( filename, "wb" );
    if( file == NULL ) {
        cerr << "Open file to write error: " << filename << endl;
        return 1;
    }
    return 0;
}

/*
 * Read a data chunk from the binary file.
 * Both offset and count are in the number of floats (not bytes).
 */
int ReadChunk( FILE* &file, long offset, long count, float* buf )
{
    long rt = fseek( file, sizeof(float) * offset, SEEK_SET );
    if( rt != 0 ){
        cerr << "File seek error! " << endl;
        return 1;
    }
    rt = fread( buf, sizeof(float), count, file );
    if( rt != count ) {
        cerr << "File read error! " << endl;
        return 1;
    }
    return 0;
}

int WriteChunk( FILE* file, float* buf, long size )
{
    long rt = fwrite( buf, sizeof(float), size, file );
    if( rt != size ) {
        cerr << "File write size error! " << endl;
        return 1;
    }
    return 0;
}

float FindThreshold ( int cratio, float* buf, long bufsize )
{
    if( bufsize % cratio != 0 )
        cerr << "Input file not divided by input cratio!" << endl;
    long n = bufsize / cratio - 1;
    
    vector<float> tmp( bufsize, 0.0 );
    for( long i = 0; i < bufsize; i++ )
        if( buf[i] > 0 )
            tmp[i] = buf[i] * -1.0;
        else
            tmp[i] = buf[i];

    nth_element( tmp.begin(), tmp.begin()+n, tmp.end() );
    float nth = tmp[n] * -1.0;

    return nth;
}

int main( int argc, char* argv[] )
{
    if( argc != 4 ) {
        cerr << "Please specify cratio, and input and output file names! " << endl;
        exit (1);
    }
    int cratio = atoi( argv[1] );
    FILE* input;
    FILE* output;
    long nbyte = OpenFileRead( input, argv[2] );
    OpenFileWrite( output, argv[3] );

    long size = nbyte / 4;

    float* buf = new float[ size ];
    ReadChunk( input, 0, size, buf );
    float t = FindThreshold( cratio, buf, size );
    float nt = t * -1.0;
    long count = 0;
    for( long i = 0; i < size; i++ )
        if( buf[i] < t &&  buf[i] > nt ) {
            buf[i] = 0.0;
            count++;
        }
    
    WriteChunk( output, buf, size );

    delete[] buf;
    fclose( input );
    fclose( output );

    cerr << "\tThreshold = " << t << endl;
    cerr << "\tZeroed out numbers = " << count << endl;

    return 0;
}
