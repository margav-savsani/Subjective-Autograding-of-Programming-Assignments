#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

int* decToBinary(int n)
{
    // array to store binary number
    int binaryNum[32];
 
    // counter for binary array
    int i = 0;
    while (n > 0) {
 
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
 
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--)
         binaryNum[j];
}

template<typename T>
void Heap<T>::insert(T obj) {

  //add the base case
  //for number of nodes =1 or 0
  //-----------
  // insert your code here
    int binaryNum[32];
 
    // counter for binary array
    int i = 0;
    while (n > 0) {
 
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
 
    // printing binary array in reverse order
    TreeNode<T> *tempDummy = root;
    TreeNode<T> *temp = root;
    bool left = true;
    for (int j = i - 1-1; j >= 0 && tempDummy!=NULL; j--){
      temp = tempDummy;
      if(binaryNum[j]==0){
        tempDummy = tempDummy->left;
        left = true;
      }
      if(binaryNum[j]==1){
        tempDummy = tempDummy->right;
        left = false;
      }
    }
    if(left){
      temp->left = new TreeNode(obj);
      return ;
    }
    else{
      temp->right = new TreeNode(obj);
    }  

  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode<T> * temp = root;
  if(root->left->object < root->right->object){
    root = root->right;
    if(root->left && root->right==nullptr)
  }

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
