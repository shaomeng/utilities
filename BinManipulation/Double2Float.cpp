/*
 * Reads in a binary file of doubles,
 * writes them back to floats.
 *
 * Programmer: Samuel Li
 * Date: 8/7/2015
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>

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
 * Read a chunk of doubles from the binary file.
 * Both offset and count are in the number of values (not bytes).
 */
void ReadDoubleChunk( FILE* &file, long offset, long count, double* buf )
{
    long rt = fseek( file, sizeof(double) * offset, SEEK_SET );
    if( rt != 0 ){
        cerr << "File seek error! " << endl;
        exit(1);
    }
    rt = fread( buf, sizeof(double), count, file );
    if( rt != count ) {
        cerr << "File read error! " << endl;
        exit(1);
    }
}

/*
 * Writes a float data chunk into the end of a binary file.
 */
void WriteFloatChunk( FILE* file, long count, float* buf )
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


int main( int argc, char* argv[] )
{
    if( argc != 4 ) {
        cerr << "\tUsage: Input_Double_Filename, Output_Float_Filename, Z_dimension " << endl;
        exit(1);
    }

    FILE* filed = NULL;     // double file
    long sized  = OpenFileRead( filed, argv[1] );
    int z = atoi( argv[3] );
    assert( sized % z == 0 );

    long planeSize = sized / z / sizeof(double);
    double* bufd = new double[ planeSize ];
    float*  buff = new float[ planeSize ];

    FILE* filef = fopen( argv[2], "wb" );
    assert ( filef != NULL );

    for( int i = 0; i < z; i++ )
    {
        ReadDoubleChunk( filed, i*planeSize, planeSize, bufd );
        for( long j = 0; j < planeSize; j++ )
            buff[j] = (float) bufd[j];

        WriteFloatChunk( filef, planeSize, buff );
    }

    fclose( filef );
    fclose( filed );
    delete[] bufd;
    delete[] buff;
    
}







