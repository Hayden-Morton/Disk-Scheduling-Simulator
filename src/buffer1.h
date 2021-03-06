#ifndef BUFFER1_H
    #define BUFFER1_H
    
    #include "linkedlist.h"

    typedef int directionType;
    #define ASCENDING 1
    #define DESCENDING -1

    typedef struct {
        int total;
        int startingPosition;
        directionType direction;
        LinkedList* requestList;
    } Buffer1;

    Buffer1* allocatedBuffer1(void);
    void refreshBuffer1(Buffer1* buffer1);
    void freeBuffer1(Buffer1* buffer1);
#endif

