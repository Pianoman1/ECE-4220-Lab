/*
 * Lab2_W1.c
 *
 *  Created on: Feb 2, 2016
 *      Author: memdm2
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <rtai.h>
#include <rtai_lxrt.h>
#include <string.h>
#include <sys/time.h>

//Define Structs
typedef struct{
	char* line;
	FILE* structFile;
	int count;
} readVal;
typedef struct{
	char* common1;
	char* common2;
	char buffer[50];
	int index;
	int count;
} bufferSet;

#define LINE_LENGTH 200
#define NUM_LINES 20

//Define tasks
RTIME BaseP;
RT_TASK* rttask1;
RT_TASK* rttask2;
RT_TASK* rttask3;

//Read from first file
void readFileFirst(void* arg) {
	//Initialize
	rttask1 = rt_task_init(nam2num("thr1"),1,4096,400);
	//Periodic
	rt_task_make_periodic(rttask1,rt_get_time()+10*BaseP,40*BaseP);
	readVal set1 = *((readVal*) arg);
	while( fgets(set1.line, 60, set1.structFile)!=NULL){
		++set1.count;
		//wait for the period to end
		rt_task_wait_period();
	}
	printf("Thread1 End\n");
	pthread_exit(0);
}
//Read from second file
void readFileSecond(void* arg) {
	//Initialize
	rttask2 = rt_task_init(nam2num("thr2"), 1, 4096, 400);
	//Periodic
	rt_task_make_periodic(rttask2,rt_get_time()+30*BaseP, 40*BaseP );
	readVal set2 = *((readVal*) arg);
	while( fgets(set2.line, 60, set2.structFile)!=NULL){
		++set2.count;
		//wait for the period to end
		rt_task_wait_period();
	}
	printf("Thread2 End\n");
	pthread_exit(0);
}

void commonBuffer(void* arg){
	//Initialize
	rttask3 = rt_task_init(nam2num("thr3"), 1, 4096, 400);
	//Periodic
	rt_task_make_periodic(rttask3,rt_get_time()+20*BaseP, 20*BaseP );
	bufferSet buff = *((bufferSet*) arg);
	while(buff.index <= 20){
		//combine lines into the buffer
		if((buff.index)%2 == 0){
			strcpy(buff.buffer,buff.common1);
			printf("%s \n", buff.buffer);
		}
		//if it's odd do secondfile
		else if((buff.index)%2 == 1){
			strcpy(buff.buffer,buff.common2);
			printf("%s \n", buff.buffer);
		}
		++buff.index;
		//wait for the period to end
		rt_task_wait_period();
	}
	printf("Thread3 End\n");
	pthread_exit(0);
}

int main(void) {

	//Declare pthreads
	pthread_t pidFirst,pidSecond, pidThird;

	//Open Files
	FILE *fp1;
	fp1 = fopen("first.txt","r"); // read mode
	if(fp1 == NULL)
	{
		perror("Error while opening the file.\n");
		return 0;
	}
	FILE *fp2;
	fp2 = fopen("second.txt","r"); // read mode
	if(fp2 == NULL)
	{
		perror("Error while opening the file.\n");
		return 0;
	}

	//Initialize/Malloc Buffer structures
	readVal set1, set2;
	int counter = 0;
	char* commonFirst = malloc(sizeof(char)*LINE_LENGTH);
	set1.line = commonFirst;
	set1.structFile = fp1;
	set1.count = counter;
	char* commonSecond = malloc(sizeof(char)*LINE_LENGTH);
	set2.line = commonSecond;
	set2.structFile = fp2;
	set2.count = counter;
	bufferSet buff;
	buff.common1 = commonFirst;
	buff.common2 = commonSecond;
	char** bufx = malloc(sizeof(char)*NUM_LINES);

	buff.index = 0;

	//Set Timer
	BaseP = start_rt_timer(nano2count(1000000));

	//Create Threads
	if(pthread_create(&pidFirst, NULL, (void*)&readFileFirst, (void*)&set1)) {
		printf("Error creating thread\n");
		return 1;
	}
	if(pthread_create(&pidSecond, NULL, (void*)&readFileSecond, (void*)&set2)) {
		printf("Error creating thread\n");
		return 1;
	}
	if(pthread_create(&pidThird, NULL, (void*)&commonBuffer, (void*)&buff)) {
		printf("Error creating thread\n");
		return 1;
	}

	//Join Threads
	pthread_join(pidFirst, NULL);
	pthread_join(pidSecond, NULL);
	pthread_join(pidThird, NULL);

	//Stop Timer
	stop_rt_timer();

	//Close Files
	fclose(fp1);
	fclose(fp2);

	//Free Memory
	free(commonFirst);
	free(commonSecond);
	free(*bufx);

	return 0;
}
