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
				pthread_mutex_lock(&mutexRead);
				continueStatus = FALSE;
				pthread_mutex_unlock(&mutexRead);
				pthread_cond_broadcast(&condRead);

		} else {
			pthread_mutex_lock(&mutexRead);
			readSuccess = !readFile(sourceFilename, buffer1);	
			pthread_mutex_unlock(&mutexRead);

			if (readSuccess) {
				printf("For %s:\n",basename(sourceFilename));
				pthread_cond_broadcast(&condRead);

				for ( i = 0; i < threadCount; i++ ) {
					pthread_mutex_lock(&mutexWrite);
					pthread_cond_wait(&condWrite,&mutexWrite);
					printf("%s: %d\n", algNames[buffer2.threadId], buffer2.value);
					buffer2.threadId = -1;	/*Mark as empty*/
					pthread_mutex_unlock(&mutexWrite);
					pthread_cond_signal(&condBuffer2Empty);
				}
				refreshBuffer1(buffer1);
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

void* thRoutine(void* args) {
	threadArguments thArgs = *(threadArguments*)args;

	while(TRUE) {
		pthread_mutex_lock(&mutexRead);
		pthread_cond_wait(&condRead,&mutexRead);
		if (*(thArgs.continueStatus)) {
			pthread_mutex_unlock(&mutexRead);
			pthread_mutex_lock(&mutexWrite);
			while (thArgs.buffer2->threadId != -1) {
				pthread_cond_wait(&condBuffer2Empty,&mutexWrite);
			}
			thArgs.buffer2->value = (thArgs.schedulAlg)(thArgs.buffer1);
			thArgs.buffer2->threadId = thArgs.threadId;

			pthread_mutex_unlock(&mutexWrite);
			pthread_cond_signal(&condWrite);
		} else {
			pthread_mutex_unlock(&mutexRead);
			printf("thread_%d terminated\n",thArgs.threadId);
			free(args);
			return NULL;
		}
	}
}

