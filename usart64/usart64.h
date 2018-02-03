#ifndef __USART_H__
#define __USART_H__

#define F_CPU 8000000UL
#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1

#include <inttypes.h>

void usart0_init(uint16_t ubrr_value);
void usart1_init(uint16_t ubrr_value);
void usart0_write_char(char data);
void usart1_write_char(char data);
void usart0_write_string(char *str);
void usart1_write_string(char *str);
char usart0_read_char(void);
char usart1_read_char(void);
void usart0_read_string(char *str);
void usart1_read_string(char *str);

#endif
