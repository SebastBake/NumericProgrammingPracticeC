/* For this exercise you must implement a function to 
   print a BST in ascending and descending order
   Chitrarth Lav, 2 August 2017
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define BST_SUCCESS 1
#define BST_FAILURE 0

#define BST_PREORDER 0
#define BST_INORDER 1
#define BST_POSTORDER 2

/* node type */
typedef struct node node_t;

struct node {
    void* data;
    node_t* left;
    node_t* right;
};

/* bst type */
typedef struct {
    int num_elements;
    node_t* root;
    void (*del)(void*);
    int (*cmp)(void*, void*);
} bst_t;

/* create a new empty bst structure */
bst_t* bst_new(void (*delfunc)(void*), int (*cmpfunc)(void*, void*))
{
    bst_t* bst;
    bst = (bst_t*)malloc(sizeof(bst_t));
    assert(bst != NULL);
    bst->root = NULL;
    bst->num_elements = 0;
    bst->del = delfunc;
    bst->cmp = cmpfunc;
    return bst;
}

/* free all memory assocated with a subtree */
void bst_free_subtree(bst_t* bst, node_t* n)
{
    assert(bst != NULL);
    if (n) {
        bst_free_subtree(bst, n->left);
        bst_free_subtree(bst, n->right);
        bst->del(n->data);
        free(n);
        bst->num_elements--;
    }
}

/* free all memory associated with a bst */
void bst_free(bst_t* bst)
{
    assert(bst != NULL);
    bst_free_subtree(bst, bst->root);
    free(bst);
}

/* insert a new element into the bst */
int bst_insert(bst_t* bst, void* d)
{
    assert(bst != NULL);
    assert(d != NULL);
    node_t* parent = NULL;
    node_t* tmp = bst->root;
    while (tmp) {
        parent = tmp;
        if (bst->cmp(tmp->data, d) > 0) { // element is smaller
            tmp = tmp->left;
        }
        else if (bst->cmp(tmp->data, d) < 0) { // element is bigger
            tmp = tmp->right;
        }
        else {
            /* ALREADY EXISTS! -> do nothing and return ERROR */
            return BST_FAILURE;
        }
    }

    /* insert as child of parent */
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    assert(new_node != NULL);
    new_node->data = d;
    new_node->left = NULL;
    new_node->right = NULL;
    if (parent != NULL) {
        if (bst->cmp(parent->data, d) > 0) { // element is smaller
            assert(parent->left == NULL);
            parent->left = new_node;
        }
        else {
            assert(parent->right == NULL);
            parent->right = new_node;
        }
    }
    else {
        assert(bst->root == NULL);
        bst->root = new_node;
    }
    bst->num_elements++;

    return BST_SUCCESS;
}
// Implement this function first (0)
void bst_reverse_print(node_t* n, void (*print)(void*))
{
    if (n) {
    	// Recursive call to move through nodes (1)

    }
}
// Implement this function next (2)
void bst_print(node_t* n, void (*print)(void*))
{
    if (n) {
    	// Recursive call to move through the nodes (3)

    }
}

int intcmp(void* a, void* b)
{
    return (*(int*)a) - (*(int*)b);
}

void print_int(void* a)
{
    printf("%d\n", *((int*)a));
}

int main(int argc, char const* argv[])
{
    /* create a new city bst */
    bst_t* bst = bst_new(free, intcmp);

    /* generate sample data  */
    for (int i = 0; i < 50; i++) {
        int* int_val = (int*)malloc(sizeof(int));
        *int_val = rand();
        bst_insert(bst, int_val);
    }

    /* print in reverse order */
    bst_reverse_print(bst->root, print_int);
    printf("\n\n");

    /* print in order */
    bst_print(bst->root, print_int);

    return 0;
}