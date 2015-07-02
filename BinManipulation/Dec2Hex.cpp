/* This file takes user's input filename and decimal numbers,
 * and writes the numbers in hexadecimal ascii in the file.
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main( int argc, char* argv[] )
{
    cout << "Usage: first, input the name of the hexadecimal ascii file you wanna create: " << endl;
    string filename;
    getline( cin, filename );

    FILE* wFile = fopen( filename.c_str(), "w" );
    if( wFile == NULL ) {
        cout << "Cannot open file to write." << endl;
        exit(1);
    }
    cout << "Second, input the float numbers you want to fill into the file: " << endl;
    cout << "REMEMBER, 1949 is the magic number that terminates the input. " << endl;
    float num;
    cin >> num;
    while( num != 1949.0 ) {
        fprintf( wFile, "%a\n", num );
        cin >> num;
    }
    fclose( wFile );
}
