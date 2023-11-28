#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr){//root case
    root = new TreeNode<T>(obj);
    lastNode = root;
  }
  else if(root->left == nullptr){//left of root
    root->left = new TreeNode<T>(obj);
    lastNode = root->left;
    lastNode->parent = root;
    lastNodeCode[0] = 0;
  }
  else if(root->right == nullptr){//right of root
    root->right = new TreeNode<T>(obj);
    lastNode = root->right;
    lastNode->parent = root;
    lastNodeCode[0] = 1;
  }
  else{
    
    if(lastNode->parent->right == nullptr){//case when lastNode is a left node of parent
      lastNode->parent->right = new TreeNode<T>(obj);
      TreeNode<T>* prevLastNode = lastNode;
      lastNode = lastNode->parent->right;//new lastNode is right of parent
      lastNode->parent = prevLastNode->parent;//parents are same
      lastNodeCode[count] = 1;//store binary bit towards right
      count++;
    }
    else{//present LastNode is the right node of parent
      int i;
      for(i=count-1;i>=0;i--){//adding one bit to current LastNode to get new LastNode
        if(lastNodeCode[i] == 0){
          lastNodeCode[i] = 1;
          break;
        }
        else{
          lastNodeCode[i] = 0;
        }
      }
      if(i==0 && lastNodeCode[i]==1){//case when the tree was complete
        lastNodeCode[count] == 0;
        count++;
      }
      TreeNode<T> *curr = root;
      for(int i=0;i<count-1;i++){//traverse tree with the help of lastNodeCode array
        if(lastNodeCode[i] == 0){
          curr = curr->left;
        }
        else{
          curr = curr->right;
        }
      }
      curr->left = new TreeNode<T>(obj);
      lastNode = curr->left;
      lastNode->parent = curr;

    }
  }
  TreeNode<T> *curr = lastNode;
  while(curr!=root){//put new inserted object in the correct location while moving upwards
    if(curr->object > curr->parent->object){//if inserted object is greater than its parent, swap
      swap(curr->object , curr->parent->object);
      curr = curr->parent;//move upwards
    }
    else{// if condition doesn't match, heap property satisfied--break
      break;
    }
  }
  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  if(lastNode == root){//base case
    T obj = root->object;
    root = nullptr;
    return obj;
  }
  root = lastNode;
  
  if(lastNode->parent->right == lastNode){//if lastNode is the rightNode of parent
    lastNode = lastNode->parent->left;
    lastNodeCode[count - 1] = 0;
    lastNode->parent->right == nullptr;
  }
  else{//lastNode is the leftNode of parent
    int i = 0;
    lastNode->parent->left = nullptr;
    for(i = count-1;i>=0;i--){//substrcation of a bit from lastNodeCode
      if(lastNodeCode[i] == 1){
        lastNodeCode[i] = 0;
        break;
      }
      else{
        lastNodeCode[i] = 1;
      }
    }
    if(i==0 && lastNodeCode[i] == 0){//case when leftmostNode is getting deleted
      count--;
    }
    TreeNode<T>* curr = root;
    for(int i=0;i<count;i++){
      if(lastNodeCode[i] == 0){
        curr = curr->left;
      }
      else{
        curr = curr->right;
      }

    }
    lastNode = curr;//traverse with help of lastNodeCode array to find the LastNode
  }
  Heapify(root);
  return root->object;
}
template<typename T>
void Heap<T>::Heapify(TreeNode<T>* root){

  TreeNode<T> *curr = root;
  if(curr->left == nullptr)//if no left node exits then right node also doesn't exist --  we have rached a leaf--return
    return;
  else if(curr->right == nullptr){// if only right node is null, apply heapify on only the left node
    if(curr->object < curr->left->object){
      swap(curr->object , curr->left->object);
    }
    Heapify(root->left);
    return;
  }
  //both left and right child of the curr node exist
  if(curr->object < curr->left->object && curr->object < curr->right->object){//if both are less , see which is greater and swap
    if(curr->right->object < curr->left->object){
      swap(curr->object , curr->left->object);
    }
    else{
      swap(curr->object , curr->right->object);
    }
  }
  else if(curr->object < curr->left->object){//only left is greater--no checking reqd just swap
    swap(curr->object , curr->left->object);
  }
  else if(curr->object < curr->right->object){//only right is greater--no checking reqd just swap
    swap(curr->object , curr->right->object);
  }
  Heapify(root->left);//recursively call heapify on the left and right nodes
  Heapify(root->right);
  return;

}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
