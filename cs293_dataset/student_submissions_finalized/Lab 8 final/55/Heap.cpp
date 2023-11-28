#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root==nullptr){
    root= new TreeNode<T>(obj);
    last=root;
    // //My Edit
    // printHeap(root);
    // //End My Edit
    return;
  }

  TreeNode<T>* tempMin=last;
  while(tempMin->parent!=nullptr){
    if(tempMin!=tempMin->parent->right){
      break;
    }
    tempMin=tempMin->parent;
  }

  if(tempMin->parent==nullptr){
    while(tempMin->left!=nullptr){
      tempMin=tempMin->left;
    }
    tempMin->left=new TreeNode<T>(obj);
    tempMin->left->parent=tempMin;
    last=tempMin->left;

  }

  else if(tempMin->parent->right==nullptr){
    tempMin->parent->right = new TreeNode<T>(obj);
    tempMin->parent->right->parent=tempMin->parent;
    last = tempMin->parent->right;
  }

  else{
    tempMin = tempMin->parent->right;
    while(tempMin->left!=nullptr){
      tempMin = tempMin->left;
    }
    tempMin->left = new TreeNode<T>(obj);
    tempMin->left->parent=tempMin;
    last = tempMin->left;
  }

  tempMin = last;

  while(true){

    if(tempMin->parent==nullptr || tempMin->object < tempMin->parent->object){
      break;
    }

    swap(tempMin->object,tempMin->parent->object);

    tempMin=tempMin->parent;
  }

  // //My Edit
  // printHeap(root);
  // //End My Edit
  return;
}

template<typename T>
void Heap<T>::delMax() {

  if(root==nullptr){
    return;
  }
  // insert your code here
  root->object=last->object;
  
  TreeNode<T>* tempMin=last,*lastcopy=last;
  while(tempMin->parent!=nullptr){
    if(tempMin!=tempMin->parent->left){
      break;
    }
    tempMin=tempMin->parent;
  }

  if(tempMin->parent==nullptr){
    while(tempMin->right!=nullptr){
      tempMin=tempMin->right;
    }
    last=tempMin;
  }

  else{
    tempMin = tempMin->parent->left;
    while(tempMin->right!=nullptr){
      tempMin = tempMin->right;
    }
    last = tempMin;
  }
  if(lastcopy->parent==nullptr){
    root = nullptr;
  }
  else if(lastcopy==lastcopy->parent->left){
    lastcopy->parent->left=nullptr;
  }
  else if(lastcopy==lastcopy->parent->right){
    lastcopy->parent->right=nullptr;
  }
  lastcopy->parent=nullptr;
  delete lastcopy;

  if(root!=nullptr){
    Heapify(root);
  }

  return;
}


template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node) {
  if(node->left==nullptr && node->right==nullptr) return;
  else if(node->right==nullptr){
    if(!(node->object<node->left->object)){return;}
    else {
      swap(node->object,node->left->object);
      Heapify(node->left);
      return;
    }
  }
  else{
    if(node->left->object<node->object && node->right->object<node->object){return;}
    else if(!(node->left->object<node->right->object)){
      swap(node->left->object,node->object);
      Heapify(node->left);
      return;
    }
    else{
      swap(node->right->object,node->object);
      Heapify(node->right);
      return;
    }
  }
}

  
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
    
    const string prefix = "";
    cout << root->object << endl;
    printer(prefix, node->left, true);
    printer(prefix, node->right, false);
    return;
}

template<typename T>
void printer(const string &prefix, TreeNode<T> *root, bool isLeft){
  if (root!=nullptr){
    
    cout << prefix;
    
    cout << (isLeft ? "|--":"|__");

    //print the value of the node
    cout << root->object << endl;
    TreeNode<T> *curr = root;
    root = curr->left;
    //enter the next tree level - left and right branch
    printer(prefix + (isLeft ? "|  " : "   "), root, true);
    root = curr->right;
    printer(prefix + (isLeft ? "|  " : "   "), root, false);
    root = curr;
  }
}
