#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  TreeNode<T> *newNode = new TreeNode(T obj);
  if (root == nullptr){
    this->root = newNode;
    return;
  }

  LinkedList<TreeNode <T>*>* treelist = new LinkedList();


  listNode<TreeNode <T>*> * newListNode = new listNode(&root);
  treeList.insert(newListNode);

  
  listNode<TreeNode <T>*> * currNode = treelist->head;
  bool inserted = false;
  while(true){
    while (currNode != nullptr){
      if (currNode->object->left != nullptr && currNode->object->right != nullptr){
        listNode<TreeNode <T>*> * leftNode = new listNode(&currNode->object->left);
        listNode<TreeNode <T>*> * rightNode = new listNode(&currNode->object->right);

        leftNode->next = rightNode;
        rightNode->prev = leftNode;

      
        rightNode->next = currNode->next;
        leftNode->prev = currNode->prev; 

        if (currNode->next != nullptr){
          currNode->next->prev = rightNode;
        }

        if (currNode->prev != nullptr){
          currNode->prev->next = leftNode;
        }

        if(currNode == treeList->head){
          treeList->head = leftNode;
        }

        if(currNode->next == nullptr){
          treeList->tail = leftNode;
        }
        
      } else if (currNode->object->left != nullptr && currNode->object->right == nullptr){
        currNode->object->right = newNode;
        return;

      } else if (currNode->left == nullptr){
        currNode->object->left = newNode;
        return;
      }

      currNode = currNode->next;
    }

    currNode = treeList->head;
  }


  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  


  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
