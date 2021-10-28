/*----------------------------------------------------------------------------
LAB EXERCISE 9 - Analog input and PWM
 ----------------------------------------
	Use two potentiometers to adjust the volume and pitch of the output sound wave.
	
	Inputs: Virtual potentiometers 1 and 2
	Output: Virtual speaker,  Real PC

	GOOD LUCK!
 *----------------------------------------------------------------------------*/
 
 /*************************************************************************
*
* File name : main.cpp
* Description : Contains main function to read Potentiometer values and control the periods and volume of the speaker
* Author: Taher Ujjainwala and Steve Christensen
* Tools : mbed, Keil
*
**************************************************************************/

#include "mbed.h"
#include "pindef.h"


//Define the PWM speaker output
//D6 --> PB_10
PwmOut speaker(D6);

//Define analog inputs
//A0 --> PA_0
//A1 --> PA_1
AnalogIn POT1(A0); 
AnalogIn POT2(A1); 

//Define serial output
//Defined on BAUD Rate 9600, 8N1 settings
Serial pc(USBTX, USBRX);

	//Write your code here


//Define variables to read pot values and period value
float i;
double pot1_val, pot2_val, period_val;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	
	//Print statement at start	
	pc.printf("Code execution begins\n\r");
	
	while(1){
		
				//Print values of the potentiometers to the PC serial terminal
				pc.printf("Potentiometer 1 value %f\n\r", pot1_val);
				pc.printf("Potentiometer 2 value %f\n\r", pot2_val);
		
				//Reading the Potentiometer 1 value 
				pot1_val = POT1.read(); 
				
				//Calculating the period based on the frequency range 300Hz - 125Khz
        period_val =(0.003*pot1_val)+0.000125; 

				//Making the period adjustable using the potentiometer
        speaker.period(period_val); 

				//Creating a saw-tooth sound wave
        for(i=0; i<=1; i+=period_val) {
            speaker=i;  
        }
				
        for(i=1; i>0; i-= period_val) {
            speaker=i;  
        }

				//Reading the Potentiometer 2 value
        pot2_val= POT2.read(); 
	
				//Makingvolume adjustable using the potentiometer
        speaker.pulsewidth((pot2_val*period_val)); 
		
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2014*************************************
