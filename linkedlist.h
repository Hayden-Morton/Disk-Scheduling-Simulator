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
    LinkedListNode* removeStart(LinkedList* list);
    

    void emptyLinkedList(LinkedList* list);
    void freeLinkedList(LinkedList* list);
    void freeNode(LinkedListNode* node);

#endif
