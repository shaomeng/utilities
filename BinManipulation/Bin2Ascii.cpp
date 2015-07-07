/* This program reads sequence of float numbers from a binary file,
 * and then outputs the numbers to an ascii file, 
 * with one number per line.
 *
 * Date: 6/30/2015
 * Programmer: Samuel Li
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main( int argc, char* argv[] )
{
    if( argc != 3 ) {
        cerr << "Please specify input and output file names." << endl;
        exit(1);
    }

    char* binName   = argv[1];
    char* asciiName = argv[2];

    FILE* readFile = fopen( binName, "rb" );
    if( readFile  == NULL ) {
        cerr << "Read file open error!" << endl;
        exit(1);
    }

    fseek( readFile, 0, SEEK_END );
    long size = ftell( readFile );
    if( size % 4 == 0 ) {
        size /= 4;
        cout << "Input file number of floats: " << size << endl;
    }
    else{
        cerr << "Input file broken!" << endl;
        exit(1);
    }

    float* buf = new float[ size ];
    fseek( readFile, 0, SEEK_SET );
    size_t result = fread( buf, sizeof(float), size, readFile );
    fclose( readFile );
    if( result != size ) {
        cerr << "Input file read error!" << endl;
        exit(1);
    }

    FILE* writeFile = fopen( asciiName, "w" );
    if( writeFile == NULL ) {
        cerr << "Write file open error!" << endl;
        exit(1);
    }
    // %e prints the numbers in decimal scientific notation.
    for( long i = 0; i < size; i++ )
        fprintf( writeFile, "%e\n", buf[i] );
    fclose( writeFile );

    delete[] buf;
}
