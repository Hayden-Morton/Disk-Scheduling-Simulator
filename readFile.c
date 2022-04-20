#include <stdio.h>
#include <stdlib.h>

#include "cylinderHead.h"
#include "linkedlist.h"


int readFile(char* sourceFileName, CylinderHead* head, LinkedList* requestList) {
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

	head->total = cylinderTotal;
	head->currentPosition = startPos;
	if (startPos > prevPos) {
		head->direction = ASCENDING;
	} else {
		head->direction = DESCENDING;
	}

	do {
		successRead = fscanf(source, "%d", &request);
		if (successRead == 1) {
			insertLast(requestList, request);
		}
	} while (successRead == 1);

	if (ferror(source)) {
		perror("Error reading File");
	}
	fclose(source);

	return 0;
}

