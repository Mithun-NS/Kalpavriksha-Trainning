#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void init_queue(Queue *q) {
	q->front = q->rear = NULL;
}
void enqueue(Queue *q, PCB *p) {
	p->next = NULL;
	if (q->rear == NULL) {
		q->front = q->rear = p;
	} else {
		q->rear->next = p;
		q->rear = p;
	}
}
PCB* dequeue(Queue *q) {
	if (q->front == NULL) return NULL;
	PCB *temp = q->front;
	q->front = q->front->next;
	if (q->front == NULL)
		q->rear = NULL;
	temp->next = NULL;
	return temp;
}
int is_empty(Queue *q) {
	return q->front == NULL;
}
void remove_from_queue(Queue *q, int pid) {
	PCB *cur = q->front, *prev = NULL;
	while (cur != NULL) {
		if (cur->pid == pid) {
			if (prev == NULL) {
				q->front = cur->next;
				if (q->front == NULL) q->rear = NULL;
			} else {
				prev->next = cur->next;
				if (cur == q->rear) q->rear = prev;
			}
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}