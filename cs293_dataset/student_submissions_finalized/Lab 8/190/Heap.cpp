#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{
	// insert your code here

 // Base case:
    if( noOfNodes == 0 ){
        // root is null right now.
        root = new TreeNode(t);
        
        return;
    }

    // putting newnode at nfi
    nfi->object = t;











    // lastNode will be the newnode
    lastNode = nfi;




    // TODO update nfi ::::::::::::::::::::::::::::::::::::::
    assert(nfi->parent != nullptr);


    
   
    // I will climb up the heap as long as I go leftwards
    // As soon as a path to left appears I will take that path and insert at leftmostNode of that subtree.
    // In case I reach root before it happens, I will insert it at leftmostNode of the full heap.

    TreeNode* c = nfi->parent;
    while( c->parent != nullptr ){
        if (c->parent->left == c){
            c = c->parent->right;
            // c can be null only from here
            break;
        }

        // End updates
        c = c->parent;
    }

    // In case c is null,  we got our nfi
    if(c == nullptr) nfi == c;
    else{
        nfi = leftmostNode(c);
    }     

    


    // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	return;
	return;
}

template <typename T>
void Heap<T>::delMax()
{

	// insert your code here

	return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

	// insert your code here

	return;
}
