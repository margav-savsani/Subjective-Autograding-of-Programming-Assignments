#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  if (root==nullptr){
    root = new  TreeNode<T>(obj);
    return;
  }
  // insert your code here
TreeNode<T>* currnode=root;
while(currnode->left!=nullptr){
  currnode=currnode->left;
}
TreeNode<T>*inserted_node;
TreeNode<T>* leftmost =currnode;
while(getsucc(currnode) !=nullptr){
  currnode=getsucc(currnode);
}
if (currnode->parent==nullptr){
    currnode->left=new TreeNode <T>(obj);
    inserted_node=currnode->left;
    inserted_node->parent=currnode;
}
else if (currnode->parent->left == currnode){
    currnode->parent->right=new TreeNode <T>(obj);
    inserted_node=currnode->parent->right;
    inserted_node->parent=currnode->parent;
    
}
else{
   if (getsucc(currnode->parent)==nullptr){
        leftmost->left=new TreeNode <T>(obj);
        inserted_node=leftmost->left;
        inserted_node->parent=leftmost;
 
   }
   else{
       getsucc(currnode->parent)->left=new TreeNode<T>(obj);
       inserted_node=getsucc(currnode->parent)->left;
       inserted_node->parent=getsucc(currnode->parent);
   }
}
while((inserted_node->parent !=nullptr)){
   if (inserted_node->object>inserted_node->parent->object)
   {
    swap(inserted_node->object,inserted_node->parent->object);
   }
   inserted_node=inserted_node->parent;
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
   if (node!=nullptr){
    cout << node->object;
    printHeap(node->left);
    printHeap(node->right);
   }
   
  // insert your code here

  return;
}

template<typename T>
TreeNode<T>* Heap<T>::getsucc(TreeNode<T>* node) {
if (node== root){
  return nullptr;
}
if (node->parent->left == node){
   return node->parent->right;
}
else {
    if (getsucc(node->parent)==nullptr){
      return nullptr;
    }
    if (getsucc(node->parent)!=nullptr){
    TreeNode<T>*x= getsucc(node->parent);
    return x->left;
    }
    else {
      return nullptr;
    }
}
  // insert your code here
}


int main(){

  Heap <int> a;
  a.insert(12);
  a.insert(13);
  a.insert(6);
  a.insert(18);
  a.printHeap(a.root);
}
