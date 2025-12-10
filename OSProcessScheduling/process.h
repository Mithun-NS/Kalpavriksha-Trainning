#ifndef PROCESS_H
#define PROCESS_H
#define NAME_LEN 50

typedef enum {
	READY,
	RUNNING,
	WAITING,
	TERMINATED
} ProcessState;

typedef struct PCB {
	int pid;
	char name[NAME_LEN];
	int cpu_burst;
	int io_start;
	int io_duration;
	int executed_cpu;
	int remaining_io;
	int arrival_time;
	int completion_time;
	ProcessState state;
	struct PCB *next;
} PCB;
#endif