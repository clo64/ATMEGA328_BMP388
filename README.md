# ATMEGA328_BMP388
Basic communication functions for interfacing with Bosch BMP388 drivers and the ATMEGA328

 I struggled to make sense of the BOSCH provided drivers and found specific help in writing the necessary SPI functions to be lacking. I hope that someone stumbles upon this working implementation and finds it useful.
  
The UART functions I provide are very sparce and utilitarian. The nature of the project I'm incorporating these elements into doesn't require a great deal of "on the fly" changing of settings, therefore many settings are hardcoded into the functions.

Two useful functions that I couldn't find documentation for, user_spi_read and user_spi_write:

### int8_t user_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

### int8_t user_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
