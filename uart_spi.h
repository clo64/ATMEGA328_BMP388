#ifndef UART_SPI_H
#define	UART_SPI_H

#include <stdint.h>

#define BAUD 38400
#define BAUDRATE (((F_CPU / (BAUD * 16UL)))-1)

/*
* Initializes UART on the ATMEGA328p. Function sets the baud rate at 38400
* and enables TX and RX in Control register B. Sets 8 data bits, no stop bits
* and no parity bit.
* Initialization success response sent over UART at function completion
*/
void uart_init(void);

/*
* Transmits one character at a time over  ATMEGA328p TX line.
* Function writes directly to UDR0 register 
*/
void uart_transmit(char data);

/*
* Transmits entire string via UART
* No return acknowledgment 
*/
void string_transmit(char stringSend[]);

/*
* Initializes SPI interface by setting relevant B register  
* data directions. SPI mode set to "11" mode.
*/
void spi_MasterInit(void);

/*
* Reads data input over the SPI interface. Requires device id, starting register address,
* register array and number of bytes expected to read. Used in conjunction with the BOSCH
* BMP388 drivers these parameters are set internally except for the dev_id which must be
* provided by the user in the dev struct.
*/
int8_t user_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

/*
* Writes data over SPI. Requires device id, starting address of write, starting register address,
* register array and number of bytes expected to be written. Used in conjunction with the BOSCH
* BMP388 drivers these parameters are set internally except for the dev_id which must be
* provided by the use in the dev struct.
*/
int8_t user_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

/*
* The Bosch BMP388 driver requires a user defined ms delay function.
* This function can be added to the dev struct
*/
void user_delay_ms(uint32_t period);

#endif