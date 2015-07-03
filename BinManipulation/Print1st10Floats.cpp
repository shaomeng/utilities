#include <iostream>
#include <cstdio>

using namespace std;

int main( int argc, char* argv[] )
{
    float buf[10];
    FILE* f = fopen( argv[1], "rb" );
    fread( buf, sizeof(float), 10, f );
    fclose( f );
    for( int i = 0; i < 10; i++ )
        cerr << "\t" << buf[i] << endl;
}
