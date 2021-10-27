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
BusIn Button(D5, D4, D3, D2);

//Define output bus for the  LED
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
			
				if (button_val != 0)
				printf("Button Pressed value%d\n\r", button_val);
			
    		if((button_val & BUTTONPress_1_val) == 1) {
						SET_BIT(output_val, INT_LED);
      			//myleds = 1;
    		}	
    		if((button_val & BUTTONPress_2_val) == 2) {
					  CLEAR_BIT(output_val, INT_LED);
      			//myleds = 0;
    		}
    		if((button_val & BUTTONPress_3_val) == 4) {
						SET_BIT(output_val, EXT_LED);
      			//myleds = 2;
    		}
    		if((button_val & BUTTONPress_4_val) == 8) {
						CLEAR_BIT(output_val, EXT_LED);
      			//myleds = 0; 
    		}
				
				myleds = output_val;
		
		wait(0.1);
		
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
