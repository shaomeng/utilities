#ifndef SAMS_MATH
#include "SamMath.h"
#include <iostream>
#endif

void 
Sams_math::GetMinMax( const float *array, float *results, long int n)
{
    float max = array[0];
    float min = array[0];
    for( long int i = 1; i < n; i++) {
        if( array[i] > max)     max = array[i];
        if( array[i] < min)     min = array[i];
    }
    results[0] = min;
    results[1] = max;
}

float 
Sams_math::GetRMS( const float *obs, const float *truth, long int n)
{
    float sum = GetRMS2( obs, truth, n); 
    return sqrt(sum);
}

float 
Sams_math::GetRMS2( const float *obs, const float *truth, long int n)
{
    float sum = 0.0;
    float c = 0.0;
    float diff;
    for( long int i = 0; i < n; i++) {
        diff = (obs[i] - truth[i]) ;
        float y = diff * diff - c;
        float t = sum + y;
        c = t - sum - y;
        sum = t;
    }
    sum /= 1.0*n;
    
    return sum;
}


float 
Sams_math::GetLInfNorm( const float *arr1, const float *arr2, long int n)
{
    float diff = 0;
    float tmp;
    for( long int i = 0; i < n; i++) {
        tmp = arr1[i] - arr2[i];
        if( tmp < 0 )       tmp *= -1.0;
        if( tmp > diff)     diff = tmp; 
    }
    
    return diff;
}

float
Sams_math::GetMean( const float *array, int n ) 
{
    float sum = 0;
    float c = 0;
    int nonzero = 0;
    for( int i = 0; i < n; i++ )
        if( array[i] != 0.0 ) {
            float y = array[i] - c;
            float t = sum + y;
            c = t - sum -y;
            sum = t;
            nonzero++;
        }
    return (sum / (float) nonzero );
}

float
Sams_math::GetPositiveMean( const float *array, int n)
{
    float *array2 = new float[n];
    ToPositive( array, array2, n);
    float mean = GetMean( array2, n );
    delete[] array2;
    return mean;
}

float
Sams_math::GetNegativeMean( const float *array, int n)
{
    float *array2 = new float[n];
    ToNegative( array, array2, n);
    float mean = GetMean( array2, n );
    delete[] array2;
    return mean;
}

float
Sams_math::GetMean( const int *array, int n ) 
{
    int sum = 0;
    int nonzero = 0;
    for( int i = 0; i < n; i++ )
        if ( array[i] != 0 ) {
            sum += array[i];
            nonzero++;
        }
    return ( (float) sum / (float) nonzero );
}

float
Sams_math::GetPositiveMean( const int *array, int n )
{
    int *array2 = new int[n];
    ToPositive( array, array2, n );
    float mean = GetMean( array2, n );
    delete[] array2;
    return mean;
}

float
Sams_math::GetNegativeMean( const int *array, int n )
{
    int *array2 = new int[n];
    ToNegative( array, array2, n );
    float mean = GetMean( array2, n );
    delete[] array2;
    return mean;
}


float 
Sams_math::GetSD( const float *array, int n )
{
    float mean = GetMean( array, n );
    float sum = 0.0;
    float c = 0.0;
    int nonzero = 0;
    for( int i = 0; i < n; i++ ) {
        if( array[i] != 0.0 ){
            float diff = mean - array[i];
            float y = diff * diff - c;
            float t = sum + y;
            c = t - sum - y;
            sum = t;
            nonzero++;
        }
    }
    return sqrt( sum / (float)nonzero );
}

float
Sams_math::GetPositiveSD( const float *array, int n )
{
    float *array2 = new float[n];
    ToPositive( array, array2, n );
    float sd = GetSD( array2, n);
    delete[] array2;
    return sd;
}

float
Sams_math::GetNegativeSD( const float *array, int n )
{
    float *array2 = new float[n];
    ToNegative( array, array2, n );
    float sd = GetSD( array2, n);
    delete[] array2;
    return sd;
}

float 
Sams_math::GetSD( const int *array, int n )
{
    float mean = GetMean( array, n );
    float sum = 0.0;
    float c = 0.0;
    int nonzero = 0;
    for( int i = 0; i < n; i++ ) {
        if( array[i] != 0 ) {
            float diff = mean - array[i];
            float y = diff * diff - c;
            float t = sum + y;
            c = t - sum - y;
            sum = t;
            nonzero++;
        }
    }
    return sqrt( sum / (float)nonzero );
}

