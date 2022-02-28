// Name: Laxmikant Bhujang Gurav
// SRN: PES1UG20CS658
#include "heap.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header
 *as static
 ** Do not use static variables
 ** All occurences of( count_ptr) indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
 */

// Initialise heap
// Set heap size to 0
// Set heap max_size to paramter max_size
// Allocate memory of max_size to the array
void init_heap(heap_t *heap, int max_size)
{
    heap->size = 0;                                    // Set heap size to 0
    heap->max_size = max_size;                         // Set heap max_size to paramter max_size
    heap->arr = (int *)malloc(sizeof(int) * max_size); // Allocate memory of max_size to the array
}

// Insert element "key" to heap "heap"
// and store the number of key comparisons made in the
// location pointed to by( count_ptr).
void insert(heap_t *heap, int key, int(*count_ptr))
{
    int i = heap->size, check = 0;
    heap->arr[heap->size] = key;
    heap->size++;
    while (check == 0) // flag to check if the key is greater than parent
    {
        (*count_ptr) += 1;
        if (heap->arr[i] > heap->arr[(i - 1) / 2]) // if child value is greater than parent then swaps child and parent
        {
            int temp = heap->arr[i];
            heap->arr[i] = heap->arr[(i - 1) / 2];
            heap->arr[(i - 1) / 2] = temp; // parent and child is swapped
            i = (i - 1) / 2;               // decrement i to parent's position and compare above elements in the heap
        }
        else
        {
            check = 1; // if child value is lesser than parent then no swap ,while loop terminate
        }
    }
}

// *Removes and Returns* the maximum element in the heap
// and store the number of key comparisons made in the
// location pointed to by( count_ptr).
int extract_max(heap_t *heap, int(*count_ptr))
{
    int max;
    if (heap->size == 0)
    {
        max = -1;
    }
    else
    {
        max = heap->arr[0]; // element to be deleted
        heap->size--;
        int l;
        int i = 0;
        heap->arr[0] = heap->arr[heap->size]; // make last element as first
        heap->arr[heap->size] = -1;
        // heapification of the heap using while loop
        while (heap->max_size > 2 * i + 1 && heap->arr[2 * i + 1] != -1)
        {
            (*count_ptr) += 1; // count for while loop
            if (heap->arr[i] < heap->arr[2 * i + 1])
            {
                (*count_ptr) += 1; // count for above if statement
                if (heap->arr[2 * i + 2] > heap->arr[2 * i + 1])
                {
                    // count for above if statement
                    (*count_ptr) += 1;
                    l = heap->arr[i];
                    heap->arr[i] = heap->arr[2 * i + 2];
                    heap->arr[2 * i + 2] = l;
                    i = 2 * i + 2;
                }
                else
                {
                    // count for last comparison in above if statement
                    (*count_ptr) += 1;
                    l = heap->arr[i];
                    heap->arr[i] = heap->arr[2 * i + 1];
                    heap->arr[2 * i + 1] = l;
                    i = 2 * i + 1;
                }
            }
            else
            {
                // count for last comparison in above if statement
                (*count_ptr) += 1;
                i = heap->max_size;
            }
        }
        (*count_ptr) += 1; // count for last comparison in while loop
    }
    return max;
}

// Searches for the element key in the heap
// Returns the element if found, else -1
int search(const heap_t *heap, int key, int(*count_ptr))
{
    int k = -1;
    for (int i = 0; i < heap->size; i++)
    {
        (*count_ptr) += 1; // count for above statement
        if (heap->arr[i] == key)
        {
            k = i;
        }
    }
    (*count_ptr) += 1; // count for last comparison of for loop
    return k;
}

// Returns the maximum value of the element in the heap
// and store the number of key comparisons made in the
// location pointed to by( count_ptr).
int find_max(const heap_t *heap, int(*count_ptr))
{
    int k = -1;
    if (heap->size > 0)
        k = heap->arr[0];
    return k;
}

// Returns the minimum value in the heap
int find_min(const heap_t *heap, int(*count_ptr))
{
    int k = -1;
    if (heap->size > 0)
    {
        k = heap->arr[heap->size / 2];
        int i;
        for (i = 1 + heap->size / 2; i < heap->size; i++)
        {
            (*count_ptr) += 1; // count for above statement
            if (k > heap->arr[i])
            {
                k = heap->arr[i];
            }
        }
        (*count_ptr) += 1; // count for last comparison of for loop
    }
    return k;
}

// Clears the heap for reuse
void clear_heap(heap_t *heap)
{
    for (int i = 0; i < (heap->size); i++)
        heap->arr[i] = -1; // initialize each element to -1
    heap->size = 0;        // mark heap size zero
}

// Frees all resources acquired to initialize heap
void free_heap(heap_t *heap)
{
    free(heap->arr);  // free the array
    heap->arr = NULL; // set the pointer to NULL
}
