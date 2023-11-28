#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
Heap::Heap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}
  
// Inserts a new key 'k'
void Heap::insertKey(int k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
  
    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
  
    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)] > harr[i])
    {
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}
  
// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void Heap::decreaseKey(int i, int new_val)
{
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i])
    {
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}
  
// Method to remove minimum element (or root) from min heap
int Heap::extractMin()
{
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
  
    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    Heapify(0);
  
    return root;
}
  
  
// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void Heap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();
}
  
// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void Heap::Heapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        Heapify(smallest);
    }
}
  
// A utility function to swap two elements
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


  
