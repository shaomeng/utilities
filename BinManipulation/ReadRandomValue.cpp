/* 
 * This program takes user's input of the x, y, and z indices of a point,
 * and returns the value of that point.
 *
 * Programmer: Samuel Li
 * Date: 7/7/2015
 *
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

int main(int argc, char* argv[])
{
    if( argc != 5 ) {
        cerr << "Please input the Filename, XDim, YDim, ZDim." << endl;
        exit (1);
    }

    FILE* readFile = NULL;
    OpenFileRead( readFile, argv[1] );
    int xDim = atoi( argv[2] );
    int yDim = atoi( argv[3] );
    int zDim = atoi( argv[4] );
    
    int x, y, z;
    float val;
    while(true) {
        cout << "Please input the x, y, and z indices that you want to read: " << endl;
        cout << "Remember, z=1949 is the secrete to exit!" << endl;
        cin >> x;
        cin >> y;
        cin >> z;
        if( z == 1949 )     
            break;

        long offset = z * xDim * yDim + y * xDim + x;
        fseek( readFile, sizeof(float) * offset, SEEK_SET );
        fread( &val, sizeof(float), 1, readFile );

        printf( "vol(%d, %d, %d) = %f\n", x, y, z, val );
    }
    
    fclose( readFile );
}
