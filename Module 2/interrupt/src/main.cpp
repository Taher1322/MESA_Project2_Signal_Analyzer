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

#include "mbed.h"


#define LED_ON  1
#define LED_OFF 0

//Define interrupt inputs
InterruptIn Button1(D2);
InterruptIn Button2(D3);
InterruptIn Button3(D4);
InterruptIn Button4(D5);

//Define outputs
DigitalOut Int_LED(LED1);
DigitalOut Ext_LED(D8);



//Define ISRs for the interrupts
void button1_ISR_routine()
{
	Int_LED = LED_ON;
}

void button2_ISR_routine()
{
	Int_LED = LED_OFF;
}

void button3_ISR_routine()
{
	Ext_LED = LED_ON;
}

void button4_ISR_routine()
{
	Ext_LED = LED_OFF;
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
	//Attach the address of the ISR to the rising edge
  Button1.rise(&button1_ISR_routine);  // attach the address of the flip function to the rising edge
	Button2.rise(&button2_ISR_routine);
	Button3.rise(&button3_ISR_routine);
	Button4.rise(&button4_ISR_routine);
	
	
	//Sleep on exit
	while(1){
		
		sleep();
		
		//Write your code here
	
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
