#include <stdlib.h>

#include "buffer1.h"
#include "linkedlist.h"
#include "algorithms.h"

int FCFS(Buffer1* buffer1) {
    
    LinkedListNode* cur = buffer1->requestList->head;
    int total = 0;
    
    total += abs(buffer1->currentPosition - cur->data);
    cur = cur->next;

    while (cur != NULL) {
        total += abs(cur->data - cur->prev->data);
        cur = cur->next;
    } 
    return total;
}

int SSTF(Buffer1* buffer1) {
    
    LinkedList* unvisited = copyLinkedList(buffer1->requestList);
    LinkedListNode* cur;

    int total = 0;
    int curPosition = buffer1->startingPosition;
    LinkedListNode* potentialNode;
    int curMin;

    printf("b4");

    while (unvisited->head != NULL) {
        cur = unvisited->head;

        curMin = abs(curPosition - cur->data);
        potentialNode = cur;
        cur = cur->next;

        while (cur != NULL) {
            if (abs(curPosition - cur->data) < curMin) {
                curMin = abs(curPosition - cur->data);
                potentialNode = cur;
            }
            cur = cur->next;
        }
        
        total += abs(curPosition - potentialNode->data);
        curPosition = potentialNode->data;
        removeNode(unvisited, potentialNode);
    }
    freeLinkedList(unvisited);
    
    return total;
}

