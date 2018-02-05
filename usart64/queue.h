#ifndef __QUEUE_H__
#define __QUEUE_H__

#define RECEIVE_BUFF_SIZE 128
#define ENQUEUE_SUCCESS 1
#define QUEUE_FULL 0
#define QUEUE_EMPTY -1

#include <inttypes.h>

volatile char Q_BUFFER[RECEIVE_BUFF_SIZE];
volatile uint8_t Q_HEAD = 0;
volatile uint8_t Q_TAIL = 0;
volatile uint8_t Q_FULL = 0;

int enqueue(char ch);
char dequeue();

#endif
