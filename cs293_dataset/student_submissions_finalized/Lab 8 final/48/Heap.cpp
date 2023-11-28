#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include<string>
#include <string.h>
#include <bits/stdc++.h>
//to find no of noodes in a root.
template<typename T>
int total(TreeNode<T>* root){
  if(root==nullptr) return 0;
  else{
    int r=total(root->left);
    int l=total(root->right);
    return 1+l+r;
  }
}
//returns the string of binary representation of a number
string s(int n){
  string str="";
  while(n){
    if(n & 1) // 1
      str+='1';
    else // 0
      str+='0';
    n>>=1; // Right Shift by 1 
  }
  reverse(str.begin(),str.end());  
  return str;
}
//to swap objects stored in two nodes
template<typename T>
void swap(TreeNode<T>* a,TreeNode<T>* b){
  T temp=a->object;
  a->object=b->object;
  b->object=temp;
}
//heapify implemented recursively 
//by find largest among its left and righr
//performing swao
//heapify on largest node.
template<typename T>
void heapify(TreeNode<T>* a){
  if(a==nullptr) return;
  if(a->left==nullptr && a->right==nullptr) return;
  if(a->left!=nullptr && a->right==nullptr){
    if(a->object < a->left->object) swap(a,a->left);
    return;
  }
  TreeNode<T>* largest=a;
  int x=0;
  if(a->object < a->left->object){
    largest=a->left;
    x++;
  }
  if(largest->object < a->right->object){
    largest=a->right;
    x++;
  }
  if(x>0){
    swap(a,largest);
    heapify(largest);
  }
  return;
}
//find binary representation of no of nodes +1 and find its n/2 position and insert it to left of it if it was even else to the right.
template<typename T>
void Heap<T>::insert(T obj) {
  if(root==nullptr){
    root=new TreeNode<T>(obj);
    n=1;
    return;
  }
  n=n+1;
  string x=s(n/2);
  x.erase(0,1);
  int y=x.length();
  TreeNode<T>* temp=root;
  TreeNode<T>* temp1=new TreeNode<T>(obj);
  for(int i=0;i<y;i++){
    if(x[i]=='1') temp=temp->right;
    else temp=temp->left;
  }
  if(n%2==0){
    temp->left=temp1;
    temp1->parent=temp;
  }
  else{
    temp->right=temp1;
    temp1->parent=temp;
  }
  TreeNode<T>* temp2=temp1;
  while(temp2!=nullptr && temp2->parent!=nullptr){
    if(temp2->parent->object < temp2->object){
      swap(temp2,temp2->parent);
    }
    temp2=temp2->parent;
  }
  //printHeap("",false);
  return;
}
//find the binaray representation of number of nodes and traverse to it by 1 means right and 0 means left and swap the last with root and delete it.
//call heapify on root.
template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  T value=getMax();
  if(root->left==nullptr && root->right==nullptr){
    root=nullptr;
    n=0;
    return value;
  }
  if(root->left!=nullptr && root->right==nullptr){
    root=root->left;
    root->parent=nullptr;
    n=1;
    return value;
  }
  TreeNode<T>* temp=root;
  string x=s(n);
  x=x.erase(0,1);
  int y=x.length();
  for(int i=0;i<y;i++){
    if(x[i]=='1') temp=temp->right;
    else temp=temp->left;
  }
  swap(root,temp);
  TreeNode<T>* temp1=temp->parent;
  delete temp;
  if(n%2==0){
    temp1->left=nullptr;
  }
  else{
    temp1->right=nullptr;
  }
  heapify(root);
  n--;
  return value; 
}
//print function with changed declaration
//print function is similar to bst pint function
template<typename T>
void Heap<T>::printHeap(const string& prefix, bool isLeft) {

  // insert your code here
  if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printHeap( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printHeap( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
  
}



  


  
