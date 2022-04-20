
#include <stdlib.h>
#include "linkedlist.h"

LinkedList* createLinkedList(void){     /*creates and allocates the LinkedList, returning it*/
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList)); /*allocates the list*/
    (*list).head = NULL;
    list->tail = NULL;  
    list->amount = 0;

    return list;
}



void insertLast(LinkedList* list, int data){  /*creates and inserts a list node to the end of the Linkedlist, with given the data*/
    
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));  /*allocates the listNode*/
    
    newNode->data = data;   
    
    newNode->next = NULL;  
    newNode->prev = list->tail;

    if (list->head == NULL){    /*if the list is empty*/
        list->head = newNode;   
    }
    else{
        list->tail->next = newNode; 
    }
    list->tail = newNode;   
    list->amount += 1;  
}

LinkedListNode* removeStart(LinkedList* list){    /*returns the head of the list, removing it from the list*/
    LinkedListNode* temp;  
   
    temp = list->head;
    if (temp->next != NULL){    /*if this is tha last node in the list*/
        list->head = list->head->next;  /*set the head to be the  second value*/
        
        temp->next = NULL;
        list->head->prev = NULL;    /*set the new head to no longer point to the removed value*/
    }
    else{
        list->head = NULL;
        list->tail = NULL;
    }
    list->amount -= 1;  /*because the list now has less values*/

    return temp;
}


void freeLinkedList(LinkedList* list){   /*frees the entire linkedListi, depending on the type data it holds*/
    freeNode(list->head); /*free all the nodes first*/
    free(list);
}

void freeNode(LinkedListNode* node){ /*frees the nodes, depending on the type of data it holds*/
    if (node != NULL){  /*Recursive call, going though all the nodes*/
        freeNode(node->next); 
        free(node); /*frees the node itself*/
    }
}
