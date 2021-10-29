#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <float.h>
#include "mbed.h"
//#include "main.h"
#include "dacdata.h"

/*!
*@brief Macro for time-resolution of data file
*/
#define SAMPLING_PERIOD (0.00001)

/*!
*@brief Macro for length of data
*/
#define DATA_SIZE (501)

/*!
*@brief Macro for maximum sample shift for autocorrelation function
*/
#define MAX_SHIFT (300)

/*!
*@brief Definition for on-board LED LD2
*/
DigitalOut led1(LED1); 

/*!
*@brief Serial communication with PC
*/
Serial pc(USBTX, USBRX);
/*!
*\fn peak_lag(float * ptr, uint16_t offset)
*\brief Function to calculate index (sample no.) of peaks in data
*       This function analyses the sampled time-series of the input signal and 
*       calculates the index/locations of peaks contained. It is called
*       by the function calc_frequency()
*
*@param pointer to float data containing autocorrelation values, integer sample offset
*@return integer index of peak location
*******************************************************************************/
uint16_t peak_lag(float * ptr, uint16_t offset)
{
  double peak = 0;
  uint16_t lag = 0;
  uint16_t k;

  for(k=offset;k<MAX_SHIFT;k++)
  {
    if(*(ptr+k)>peak) //find and store peak value
    {
      peak = *(ptr+k);
      lag = k; //index corresponding to peak
    }
  }
  return lag;
}


/*!
*\fn calc_frequency(float * data)  
*\brief Function to calculate frequency of input signal
*       This function analyses sampled time-series and calculates the signal frequency
*       using time difference between sucessive peaks of the autocorrelation function.
*@param Pointer to float array containing sampled time series
*@return frequency of type float
******************************************************************************/
float calc_frequency(float * dacdata)
{
  uint16_t i;
  uint16_t shift;
  float * autocorr = (float *) malloc(sizeof(float)*MAX_SHIFT); //reserve memory of type float for autocorrelation samples
  for (shift=0;shift<MAX_SHIFT;shift++)
  {
    *(autocorr+shift) = 0;
    for(i=0;i<DATA_SIZE-shift;i++)
    {
      *(autocorr+shift) += (*(dacdata+i)) * (*(dacdata+i+shift)); //compute autocorrelation
    }
    *(autocorr+shift) /= (DATA_SIZE-shift);
  }

  float f = 0;
  uint16_t lag_1 = peak_lag(autocorr,0); //calculate indices corresponding to successive peaks
  uint16_t lag_2 = peak_lag(autocorr,lag_1+2);
  f = 1/(SAMPLING_PERIOD*(lag_2-lag_1)); //calculate frequency

  free(autocorr); //free allocated memory
  return f;
}



/*!
*@brief Main function to calculate frequency and blink LED using the obtained frequency
*/
int main() 
{
    float freq;
    freq = calc_frequency(dacdata);
    pc.printf("Frequency is: %f\n",freq);
    
    while(1)
    {
        freq = calc_frequency(dacdata);
        led1=!led1;
        wait(1000/freq);
        led1=!led1;
        wait(1000/freq);
        
        pc.printf("Frequency is: %f\n",freq);
    }
    return 0;
}