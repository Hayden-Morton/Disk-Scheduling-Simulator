#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <pthread.h>

#include "buffer1.h"
#include "linkedlist.h"
#include "readFile.h"
#include "algorithms.h"

#include "simulator.h"
#include "assumptions.h"


pthread_mutex_t mutexRead, mutexWrite;
pthread_cond_t condRead, condWrite, condBuffer2Empty;

int main(void) {

	char sourceFilename[MAXUSERINPUTLENGTH];

	Buffer1* buffer1 = allocatedBuffer1();
	Buffer2 buffer2;

	bool buffer2Empty = TRUE;

	threadArguments* thArgs;
	int i;
	
	bool continueStatus = TRUE;

	char* algNames[] = {"FCFS","SSTF","SCAN","CSCAN","LOOK","CLOOK"};
	schedulingAlg algs[] = {FCFS,SSTF,SCAN,CSCAN,LOOK,CLOOK};

	int threadCount = 6;

	pthread_t thread[6];

	pthread_mutex_init(&mutexRead,NULL);
	pthread_mutex_init(&mutexWrite,NULL);

	pthread_cond_init(&condRead,NULL);
	pthread_cond_init(&condWrite,NULL);
	pthread_cond_init(&condBuffer2Empty,NULL);

	buffer2.value = 0;
	buffer2.threadId = -1;


	for (i = 0; i < threadCount; i++) {
		thArgs = malloc(sizeof(threadArguments));
		thArgs->threadId = i;
		thArgs->schedulAlg = algs[i];
		thArgs->buffer1 = buffer1;
		thArgs->buffer2 = &buffer2;
		thArgs->buffer2Empty = &buffer2Empty;
		thArgs->continueStatus = &continueStatus;
		if (pthread_create(&thread[i],NULL,&thRoutine,thArgs)) {
			return 1;
		}
	}

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

			if (!readFile(sourceFilename, buffer1)) {
				pthread_cond_broadcast(&condRead);

				for ( i = 0; i < threadCount; i++ ) {
					pthread_mutex_lock(&mutexWrite);
					pthread_cond_wait(&condWrite,&mutexWrite);
					printf("%s: %d\n", algNames[buffer2.threadId], buffer2.value);
					buffer2Empty = TRUE;
					pthread_mutex_unlock(&mutexWrite);
					pthread_cond_broadcast(&condBuffer2Empty);
				}
				refreshBuffer1(buffer1);
			}
		}
	
	} while (continueStatus);

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

	pthread_mutex_lock(&mutexRead);
	while(TRUE) {
		pthread_cond_wait(&condRead,&mutexRead);
		if (thArgs.continueStatus) {
			pthread_mutex_lock(&mutexWrite);
			if (!(thArgs.buffer2Empty)) {
				pthread_cond_wait(&condBuffer2Empty,&mutexWrite);
			}
			thArgs.buffer2Empty = FALSE;
			thArgs.buffer2->value = (thArgs.schedulAlg)(thArgs.buffer1);
			thArgs.buffer2->threadId = thArgs.threadId;

			pthread_mutex_unlock(&mutexWrite);
			pthread_cond_signal(&condWrite);
		} else {
			printf("thread_%d terminated\n",thArgs.threadId);
			free(args);
			pthread_mutex_unlock(&mutexRead);
			return NULL;
		}
		pthread_mutex_unlock(&mutexRead);
	}
}

