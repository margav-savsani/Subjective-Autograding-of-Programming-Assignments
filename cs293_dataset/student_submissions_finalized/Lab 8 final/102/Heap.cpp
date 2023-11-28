#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include<cmath>


// void Heapifier(TreeNode<T> *node){
//   if(node->left->object){

//   }
// }

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  int x=noe+1;

  //calculating binary of a number
  int nodb;//Number of digits in binary
  nodb=(log(x)/log(2))+1;
  int *arr=new int[nodb];
  
  // 1 0 0 0 0
  // 0 1 2 3 4

  for(int i=0; i<nodb ; i++){
    arr[nodb-1-i]=x%2;
    x=x/2;
  }

  // for(int i=0; i<nodb; i++){
  //   cout<<arr[i]<<endl;
  // }

  noe++;
  if(root==nullptr){
    root=new TreeNode<T>(obj);
    return;
  }
  else{
    TreeNode<T> *currNode=root; //keeps check of current node
    TreeNode<T> *currPar;//keeps check of current parent
    int p;
    for(int i=1 ; i<nodb && currNode!=nullptr ; i++){

      //if digit is zero go left
      if(arr[i]==0){
        if(i==nodb-1) p=1;
        currPar=currNode;
        currNode=currNode->left;
      }
      //if digit is one go right
      else if(arr[i]==1){
        if(i==nodb-1) p=2;
        currPar=currNode;
        currNode=currNode->right;
      }
    }
    currNode=new TreeNode<T>(obj);
    currNode->parent=currPar;
    if(p==1){
      currPar->left = currNode;
    }
    else{
      currPar->right = currNode;
    }
    //Heapify Part

    while(currPar!=nullptr && currPar->object<currNode->object  ){
      T temp = currNode->object;
      currNode->object=currPar->object;
      currPar->object=temp;
      currNode=currPar;
      currPar=currPar->parent;
    }
  }

  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  // printHeap(root);

  int x=noe;

  //calculating binary of a number
  int nodb;//Number of digits in binary
  nodb=log(noe)/log(2)+1;
  int *arr=new int[nodb];
  
  // 1 0 0 0 0
  // 0 1 2 3 4

  for(int i=0; i<nodb ; i++){
    arr[nodb-1-i]=x%2;
    x=x/2;
  }

  noe--;
  if(root==nullptr){
    return;
  }
  else{
    TreeNode<T> *currNode=root; //keeps check of current node
    TreeNode<T> *currPar;//keeps check of current parent
    int p;
    for(int i=1 ; i<nodb && currNode!=nullptr ; i++){

      //if digit is zero go left
      if(arr[i]==0){
        if(i==nodb-1) p=1;
        currPar=currNode;
        currNode=currNode->left;
      }
      //if digit is one go right
      else if(arr[i]==1){
        if(i==nodb-1) p=2;
        currPar=currNode;
        currNode=currNode->right;
      }
    }
    // TreeNode<T> *temp=currNode;
    root->object=currNode->object;
    if(p==1){
      currNode->parent->left=nullptr;
    }
    else{
      currNode->parent->right=nullptr;
    }
    currNode=nullptr;

    //Heapify it
    TreeNode<T> *currNodeH=root; //keeps check of current node
    //TreeNode<T> *currParH;//keeps check of current parent


    while(currNodeH!=nullptr){
      if(currNodeH->right==nullptr && currNodeH->left==nullptr){
        break;
      }
      if(currNodeH->right==nullptr && currNodeH->left!=nullptr){
        if(currNodeH->object<currNodeH->left->object){
          T temp=currNodeH->left->object;
          currNodeH->left->object=currNodeH->object;
          currNodeH->object=temp;     
          currNodeH=currNodeH->left;
        }
        else break;
      }
      if(currNodeH->right!=nullptr && currNodeH->left!=nullptr){
        if(currNodeH->left->object<currNodeH->object && currNodeH->right->object<currNodeH->object) break;
        T left = currNodeH->left->object;
        T right = currNodeH->right->object;
        if(left<right){
          T temp=currNodeH->right->object;
          currNodeH->right->object=currNodeH->object;
          currNodeH->object=temp;
          currNodeH=currNodeH->right; 
        }
        else{
          T temp=currNodeH->left->object;
          currNodeH->left->object=currNodeH->object;
          currNodeH->object=temp;     
          currNodeH=currNodeH->left;  
        }
      }
      // if(currNodeH->left!=nullptr && currNodeH->object<currNodeH->left->object){
      //   //swapping
      //   T temp=currNodeH->left->object;
      //   currNodeH->left->object=currNodeH->object;
      //   currNodeH->object=temp;     
      //   currNodeH=currNodeH->left;   
      // }
      // else if(currNodeH->right!=nullptr && currNodeH->object<currNodeH->right->object){
      //   T temp=currNodeH->right->object;
      //   currNodeH->right->object=currNodeH->object;
      //   currNodeH->object=temp;
      //   currNodeH=currNodeH->right;   
      // }
      // else if(currNodeH->right==nullptr && currNodeH->left==nullptr){
      //   break;
      // }
    }
  }


  return;
}

// template<typename T>
// void Heap<T>::print(){
//   TreeNode<T> *curr = root;
//   while(curr!=nullptr){
//     cout<<curr->object<<endl;
//     curr=curr->left;
//   }
// }

template<typename T>
void Heap<T>::printBST(const string& prefix, bool isLeft){
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  printBST("", false);
  return;
}

  
