#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"

typedef struct Queue {
PCB *front;
PCB *rear;
} Queue;

void init_queue(Queue *q);
void enqueue(Queue *q, PCB *p);
PCB* dequeue(Queue *q);
int is_empty(Queue *q);
void remove_from_queue(Queue *q, int pid);
#endif