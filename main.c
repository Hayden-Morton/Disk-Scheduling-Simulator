#include <stdio.h>
#include <stdlib.h>

#include "cylinderHead.h"

int main(int argc, char* argv[]) {
	char* sourceFile = argv[1];
	FILE* source;

	int cylinderTotal, startPos, prevPos;
	CylinderHead head;
	
	int successRead;

	if (argc < (1 + 1)) {
		printf("Invalid Arguments\n");
		return 1;
	}

	source = fopen(sourceFile,"r");
	if (source == NULL) {
		perror("Error openning File");
		return 2;
	}
	
	successRead = fscanf(source, "%d %d %d", &cylinderTotal, &startPos, &prevPos);
	if (successRead != 3) {
		printf("Error Reading File: Incorrect Format\n");
		fclose(source);
		return 3;
	}

	head.total = cylinderTotal;
	head.currentPosition = startPos;
	if (startPos > prevPos) {
		head.direction = ASCENDING;
	} else {
		head.direction = DESCENDING;
	}

	fclose(source);
	if (ferror(source)) {
		perror("Error reading File");
	}
	
	printf("%d\n%d\n%d\n",head.total,head.currentPosition,head.direction);
	
	return 0;
}

