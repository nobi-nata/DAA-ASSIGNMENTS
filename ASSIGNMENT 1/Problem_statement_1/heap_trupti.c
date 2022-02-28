// Name:THRUPTHI N
// SRN: PES1UG20CS470
#include "heap.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header
 *as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
 */

// Initialise heap
// Set heap size to 0
// Set heap max_size to paramter max_size
// Allocate memory of max_size to the array
void init_heap(heap_t *heap, int max_size)
{
    heap->arr = (int *)malloc(sizeof(int) * max_size);
    heap->size = 0;
    heap->max_size = max_size;
}

// Insert element "key" to heap "heap"
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
void insert(heap_t *heap, int key, int *count_ptr)
{
    int c = heap->size;
    int p = (c - 1) / 2;
    while (c > 0 && ++(*count_ptr) && heap->arr[p] < key)
    {
        heap->arr[c] = heap->arr[p];
        c = p;
        p = (c - 1) / 2;
    }
    heap->arr[c] = key;
    heap->size++;
}

// Removes and Returns the maximum element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int extract_max(heap_t *heap, int *count_ptr)
{
    int max;
    if (heap->size == 0)
    {
        (*count_ptr) = 0;
        max = -1;
    }
    else
    {
        max = heap->arr[0];
        int p = 0;
        int c = 1;
        int elt = heap->arr[heap->size - 1];
        if ((c + 1) < heap->size && heap->arr[c + 1] > heap->arr[c])
            c = c + 1;
        if (heap->size < 2)
            c = -1;
        while (c >= 0 && ++(*count_ptr) && heap->arr[c] > elt)
        {
            heap->arr[p] = heap->arr[c];
            p = c;
            c = 2 * p + 1;
            if ((c + 1) < (heap->size - 1) && heap->arr[c + 1] > heap->arr[c])
                c = c + 1;
            if (c >= (heap->size - 1))
                c = -1;
        }
        heap->arr[p] = elt;
    }
    return max;
}

// Searches for the element key in the heap
// Returns the element if found, else -1
int search(const heap_t *heap, int key, int *count_ptr)
{
    int c = 0;
    int pos = -1;
    while (c < heap->size && pos == -1)
    {
        (*count_ptr)++;
        if (heap->arr[c] == key)
        {
            pos = c;
        }
        c = c + 1;
    }
    return (pos == -1) ? -1 : key;
}

// Returns the maximum value of the element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int find_max(const heap_t *heap, int *count_ptr)
{
    (*count_ptr) = 0;
    int max = heap->size ? (heap->arr[0]) : -1;
    return max;
}

// Returns the minimum value in the heap
int find_min(const heap_t *heap, int *count_ptr)
{
    int min;
    if (heap->size == 0)
    {
        (*count_ptr) = 0;
        min = -1;
    }
    else
    {
        int c = 0;
        min = heap->arr[0];
        c = (heap->size) / 2;
        c = c + 1;
        while (c < heap->size)
        {
            (*count_ptr)++;
            if (heap->arr[c] < min)
                min = heap->arr[c];
            c++;
        }
    }
    return min;
}

// Clears the heap for reuse
void clear_heap(heap_t *heap)
{
    heap->size = 0;
}

// Frees all resources acquired to initialize heap
void free_heap(heap_t *heap)
{
    free(heap->arr);
    heap->arr = NULL;
}