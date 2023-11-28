#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  
   TreeNode<T> *newnnode=new TreeNode<T>(obj);
  if(root==NULL){
    root=newnnode;
    lastinpt=newnnode;
  }
  else if(lastinpt->left==NULL){
     //cout<<"ok"<<endl;
    lastinpt->left=newnnode;
     newnnode->parent=lastinpt;
  }
  else{
     //cout<<"inserting: "<<obj<< "at"<< lastinpt->object<<endl;
    lastinpt->right=newnnode;
    newnnode->parent=lastinpt;
    
    TreeNode<T> *par=newnnode->parent;
    TreeNode<T> *current=newnnode;
    while(par!=NULL && current!=par->left){
      current=par;
      par=par->parent;
    }
    if(par!=NULL){
    current=par->right;
    }
    while(current->left!=NULL){
      current=current->left;
    }
    lastinpt=current;
    }
  lastNode=newnnode;
  Heapify(root);
  //printHeap("",false);
  //cout<<endl;
  return;
}

template<typename T>
void Heap<T>::delMax() {
  //cout<<"lastNode: "<<lastNode->object<<endl;
  //cout<<endl;
  swap(root,lastNode);
  
  TreeNode<T> *parent=lastNode->parent;
  if(parent==NULL){
      lastNode=NULL;
      lastinpt=NULL;
      root=NULL;
      //cout<<"BAZINGA1\n";
      return ;
  }
  if(parent->left==lastNode){
    //cout<<"BAZINGA2\n";
    TreeNode<T> *par=lastNode->parent;
    lastinpt=par;
    TreeNode<T> *current=lastNode;
    while(par!=NULL && current!=par->right){
      current=par;
      par=par->parent;
    }
    if(par!=NULL){
    current=par->left;
    }
    while(current->right!=NULL){
      current=current->right;
    }
    lastinpt=lastNode->parent;
    lastNode->parent=NULL;
    lastNode=current;
    parent->left=NULL;

  }
  else{
    //cout<<"BAZINGA3\n";
    parent->right=NULL;
    lastNode->parent=NULL;
    lastNode=parent->left;
    lastinpt=lastNode->parent;
  }
  //printHeap("",false);
  //cout<<"-----------------------------------------------"<<endl;
  Heapify(root);
  //printHeap(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node){
  printBST(root,"");
  return;
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node) {
  TreeNode<T> *left=node->left;
  TreeNode<T> *right=node->right;
  if(right==NULL && left==NULL){
    return;
  }
  else if(right==NULL){
    if(!(left->object<node->object)){
    swap(node,left);
  }
    return;
  }
  
  
  if(!(left->object<node->object) || !(right->object<node->object)){
    if( left->object<right->object){
      swap(node,right);
    }
  else{
    swap(node,left);
  }
}
  Heapify(left);
  Heapify(right);
  return;
}

template<typename T>
void swap(TreeNode<T> *node1,TreeNode<T> *node2){
  T temp=node1->object;
  node1->object=node2->object;
  node2->object=temp;
  return;
}   

template<typename T>
void printBST(TreeNode<T> *root,const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root-> object<< endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(root,prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(root,prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}