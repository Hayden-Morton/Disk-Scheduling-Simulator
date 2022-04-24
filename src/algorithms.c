#include <stdio.h>
#include <stdlib.h>

#include "buffer1.h"
#include "linkedlist.h"
#include "algorithms.h"

int FCFS(Buffer1* buffer1) {
    
    LinkedListNode* cur = buffer1->requestList->head;
    int total = 0;
    
    total += abs(buffer1->startingPosition - cur->data);
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


int _iterateThroughCylinders(Buffer1* buffer1, restartSearchFunction restart) {
    
    LinkedList* unvisited = copyLinkedList(buffer1->requestList);
    LinkedListNode* cur;

    int total = 0;
    int curPosition = buffer1->startingPosition;
    int prevPosition = curPosition;
    int cylinderDirection = buffer1->direction;

    while (unvisited->head != NULL) {
        cur = unvisited->head;
        while (cur != NULL) {
            if (cur->data == curPosition) {
                total += abs(prevPosition - cur->data);
                prevPosition = cur->data;
                removeNode(unvisited,cur);
                cur = NULL;
            } else {
                cur = cur->next;
            }
        }
        curPosition += 1 * cylinderDirection;
        
        restart(&(buffer1->total), &curPosition, &prevPosition, &cylinderDirection, &total);
    }
    freeLinkedList(unvisited);
    
    return total;
}

int SCAN(Buffer1* buffer1) {
    return _iterateThroughCylinders(buffer1, _SCANRestart);
}
void _SCANRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* total) {
     if ((*curPosition >= *maxSize -1) || (*curPosition <= 0)) {
        *direction *= -1;
        *total += abs(*curPosition - *prevPosition);
        *prevPosition = *curPosition;
    }
}


int CSCAN(Buffer1* buffer1) {
    return _iterateThroughCylinders(buffer1, _CSCANRestart);
}
void _CSCANRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* total) {
     if ((*curPosition >= *maxSize -1) || (*curPosition <= 0)) {
        *total += abs(*curPosition - *prevPosition) + *maxSize -1;
        *curPosition = *maxSize -1 - *curPosition;
        *prevPosition = *curPosition;
    }
}


int LOOK(Buffer1* buffer1) {
    return _iterateThroughCylinders(buffer1, _LOOKRestart);
}
void _LOOKRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* total) {
     if ((*curPosition >= *maxSize -1) || (*curPosition <= 0)) {
        *direction *= -1;
    }
}


int CLOOK(Buffer1* buffer1) {
    return _iterateThroughCylinders(buffer1, _CLOOKRestart);
}
void _CLOOKRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* total) {
     if ((*curPosition >= *maxSize -1) || (*curPosition <= 0)) {
        *curPosition = *maxSize -1 - *curPosition;
    }
}








