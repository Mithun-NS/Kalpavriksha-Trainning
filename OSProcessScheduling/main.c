#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"

Queue ready_q, wait_q, term_q;
int system_time = 0;

int main() {
    init_queue(&ready_q);
    init_queue(&wait_q);
    init_queue(&term_q);
    init_hashmap();
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
    PCB *p = malloc(sizeof(PCB));
    printf("Enter <name pid cpuBurst ioStart ioDuration>: ");
    scanf("%s %d %d %d %d", p->name, &p->pid, &p->cpu_burst, &p->io_start, &p->io_duration);
    p->executed_cpu = 0;
    p->remaining_io = 0;
    p->arrival_time = 0;
    p->state = READY;
    insert_pcb(p);
    enqueue(&ready_q, p);
    }
    run_scheduler();
    printf("\n===== FINAL OUTPUT =====\n");
    PCB *cur = term_q.front;
    while (cur) {
    int tat = cur->completion_time - cur->arrival_time;
    int wt = tat - cur->cpu_burst - cur->io_duration;
    printf("PID: %d | Name: %s | CPU: %d | IO: %d | TAT: %d | WT: %d\n",
    cur->pid, cur->name, cur->cpu_burst, cur->io_duration, tat, wt);
    cur = cur->next;
    }
    return 0;
}