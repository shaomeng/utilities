/* This file takes user's input filename and decimal numbers,
 * and writes the numbers in binary to the file.
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main( int argc, char* argv[] )
{
    cout << "Usage: first, input the name of the binary file you wanna create: " << endl;
    string filename;
    cin >> filename;

    FILE* wFile = fopen( filename.c_str(), "wb" );
    if( wFile == NULL ) {
        cout << "Cannot open file to write." << endl;
        exit(1);
    }
    cout << "Second, input the numbers you want to fill into the binary file: " << endl;
    cout << "REMEMBER, 1949 is the magic number that terminates the input. " << endl;
    double num;
    cin >> num;
    while( num != 1949.0 ) {
        fwrite( &num, sizeof(double), 1, wFile );
        cin >> num;
    }
    fclose( wFile );

    return 0;
}
