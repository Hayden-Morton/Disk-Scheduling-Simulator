#include <stdio.h>
#include <stdlib.h>

#include "buffer1.h"
#include "linkedlist.h"
#include "readFile.h"

int main(int argc, char* argv[]) {
	char* sourceFile = argv[1];

	Buffer1* buffer1 = allocatedBuffer1();
	
	#ifdef DEBUG
	LinkedListNode* cur;
	#endif

	int failure;

	failure = readFile(sourceFile, buffer1);
	if (failure) {
		freeBuffer1(buffer1);
		return 1;
	}

	#ifdef DEBUG
		printf("%d\n%d\n%d\n",buffer1->total,buffer1->currentPosition,buffer1->direction);
		cur = buffer1->requestList->head;
		while (cur != NULL) {
			printf("%d\n",(cur->data));
			cur = cur->next;
		}
	#endif
	
	freeBuffer1(buffer1);
	return 0;
}

