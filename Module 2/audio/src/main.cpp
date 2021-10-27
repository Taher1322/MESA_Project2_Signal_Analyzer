/*----------------------------------------------------------------------------
LAB EXERCISE 9 - Analog input and PWM
 ----------------------------------------
	Use two potentiometers to adjust the volume and pitch of the output sound wave.
	
	Inputs: Virtual potentiometers 1 and 2
	Output: Virtual speaker,  Real PC

	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"
#include "pindef.h"

/*
Define the PWM speaker output
Define analog inputs
Define serial output
*/
PwmOut speaker(D6);
AnalogIn POT1(A0); 
AnalogIn POT2(A1); 

Serial pc(USBTX, USBRX);

	//Write your code here


//Define variables
float i;
double pot1_val, pot2_val, period_val;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	
	pc.printf("Code execution\n\r");
	
	while(1){
		/*
		Print values of the potentiometers to the PC serial terminal
		Create a saw-tooth sound wave
		Make the period and volume adjustable using the potentiometers
		*/
		pot1_val = POT1.read(); 

        period_val =(0.003*pot1_val)+0.000125; 

        speaker.period(period_val); 

        for(i=0; i<=1; i+=period_val) {
            speaker=i;  
        }
        for(i=1; i>0; i-= period_val) {
            speaker=i;  
        }

        pot2_val= POT2.read(); 

        speaker.pulsewidth((pot2_val*period_val)); 
		
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2014*************************************
