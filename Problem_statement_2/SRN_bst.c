// Name: Laxmikant Bhujang Gurav
// SRN: PES1UG20CS658
#include "bst.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
 */

// Initializes the root of the bst
void init_bst(bst_t *bst)
{
    bst->root = NULL;
}

static void insert_ele(bst_t *p, int key, int *count_ptr)
{
    if (p == NULL)
        p->key = key;

    else if (p > key && ++*count_ptr)
    {
        insert_ele(p->left, key, count_ptr);
    }
    else if (p < key && ++*count_ptr)
    {
        insert_ele(p->right, key, count_ptr);
    }
}
// Inserts element key into the Binary search tree
// Stores the number of comparisons at the location
// pointed by count_ptr
void insert(bst_t *tree, int key, int *count_ptr)
{
    if (tree->root == NULL)
    {
        tree->root->key = key;
        return;
    }
    insert_ele(tree->root, key, c);
}

static int findMinimum(bst_t *p, int *count_ptr)
{
    if (p->left != NULL && ++*count_ptr)
    {
        findMinimum(p->left, count_ptr);
    }

    return p->key;
}
static void delete (bst_t *p, int key, int *count_ptr)
{
    node_t *temp = NULL;
    if (key < p->key && ++*count_ptr)
        p->left = delete (p->left, key, count_ptr);
    else if (key > p->key && ++*count_ptr)
        p->right = delete (p->right, key, count_ptr);
    else if (p->left == NULL) // single right child case and leaf node case
    {
        temp = p->right;
        free(p);
        return temp;
    }
    else if (p->right == NULL) // single left child case
    {
        temp = p->left;
        free(p);
        return temp;
    }
    else // replacing with inorder successor
    {
        temp = p->right;
        if (temp->left != NULL)
        {
            temp->key = findMinimum(temp, count_ptr);
        }
        p->key = temp->key;
        p->right = delete (p->right, temp->key, count_ptr);
    }
}
// Delete key from the BST
// Replaces node with in-order successor
void delete_element(bst_t *tree, int key, int *count_ptr)
{
    if (tree->root == NULL)
    {
        return;
    }
    tree->root = delete (tree->root, key, count_ptr);
}

static int search_ele(bst_t *p, int key, int *count_ptr)
{
    if (p != NULL)
    {
        if (key == p->key)
            return key;
        else if (key < p->key && ++*count_ptr)
            return search(p->left, key);
        else if (key > p->key && ++*count_ptr)
            return search(p->right, key);
    }
    return -1;
}
// Searches for the element key in the bst
// Returns the element if found, else -1
int search(const bst_t *tree, int key, int *count_ptr)
{
    return search(pt->root, key, count_ptr);
}
static int findMaximum(bst_t *p, int *count_ptr)
{
    if (p->right != NULL && ++*count_ptr)
    {
        findMaximum(p->right, count_ptr);
    }
    return p->key;
}
// Returns the maximum element in the BST
int find_max(const bst_t *tree, int *count_ptr)
{
    if (tree->root == NULL)
        return -1;
    return findMaximum(tree->root);
}

// Deletes all the elements of the bst
static void free_b(bst_t *p)
{
    if (p != NULL)
    {
        free_b(p->left);
        free_b(p->right);
        free(p);
    }
}
void free_bst(bst_t *bst)
{
    if (bst->root != NULL)
    {
        free_b(bst->root);
        bst->root = NULL;
    }
}

// Deletes all the elements if the bst and ensures it can be used again
void clear_bst(bst_t *bst)
{
    if (bst->root != NULL)
    {
        free_b(bst->root);
        // bst->root = NULL;
    }
    free(bst->root)
}
