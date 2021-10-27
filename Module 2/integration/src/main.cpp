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

#include "NHD_0216HZ.h"
#include "DS1631.h"
#include "pindef.h"

//Define the LCD and the temperature sensor
NHD_0216HZ LCD(SPI_CS, SPI_MOSI, SPI_SCLK);
DS1631 TEMP(I2C_SDA, I2C_SCL, 0x90);
//Write your code here


//Define a variable to store temperature measurement
float temp;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main() {
	//Initialise the LCD
	LCD.init_lcd();
	//Write your code here
	
	
 //   SPI_CS = 1;
    
 //   spi.format(8, 3);         //8bit spi mode 2
 //   spi.frequency(100000);    //100 kHz spi clock

	while(1){
		/*
		Read the temperature from the DS1631
		Update the LCD with new temperature measurement
		*/
		
		LCD.set_cursor(0,0); 
		temp = TEMP.read();
		//LCD.printf("Hello");
		printf("Temperature is %f\n\r", temp);
		LCD.printf("Temp: %2f", temp);
		wait_ms(2000);
		LCD.clr_lcd();
		
		//Write your code here
		
		
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
