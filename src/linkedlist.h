#ifndef LINKEDLIST_H
    #define LINKEDLIST_H

    typedef struct LinkedListNode{  
        int data; 
        struct LinkedListNode* next;
        struct LinkedListNode* prev;
    } LinkedListNode;
    
    typedef struct {    
        LinkedListNode* head;
        LinkedListNode* tail;
        int amount; 
    } LinkedList;
    
    
    LinkedList* createLinkedList(void);

    void insertLast(LinkedList* list, int data);
    void removeNode(LinkedList* list, LinkedListNode* node);

    LinkedList* copyLinkedList(LinkedList* orig);

    void freeLinkedList(LinkedList* list);
    void freeNode(LinkedListNode* node);

#endif
