/*
File: readFile.c
Author: Hayden Morton
Course: Operating Systems
Date: Semester 1 2022
Summary: all file reading for the input file for disk scheduling simulator
	takes in format of:
		<totalCylinder> <currentCylinder> <previousCylinder> <CylinderRequests>+
*/
#include <stdio.h>
#include <stdlib.h>

#include "buffer1.h"
#include "linkedlist.h"


int readFile(char* sourceFileName, Buffer1* buffer1) { /*read the file storing it in the supplied buffer1, if successful*/
	/*returns 0 if successful, 1/2/3 if not*/
	FILE* source;

	int cylinderTotal, startPos, prevPos;
	int request;
	int successRead;

	refreshBuffer1(buffer1);

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
			if (request > buffer1->total - 1) {
				printf("Error Reading File: Request cannot be greater than cylinder total\n");
				fclose(source);
				return 3;
			}
			insertLast(buffer1->requestList, request);
		}
	} while (successRead == 1);

	if (ferror(source)) {
		perror("Error reading File");
		fclose(source);
		return 3;
	}
	fclose(source);

	return 0;
}

