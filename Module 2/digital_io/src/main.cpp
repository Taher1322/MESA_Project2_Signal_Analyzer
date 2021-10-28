/*----------------------------------------------------------------------------
LAB EXERCISE 8.1 - DIGITAL INPUTS AND OUTPUTS
PROGRAMMING USING MBED API
 ----------------------------------------
 In this exercise you need to use the mbed API functions to:
 
	1) Define BusIn, BusOut interfaces for inputs and outputs
	2) The LED is controlled by the button:
			+ USER_BUTTON - LED1
			
			
	GOOD LUCK!
 *----------------------------------------------------------------------------*/
/*************************************************************************
*
* File name : main.cpp
* Description : Contains main function to read the button press values and control the led's depending on that 
* Author: Taher Ujjainwala and Steve Christensen
* Tools : mbed, Keil
*
**************************************************************************/


#include "mbed.h"

//Define input bus
// Input bus selectors
#define BUTTONPress_1_val  0x1
#define BUTTONPress_2_val  0x2
#define BUTTONPress_3_val  0x4
#define BUTTONPress_4_val  0x8


//Output bus selector
#define INT_LED 1
#define EXT_LED 2

//Define input bus
//D5 --> PB_4
//D4 --> PB_5
//D3 --> PB_3
//D2 --> PA_10
BusIn Button(D5, D4, D3, D2);

//Define output bus for the  LED 
//LED1 --> LD2
//D8 --> PA_9
BusOut myleds(LED1, D8);



/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	
	int button_val;  // value from input bus
	int output_val;  // Value for output bus
	
	while(1){
		
		//Check which button was pressed and light up the corresponding LED
    		button_val = Button.read(); 
			
				//Statement for debugging purpose - Determining which button is pressed and what is the button value
				if (button_val != 0)
				printf("Button Pressed value%d\n\r", button_val);
			
				//Button 1 press check function 
    		if((button_val & BUTTONPress_1_val) == 1) {
						SET_BIT(output_val, INT_LED);
      			//myleds = 1;
    		}	
				
				//Button 2 press check function
    		if((button_val & BUTTONPress_2_val) == 2) {
					  CLEAR_BIT(output_val, INT_LED);
      			//myleds = 0;
    		}
				
				//Button 3 press check function
    		if((button_val & BUTTONPress_3_val) == 4) {
						SET_BIT(output_val, EXT_LED);
      			//myleds = 2;
    		}
				
				//Button 4 press check function
    		if((button_val & BUTTONPress_4_val) == 8) {
						CLEAR_BIT(output_val, EXT_LED);
      			//myleds = 0; 
    		}
				
				//Updating the led values
				myleds = output_val;
		
		wait(0.1);
		
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
