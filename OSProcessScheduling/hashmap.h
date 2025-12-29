#ifndef HASHMAP_H
#define HASHMAP_H

#include "process.h"
#define HASH_SIZE 50

PCB* hashmap[HASH_SIZE];
void init_hashmap();
int hash(int pid);
void insert_pcb(PCB *p);
PCB* get_pcb(int pid);
void delete_pcb(int pid);
#endif