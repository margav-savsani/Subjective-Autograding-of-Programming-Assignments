#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
int Heap<T>::leftheight(TreeNode<T> *node){
  if(node == nullptr){
    return -1;
  }
  else {
    return 1 + leftheight(node->left);
  }

}

template<typename T>
int Heap<T>::rightheight(TreeNode<T> *node){
  if(node == nullptr){
    return -1;
  }
  else {
    return 1+rightheight(node->right);
  }

}

template<typename T>
void Heap<T>::insertnode(TreeNode<T> *node, T obj){

  if( node->left != nullptr && node->right != nullptr){

    if(leftheight(node->left) == rightheight(node->left)){
      if(leftheight(node->right) == rightheight(node->right)){
        if(leftheight(node->left) == rightheight(node->right)){
          insertnode(node->left , obj);
        }
        else{
          insertnode(node->right , obj);
        }
      }
      else{
        insertnode(node->right,obj);
      }
    }
    else{
      insertnode(node->left , obj);
    }
  }
  else if(node->left == nullptr){
    node->left = new TreeNode<T>( obj);
    (node->left)->parent = node;
    heapifyinsert(node->left);
  }
  else{
    node->right = new TreeNode<T>(obj);
    (node->right)->parent = node;
    heapifyinsert(node->right);
  }

}

template<typename T>
void Heap<T>::heapifyinsert(TreeNode<T> *node){

  if(node->parent == nullptr){
    return;
  }
  
  if( (node->parent)->object < node->object  ){
       T ect = node->object;
      node->object = (node->parent)->object;
      (node->parent)->object = ect;
      heapifyinsert(node->parent);
  }
  
    return;
  

}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

    if(root == nullptr){
      root = new TreeNode<T>(obj);

    }
    else{
      insertnode(root , obj);
    }


}


template<typename T>
TreeNode<T>* Heap<T>::lastelement(TreeNode<T> *node){

   if( node->left != nullptr && node->right != nullptr){

    if(leftheight(node->left) == rightheight(node->left)){
      if(leftheight(node->right) == rightheight(node->right)){
        if(leftheight(node->left) == rightheight(node->right)){
          return lastelement(node->right);
        }
        else{
          return lastelement(node->left);
        }
      }
      else{
        return lastelement(node->right);
      }
    }
    else{
      return lastelement(node->left);
    }
  }
  else if(node->left != nullptr && node->right == nullptr ){
    return node->left;
    
  }
  
    return node;
    
  

}

template<typename T>
void Heap<T>::heapifydelete(TreeNode<T> *node){

  TreeNode<T> *max ;
  if(node->left != nullptr && node->right != nullptr){
    if((node->right)->object < (node->left)->object){
      max = node->left;
    }
    else{
      max = node->right;
    }
  }
  else if (node->left == nullptr)
  {
    max = nullptr;
  }
  else{
    max = node->left;
  }

  if( max == nullptr){
    return;
  }
  else{

    if(node->object < max->object){
      T ect = node->object;
      node->object = max->object;
      max->object = ect;      
      heapifydelete(max);
    }
    
      return;
    
  }

}



template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode<T> *le = lastelement(root);
  if( le == root){
    root = nullptr;
    return;
  }

  TreeNode<T> *par = le->parent;
  root->object = le->object;
  

  if(par->left == le){
    par->left = nullptr;
  }
  else{
    par->right = nullptr;
  }
  heapifydelete(root);


  return;
}


template<typename T> 
void Heap<T>::printHeapTree(TreeNode<T> *root,const string& prefix, bool isLeft) {
   if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << "[Rt: " << (root->object).rating << ", id: " << (root->object).revId << "]";
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printHeapTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeapTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL Heap" << endl;
  }
}

template<typename T>
void Heap<T>::printHeap() {

  // insert your code here
  printHeapTree(root, "", false);
  return;
  
}



  
