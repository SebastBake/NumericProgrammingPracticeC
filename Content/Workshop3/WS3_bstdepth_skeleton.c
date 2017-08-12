/* For this exercise you must compute the average depth of the BST provided
   The empty spaces are indicated by the comment of the type //
   Compile with -lm for math stuff
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

int intcmp(void* a, void* b)
{
    return (*(int*)a) - (*(int*)b);
}
// Implement this function next (3)
int bst_depth_sum(node_t* n, int depth)
{
    if (n) {
    	// compute the left depth here (4)
        int left_depth;
        // compute the right depth here (5)
        int right_depth;
        // return the sum of depths here (6)
        
    }
    return 0;
}

int bst_height_rec(node_t* n)
{
    if (n) {
        int left_height = bst_height_rec(n->left);
        int right_height = bst_height_rec(n->right);
        return MAX(left_height, right_height) + 1;
    }
    return -1;
}
// Implement this function (0)
double bst_average_depth(bst_t* bst)
{
    if (bst->num_elements > 0) {
        // call the function bst_depth_sum here (1)
    	int depth_sum;
        // return the average depth here (2)
        
    }
    return 0;
}

int bst_height(bst_t* bst)
{
    if (bst->num_elements > 0) {
        int h = bst_height_rec(bst->root);
        return h;
    }
    return 0;
}

int main(int argc, char const* argv[])
{
    /* create a new city bst */
    bst_t* bst = bst_new(free, intcmp);

    /* generate sample data  */
    int n = 8192 * 1024;
    for (int i = 0; i < n; i++) {
        int* int_val = (int*)malloc(sizeof(int));
        *int_val = rand();
        bst_insert(bst, int_val);
    }

    /* print depth */
    double avg_depth = bst_average_depth(bst);
    int height = bst_height(bst);
    printf("avg_depth = %.2f\n", avg_depth);
    printf("height = %d\n", height);
    printf("log2(n) = %.2f\n", ceil(log2(n + 1)));

    return 0;
}