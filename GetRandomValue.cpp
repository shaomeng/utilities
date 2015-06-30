#include <iostream>
#include <fstream>

#define WIDTH 512
#define HEIGHT 256

using namespace std;

int main() {
    while(true) {
        cout << "please input X and Y: " << endl;
        int x, y, idx;
        cin >> x;
        cin >> y;
        idx = y*WIDTH + x;
        float result[2];

        FILE* file = fopen( "../outputbin/dg0.vec.bin", "rb" );
        int offset = idx * sizeof( float );
        fseek( file, offset, SEEK_SET );
        fread( (void*) result, sizeof(float), 2, file);
        fclose (file);

        cout << "velocity read: " << result[0] << "\t" << result[1] << endl; 
    }
}
