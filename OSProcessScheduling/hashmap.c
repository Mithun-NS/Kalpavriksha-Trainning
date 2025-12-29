#include <string.h>
#include <stdlib.h>
#include "hashmap.h"

void init_hashmap() {
	for (int i = 0; i < HASH_SIZE; i++) hashmap[i] = NULL;
}
int hash(int pid) {
	return pid % HASH_SIZE;
}
void insert_pcb(PCB *p) {
	int index = hash(p->pid);
	p->next = hashmap[index];
	hashmap[index] = p;
}
PCB* get_pcb(int pid) {
	int index = hash(pid);
	PCB *cur = hashmap[index];
	while (cur) {
		if (cur->pid == pid) return cur;
		cur = cur->next;
	}
	return NULL;
}
void delete_pcb(int pid) {
	int index = hash(pid);
	PCB *cur = hashmap[index], *prev = NULL;
	while (cur) {
		if (cur->pid == pid) {
			if (prev == NULL) hashmap[index] = cur->next;
			else prev->next = cur->next;
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}