#ifndef SIMULATOR_H
    #define SIMULATOR_H

    #include "buffer1.h"
    #include "algorithms.h"

    typedef struct {
        int value;
        int threadId;
    } Buffer2;

    typedef struct {
        int threadId;
        Buffer1* buffer1;
        Buffer2* buffer2;
        schedulingAlg schedulAlg;
        bool* continueStatus;
    } threadArguments;

    void* thRoutine(void* args);

#endif
