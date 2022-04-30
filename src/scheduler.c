#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>


#include "buffer1.h"
#include "linkedlist.h"
#include "readFile.h"
#include "algorithms.h"

#include "assumptions.h"

int main(void) {

	Buffer1* buffer1;
	
	int continueStatus = TRUE;
		
	char sourceFilename[MAXUSERINPUTLENGTH];

	do {
		printf("Disk Scheduler Simulation: ");
		scanf("%s",sourceFilename);
		

		if ((int)strlen(basename(sourceFilename)) > MAXINPUTFILELENGTH) {
			printf("Invalid File, Name must be less than %d characters\n",MAXINPUTFILELENGTH);
		} else if (!strcmp(sourceFilename,QUITSYMBOL)) {
				continueStatus = FALSE;
		} else {

			buffer1 = allocatedBuffer1();
			if (!readFile(sourceFilename, buffer1)) {


				printf("FCFS %d\n",FCFS(buffer1));
				printf("SSTF %d\n",SSTF(buffer1));
				printf("SCAN %d\n",SCAN(buffer1));
				printf("CSCAN %d\n",CSCAN(buffer1));
				printf("LOOK %d\n",LOOK(buffer1));
				printf("CLOOK %d\n",CLOOK(buffer1));
			}
			freeBuffer1(buffer1);
		}
	} while (continueStatus);

	return 0;
}

