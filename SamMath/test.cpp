#include <iostream>
#include <cstring>
#include "sams_math.h"

using std::cout;
using std::endl;

int main(){
    float arr[3] = {0, 1, 2};
    float arr2[2] = {-1, -1};
    Sams_math::GetMinMax( arr, arr2, 3 );
    cout << arr2[0] << "   " << arr2[1] << endl;
    float truth[3] = {1, -2, 3};
    float rms = Sams_math::GetRMS( arr, truth, 3);
    cout << "rms=" << rms << endl;

    float a, b;
    a = b = 1;
    cout << "a=" << a << ", b=" << b << endl;
}
