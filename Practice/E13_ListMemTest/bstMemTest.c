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
#define BST_ROOT_DEPTH 1

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

/*======= memory funcs =======*/

static uint64_t cur_mem_bytes = 0;
static uint64_t peak_mem_bytes = 0;

void* mymalloc(size_t size)
{
	size_t new_size = size + sizeof(uint64_t);
	void* mem = malloc(new_size);
	assert(mem != NULL);
	uint64_t* mem64 = (uint64_t*)mem;
	*mem64 = size;
	mem64++;
	cur_mem_bytes += size;
	if (cur_mem_bytes > peak_mem_bytes)
		peak_mem_bytes = cur_mem_bytes;
	return (void*)mem64;
}

void myfree(void* ptr)
{
	uint64_t* mem64 = (uint64_t*)ptr;
	mem64--;
	size_t bytes = *mem64;
	cur_mem_bytes -= bytes;
	void* real_ptr = (void*)mem64;
	free(real_ptr);
}

void print_mem_usage()
{
	printf("MB used:    current = %f,  peak = %f\n",
	(double)cur_mem_bytes/1000000, (double)peak_mem_bytes/1000000);
}

/*======= end mem usage funcs =======*/

/* create a new empty bst structure */
bst_t* bst_new(void (*delfunc)(void*), int (*cmpfunc)(void*, void*))
{
	bst_t* bst;
	bst = (bst_t*)mymalloc(sizeof(bst_t));
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
		myfree(n);
		bst->num_elements--;
	}
}

/* free all memory associated with a bst */
void bst_free(bst_t* bst)
{
	assert(bst != NULL);
	bst_free_subtree(bst, bst->root);
	myfree(bst);
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
	node_t* new_node = (node_t*)mymalloc(sizeof(node_t));
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

int bst_height_rec(node_t* n)
{
	if (n) {
		int left_height = bst_height_rec(n->left);
		int right_height = bst_height_rec(n->right);
		return MAX(left_height, right_height) + 1;
	}
	return -1;
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
	bst_t* bst = bst_new(myfree, intcmp);
	 int height;

	/* generate sample data  */
	int i=1;
	while (i++) {
		int* int_val = (int*)mymalloc(sizeof(int));
		*int_val = rand();
		bst_insert(bst, int_val);
		height = bst_height(bst);
		printf("\nTree size:  elements = %d,  height = %d\n", bst->num_elements, height);
		print_mem_usage();
	}
	return 0;
}