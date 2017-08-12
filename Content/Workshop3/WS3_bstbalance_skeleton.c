/* For this exercise you must return a balanced BST from an 
   array with n elements in sorted order
   compile with -lm for math stuff
   Chitrarth Lav, 2 August 2017
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define BST_SUCCESS 1
#define BST_FAILURE 0

#define BST_PREORDER 0
#define BST_INORDER 1
#define BST_POSTORDER 2

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

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
    int (*cmp)(const void*, const void*);
} bst_t;

/* create a new empty bst structure */
bst_t* bst_new(void (*delfunc)(void*), int (*cmpfunc)(const void*, const void*))
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

int intcmp(const void* a, const void* b)
{
    return (*(int*)a) - (*(int*)b);
}
// Implement this function (0)
void perfect_insert(bst_t* bst, int* array, int low, int high)
{
    if (low <= high) {
    	// Choose root from array and insert

    }
}

void no_free(void* v)
{
}

int make_unique(int* array, int n)
{
    int dest = 0;
    int itr = 1;
    while (itr != n) {
        if (array[dest] != array[itr]) {
            array[++dest] = array[itr];
        }
        itr++;
    }
    return dest;
}

int main(int argc, char const* argv[])
{
    /* create a new city bst */
    bst_t* bst = bst_new(no_free, intcmp); // memory is held by the array itself

    /* generate sample data  */
    int n = 8192 * 1024;
    int* array = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        array[i] = rand();
    }

    /* sort data */
    qsort(array, n, sizeof(int), intcmp);
    /* make sure all ints only occur once */
    n = make_unique(array, n);

    /* perfect insert */
    perfect_insert(bst, array, 0, n - 1);
    printf("num_elements = %d\n", bst->num_elements);
    assert(bst->num_elements == n);
    
    return 0;
}