#ifndef __GSM_H__
#define __GSM_H__

#define USART0 0
#define USART1 1
#define NO_NEW_MSG 2

#define GSM_PWON_DDR DDRC
#define GSM_PWON_PORT PORTC
#define GSM_PWON_PIN PINC0

void gsm_init(int usart);
void gsm_send(char *cmd);
void gsm_receive(char *buffer);
void gsm_get_msg_body(char *msg, short msgnum);
int gsm_wait_for_new_msg();

#endif
