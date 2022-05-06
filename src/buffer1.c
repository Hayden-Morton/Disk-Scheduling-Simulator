#include <stdio.h>
#include <stdlib.h>

#include "buffer1.h"
#include "linkedlist.h"

Buffer1* allocatedBuffer1(void) {
    Buffer1* buffer1 = (Buffer1*)malloc(sizeof(Buffer1));
    buffer1->requestList = NULL;
    refreshBuffer1(buffer1);

    return buffer1;
}

void refreshBuffer1(Buffer1* buffer1) {
    if (buffer1->requestList != NULL) {
        freeLinkedList(buffer1->requestList);
        buffer1->requestList = NULL;
    }
    buffer1->requestList = createLinkedList();

    buffer1->total = -1;
    buffer1->startingPosition = -1;
    buffer1->direction = 0;
}


void freeBuffer1(Buffer1* buffer1) {
    freeLinkedList(buffer1->requestList);
    buffer1->requestList = NULL;
    free(buffer1);
    buffer1 = NULL;
}
