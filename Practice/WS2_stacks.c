/* For this exercise, you must fill in the mystack_t to use arrays
   Then you must implement stack_push, stack_pop and stack_empty
   You must fill in steps 0-4
   
   Chitrarth Lav, 27 July 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_SIZE 5

/* data type */
typedef struct {
    int r;
    int g;
    int b;
} data_t;

data_t new_rgb(int r, int g, int b)
{
    data_t d;
    d.r = r;
    d.g = g;
    d.b = b;
    return d;
}

/* stack type */
typedef struct {

    /* (0) Create the struct to populate arrays */
    data_t * array;
    int top;
    int array_size;

} mystack_t;

/* create a new stack structure */
mystack_t* stack_new()
{
    mystack_t* s = (mystack_t*)malloc(sizeof(mystack_t));
    assert(s != NULL);

    s->array = (data_t*)malloc(INIT_SIZE * sizeof(data_t));
    assert(s != NULL);

    s->array_size = INIT_SIZE;
    s->top = -1;
    return s;
}

/* free all memory associated with a stack */
void stack_free(mystack_t* s)
{
    assert(s != NULL);
    assert(s->array != NULL);
    free(s->array);
    free(s);
}

/* remove item on the stack */
data_t stack_pop(mystack_t* s)
{
    assert(s != NULL);
    assert(s->array != NULL);
    assert(s->top >= 0);

    /* (1) Write here to remove item */
    data_t removedItem = s->array[s->top];
    s->top--;

    return removedItem;
}

/* add item to the stack */
void stack_push(mystack_t* s, data_t d)
{
    assert(s != NULL);
    assert(s->array != NULL);

    /* (2) Reallocate here */
    if (s->top == s->array_size - 1) {
        s->array_size= (int)(s->top)*1.5;
        s->array = (data_t*)realloc(s->array, (s->array_size)*sizeof(data_t));
        assert(s->array != NULL);
    }

    /* (3) Place item d at top of stack here */
    s->top++;
    s->array[s->top] = d;
}

int stack_empty(mystack_t* s)
{
    /* (4) Return check here */
    return s->top == -1; 
}

int stack_size(mystack_t* s)
{
    return s->top + 1;
}

int main(int argc, char const* argv[])
{
    mystack_t* s = stack_new();

    for (int i = 0; i < 5000; i++) {
        stack_push(s, new_rgb(rand() % 255, rand() % 255, rand() % 255));
        if (rand() % 3 == 0) {
            stack_pop(s);
        }
    }

    printf("%d items on the stack\n", stack_size(s));

    while (!stack_empty(s)) {
        stack_pop(s);
    }

    printf("%d items on the stack\n", stack_size(s));

    stack_free(s);

    return 0;
}
