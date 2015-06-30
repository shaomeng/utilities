#ifndef SAMS_MATH
#define SAMS_MATH

#include <cmath>

class Sams_math
{
  public:
    static float GetMean( const float *array, int n);
    static float GetMean( const int   *array, int n);

    static float GetPositiveMean( const float *array, int n);
    static float GetPositiveMean( const int   *array, int n);

    static float GetNegativeMean( const float *array, int n);
    static float GetNegativeMean( const int   *array, int n);

    static float GetSD(   const float *array, int n);
    static float GetSD(   const int   *array, int n);

    static float GetPositiveSD(   const float *array, int n);
    static float GetPositiveSD(   const int   *array, int n);

    static float GetNegativeSD(   const float *array, int n);
    static float GetNegativeSD(   const int   *array, int n);

    static int GetPositiveCount(   const float *array, int n);
    static int GetPositiveCount(   const int   *array, int n);

    static int GetNegativeCount(   const float *array, int n);
    static int GetNegativeCount(   const int   *array, int n);

    /*
     * Input: float array:
              2-element array: min = results[0], max = results[1]
              float array length.
       Output: void
     */
    static void GetMinMax( const float *array, float *results, long int n);

    /*
     * Calculate the Root Mean Square value between an observed array
     * and the theoratical true values.
     * Input: observed array, truth array, and the data number n.
     * Output: RMS
     */
    static float GetRMS( const float *obs, const float *truth, long int n); 

    /*
     * Calculate the square of Root Mean Square value between 
     * an observed array and the theoratical true values.
     * Input: observed array, truth array, and the data number n.
     * Output: RMS
     */
    static float GetRMS2( const float *obs, const float *truth, long int n); 

    /* 
     * Calculate the max difference between two arrays.
     * This is also call the L-Infinity Norm.
     */
    static float GetLInfNorm( const float *arr1, const float *arr2, long int n); 
    
    /*
    Input: data array: array
           length of data array: n
    Output: bell distribution: absolute count of size 16
            bell distribution: bell of size 16.
            It measures the distribution of (u-7SD, u+7SD),
            which has a probability more than 0.999999999.
    http://en.wikipedia.org/wiki/Tolerance_interval
    */
    static void GetBell( const int   *array, int n, int *count, float *bell);
    static void GetBell( const float *array, int n, int *count, float *bell ) {}

    /*
    GetIntDistribution examines range [lbound, hbound)
    The size of count and distribution should be:
    (hbound - lbound + 2)
    */
    static void GetIntDistribution( const int *array, int n, int lbound, 
                            int hbound, int *count, float *distribution);

  protected:
    static void  ToPositive( const float *array, float *array2, int n);
    static void  ToNegative( const float *array, float *array2, int n);
    static void  ToPositive( const int *array, int *array2, int n);
    static void  ToNegative( const int *array, int *array2, int n);
};


#endif