float
Sams_math::GetPositiveSD( const int *array, int n)
{
    int *array2 = new int[n];
    ToPositive( array, array2, n );
    float sd = GetSD( array2, n );
    delete[] array2;
    return sd;
}

float
Sams_math::GetNegativeSD( const int *array, int n)
{
    int *array2 = new int[n];
    ToNegative( array, array2, n );
    float sd = GetSD( array2, n );
    delete[] array2;
    return sd;
}

void
Sams_math::ToPositive( const float *array, float *array2, int n)
{
    for( int i = 0; i < n; i++ )
        if( array[i] > 0 )      array2[i] = array[i];
        else                    array2[i] = 0.0;
}

void
Sams_math::ToNegative( const float *array, float *array2, int n)
{
    for( int i = 0; i < n; i++ )
        if( array[i] < 0 )      array2[i] = array[i];
        else                    array2[i] = 0.0;
}

void
Sams_math::ToPositive( const int *array, int *array2, int n )
{
    for( int i = 0; i < n; i++)
        if( array[i] > 0 )      array2[i] = array[i];
        else                    array2[i] = 0;
}

void
Sams_math::ToNegative( const int *array, int *array2, int n )
{
    for( int i = 0; i < n; i++)
        if( array[i] < 0 )      array2[i] = array[i];
        else                    array2[i] = 0;
}

int
Sams_math::GetPositiveCount( const float *array, int n)
{
    int count = 0;
    for( int i = 0; i < n; i++ )
        if( array[i] > 0 )      count++;
    return count;
}

int
Sams_math::GetNegativeCount( const float *array, int n)
{
    int count = 0;
    for( int i = 0; i < n; i++ )
        if( array[i] < 0 )      count++;
    return count;
}

int
Sams_math::GetPositiveCount( const int *array, int n)
{
    int count = 0;
    for( int i = 0; i < n; i++ )
        if( array[i] > 0 )      count++;
    return count;
}

int
Sams_math::GetNegativeCount( const int *array, int n)
{
    int count = 0;
    for( int i = 0; i < n; i++ )
        if( array[i] < 0 )      count++;
    return count;
}

void
Sams_math::GetBell( const int *array, int n, int *count, float *bell )
{
    float mean = GetMean( array, n );
    float SD = GetSD( array, n );
    std::cerr << "mean=" << mean << "\t SD=" << SD << std::endl;

    float SDs[15];
    for( int i = 0; i < 15; i++ ) {
        SDs[i] = mean + (i-7) * SD;
        std::cerr << SDs[i] << std::endl;
    }
    for( int i = 0; i < 16; i++ )
        count[i] = 0;

    for( int i = 0; i < n; i++ )
    {
        int t = array[i];
        if     ( t < SDs[0] )                  count[0]++;
        else if( SDs[0] <= t && t < SDs[1] )   count[1]++;
        else if( SDs[1] <= t && t < SDs[2] )   count[2]++;
        else if( SDs[2] <= t && t < SDs[3] )   count[3]++;
        else if( SDs[3] <= t && t < SDs[4] )   count[4]++;
        else if( SDs[4] <= t && t < SDs[5] )   count[5]++;
        else if( SDs[5] <= t && t < SDs[6] )   count[6]++;
        else if( SDs[6] <= t && t < SDs[7] )   count[7]++;
        else if( SDs[7] <= t && t < SDs[8] )   count[8]++;
        else if( SDs[8] <= t && t < SDs[9] )   count[9]++;
        else if( SDs[9] <= t && t < SDs[10] )  count[10]++;
        else if( SDs[10] <= t && t < SDs[11] ) count[11]++;
        else if( SDs[11] <= t && t < SDs[12] ) count[12]++;
        else if( SDs[12] <= t && t < SDs[13] ) count[13]++;
        else if( SDs[13] <= t && t <= SDs[14] ) count[14]++;
        else                                   count[15]++;
    }

    for( int i = 0; i < 16; i++)
        bell[i] = (float)count[i] / (float)n;
}

void
Sams_math::GetIntDistribution( const int *array, int n, int lbound, 
                        int hbound, int *count, float *distribution)
{
    int range = hbound - lbound;
    for( int i = 0; i < range+2; i++)
        count[i] = 0;

    int j;
    for( int i = 0; i < n; i++ )
    {
        int val = array[i];
        if( val < lbound )      count[0]++;
        else if( val >= hbound ) count[range+1]++;
        else {
            for( j = 0; j < range; j++ )
                if( val == lbound + j ) break;
            count[j+1]++; 
        }
    }

    for( int i = 0; i < range+2; i++ )
        distribution[i] = (float)count[i] / (float)n;
}










