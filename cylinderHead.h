#ifndef CYLINDERHEAD_H
    #define CYLINDERHEAD_H
    
    #define ASCENDING 0
    #define DESCENDING 1
    typedef int directionType;

    typedef struct {
        int total;
        int currentPosition;
        directionType direction;
    } CylinderHead;

#endif

