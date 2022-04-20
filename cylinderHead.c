#include <stdio.h>
#include <stdlib.h>

#include "cylinderHead.h"

CylinderHead* emptyCylinderHead(void) {
    CylinderHead* head = (CylinderHead*)malloc(sizeof(CylinderHead));

    head->total = 0;
    head->currentPosition = 0;
    head->direction = 0;

    return head;
}
