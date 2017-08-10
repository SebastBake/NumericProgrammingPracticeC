/*
Used as practice by Sebastian Baker for Unimelb - Numerical Programming for Engineers
==========================================================================================
Lecture 2, Ex 4

Download linkedlist.c and implement the function:
    insert_after(list t* l,node t* n,data t d)
which inserts element d after node node in the list.

Write some test code to make sure your implementation is correct.
==========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* data type */
typedef struct {
    int r;
    int g;
    int b;
} rgb_t;

/* node type */
typedef struct node node_t;

struct node {
    void* data;
    node_t* next;
};

/* linked list type */
typedef struct {
    int num_elements;
    node_t* head;
    node_t* tail;
    void (*del)(void*);
} list_t;

/* print the RGB tuple */
void rgb_print(void* d)
{
    assert(d != NULL);
    rgb_t* rd = (rgb_t*)d;
    printf("(%.3d,%.3d,%.3d)\n", rd->r, rd->g, rd->b);
}

/* process all elements in the list */
void list_process_all(node_t* p, void (*process)(void*))
{
    while (p) {
        process(p->data);
        p = p->next;
    }
}

/* remove node at the front of the list */
void* list_pop_front(list_t* list)
{
    assert(list != NULL);
    assert(list->head != NULL);
    assert(list->num_elements > 0);
    
    node_t* old = list->head;
    list->head = list->head->next;
    void* d = old->data;
    free(old);

    list->num_elements--;
    if (list->num_elements == 0) {
        list->head = NULL;
        list->tail = NULL;
    }

    

    return d;
}

/* add node add the front of the list */
void list_push_front(list_t* list, void* d)
{
    assert(list != NULL);
    node_t* new = (node_t*)malloc(sizeof(node_t));
    assert(new);
    new->data = d;
    new->next = list->head;
    list->head = new;
    if (list->tail == NULL)
        list->tail = new;
    list->num_elements++;
}

/* add node add the back of the list */
void list_push_back(list_t* list, void* d)
{
    assert(list != NULL);

    // Create new node
    node_t* new = (node_t*)malloc(sizeof(node_t));
    assert(new != NULL);
    new->data = d;
    new->next = NULL;

    // Insert new node at the end of the List
    if  (list->tail == NULL || list->head == NULL) {
        list->tail = new;
        list->head = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
    list->num_elements++;
}

/* inserts element d after node node in the list */
void list_insert_after(list_t* list, node_t* insertAfter, void* d)
{
    assert(list != NULL);
    assert(insertAfter != NULL);

    // Find place to insert node
    node_t *insertBefore = insertAfter->next;

    // create and insert new node
    node_t *newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);
    list->num_elements++;
    newNode->data = d;
    newNode->next = insertBefore;
    insertAfter->next = newNode;
}

node_t * getNodeAtIndex(list_t* list, int nodeIndex) {
    assert(list != NULL);
    assert( nodeIndex < list->num_elements);

    node_t * returnNode = list->head;
    int i;
    for (i=1; i<nodeIndex; i++) {
        returnNode = returnNode->next;
    }

    return returnNode;
}

/* TODO: implement a function which removes the
		 last element in the list 
*/
void* list_pop_back(list_t* list)
{
    assert(list != NULL);
    assert(list->num_elements > 0);

    rgb_t* endData = list->tail->data;

    // find second last element
    node_t* secondLastNode = list->head;
    while ((secondLastNode->next != list->tail) && list->num_elements != 1) {
        secondLastNode = secondLastNode->next;
    }
    free(list->tail);
    list->tail = secondLastNode;
    list->tail->next = NULL;
    list->num_elements--;
    if (list->num_elements == 0)
        list->head = NULL;
    return endData;
}

/* create a new linked list structure */
list_t* list_new(void (*delfunc)(void*))
{
    list_t* list;
    list = (list_t*)malloc(sizeof(list_t));
    assert(list != NULL);
    list->head = NULL;
    list->tail = NULL;
    list->num_elements = 0;
    list->del = delfunc;
    return list;
}

/* free all memory associated with a list */
void list_free(list_t* list)
{
    assert(list != NULL);
    while (list->num_elements) {
        void* elem = list_pop_front(list);
        list->del(elem);
    }
    free(list);
}

int main(int argc, char const* argv[])
{
    /* create new list object with regular 'free' as the del function */
    list_t* list = list_new(free);

    /* insert some elements at the back */
    printf("Num Elements: %d\n", list->num_elements);
    printf("Insert 5 random elements at the back\n");
    assert(list->num_elements == 0);
    for (int i = 0; i < 5; i++) {
        rgb_t* new_dat = (rgb_t*)malloc(sizeof(rgb_t));
        new_dat->r = rand() % 255;
        new_dat->g = rand() % 255;
        new_dat->b = rand() % 255;
        list_push_back(list, new_dat);
    }
    assert(list->num_elements == 5);
    list_process_all(list->head, rgb_print);

    /* insert some elements at the front */
    printf("Num Elements: %d\n", list->num_elements);
    printf("Insert 5 random elements at the front\n");
    for (int i = 0; i < 5; i++) {
        rgb_t* new_dat = (rgb_t*)malloc(sizeof(rgb_t));
        new_dat->r = rand() % 255;
        new_dat->g = rand() % 255;
        new_dat->b = rand() % 255;
        list_push_front(list, new_dat);
    }
    assert(list->num_elements == 10);
    list_process_all(list->head, rgb_print);

    // insert new test node 
    printf("Num Elements: %d\n", list->num_elements);
    printf("Insert test node at index 3\n");
    node_t * testNode = getNodeAtIndex(list, 3);
    rgb_t* new_dat = (rgb_t*)malloc(sizeof(rgb_t));
    new_dat->r = rand() % 255;
    new_dat->g = rand() % 255;
    new_dat->b = rand() % 255;
    list_insert_after(list, testNode, new_dat);
    assert(list->num_elements == 11);
    list_process_all(list->head, rgb_print);

    /* remove everything */
    printf("Num Elements: %d\n", list->num_elements);
    printf("Delete everything!\n");
    list_free(list);

    printf("Done!\n");
    return 0;
}