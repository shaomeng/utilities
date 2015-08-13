/*
 * This program extends CropCube.cpp to support input and output files of any size.
 * In addition, it requires users to specify the start and finish indices to
 * crop from the input file.
 * 
 * Programmer: Samuel Li
 * Date: 7/17/2015
 *
 * Modified: add support for double precision numbers.
 * Date: 8/6/2015
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>

#define FLOAT double

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
void ReadChunk( FILE* file, long offset, long count, FLOAT* buf )
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

/*
 * Writes a data chunk into the end of a binary file.
 */
void WriteChunk( FILE* file, long count, FLOAT* buf )
{
    long rt = fseek( file, 0, SEEK_END );
    if( rt != 0 ){
        cerr << "File seek error! " << endl;
        exit(1);
    }
    rt = fwrite( buf, sizeof(FLOAT), count, file );
    if( rt != count ) {
        cerr << "File write error! " << endl;
        exit(1);
    }
}

int main(int argc, char* argv[]) {

    if( argc != 12 ){
        cerr << "Usage: InFileName, InFileNX, InFileNY, InFileNZ, "
             << "OutFileName, OutStartX, OutFinishY, "
             << "OutStartY, OutFinishY, OutStartZ, OutFinishZ. " << endl
             << "For example, if you want to crop from index 64 "
             << "to index 127 in X dimension, just type 64 and 127!" << endl;
        exit (1);
    }

    /*
     * It is the user's responsibility to make sure the range to crop 
     * is within the range of input file.
     */
    int inNX  = atoi( argv[2] );
    int inNY  = atoi( argv[3] );
    int inNZ  = atoi( argv[4] );
    int outStartX  = atoi( argv[6] );
    int outFinishX = atoi( argv[7] );
    int outStartY  = atoi( argv[8] );
    int outFinishY = atoi( argv[9] );
    int outStartZ  = atoi( argv[10] );
    int outFinishZ = atoi( argv[11] );

    FILE* infile = NULL;
    OpenFileRead( infile, argv[1] );
    FILE* outfile = NULL;
    outfile = fopen( argv[5], "wb" );  
    if( outfile == NULL ) {
        cerr << "output file open error: " << argv[5] << endl;
        exit (1);
    }


    int outNX = outFinishX - outStartX + 1;
    FLOAT* buf = new FLOAT[ outNX ];

    for( int z = outStartZ; z <= outFinishZ; z++ )
        for( int y = outStartY; y <= outFinishY; y++ ) {
            long offset = z*inNX*inNY + y*inNX;
            ReadChunk( infile, offset, outNX, buf );
            WriteChunk( outfile, outNX, buf );
        }

    delete[] buf;
    fclose( infile );
    fclose( outfile );

    return 0;
}
