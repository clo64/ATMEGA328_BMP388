#include "uart_spi.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/io.h>
#include <stdlib.h >

#define BAUD 38400
#define BAUDRATE (((F_CPU / (BAUD * 16UL)))-1)

void uart_init(void) {

	//Set baud rate to 38400, refernce ATMEGA328p datasheet for alternate values
	UBRR0H = (BAUDRATE>>8);
	UBRR0L = (BAUDRATE);
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);   //Enable RX and TX
	
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01); // set 8 data bits, all other bits remain default 0
	
	string_transmit("UART Initialized\n");
	
}

void uart_transmit(char data) {
	
	while(!(UCSR0A & (1<<UDRE0))); //Wait for write operation complete flag
	
	UDR0 = data;                   //Write user data to the UART buffer
	
}

void string_transmit(char *stringSend) {
	
	while(!(UCSR0A & (1<<UDRE0))); //Wait for write operation complete flag
	
	while(*stringSend != '\0')	   //Loop through user provided array sending each char via UART
	{
		uart_transmit(*stringSend);
		stringSend++;
		
	}
	
}

void spi_MasterInit(void) {
	
	DDRB = 0b00101101; //0x2D
	
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0)|(1<<CPOL)|(1<<CPHA);
	
	string_transmit("\r\nSPI Initialized\n\r");
	
}

int8_t user_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len){
	
	int8_t rslt = 0;				// not relev
	
	if(dev_id == 0)
	{
		PORTB &=~ (1<<PORTB2);
		_delay_us(10);	 // Send CS line low
	}
	
	SPDR = reg_addr;		    // write reg address to BMP388
	
	while(!(SPSR & (1<<SPIF)));         // wait for write complete
	
	for(int i=0; i<len; i++)
	{		    // loop write dummy data to device while reading into reg_data	
		SPDR = 0xff;		    // dummy write data
		while(!(SPSR & 1<<SPIF));
		reg_data[i] = SPDR;         // read from SPI register into data array
	}
	
	if(dev_id == 0)
	{
		_delay_us(10);
		PORTB |= (1<<PORTB2);	    // Send CS line high
	}
	
	return(rslt);
	
}

int8_t user_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
	
	int8_t rslt = 0; // 0 for success and 1 for failure
	
	//To add additional devices, alter logic to accomodate any number of device id's
	if(dev_id == 0)	 // Only one device to select, for now
	{ 
		PORTB &=~ (1<<PORTB2);
		_delay_us(10);
	}
	
	SPDR = reg_addr;
	while(!(SPSR & 1<<SPIF));
	
	for(int i=0; i<len; i++)
	{		
		SPDR = reg_data[i];
		while(!(SPSR & 1<<SPIF));	
	}
	
	if(dev_id == 0)  // Bring the CS line high, signals end of transmission
	{ 
		_delay_us(10);
		PORTB |= (1<<PORTB2);
	}
	
	return(rslt);
	
}

void user_delay_ms(uint32_t period){
	
	while(period--)
	{	
		_delay_ms(1);	
	}	
}
