#include <avr/io.h>
#include <inttypes.h>
#include "usart64.h"

void usart0_init(uint16_t ubrr_value){
	/*
	 * Set USART Baud Rate Register value with the currect
	 * baud rate settings. It is calculated with the following
	 * equation(Asynchronious normal mode - U2Xn = 0):
	 * UBRR = (F_CPU / (16 * BAUD)) - 1
	 */
	UBRR0H = (ubrr_value >> 8);
	UBRR0L = ubrr_value;

	/* Transmit and receive enable */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	/* 8N1 configuration of data frame */
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void usart1_init(uint16_t ubrr_value){
	UBRR1H = (ubrr_value >> 8);
	UBRR1L = ubrr_value;

	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	
	UCSR1C = (1 << UCSZ10) | (1 << UCSZ11);
}

void usart0_write_char(char data){
	while(!(UCSR0A & (1 << UDRE0))){

	}

	UDR0 = data;
}

void usart1_write_char(char data){
	while(!(UCSR1A & (1 << UDRE1))){

	}

	UDR1 = data;
}

void usart0_write_string(char *str){
	while(*str){
		usart0_write_char(*str++);
	}
}

void usart1_write_string(char *str){
	while(*str){
		usart1_write_char(*str++);
	}
}

char usart0_read_char(void){
	while(!(UCSR0A & (1 << RXC0))){

	}

	return UDR0;
}

char usart1_read_char(void){
	while(!(UCSR1A & (1 << RXC1))){

	}

	return UDR1;
}

void usart0_read_string(char *str){
	char ch;
	while(1){
		ch = usart0_read_char();
		if(ch == '\r' || ch == '\n'){
			*str = '\0';
			break;
		}
		*str++ = ch;
	}
}

void usart1_read_string(char *str){
	char ch;
	while(1){
		ch = usart1_read_char();
		if(ch == '\r' || ch == '\n'){
			*str = '\0';
			break;
		}
		*str++ = ch;
	}
}
