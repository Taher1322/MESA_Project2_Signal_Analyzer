/*----------------------------------------------------------------------------
LAB EXERCISE 11.4- SPI and I2C interface
SERIAL COMMUNICATION
 ----------------------------------------
 Display the temperature from the virtual DS1631 temperature sensor on the 
      virtual LCD
 
 Input: virtual DS1631 temperature sensor
 Output: virtual LCD display
	
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

#include "NHD_0216HZ.h"
#include "DS1631.h"
#include "pindef.h"

//Define the LCD and the temperature sensor
NHD_0216HZ LCD(SPI_CS, SPI_MOSI, SPI_SCLK);   //Defining the default SPI pins for communication using SHIFT Register 
DS1631 TEMP(I2C_SDA, I2C_SCL, 0x90);					//Defining the default I2C pins for communication with the Slave Address

//Define a variable to store temperature measurement
float temp;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main() {
	//Initialise the LCD
	LCD.init_lcd();


	while(1){
		
		//Setting the LCD cursor on Row 0 and Column 0
		LCD.set_cursor(0,0); 
		
		//Reading the Temperature from DS1631
		temp = TEMP.read();
		
		//Printing debugging message for reference 
		printf("Temperature is %f\n\r", temp);
		
		//Printing the Temperature value on LCD 
		LCD.printf("Temp: %2f", temp);
		
		//Delay for 2 second
		wait_ms(2000);
		
		//Clearing the data on LCD before printing next statement or values
		LCD.clr_lcd();
			
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
