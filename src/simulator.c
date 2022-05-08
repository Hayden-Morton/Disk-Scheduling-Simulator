/*
File: simulator.c
Author: Hayden Morton
Course: Operating Systems
Date: Semester 1 2022
Summary: runs the disk scheduling simulator with threads
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <pthread.h>

#include "buffer1.h"
#include "linkedlist.h"
#include "readFile.h"
#include "algorithms.h"
#include "scheduler.h"
#include "simulator.h"
#include "assumptions.h"


pthread_mutex_t mutexRead, mutexWrite;
pthread_cond_t condRead, condWrite, condBuffer2Empty;

int main(void) {

	char sourceFilename[MAXUSERINPUTLENGTH];
	int readSuccess;

	bool continueStatus = TRUE;
	int finishedChildren = 0; /*to track if parent thread needs to wait*/
	int buffer1Rewrites = 0; /*to track how many times the input buffer has been overritten, so the child threads can detemine if new data*/

	char* algNames[] = {"FCFS","SSTF","SCAN","CSCAN","LOOK","CLOOK"};
	schedulingAlg algs[] = {FCFS,SSTF,SCAN,CSCAN,LOOK,CLOOK};

	int threadCount = SCHEDULINGALGORITHMSNUMBER;
	pthread_t thread[SCHEDULINGALGORITHMSNUMBER];

	threadArguments* thArgs;	/*Used for thread management*/
	int i;

	Buffer1* buffer1 = allocatedBuffer1(); /*Read In*/
	Buffer2 buffer2;	/*Mono Bounded Buffer*/

	/*Setup*/
	buffer2.value = 0;
	buffer2.threadId = -1; /*"-1" signifies buffer2 is empty, can be overridden*/
	pthread_mutex_init(&mutexRead,NULL);
	pthread_mutex_init(&mutexWrite,NULL);
	pthread_cond_init(&condRead,NULL);
	pthread_cond_init(&condWrite,NULL);
	pthread_cond_init(&condBuffer2Empty,NULL);

	for (i = 0; i < threadCount; i++) {
		thArgs = malloc(sizeof(threadArguments));	/*passing arguments to the child threads, instead of using global variables*/
		thArgs->threadId = i;
		thArgs->schedulAlg = algs[i];
		thArgs->buffer1 = buffer1;
		thArgs->buffer2 = &buffer2;
		thArgs->continueStatus = &continueStatus;
		thArgs->finishedChildren = &finishedChildren;
		thArgs->buffer1Rewrites = &buffer1Rewrites;
		if (pthread_create(&thread[i],NULL,&thRoutine,thArgs)) {
			return 1;
		}
	}

	/*Main Loop*/
	do {
		printf("Disk Scheduler Simulation: ");
		scanf("%s",sourceFilename);
		

		if ((int)strlen(basename(sourceFilename)) > MAXINPUTFILELENGTH) {
			printf("Invalid File, Name must be less than %d characters\n",MAXINPUTFILELENGTH);

		} else if (!strcmp(sourceFilename,QUITSYMBOL)) {
				continueStatus = FALSE;
				buffer1Rewrites +=1;
				pthread_cond_broadcast(&condRead);

		} else {
			readSuccess = !readFile(sourceFilename, buffer1);	

			if (readSuccess) {
				printf("For %s:\n",basename(sourceFilename));
				buffer1Rewrites += 1;
				pthread_cond_broadcast(&condRead);

				for ( i = 0; i < threadCount; i++ ) {
					pthread_mutex_lock(&mutexWrite);
					while (finishedChildren == 0) {
						pthread_cond_wait(&condWrite,&mutexWrite); /*wait for child thread to write to buffer2*/
					}
					printf("%s: %d\n", algNames[buffer2.threadId], buffer2.value);
					buffer2.threadId = -1;	/*Mark as empty*/
					finishedChildren -= 1;
					pthread_mutex_unlock(&mutexWrite);
					pthread_cond_signal(&condBuffer2Empty); /*signal any waiting child threads that buffer2 is now empty*/
				}
			}
		}
	
	} while (continueStatus);

	/*Clean up*/
	for (i = 0; i < threadCount; i++) {
		if (pthread_join(thread[i],NULL)) {
			return 2;
		}
	}
	freeBuffer1(buffer1);
	pthread_mutex_destroy(&mutexRead);
	pthread_mutex_destroy(&mutexWrite);
	pthread_cond_destroy(&condRead);
	pthread_cond_destroy(&condWrite);
	pthread_cond_destroy(&condBuffer2Empty);

	return 0;
}

void* thRoutine(void* args) { /*the child threads each compute when buffer1 available, storing results in buffer2, continuing until request not*/
	int seekTime;
	threadArguments thArgs = *(threadArguments*)args; /*since pass by reference only given once on creation*/
	int prevBuffer1Written = 0;
	while(TRUE) {
		pthread_mutex_lock(&mutexRead);
		while(*(thArgs.buffer1Rewrites) != prevBuffer1Written + 1) {
			pthread_cond_wait(&condRead,&mutexRead); /*wait for buffer1 to be written*/
		}
		prevBuffer1Written = *(thArgs.buffer1Rewrites);
		if (*(thArgs.continueStatus)) {
			pthread_mutex_unlock(&mutexRead);
			seekTime = (thArgs.schedulAlg)(thArgs.buffer1);
			pthread_mutex_lock(&mutexWrite);
			while (thArgs.buffer2->threadId != -1) { /*while buffer2 is full, wait*/
				pthread_cond_wait(&condBuffer2Empty,&mutexWrite);
			}
			thArgs.buffer2->value = seekTime;
			thArgs.buffer2->threadId = thArgs.threadId;

			*(thArgs.finishedChildren) += 1;
			pthread_mutex_unlock(&mutexWrite);
			pthread_cond_signal(&condWrite); /* signal parent to write out buffer2*/
		} else {
			pthread_mutex_unlock(&mutexRead);
			printf("thread_%d terminated\n",thArgs.threadId);
			free(args);
			return NULL;
		}
	}
}

