#include <stdlib.h>

#include "cylinderHead.h"
#include "linkedlist.h"

int FCFS(CylinderHead* head, LinkedList* requestList) {
    
    LinkedListNode* cur = requestList->head;
    int total = 0;

    while (cur != NULL) {
        total += abs(cur->data - cur->next->data);
        cur = cur->next;
    } 
}

int SSTF(CylinderHead* head, LinkedList* requestList) {

    LinkedListNode* cur = requestList->head;
    int total = 0;

    j
