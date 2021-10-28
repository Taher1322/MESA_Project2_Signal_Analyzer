/*----------------------------------------------------------------------------
LAB EXERCISE 8.2 - INTERRUPT IN/OUT
PROGRAMMING USING MBED API
 ----------------------------------------
 In this exercise you need to use the mbed API functions to:
 
	1) Define InterruptIn and ISR for the button press
	2) In the interrupt service routine, the LED is used to indicate when a
	button was pressed:
			+ USER_BUTTON - LED1

	3) Put the processor into sleep mode upon exiting from the ISR
			
	GOOD LUCK!
 *----------------------------------------------------------------------------*/

/*************************************************************************
*
* File name : main.cpp
* Description : Contains main function to read the button press values in interrupt based mode and control the led's
* Author: Taher Ujjainwala and Steve Christensen
* Tools : mbed, Keil
*
**************************************************************************/

#include "mbed.h"

//Defining the ON and OFF state of Led's
#define LED_ON  1
#define LED_OFF 0

//Define interrupt inputs
InterruptIn Button1(D2);     //PA_10
InterruptIn Button2(D3);		 //PB_3
InterruptIn Button3(D4);		 //PB_5
InterruptIn Button4(D5);		 //PB_4

//Define outputs
DigitalOut Int_LED(LED1);		//LD2
DigitalOut Ext_LED(D8);			//PA_9



//Define ISRs for the interrupts
//Button 1 ISR routine
void button1_ISR_routine()
{
	Int_LED = LED_ON;   //Switching the Internal LED ON 
}

//Button 2 ISR routine 
void button2_ISR_routine()
{
	Int_LED = LED_OFF;	//Switching the Internal LED OFF
}

//Button 3 ISR routine
void button3_ISR_routine()
{
	Ext_LED = LED_ON;		//Switching the External LED ON
}

//Button 4 ISR routine 
void button4_ISR_routine()
{
	Ext_LED = LED_OFF;	//Switching the External LED OFF
}


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	
	__enable_irq();			//enable interrupts
	
	//initially turn off  LED
	
	Int_LED = LED_OFF;
	Ext_LED = LED_OFF;

	
	//Interrupt handlers
	//Defining 4 Button Interrupts to handle button press - The system is in PULL UP mode 
	//The interrupt is generated on RISING EDGE - that is when a button is pressed the event occurs and executes the ISR
  Button1.rise(&button1_ISR_routine);  
	Button2.rise(&button2_ISR_routine);
	Button3.rise(&button3_ISR_routine);
	Button4.rise(&button4_ISR_routine);
	
	
	//Sleep on exit
	while(1){
		
		sleep();
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
