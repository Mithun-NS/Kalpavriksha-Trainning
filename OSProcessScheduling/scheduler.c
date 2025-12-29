#include <stdio.h>
#include <unistd.h>
#include "scheduler.h"
extern Queue ready_q, wait_q, term_q;
extern int system_time;
void update_waiting_queue() {
	PCB *cur = wait_q.front;
	while (cur) {
		cur->remaining_io--;
		if (cur->remaining_io == 0) {
			remove_from_queue(&wait_q, cur->pid);
			cur->state = READY;
			enqueue(&ready_q, cur);
		}
		cur = cur->next;
	}
}
void run_scheduler() {
	while (!is_empty(&ready_q) || !is_empty(&wait_q)) {
		PCB *current = dequeue(&ready_q);
		if (!current) {
			system_time++;
			update_waiting_queue();
			continue;
		}
		current->state = RUNNING;
		while (current->executed_cpu < current->cpu_burst) {
			sleep(1);
			system_time++;
			current->executed_cpu++;
			update_waiting_queue();
			if (current->executed_cpu == current->io_start && current->io_duration > 0) {
				current->state = WAITING;
				current->remaining_io = current->io_duration;
				enqueue(&wait_q, current);
				break;
			}
		}
		if (current->executed_cpu == current->cpu_burst) {
			current->state = TERMINATED;
			current->completion_time = system_time;
			enqueue(&term_q, current);
		}
	}
}