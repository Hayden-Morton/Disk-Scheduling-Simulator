#include <stdio.h>
#include <stdlib.h>

#include "buffer1.h"
#include "linkedlist.h"


int readFile(char* sourceFileName, Buffer1* buffer1) { 
	FILE* source;

	int cylinderTotal, startPos, prevPos;
	int request;
	int successRead;

	source = fopen(sourceFileName,"r");
	if (source == NULL) {
		perror("Error openning File");
		return 1;
	}
	
	successRead = fscanf(source, "%d %d %d", &cylinderTotal, &startPos, &prevPos);
	if (successRead != 3) {
		printf("Error Reading File: Incorrect Format\n");
		fclose(source);
		return 2;
	}

	buffer1->total = cylinderTotal;
	buffer1->startingPosition = startPos;
	if (startPos > prevPos) {
		buffer1->direction = ASCENDING;
	} else {
		buffer1->direction = DESCENDING;
	}

	do {
		successRead = fscanf(source, "%d", &request);
		if (successRead == 1) {
			insertLast(buffer1->requestList, request);
		}
	} while (successRead == 1);

	if (ferror(source)) {
		perror("Error reading File");
	}
	fclose(source);

	return 0;
}

