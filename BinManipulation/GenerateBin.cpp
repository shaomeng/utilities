/* 
 * This program generates binary file with specific values on each grid point.
 * For example, the grid at (xxx, yyy, zzz) will have xxx+yyy+zzz value.
 *
 * Programmer: Samuel Li
 * Date: 12/5/2015
 *
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

float Value( int x, int y, int z )
{
//	float f = x * 1000000.0 + y * 1000.0 + z * 1.0;
	float f = x * 1.0 + y * 1.0 + z * 1.0;
	return f;
}

int main(int argc, char* argv[])
{
    if( argc != 5 ) {
        cerr << "Please input XDim, YDim, ZDim, and the Filename." << endl;
        exit (1);
    }

    int xDim = atoi( argv[1] );
    int yDim = atoi( argv[2] );
    int zDim = atoi( argv[3] );

	size_t totallen = xDim * yDim * zDim;
	float* buf = new float[ totallen ];
	size_t counter = 0;
	for( int k = 0; k < zDim; k++ )
		for( int j = 0; j < yDim; j++ )
			for( int i = 0; i < xDim; i++ )
				buf[counter++] = Value( i, j, k );

	FILE* f = fopen( argv[4], "wb" );
	fwrite( buf, sizeof(float), totallen, f );
	fclose( f );

	delete[] buf;
}
