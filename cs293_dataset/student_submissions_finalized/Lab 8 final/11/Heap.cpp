#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
void Heap<T>::Heapify(TreeNode<T>* root) { 
    if (root==nullptr) return ; //base case
    else if (root->left == nullptr)  return ; //no child
    else if (root->right == nullptr) { //only left child
         if ( !(root->left->object < root->object) ) { 
            swap(root->object,root->left->object);  
            Heapify(root->left); //swap and heapify left child 
         }
    } 
    else { 
        T maxi = root->left->object ;  //maximum of two childs 
        if ( root->left->object < root->right->object) maxi = root->right->object ;   
        if ( !(root->object < maxi) ) return ; //if root is maximum , then done 
        else if ( !(root->left->object < maxi ) )  {  // else left is maximum
            swap(root->object,root->left->object);  
            Heapify(root->left);
        }
        else if  ( !(root->right->object < maxi) ) { //else right is maximum
            swap(root->object,root->right->object);  
            Heapify(root->right);
        }
        else {;}
    } 
}

template<typename T>
TreeNode<T>* Heap<T>::elementAtIndex( int i ) { 
     //recursive function to give the element at a given index 
     if (i == 0 ) return root ; 
     if ( i%2 == 0 ) return elementAtIndex( (i-1)/2 )->right ; //recursively find its parent 
     else return elementAtIndex( (i-1)/2 )->left ;  
}

template<typename T>
void Heap<T>::insert(T obj) { //insert function 
  TreeNode<T>* curr = new TreeNode<T>(obj) ; // the new node to be inserted 
  if (root == nullptr)  { root = curr; lastIndex = 0 ;  return ;  } //base case

  lastIndex++;  // the variable to keep track of the index of the node that was last inserted 
  TreeNode<T>* parent = elementAtIndex( (lastIndex-1)/2 ); //parent 
  curr->parent = parent ; 
  if ( lastIndex%2 == 0 ) parent->right = curr ; 
  else parent->left = curr ; 
  
  while ( parent != nullptr && !(curr->object < parent->object) ) {
     //swap until its not greater than its parent or its parent is null
     swap(curr->object , parent->object);
     curr = parent ; 
     parent = parent->parent ; 
  }

  return ; 
}

template<typename T>
void Heap<T>::delMax() {
  T max  = root->object ; 
  if ( root == nullptr ) return  ; 
  if ( lastIndex == 0 ) { //base case 
       root = nullptr ; 
       lastIndex = -1 ;
       return  ; 
  }
  //if its not root , exchange with last index node and delete the last index node 
  TreeNode<T>* last =  elementAtIndex(lastIndex); 
  swap(last->object , root->object) ; 

  if (lastIndex%2 == 0 ) last->parent->right = nullptr ; 
  else last->parent->left = nullptr ;  

  delete last ; 
  lastIndex -- ; 
  Heapify(root); //heafiy the root element 
  return  ;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T>* root) { 

}

