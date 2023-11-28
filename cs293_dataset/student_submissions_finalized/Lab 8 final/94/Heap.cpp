#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<vector>
#include <cmath>
#include <algorithm>
using namespace std;
#ifndef HEAP_H

#include "Heap.h"

#endif
vector<int> convert(int n){ // converts a number into binary leaving the first digit
    vector<int> a;
    while(n!=1){
        a.push_back(n%2);// storing each digit into vector
        n=n/2;
    }
    return a; // returning the vector

}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(num==0){     // creating the node if root is null
    root=new TreeNode(obj);
    num++; // increasing no of number
    return;
  }
  else{
    vector<int>k=convert(num+1);
    reverse(k.begin(),k.end()); // reversing the array so that we can traverse to the node
    TreeNode<T>*curr=root;
    for(int i=0;i<k.size()-1;i++){
      if(k[i]==0) curr=curr->left; //traversing to node
      else curr=curr->right;
    }
    if(k[k.size()-1]==0){ // creating a node if left is null
      curr->left=new TreeNode<T>(obj);
      curr->left->parent=curr;
      num++;
      CompleteHeapify(); // heapifying the complete tree starting from last level
      return;
    }
    else{
      curr->right=new TreeNode(obj); // creating a node right if left is non null
      curr->right->parent=curr;
      num++;
      CompleteHeapify(); // heapifying the complete tree starting from last level
      return;
    }

  }
  return;
}


template<typename T>
void Heap<T>::delMax() {
  if(num==1){
     root=NULL; // deleting root if it is one element
     num-=1; // decresing number
     return;
  }
  vector<int> k=convert(num); // reversing the array so that we can traverse to the node
  reverse(k.begin(),k.end());
  TreeNode<T>*curr=root;
  for(int i=0;i<k.size()-1;i++){  //traversing to node
      if(k[i]==0) curr=curr->left;
      else curr=curr->right;
  }
  if(k[k.size()-1]==0){
    T obj2=curr->left->object; //  keeping the last element into root
    root->object=obj2;
    curr->left=NULL;
  }
  else{
    T obj2=curr->right->object;
    root->object=obj2;
    curr->right=NULL;
  }
  num=num-1;
  Heapify(root);  // heapifing the root
  


  // insert your code here
  //printHeap(root);
  return;
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *r1){
  TreeNode<T> *r=r1;
  if(r->left==NULL && r->right==NULL) { return; } // returning if it is a leaf
  else if(r->left!=NULL && r->right==NULL)
  {
    if(r->object < r->left->object)
    {
      exchange(r,r->left);  // swapping left and parent
      return;
    }
    else return;
  }
  else if(r->left!=NULL && r->right!=NULL) // checking for max between left and right
  {
    if(r->right->object<r->left->object)
    {
      if(r->object < r->left->object)
      {
        exchange(r,r->left); // swapping left and parent
        Heapify(r->left);
        return;
      }
      else return;
    }
    else
    {
      if(r->object < r->right->object)
      {
        exchange(r,r->right); // swapping with right and parent
        Heapify(r->right);
        return;
      }
      else return;
    }
  }
  else  return;

}

template<typename T>
void Heap<T>::CompleteHeapify(){ // heapifying from bottom to top
  int a=log2(num);

  for(int i=int(pow(2,a)+0.01)-1;i>1;i=i-1){ // going through all nodes

    vector<int> k=convert(i);
    reverse(k.begin(),k.end());
    TreeNode<T> *curr=root;
    T obj1=root->object;
    for(int i=0;i<k.size();i++){
        if(k[i]==0) curr=curr->left;
        else curr=curr->right;
    }
    Heapify(curr);
  }
  Heapify(root); // heapifying the root
  return;

}

template<typename T>
void exchange(TreeNode<T> *a,TreeNode<T>*b){
  T obj=a->object;
  a->object=b->object;  // exchange the object of both pointers
  b->object=obj;
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) { // prints the heap below this node

  // insert your code here
  string s="";
  print(node,s,false); // passing the node into print function which is similar to BST
  
}

template<typename T>
void print(TreeNode<T> *node,const string& prefix, bool isLeft=false){

   if( node != nullptr )
    {
        cout<<prefix;
        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object<< endl;
        TreeNode<T> *curr = node;
        node = node->left;        // enter the next tree level - left and right branch
        print( node,prefix + (isLeft ? "│   " : "    "), true);
        node = curr->right;
        print(node, prefix + (isLeft ? "│   " : "    "), false);
        node = curr;  
    }

  return;

}

  
