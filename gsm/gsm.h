#ifndef __GSM_H__
#define __GSM_H__

/* Select USART to communicate GSM with
 * 0 - USART0
 * 1 - USART1
 */
#define USART 0

void gsm_init();
void gsm_send(char *cmd);
void gsm_receive(char *buffer);
void gsm_get_msg_body(char *msg, short msgnum);
int gsm_wait_for_new_msg();

#endif
