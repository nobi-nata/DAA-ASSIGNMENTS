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

// Recursive insert function
static void insert_ele(bst_t *bst, node_t *p, node_t *temp, int *count_ptr)
{
    if (p == NULL)
    {
        bst->root = temp; // insert first node
        p = temp;
        return;
    }

    if (p->key <= temp->key)
    {
        // Incrementing the counter as comparison took place and has entered IF block
        (*count_ptr) += 1;
        if (p->right == NULL)
        {
            p->right = temp;
        }
        else
        {
            insert_ele(bst, p->right, temp, count_ptr);
        }
    }
    else
    {
        // Imcrementing the counter as comparison took place in IF statement condition and then has entered ELSE block
        (*count_ptr) += 1;
        if (p->left == NULL)
        {
            p->left = temp;
        }
        else
        {
            insert_ele(bst, p->left, temp, count_ptr);
        }
    }
}
// Inserts element key into the Binary search tree
// Stores the number of comparisons at the location
// pointed by count_ptr
void insert(bst_t *tree, int key, int *count_ptr)
{
    node_t *temp = malloc(sizeof(node_t));
    temp->left = NULL;
    temp->right = NULL;
    temp->key = key;
    // calling the recursive insert function
    insert_ele(tree, tree->root, temp, count_ptr);
}
// Recursive delete function
static node_t *delete (node_t *p, int key, int *count_ptr)
{
    node_t *temp;
    if (p == NULL)
        return p;
    else if (p->key < key)
    {
        // Incrementing the counter as comparison took place in IF ELSE statement condition and then has entered IF ELSE block
        (*count_ptr) += 1;
        if (p->right == NULL)
        {
            return NULL;
        }
        p->right = delete (p->right, key, count_ptr);
    }
    else if (p->key > key)
    {
        // Incrementing the counter as comparison took place in IF ELSE statement condition and then has entered IF ELSE block
        // incrementing by 2 becoz to comparisons took place
        (*count_ptr) += 2;
        if (p->left == NULL)
        {
            return NULL;
        }
        p->left = delete (p->left, key, count_ptr);
    }
    else
    {
        // Incrementing the counter as comparison took place in both IF ELSE statement condition and then has entered ELSE block
        // incrementing by 2 becoz to comparisons took place
        (*count_ptr) += 2;
        if (p->left == NULL)
        {
            temp = p->right;
            free(p);
            return temp;
        }
        else if (p->right == NULL)
        {
            temp = p->left;
            free(p);
            return temp;
        }
        else
        {
            temp = p->right;
            while (temp->left != NULL)
            {
                // incrementing the counter as got into the loop
                (*count_ptr) += 1;
                temp = temp->left;
            }
            // incrementing the counter for last comparison
            (*count_ptr) += 1;
            p->key = temp->key;
            p->right = delete (p->right, temp->key, count_ptr);
        }
    }
    return p;
}
// Delete key from the BST
// Replaces node with in-order successor
void delete_element(bst_t *tree, int key, int *count_ptr)
{
    tree->root = delete (tree->root, key, count_ptr);
}
// Recursive search function
static int search_ele(node_t *p, int key, int *count_ptr)
{
    if (p == NULL)
        return -1;
    if (p->key == key)
    {
        return p->key;
    }
    else if (key < p->key)
    {
        // Incrementing the counter as comparison took place in both IF ELSE statement condition and then has entered IF ELSE block
        (*count_ptr) += 1;
        if (p->left == NULL)
        {
            return -1;
        }
        else
        {
            return search_ele(p->left, key, count_ptr);
        }
    }
    else
    {
        // Incrementing the counter as comparison took place in both IF ELSE statement condition and then has entered ELSE block
        (*count_ptr) += 1;
        if (p->right == NULL)
        {
            return -1;
        }
        else
        {
            return search_ele(p->right, key, count_ptr);
        }
    }
}
// Searches for the element key in the bst
// Returns the element if found, else -1
int search(const bst_t *tree, int key, int *count_ptr)
{
    return search_ele(tree->root, key, count_ptr);
}
// Recursive findMaximum function
static int findMaximum(node_t *p, int *count_ptr)
{
    if (p->right != NULL)
    {
        (*count_ptr) += 1;
        return findMaximum(p->right, count_ptr);
    }
    (*count_ptr) += 1;
    return p->key;
}
// Returns the maximum element in the BST
int find_max(const bst_t *tree, int *count_ptr)
{
    if (tree->root == NULL)
        return -1;
    return findMaximum(tree->root, count_ptr);
}
// Recursive free function
static void free_b(node_t *p)
{
    if (p != NULL)
    {
        free_b(p->left);
        free_b(p->right);
        free(p);
    }
}
// Deletes all the elements of the bst
void free_bst(bst_t *bst)
{
    if (bst->root != NULL)
    {
        free_b(bst->root);
        bst->root = NULL;
        free(bst->root);
    }
}

// Deletes all the elements if the bst and ensures it can be used again
void clear_bst(bst_t *bst)
{
    if (bst->root != NULL)
    {
        free_b(bst->root);
        bst->root = NULL;
    }
}
