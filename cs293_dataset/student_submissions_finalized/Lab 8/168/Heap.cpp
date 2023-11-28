#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  if(!root){
    root=new TreeNode<int>(obj);
    numOfNodes++;
    return;
  }
  else{
    int level=logarithm2(numOfNodes+1);
    int power=exp(level);
    int temp=numOfNodes+1-power;
    TreeNode<int>* currNode=root;
    for(int i=1;i<level;i++){
      if(temp<power/2){
        currNode=currNode->left;
      }
      else{
        currNode=currNode->right;
        temp=temp-power/2;
      }
      power=power/2;
    }

    if(temp%2==0){
      currNode->left=new TreeNode<int>(obj);
      currNode->left->parent=currNode;
      currNode=currNode->left;
    }
    else{
      currNode->right=new TreeNode<int>(obj);
      currNode->right->parent=currNode;
      currNode=currNode->right;
    }
    numOfNodes++;

    //carrying out swaps to obey heap property
    
    while(currNode->parent!=nullptr && currNode->object>currNode->parent->object){
      T temp=currNode->object;
      currNode->object=currNode->parent->object;
      currNode->parent->object=temp;
      currNode=currNode->parent;
    }

    return;
  }
}

template<typename T>
void Heap<T>::delMax() {

  int level=logarithm2(numOfNodes);
  int power=exp(level);
  int temp=numOfNodes-power;
  TreeNode<int>* currNode=root;
  for(int i=1;i<level;i++){
    if(temp<power/2){
      currNode=currNode->left;
    }
    else{
      currNode=currNode->right;
      temp=temp-power/2;
    }
    power=power/2;
  }

  if(temp%2==0){
    currNode=currNode->left;
    currNode->parent->left=nullptr;
  }
  else{
    currNode=currNode->right;
    currNode->parent->right=nullptr;
  }

  root->object=currNode->object;
  delete currNode;

  //We need to Heapify the root
  currNode=root;
  while(true){
    if(currNode->left && currNode->right){
      if(currNode->object>currNode->left->object && currNode->object>currNode->right->object){
        break;
      }
      else{
        if(currNode->left->object>currNode->right->object){
          T temp=currNode->left->object;
          currNode->left->object=currNode->object;
          currNode->object=temp;
          currNode=currNode->left;
        }
        else{
          T temp=currNode->right->object;
          currNode->right->object=currNode->object;
          currNode->object=temp;
          currNode=currNode->right;
        }
      }
    }
    else if(currNode->left){
      if(currNode->object>currNode->left->object){
        break;
      }
      else{
        T temp=currNode->left->object;
          currNode->left->object=currNode->object;
          currNode->object=temp;
          currNode=currNode->left;
      }
    }
    else{
      break;
    }
  }
  return;
  
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  printTree(root,"",true);

  return;
}

template<typename T>
int Heap<T>::exp(int a){
  int p=1;
  for(int i=0;i<a;i++){
    p=p*2;
  }
  return p;
}

template<typename T>
int Heap<T>::logarithm2(int a){
  int log=0;
  while(a!=1){
    a=a/2;
    log++;
  }
  return log;
}

template<typename T>
void Heap<T>::printTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}