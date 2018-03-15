#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../usart64/usart64.h"
#include "gsm.h"

int USART;

/* initialize gsm with correct baud rate settings */
void gsm_init(int usart){
	if(usart == USART0){
		USART = 0;
	}
	else if(usart == USART1){
		USART = 1;
	}

	if(!USART){
		usart0_init(MYUBRR);
	}
	else{
		usart1_init(MYUBRR);
	}

	/*Make PWKEY HIGH for 2 seconds to power on the gsm module */ 
	GSM_PWON_DDR |= (1 << GSM_PWON_PIN);
	GSM_PWON_PORT |= (1 << GSM_PWON_PIN);
	_delay_ms(2000);
	GSM_PWON_PORT &= ~(1 << GSM_PWON_PIN);
}

/* Send an AT command to GSM */
void gsm_send(char *cmd){
	if(!USART){
		usart0_write_string(cmd);
		usart0_write_char('\r');
	}
	else{
		usart1_write_string(cmd);
		usart1_write_char('\r');
	}
}

/* Receive reply or data from GSM */
void gsm_receive(char *buffer){
	char ch;
	short is_first_cr = 1;

	while(1){
		/* Extract one by one character from GSM */
		if(!USART){
			ch = usart0_read_char();
		}
		else{
			ch = usart1_read_char();
		}

		/* First CR. Just extract the following LF */
		if(ch == '\r' && is_first_cr){
			if(!USART){
				usart0_read_char();
			}
			else{
				usart1_read_char();
			}
			
			is_first_cr = 0;
		}

		/* Ending CR
		 * Extract following LF
		 * Complete the string by NULL terminating
		 * Exit loop
		 */
		else if(ch == '\r' && !is_first_cr){
			if(!USART){
				usart0_read_char();
			}
			else{
				usart1_read_char();
			}
		
			*buffer = '\0';
			break;
		}

		/* No controll character, text reply */
		else{
			*buffer++ = ch;
		}
	}
}

/* Returns a message body */
void gsm_get_msg_body(char *msg, short msgnum){
	char reply[128];
	char cmd[15];
	char ch;
	
	sprintf(cmd, "AT+CMGR=%d", msgnum);
	gsm_send(cmd);
	
	/* Should return data before message body */
	gsm_receive(reply);

	/* Now retrieve message body */
	while(1){
		if(!USART){
			ch = usart0_read_char();
		}
		else{
			ch = usart1_read_char();
		}

		if(ch == '\r'){
			*msg = '\0';

			/* following NL */
			if(!USART){
				usart0_read_char();
			}
			else{
				usart1_read_char();
			}

			break;
		}
		else{
			*msg++ = ch;
		}
	}
}

/*
 * Wait for new message. Returns message slot number,
 * when a new message arrives.
 */
int gsm_wait_for_new_msg(){
	char *reply = (char *)malloc(20);
	char *cmd = (char *)malloc(10);
	char *msgnum;

	gsm_receive(reply);

	/* Extract command part from the reply */
	strncpy(cmd, reply, 6);
	cmd[6] = '\0';

	if(strcmp(cmd, "+CMTI:") == 0){
		msgnum = strchr(reply, ',');

		return atoi(++msgnum);
	}

	return NO_NEW_MSG;
}
