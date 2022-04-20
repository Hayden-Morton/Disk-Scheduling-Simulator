#ifndef LINKEDLIST_H
    #define LINKEDLIST_H

    typedef struct LinkedListNode{  
        void* data; 
        struct LinkedListNode* next;
        struct LinkedListNode* prev;
    } LinkedListNode;
    
    typedef struct {    
        LinkedListNode* head;
        LinkedListNode* tail;
        int amount; 
    } LinkedList;
    
    typedef void (*listFunc)(void* data);   
    
    LinkedList* createLinkedList(void);

    void insertLast(LinkedList* list, void* data);
    LinkedListNode* removeStart(LinkedList* list);
    

    void emptyLinkedList(LinkedList* list, listFunc freeData);
    void freeLinkedList(LinkedList* list, listFunc freeData);
    void freeNode(LinkedListNode* node, listFunc freeData);

#endif
