#include <stdio.h>
#include <stdlib.h>

#include "buffer1.h"
#include "linkedlist.h"

Buffer1* allocatedBuffer1(void) {
    Buffer1* buffer1 = (Buffer1*)malloc(sizeof(Buffer1));
    buffer1->requestList = createLinkedList();

    buffer1->total = 0;
    buffer1->currentPosition = 0;
    buffer1->direction = 0;

    return buffer1;
}

void freeBuffer1(Buffer1* buffer1) {
    freeLinkedList(buffer1->requestList);
    free(buffer1);
}