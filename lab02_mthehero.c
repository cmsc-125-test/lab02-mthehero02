/*
 * Author: John Michael Raqueño
 * Section: CD-1L
 * Program Description: Simulation of Shortest Remaining Processing Time (SRPT) algorithm
 * Note: process.txt is patterned to the reference given in Slack
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 10
# define MIN 30
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
		int index = 0;
		char chr;
		fscanf(fp, "%d", &pcnt); 	// stores first line as process count 

		// loop through the processes in the process.txt
		do {
			chr = fscanf(fp, "%d %d", &arrival, &length); // scan and store the values in the respective arrays
			arrival_time[index] = arrival;			
			job_length[index] = length;		
			index++;	// increments the index
		
		} while (chr != EOF); // scan for the values until it reaches an End of Line
		
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
	
	// created a temporary node to point at the head node of ready_queue
	linked_list *temp = (linked_list *) malloc (sizeof(linked_list)); 
	temp = ready_queue;

	// moves head pointer ready_queue to the second data of the list
	ready_queue = ready_queue->next;

	// prints the PCB of the ended process
	PrintPCB(temp->pcb);

	// frees the temporary node 
	free(temp);
}


/* Inserts the process in the queue */
void Enqueue(int process_id, int arrival, int job_length){
	// created a temporary node before adding it to the ready_queue
	linked_list *new_pcb = (linked_list *) malloc (sizeof(linked_list)); 
	new_pcb->pcb.process_id = process_id;
	new_pcb->pcb.arrival_time = arrival;
	new_pcb->pcb.job_length = job_length;
	new_pcb->pcb.wait_time = 0;
	new_pcb->pcb.run_time = 0;
	new_pcb->next = NULL;

	// assigns a pointer temp to ready_queue
	linked_list *temp = ready_queue;

	// if ready_queue is empty, insert the new process as head
	if (ready_queue == NULL) {
		ready_queue = new_pcb;
		return;
	}
	
	// if the ready_queue is greater in terms of remaining process time than the new PCB,
	// insert the new process as the head of the node
	else if (((temp->pcb.job_length) - (temp->pcb.run_time)) > (new_pcb->pcb.job_length)) {
		new_pcb->next = temp;
		ready_queue = new_pcb;
		return;
	}
	
	// check every process before inserting the new process to the queue and
	// inserts it before a process that has less remaining process time
	// yes
	while (temp->next != NULL && ((temp->next->pcb.job_length) - (temp->next->pcb.run_time)) < (new_pcb->pcb.job_length)) {
		temp = temp->next;
	}

	new_pcb->next = temp->next;
	temp->next = new_pcb;

	return;
}


/*
 * Simulates processing of a single CPU cycle
 * Increases the run time of the currently executing process
   * Currently executing processs is the first process in the queue
 * Increases the wait time of the other processes in the queue
 * Checks if a process terminates (run time == job length)
 */
void Processing(){
	// created a temporary node to point at the head node of ready_queue
	linked_list *temp = (linked_list *) malloc (sizeof(linked_list)); 
	temp = ready_queue;

	// updates run time of the head of ready_queue
	ready_queue->pcb.run_time = ready_queue->pcb.run_time + 1;

	// updates the waiting time of the other nodes aside from the head or running node
	while (temp->next != NULL) {
		temp->next->pcb.wait_time = temp->next->pcb.wait_time + 1;
		temp = temp->next;
	}

	// removes terminated process from the queue by equating run_time to job_length
	if (ready_queue->pcb.run_time == ready_queue->pcb.job_length) {
		Dequeue();
		return;
	}

	return;
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
		
		// checks if the arrival time of the process is equivalent to the cpu cycle
		// for it to be enqueued and increments the index to access the array
		if (arrival_time[i] == cpu_cycles) {
			Enqueue(i, arrival_time[i], job_length[i]);
			i++;
		}
		Processing();
		PrintReadyQueue();
		cpu_cycles++;
		if(ready_queue == NULL) break;
	}
}

void PrintSomethingSomething(){
	printf("Hello World po!");
	printf("Hello World po!");
	printf("Hello World po!");
}


int main(){	
	int arrival_time[MAX], job_length[MAX];
	int process_count = ReadProcesses(arrival_time, job_length);
	RunSimulation(arrival_time, job_length, process_count);
}