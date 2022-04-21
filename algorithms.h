#ifndef ALGORITHMS_H
    #define ALGORITHMS_H
    
    #include "buffer1.h"
    #include "linkedlist.h"

    typedef int (*schedulingAlg)(Buffer1* buffer1);

    int FCFS(Buffer1* buffer1);
    int SSTF(Buffer1* buffer1);
    int SCAN(Buffer1* buffer1);
    int CSCAN(Buffer1* buffer1);
    int LOOK(Buffer1* buffer1);
    int CLOOK(Buffer1* buffer1);


    typedef void (*restartSearchFunction)(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* Total);

    void _SCANRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* Total);
    void _CSCANRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* Total);
    void _LOOKRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* Total);
    void _CLOOKRestart(int* maxSize, int* curPosition, int* prevPosition, directionType* direction, int* Total);

    
    int _iterateThroughCylinders(Buffer1* buffer1, restartSearchFunction restart);

#endif

