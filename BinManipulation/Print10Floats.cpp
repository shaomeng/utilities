#include <iostream>
#include <stdlib.h>

using namespace std;

int main( int argc, char* argv[] )
{
    string name = argv[1];
    float buf[10];
    FILE* f = fopen( name.c_str(), "rb" );
    fseek( f, 256*256 - 5, SEEK_SET );
    fread( buf, sizeof(float), 10, f );
    fclose( f );
    for( int i = 0; i < 10; i++ )
        cerr << "\t" << buf[i] << endl;
}
