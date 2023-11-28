#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
TreeNode<T>* Heap<T>::lastelement(TreeNode<T> *root){


}
template<typename T>
void Heap<T>::heapify(TreeNode<T> * r){
  if(r->left!=nullptr && r->right !=nullptr){
    if(max(r->left->object , r->right->object)<r->object){
      return;
    }
    else{
      if(r->left->object>r->right->object){
        swap(r->object,r->left->object);
        heapify(r->left);
      }
      else{
        swap(r->object,r->right->object);
        heapify(r->right);
      }
    }
  }
  else if(r->left !=nullptr){
     if(r->left->object > r->object){
      swap(r->object,r->left->object);
      return;
     }
     else{
      return;
     }
  }
  else{
    return;
  }
  
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if( root ==  nullptr){
    root = new TreeNode<T>(T obj);
    // presentelementparent=lastparent;
    presentelement =root;
    last = root->left;
    lastparent = root;
    return;
  }
  else{
   last = new TreeNode<T>(T obj);
   if(lastparent->left == nullptr){
    lastparent->left= last;
    last->parent = lastparent;
    // presentelementparent = lastparent;
    presentelement =last;
    last = lastparent->right;
    // return;
   }
   else if(lastparent->right == nullptr){
    lastparent->right= last;
    last->parent = lastparent;
    // presentelementparent=lastparent;
    presentelement=last;
    bool a =true;
    while(lastparent->parent != nullptr ){
      if(lastparent ->parent ->left == lastparent){
        lastparent = lastparent->parent;
        a=false;
        break;
      }
      lastparent=lastparent->parent;

    }
    if( a == true){
      while(lastparent->left != nullptr){
        lastparent=lastparent->left;
      }
      last=lastparent->left;
      return;

    }
    else{
      lastparent=lastparent->right;
      while(lastparent->left != nullptr){
        lastparent=lastparent->left;

      }
      last = lastparent->left;

    }
    
   }
   TreeNode<T> *p=presentelement;
   while(p->parent != nullptr){
    if(p->parent->object >= p->object){
      break;
    }
    else{
      swap(p->parent->object,p->object);
      p=p->parent;
    }
   }
   return;

  }
  return;
}

template<typename T>
T Heap<T>::delMax() {
  T x = root->object;
  swap(root->object,presentelement->object);
  presentelement->parent = lastparent;
  presentelement = nullptr;
  last = presentelement;
  TreeNode<T> *p=lastparent;
  if(p->left == nullptr)

{
  while(p->parent!=nullptr){
    if(p->parent->right == p){
      p=p->parent;
      break;
    }
    p=p->parent;
  }
  p=p=>left;
  while(p->right != nullptr){
    p=p->right;

    

  }
  presentelement=p;

  
}
else{
  presentelement=p->left;
}  
heapify(root);
  




  // insert your code here

  return x ;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {


  // insert your code here

  return;
}

  
