#include <stdio.h>
#include <stdlib.h>

#include "cylinderHead.h"
#include "linkedlist.h"
#include "readFile.h"

int main(int argc, char* argv[]) {
	char* sourceFile = argv[1];

	CylinderHead* head = emptyCylinderHead();
	LinkedList* requestList = createLinkedList();

	LinkedListNode* cur;

	int failure;

	failure = readFile(sourceFile, head, requestList);
	if (failure) {
		freeLinkedList(requestList);
		free(head);
		return 1;
	}
	printf("%d\n%d\n%d\n",head->total,head->currentPosition,head->direction);
	
	cur = requestList->head;
	while (cur != NULL) {
		printf("%d\n",(cur->data));
		cur = cur->next;
	}
	freeLinkedList(requestList);
	free(head);
	return 0;
}

