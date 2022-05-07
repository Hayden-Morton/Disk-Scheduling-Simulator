/*
File: algorithms.c

Author: Hayden Morton
Course: Operating Systems
Date: Semester 1 2022

Summary
    Contains 6 disk schedling algorithms which compute the total movement of a disk head, depending on the type.


*/
#include <stdio.h>
#include <stdlib.h>

#include "buffer1.h"
#include "linkedlist.h"
#include "algorithms.h"

int FCFS(Buffer1* buffer1) { /*First Come First Served*/
    
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

int SSTF(Buffer1* buffer1) { /*Shorted Seek Time First*/
    
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


int _iterateThroughCylinders(Buffer1* buffer1, restartSearchFunction restart) { /*repeated use for SCAN, CSCAN, LOOK, and CLOOK*/
    
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
        
        if ((curPosition > buffer1->total -1) || (curPosition < 0)) {
            restart(&(buffer1->total), &curPosition, &prevPosition, &cylinderDirection, &total);
        }
    }
    freeLinkedList(unvisited);
    
    return total;
}

int SCAN(Buffer1* buffer1) { /*Scan: directional scan until end of cylinder then reverse*/
    return _iterateThroughCylinders(buffer1, _SCANRestart); /*Wrapper */
}
void _SCANRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* total) { /*restart condition for when it reverses or wraps, same for all others*/
    *direction *= -1;

    if (*curPosition > *maxSize -1) {
        *curPosition = *maxSize - 1;
    } else {
        *curPosition = 0;
    }

    *total += abs(*curPosition - *prevPosition);
    *prevPosition = *curPosition;
}


int CSCAN(Buffer1* buffer1) { /*Cylical Scan: direction scan until end of cylinder then wrap to other side*/
    return _iterateThroughCylinders(buffer1, _CSCANRestart); /*Wrapper */
}
void _CSCANRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* total) {
    if (*curPosition > *maxSize -1) {
        *curPosition = *maxSize - 1;
    } else {
        *curPosition = 0;
    }
    *total += abs(*curPosition - *prevPosition) + *maxSize -1;
    *curPosition = *maxSize -1 - *curPosition;
    *prevPosition = *curPosition;
}


int LOOK(Buffer1* buffer1) { /*Look: directional scan up to end of requests then reverse*/
    return _iterateThroughCylinders(buffer1, _LOOKRestart);/*Wrapper*/
}
void _LOOKRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* total) {
    *direction *= -1;
}


int CLOOK(Buffer1* buffer1) {/*Cyclic Look: directional scan up to end of requests then wrap to other side*/
    return _iterateThroughCylinders(buffer1, _CLOOKRestart);/*Wrapper*/
}
void _CLOOKRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* total) {
    *curPosition = *maxSize -1 - *curPosition;
}
