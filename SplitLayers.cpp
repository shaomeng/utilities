//* This program reads in a data cube of size n^3
//* splits the cube into m slices
//* and writes these n slices into m files.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

#define N 256
#define M 256

using std::string;
using std::cerr;
using std::endl;
using std::stringstream;


void WriteSlice( const float* plane, string filename )
{
    FILE* wfile = fopen( filename.c_str(), "wb" ); 
    fwrite( plane, sizeof(float), N*N, wfile );
    fclose( wfile );
}

int main(int argc, char* argv[]) {

    string srcFile = argv[1];
    string dstPath = argv[2];

    FILE* rfile  = fopen( srcFile.c_str(), "rb" );
    float* buf = new float[ N * N ];

    for( int i = 0; i < M; i++ ) {
        fseek( rfile, i * sizeof(float) * N * N, SEEK_SET );
        fread( buf, sizeof(float), N*N, rfile );
        string dstFile = dstPath + std::to_string(i) + ".float";
        WriteSlice( buf, dstFile );
    }
    
    fclose( rfile );
    delete[] buf;
    return 0;
}
