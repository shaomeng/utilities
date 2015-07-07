/*
 * This program reads a cubic file of size inDim^3,
 * crops the lower corner of size outDim^3,
 * and writes the lower corner into a file.
 * 
 * Programmer: Samuel Li
 * Date: 7/7/2015
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>

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
void ReadChunk( FILE* file, long offset, long count, float* buf )
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

/*
 * Writes a data chunk into the end of a binary file.
 */
void WriteChunk( FILE* file, long count, float* buf )
{
    long rt = fseek( file, 0, SEEK_END );
    if( rt != 0 ){
        cerr << "File seek error! " << endl;
        exit(1);
    }
    rt = fwrite( buf, sizeof(float), count, file );
    if( rt != count ) {
        cerr << "File write error! " << endl;
        exit(1);
    }
}

int main(int argc, char* argv[]) {

    if( argc != 5 ){
        cerr << "Usage: InFileName, InFileDimension, OutFileName, OutFileDimension" << endl;
        exit (1);
    }

    int inDim  = atoi( argv[2] );
    int outDim = atoi( argv[4] );
    if( outDim > inDim ) {
        cerr << "InFileDimension may not smaller than OutFileDimension" << endl;
        exit (1);
    }

    FILE* infile = NULL;
    OpenFileRead( infile, argv[1] );
    FILE* outfile = NULL;
    outfile = fopen( argv[3], "wb" );  
    if( outfile == NULL ) {
        cerr << "output file open error: " << argv[3] << endl;
        exit (1);
    }

    float* buf = new float[ outDim ];

    for( long z = 0; z < outDim; z++ )
        for( long y = 0; y < outDim; y++ ) {
            long offset = z * inDim * inDim + y * inDim;
            ReadChunk( infile, offset, outDim, buf );
for( int i = 0; i < outDim; i++ )
    cerr << "\t" << buf[i] << endl;
            WriteChunk( outfile, outDim, buf );
        }

    delete[] buf;
    fclose( infile );
    fclose( outfile );

    return 0;
}
