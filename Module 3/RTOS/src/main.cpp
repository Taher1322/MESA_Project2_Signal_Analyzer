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

#include "mbed.h"
#include "rtos.h"
#include "DS1631.h"
#include "NHD_0216HZ.h"
#include "pindef.h"
#include "cmsis_os.h"
//#include "platform/mbed_thread.h"

/*
Define the mutex
Define the LCD display and the temperature sensor
Define other inputs and outputs
*/

Mutex LCD_Display;
//osThreadDef t2;




NHD_0216HZ LCD(SPI_CS, SPI_MOSI, SPI_SCLK);

DS1631 TEMP(I2C_SDA, I2C_SCL, 0x90);


PwmOut Ext_LED(D8);
DigitalOut Int_LED(LED1);
AnalogIn POT_VAL(A0);

uint32_t counter = 0;
float temp;


//Write your code here


//Display temperature on the LCD
void temp_thread(void const *args){
	
	while (true){
	LCD_Display.lock();
	LCD.clr_lcd();
	LCD.set_cursor(0,0); 
	temp = TEMP.read();
	LCD.printf("Temp: %f", temp);
	printf("Temperature is %f\n\r", temp);
	osDelay(2000);
	LCD_Display.unlock();
	}
	
	//write your code here
	
}

//Adjust the brightness of the RGB LED
void adjust_brightness(void const *args){
		while(true) {
			Ext_LED = (0.5 * POT_VAL.read());
			osDelay(1000);
		}
	//write your code here
	
}

//Blink an LED
void led1_thread(void const *args){
	
	while (true) {
        Int_LED =! Int_LED;
        osDelay(500);
				//Int_LED =0;
    }
	//write your code here
	
}

//Display a counter on the LCD
void count_thread(void const *args){
	
	while (true){
	LCD_Display.lock();
	LCD.clr_lcd();
	LCD.set_cursor(0,0); 
	LCD.printf("Counter: %d", counter);
	counter++;
	osDelay(2000);
	printf("Counter value is %d\n\r", counter);
	LCD_Display.unlock();

	}	//write your code here
	
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
	osThreadDef(led1_thread, osPriorityNormal, DEFAULT_STACK_SIZE);
	osThreadDef(adjust_brightness, osPriorityNormal, DEFAULT_STACK_SIZE);
	osThreadDef(temp_thread, osPriorityNormal, DEFAULT_STACK_SIZE);
	osThreadDef(count_thread, osPriorityNormal, DEFAULT_STACK_SIZE);

int main(){
	/*
	Initialise and clear the LCD display
	Start all threads
	Wait for timer interrupt
	*/
	
	LCD.init_lcd();
	LCD.clr_lcd();
	

	osThreadCreate(osThread(led1_thread), NULL);
	osThreadCreate(osThread(adjust_brightness), NULL);
	osThreadCreate(osThread(temp_thread), NULL);
	osThreadCreate(osThread(count_thread), NULL);
	
	while (1){
		
		//sleep();
	__WFI();
	//write your code here
	}
	
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
