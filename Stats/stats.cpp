#ifndef STATS
#include "stats.h"
#include <iostream>
#endif

void 
Stats::GetMinMax( const float *array, float *results, long int n)
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

double
Stats::GetRMSE( const float *obs, const float *truth, long int n)
{
    double sum = GetRMSE2( obs, truth, n); 
    return sqrt(sum);
}

double
Stats::GetRMSE2( const float *obs, const float *truth, long int n)
{
    double sum = 0.0;
    double c = 0.0;
    double diff;
    for( long int i = 0; i < n; i++) {
        diff = (obs[i] - truth[i]) ;
        double y = diff * diff - c;
        double t = sum + y;
        c = t - sum - y;
        sum = t;
    }
    sum /= 1.0*n;
    
    return  sum;
}


float 
Stats::GetLInfNorm( const float *arr1, const float *arr2, long int n)
{
    double diff = 0;
    double tmp;
    for( long int i = 0; i < n; i++) {
        tmp = arr1[i] - arr2[i];
        if( tmp < 0 )       tmp *= -1.0;
        if( tmp > diff)     diff = tmp; 
    }
    
    return diff;
}

double
Stats::GetQuadraticMean( const double* arr, long n )
{
    double sum = 0.0;
    double c = 0.0;
    for( long int i = 0; i < n; i++) {
        double y = arr[i] * arr[i] - c;
        double t = sum + y;
        c = t - sum - y;
        sum = t;
    }
    sum /= 1.0*n;
    return sqrt( sum );
}


double
Stats::GetMean( const double *array, long int n ) 
{
    double sum = 0;
    double c = 0;
    for( long i = 0; i < n; i++ ) {
        double y = array[i] - c;
        double t = sum + y;
        c = t - sum -y;
        sum = t;
    }
    return (sum / (double)n );
}

/*
float
Stats::GetPositiveMean( const float *array, int n)
{
    float *array2 = new float[n];
    ToPositive( array, array2, n);
    float mean = GetMean( array2, n );
    delete[] array2;
    return mean;
}

float
Stats::GetNegativeMean( const float *array, int n)
{
    float *array2 = new float[n];
    ToNegative( array, array2, n);
    float mean = GetMean( array2, n );
    delete[] array2;
    return mean;
}

float
Stats::GetMean( const int *array, int n ) 
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
Stats::GetPositiveMean( const int *array, int n )
{
    int *array2 = new int[n];
    ToPositive( array, array2, n );
    float mean = GetMean( array2, n );
    delete[] array2;
    return mean;
}

float
Stats::GetNegativeMean( const int *array, int n )
{
    int *array2 = new int[n];
    ToNegative( array, array2, n );
    float mean = GetMean( array2, n );
    delete[] array2;
    return mean;
}


float 
Stats::GetSD( const float *array, int n )
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
Stats::GetPositiveSD( const float *array, int n )
{
    float *array2 = new float[n];
    ToPositive( array, array2, n );
    float sd = GetSD( array2, n);
    delete[] array2;
    return sd;
}

float
Stats::GetNegativeSD( const float *array, int n )
{
    float *array2 = new float[n];
    ToNegative( array, array2, n );
    float sd = GetSD( array2, n);
    delete[] array2;
    return sd;
}

float 
Stats::GetSD( const int *array, int n )
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
Stats::GetPositiveSD( const int *array, int n)
{
    int *array2 = new int[n];
    ToPositive( array, array2, n );
    float sd = GetSD( array2, n );
    delete[] array2;
    return sd;
}

float
Stats::GetNegativeSD( const int *array, int n)
{
    int *array2 = new int[n];
    ToNegative( array, array2, n );
    float sd = GetSD( array2, n );
    delete[] array2;
    return sd;
}

void
Stats::ToPositive( const float *array, float *array2, int n)
{
    for( int i = 0; i < n; i++ )
        if( array[i] > 0 )      array2[i] = array[i];
        else                    array2[i] = 0.0;
}

void
Stats::ToNegative( const float *array, float *array2, int n)
{
    for( int i = 0; i < n; i++ )
        if( array[i] < 0 )      array2[i] = array[i];
        else                    array2[i] = 0.0;
}

void
Stats::ToPositive( const int *array, int *array2, int n )
{
    for( int i = 0; i < n; i++)
        if( array[i] > 0 )      array2[i] = array[i];
        else                    array2[i] = 0;
}

void
Stats::ToNegative( const int *array, int *array2, int n )
{
    for( int i = 0; i < n; i++)
        if( array[i] < 0 )      array2[i] = array[i];
        else                    array2[i] = 0;
}

int
Stats::GetPositiveCount( const float *array, int n)
{
    int count = 0;
    for( int i = 0; i < n; i++ )
        if( array[i] > 0 )      count++;
    return count;
}

int
Stats::GetNegativeCount( const float *array, int n)
{
    int count = 0;
    for( int i = 0; i < n; i++ )
        if( array[i] < 0 )      count++;
    return count;
}

int
Stats::GetPositiveCount( const int *array, int n)
{
    int count = 0;
    for( int i = 0; i < n; i++ )
        if( array[i] > 0 )      count++;
    return count;
}

int
Stats::GetNegativeCount( const int *array, int n)
{
    int count = 0;
    for( int i = 0; i < n; i++ )
        if( array[i] < 0 )      count++;
    return count;
}

void
Stats::GetBell( const int *array, int n, int *count, float *bell )
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
Stats::GetIntDistribution( const int *array, int n, int lbound, 
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
*/









