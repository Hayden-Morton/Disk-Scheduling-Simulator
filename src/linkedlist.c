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

void removeNode(LinkedList* list, LinkedListNode* node){

    if ( (list->head == node) && (list->tail == node) ) {
        list->head = NULL;
        list->tail = NULL;
    } else if (list->head== node) {
        node->next->prev = NULL;
        list->head = node->next;
    } else if (list->tail == node) {
        node->prev->next = NULL;
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    node->next = NULL;
    node->prev = NULL;
    freeNode(node);
}

LinkedList* copyLinkedList(LinkedList* orig) {
    LinkedList* copy = createLinkedList();
    LinkedListNode* cur = orig->head;
    while (cur != NULL) {
        insertLast(copy, cur->data);
        cur = cur->next;
    }
    return copy;
}

void freeLinkedList(LinkedList* list){   /*frees the entire linkedListi, depending on the type data it holds*/
    freeNode(list->head); /*free all the nodes first*/
    free(list);
    list = NULL;
}

void freeNode(LinkedListNode* node){ /*frees the nodes, depending on the type of data it holds*/
    if (node != NULL){  /*Recursive call, going though all the nodes*/
        freeNode(node->next); 
        free(node); /*frees the node itself*/
        node = NULL;
    }
}
