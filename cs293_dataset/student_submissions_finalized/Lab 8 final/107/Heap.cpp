#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


template<typename T>
void Heap<T>::delLast()
{
  if(last==root)  // If only one element is in heap
  {
    delete root;  // delete root

    // set everything to nullptr
    root=nullptr;
    last=nullptr;
    nextInsert=nullptr;
    nextleftInsert=false;
    return;
  }

  TreeNode<T> *toDelete=last;

  nextInsert=last->parent;  // nextInsert will be last's parent as next insertion will take place at location from where last is deleted
  if(last->parent->left==last)
  {
    nextleftInsert=true;

    // Update last
    // Find root or a node such that last is descendant of it's left child
    while(last->parent!=nullptr && last->parent->left==last)
    {
      last=last->parent;
    }
    if(last->parent!=nullptr) // Not root
    {
      last=last->parent->left;
    }
    while(last->right!=nullptr) // New last will be rightmost descendant
    {
      last=last->right;
    }
    toDelete->parent->left=nullptr; // Set last node's left child as nullptr
  }
  else
  {
    nextleftInsert=false;
    last=last->parent->left;  // New last will be last's parent's left child
    toDelete->parent->right=nullptr;  // Set last node's right child as nullptr
  }
  delete toDelete;  // Delete last node
  return;
}


template<typename T>
void Heap<T>::insert(T obj) {
  
  // insert your code here

  TreeNode<T> *newNode=new TreeNode<T>(obj);
  last=newNode; // last will be updated to node just inserted

  if(root==nullptr) // Heap is empty
  {
    root=newNode;
    nextInsert=root;
    nextleftInsert=true;
    return;
  }


  newNode->parent=nextInsert;
  if(nextleftInsert)
  {
    nextInsert->left=newNode;
    nextleftInsert=false; // Next time insertion will be at right child of nextInsert
  }
  else
  {
    nextInsert->right=newNode;
    nextleftInsert=true; // Next time insertion will be at left child of new nextInsert

    // Update nextInsert
    // Find root or a node such that nextInsert is descendant of it's right child
    while(nextInsert->parent!=nullptr && nextInsert->parent->right==nextInsert)
    {
      nextInsert=nextInsert->parent;
    }
    if(nextInsert->parent!=nullptr) // Not root
    {
      nextInsert=nextInsert->parent->right;
    }
    while(nextInsert->left!=nullptr)  // New nextInsert will be leftmost descendant
    {
      nextInsert=nextInsert->left;
    }
  }

  // Go up from last swapping the objects so as to get a heap
  TreeNode<T> *toSwap=last;
  while(toSwap->parent!=nullptr && toSwap->parent->object<toSwap->object) // Swap until toSwap->parent's object is larger than toSawp's object or toSwap becomes root
  {
    swap(toSwap->object, toSwap->parent->object);
    toSwap=toSwap->parent;  // Move up the heap
  }

  // printHeap(root);
  return;
}


template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(last==nullptr) // Nothing to delete
    return;
    
  // Swap root's object and last node's object and delete last node and heapify the heap
  if(last!=root)  
    swap(last->object, root->object); 
  delLast();

  // No element left in heap
  if(root==nullptr)
    return;

  // Heapify
  TreeNode<T> *toSwap=root;
  while(true)
  {
    if(toSwap->left==nullptr) // We have reached leaf
      break;
    else if(toSwap->right==nullptr) // We have reached parent of a leaf
    {
      if(toSwap->object < toSwap->left->object)
        swap(toSwap->object, toSwap->left->object);
      break;
    }
    else
    {
      // Swap if any of it's child is smaller than it and repeat the process, else heapify is done... break out
      if(toSwap->left->object < toSwap->right->object)
      {
        if(toSwap->object < toSwap->right->object)
        {
          swap(toSwap->object, toSwap->right->object);
          toSwap=toSwap->right;
        }
        else
          break;
      }
      else
      {
        if(toSwap->object < toSwap->left->object)
        {
          swap(toSwap->object, toSwap->left->object);
          toSwap=toSwap->left;
        }
        else
          break;
      }
    }
  }
  // printHeap(root);
  return;
}


template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  // Adapted from Lab-4 printBST()

  // insert your code here

  if(node==nullptr)
    return;

  static int recursionlevel=-1; // recursion level
  static bool isLeft=false; // If node isLeft Child of it's parent
  static string prefix="";  // Prefix to be added while printing


  recursionlevel++;
  cout << prefix;
  if(recursionlevel!=0) // No prefix for root
  {
    cout << (isLeft ? "|--" : "|__" );
  }
  // print the value of the node
  cout << node->object.rating << endl;
  
  // enter the next tree level - left and right branch
  bool prevIsLeft=isLeft; // store curr state
  string prevprefix=prefix;  // store curr state


  // Print Heap for left child
  if(recursionlevel!=0) 
  {
    if(isLeft)
      prefix=prefix+"│   ";
    else
      prefix=prefix+"    ";
  }
  isLeft=true;
  printHeap(node->left);

  // Restore state
  isLeft=prevIsLeft;
  prefix=prevprefix;

  // Print Heap for right child
  if(recursionlevel!=0)
  {
    if(isLeft)
      prefix=prefix+"│   ";
    else
      prefix=prefix+"    ";
  }
  isLeft=false;
  printHeap(node->right);

  // Restore state
  prefix=prevprefix;
  isLeft=prevIsLeft;


  recursionlevel--;
  return;
}

  
template<typename T>
void Heap<T>::recursiveDelete(TreeNode<T> *node) {
  if(node==nullptr)
    return;

  TreeNode<T> *curr = node;
  node = node->left;
  // enter the next tree level - left and right branch
  recursiveDelete(node);
  node = curr->right;
  recursiveDelete(node);
  node = curr;
  delete node;
}