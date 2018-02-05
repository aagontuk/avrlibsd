#include "queue.h"

int enqueue(char ch){
	int q_status;

	if(!Q_FULL){
		Q_BUFFER[Q_TAIL] = ch;
		q_status = ENQUEUE_SUCCESS;
	}
	else{
		q_status = QUEUE_FULL;
	}

	/* Queue not full */
	if(!(Q_HEAD == 0 && Q_TAIL == RECEIVE_BUFF_SIZE - 1) && (Q_HEAD != Q_TAIL + 1)){

		if(Q_TAIL == (RECEIVE_BUFF_SIZE - 1)){
			Q_TAIL = 0;
		}
		else{
			Q_TAIL++;
		}

		Q_FULL = 0;
	}
	else{
		Q_FULL = 1;
	}

	return q_status;
}

char dequeue(){
	char ch;

	/* Queue not empty */
	if(!(Q_HEAD == Q_TAIL)){
		ch = Q_BUFFER[Q_HEAD];

		if(Q_HEAD == (RECEIVE_BUFF_SIZE - 1)){
			Q_HEAD = 0;
		}
		else{
			Q_HEAD += 1;
		}
	}
	else{
		ch = QUEUE_EMPTY;
	}

	return QUEUE_EMPTY;
}
