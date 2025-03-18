/*
 * Author: 
 * Section: 
 * Program Description: 
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

/* Process Control Block (PCB) */
typedef struct PCB {
	int process_id;
	int arrival_time;
	int job_length;
	int wait_time;
	int run_time;
}PCB;

/* Singly-linked list of PCB */
typedef struct linked_list{
	PCB pcb;
	struct linked_list *next;
}linked_list;

/* Stores the processes */
linked_list *ready_queue = NULL;


/* Prints the details of the process */
void PrintPCB(PCB pcb){
	printf("\tProcess ID: %d, Arrival Time: %d, Job Length: %d, Wait Time: %d, Run Time: %d\n", pcb.process_id, pcb.arrival_time, pcb.job_length, pcb.wait_time, pcb.run_time);
}


/* Prints the processes in the ready queue */
void PrintReadyQueue(){
	linked_list *ptr = ready_queue;

	printf("\n\tPrinting Ready Queue:\n");

	while(ptr!=NULL){
		PrintPCB(ptr->pcb);
		ptr = ptr->next;
	}
}


/* 
 * Reads from process.txt
   * First line of the file is the process count
   * Succeeding lines are the <arrival_time> <job_length> values
   * Assume that the processes are sorted in ascending order by arrival time
 * Stores <arrival_time> to arrival_time array
 * Stores <job_length> to job_length array
 * Returns the process count
 */
int ReadProcesses(int *arrival_time, int *job_length){
	int arrival, length, pcnt;
	FILE *fp;

	fp = fopen("process.txt", "rw");
	
	if(fp != NULL){






		fclose(fp);
	}
	return pcnt;
}


/* 
 * Prints the terminated process
 * Removes the terminated process at the head of the queue
 */
void Dequeue(){	
	printf("\tThe following process already ended:\n");
	

}


/* Inserts the process in the queue */
void Enqueue(int process_id, int arrival, int job_length){
	

}


/*
 * Simulates processing of a single CPU cycle
 * Increases the run time of the currently executing process
   * Currently executing processs is the first process in the queue
 * Increases the wait time of the other processes in the queue
 * Checks if a process terminates (run time == job length)
 */
void Processing(){
	

}


/* 
 * Simulates the CPU scheduling
 * Checks the arrival of processes in a given cpu cycle
 * Updates the processes in the queue
 * Prints the processes in the ready queue
 */
void RunSimulation(int *arrival_time, int *job_length, int process_count){
	int i=0, cpu_cycles=1;
	
	while(1){
		printf("\nCPU Cycle: %d\n", cpu_cycles);
		




		Processing();
		PrintReadyQueue();
		cpu_cycles++;
		if(ready_queue == NULL) break;
	}
}


int main(){	
	int arrival_time[MAX], job_length[MAX];
	int process_count = ReadProcesses(arrival_time, job_length);
	RunSimulation(arrival_time, job_length, process_count);
}