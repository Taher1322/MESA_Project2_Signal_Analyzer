/*----------------------------------------------------------------------------
LAB EXERCISE 12 - Real-Time Operating System
 ----------------------------------------
	Integrate functions developed in previous modules and run then concurrently
	in the mbed RTOS. The following four threads have to be implemented:
	
	1. Display the temperature on the LCD and to the PC
	2. Adjust the brightness of the RGB LED using a potentiometer
	3. Display an incrementing counter on the LCD and to the PC
	4. Blink an LED
  
  NOTE:  For this lab, the LCD, temp sensor and POT are virtual devices.

	GOOD LUCK!
 *----------------------------------------------------------------------------*/
 
 /*************************************************************************
*
* File name : main.cpp
* Description : Contains main function to read temperature values from DS1631 I2C based sensor and display on 16X2 LCD display - SPI based module
* Author: Taher Ujjainwala and Steve Christensen
* Tools : mbed, Keil
*
**************************************************************************/

#include "mbed.h"
#include "rtos.h"
#include "DS1631.h"
#include "NHD_0216HZ.h"
#include "pindef.h"
#include "cmsis_os.h"


//Defining Mutex for LCD - Because LCD is a shared process 
Mutex LCD_Display;

//Define the LCD and the temperature sensor
NHD_0216HZ LCD(SPI_CS, SPI_MOSI, SPI_SCLK);		//Defining the default SPI pins for communication using SHIFT Register 
DS1631 TEMP(I2C_SDA, I2C_SCL, 0x90);  				//Defining the default I2C pins for communication with the Slave Address

//Defining PWM for External LED 
//D8 --> PA_9
PwmOut Ext_LED(D8);

//Defining Internal LED 
//LED1 --> LD2
DigitalOut Int_LED(LED1);

//Defining Analog Pin to Read Potentiometer value - To control LED brightness 
//A0 --> PA_0
AnalogIn POT_VAL(A0);

//Defining variables for counter and temperature value
uint32_t counter = 0;
float temp;



//Display temperature on the LCD - Thread to read temperature and display on LCD
void temp_thread(void const *args){
	
	//Infinite While Loop 
	
	while (true){	
		//Locking the Display to access the shared resource 
		LCD_Display.lock();
		
		//Clearing the LCD content if any 
		LCD.clr_lcd();
		
		//Setting the LCD cursor to Row 0 Column 0
		LCD.set_cursor(0,0); 
		
		//Reading the temperature from DS1631 module 
		temp = TEMP.read();
		
		//Displaying the temperature on LCD display 
		LCD.printf("Temp: %f", temp);
		
		//Printing on serial for debugging purposes
		printf("Temperature is %f\n\r", temp);
		
		//Delay for 2 seconds 
		osDelay(2000);
		
		//Releasing the shared resouces for other threads
		LCD_Display.unlock();
		
		}
	}

	
//Adjust the brightness of the External LED using Potentiometer
void adjust_brightness(void const *args){
		//Infinite While loop 
	
		while(true) {
			
			//Reading the potentiometer value and changing the brightness of External LED 
			Ext_LED = (0.5 * POT_VAL.read());
			
			//Delay for 1 second
			osDelay(1000);
		}
		
}

//Blink an Internal LED
void led1_thread(void const *args){
	
	//Infinite While Loop
	while (true) {
				//Blinking an Internal LED 
        Int_LED =! Int_LED;
				
				//Delay for 500mseconds
        osDelay(500);
				
	}
	
}

//Display a counter on the LCD
void count_thread(void const *args){
	
	//Infinite While Loop
	while (true){
		
		//Locking the Display to access the shared resource 
		LCD_Display.lock();
		
		//Clearing the LCD content if any 
		LCD.clr_lcd();
		
		//Setting the LCD cursor to Row 0 Column 0
		LCD.set_cursor(0,0); 
		
		///Displaying the Counter on LCD display 
		LCD.printf("Counter: %d", counter);
		
		//Incrementing the Counter value 
		counter++;
		
		//Delay for 2 seconds
		osDelay(2000);
		
		//Printing the Counter value for debugging purposes 
		printf("Counter value is %d\n\r", counter);
		
		//Releasing the shared resouces for other threads
		LCD_Display.unlock();

	}	
	
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

//Defining All the threads with their callback functions, Priority and Stack size

	osThreadDef(led1_thread, osPriorityNormal, DEFAULT_STACK_SIZE);
	osThreadDef(adjust_brightness, osPriorityNormal, DEFAULT_STACK_SIZE);
	osThreadDef(temp_thread, osPriorityNormal, DEFAULT_STACK_SIZE);
	osThreadDef(count_thread, osPriorityNormal, DEFAULT_STACK_SIZE);

int main(){
	
		//Initialising LCD and clear the LCD display
		LCD.init_lcd();
		LCD.clr_lcd();
	
		//Starting all threads
		osThreadCreate(osThread(led1_thread), NULL);
		osThreadCreate(osThread(adjust_brightness), NULL);
		osThreadCreate(osThread(temp_thread), NULL);
		osThreadCreate(osThread(count_thread), NULL);
	
	while (1){
		__WFI();
	
	}
	
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
