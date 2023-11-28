#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
bool Heap<T>::isLeft(TreeNode<T>* node){
  if(node->parent->left == node){
    return true;
  }
  return false;
}
template <typename T>
bool Heap<T>::isLeftof(TreeNode<T>* node, TreeNode<T>* Parent){
  if(Parent->left == node){
    return true;
  }
  else return false;
}
template <typename T>
bool Heap<T>::check(TreeNode<T>* node){
  int value = node->object.rating;
  if(node->left==nullptr){
    return false;
  }
  else if(node->right==nullptr){
    int lv=node->left->object.rating;
    if(lv>value){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    int lv = node->left->object.rating;
    int rv = node->right->object.rating;
    if(lv>value || rv>value){
      return true;
    }
    else return false;
  }
}

template <typename T>
void Heap<T>::Heapify(TreeNode<T>* node){
  int value = node->object.rating;
  if(node->left==nullptr){
    return;
  }
  else if(node->right == nullptr){
    T dummy = node->left->object;
    int l= dummy.rating;
    if(l>value){
      node->left->object = node->object;
      node->object=dummy;
    }
  }
  else{
    int l = node->left->object.rating;
    int r= node->right->object.rating;

    if(l>r){
      if(l>value){
      T dummy = node->left->object;
      node->left->object = node->object;
      node->object = dummy;
      }
    }
    else if(l<=r){
      if(r>value){
      T dummy = node->right->object;
      node->right->object = node->object;
      node->object = dummy;
      }
    }
  }
  return;
}

template <typename T>
void Heap<T>::recc_heapify(TreeNode<T>* node){
  int value = node->object.rating;
    if(check(node)){
      Heapify(node);
      if(node->right == nullptr){
        T dummy = node->left->object;
        int l= dummy.rating;
        if(l>value){
          node->left->object = node->object;
          node->object=dummy;
        }
      }
    
    else{
      recc_heapify(node->right);
      recc_heapify(node->left);
    }
    }
    return;
}

template <typename T>
TreeNode<T>* Heap<T>::getend(TreeNode<T>* node){
  
  TreeNode<T> *A = end;
  if(end->left==nullptr){
    while (A!=nullptr && A!=root)
    {
      if(isLeft(A)){
        A=A->parent;
      }
      else break;
    }

    if(A==root){
      while(A->right!=nullptr){
        A=A->right;
      }
      return A;
    }
    
  else if(!isLeft(end)){
    A=end;
    return A->parent->left->right;
  }
  else if(isLeft(end)){
    A=end->parent;
    while(A!=nullptr && A->parent != nullptr){
      if(!isLeft(A)){
        A=A->parent->left;
        while(A->right!=nullptr){
          A=A->right;
        }
        return A;
      }
      else if(isLeft(A)){
        A=A->parent;
      }
    }
  }
  }

  else if(end->right == nullptr){
    A=A->left;
  }
  return A;
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T>* A = new TreeNode<T>(obj);
  if(root == nullptr){
    root =A;
    end = root;
  } 
  else if(end->left==nullptr){
    end->left = A;
    end->left->parent = end;
    TreeNode<T>* dummy = end;
    while(dummy != nullptr){
      if(check(dummy)){
        Heapify(dummy);
        dummy = dummy->parent;
      }
      else break;
    }
  }
  else if(end->right == nullptr){
    end->right =A;
    end->right->parent=end;
    TreeNode<T>* dummy = end;
    while(dummy != nullptr){
      if(check(dummy)){
        Heapify(dummy);
        dummy = dummy->parent;
      }
      else break;
    }
    if(end==root){
      end=end->left;
    }
    else if(isLeft(end)){
      end=end->parent->right;
    }
    else if(!isLeft(end)){
        TreeNode<T>* dummy1 = end->parent;
        while (dummy1 !=nullptr)
        {
          if(dummy1==root){
            while (dummy1->left!=nullptr)
            {
              dummy1=dummy1->left;
            }
            end=dummy1;
            break;
          }
          else if(isLeft(dummy1)){
            dummy1=dummy1->parent->right;
            while (dummy1->left!=nullptr)
            {
              dummy1 = dummy1->left;
            }
            end = dummy1;
            break;
          }
          else if(!isLeft(dummy1)){
            dummy1=dummy1->parent;
          }
        }
        
    }

  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode<T>* B = root; 
  TreeNode<T>* enddummy = getend(root);
  T dummy  = enddummy->object;
  enddummy->object = root->object;
  root->object = dummy;
  end = enddummy->parent;
  if(isLeftof(enddummy,end)){
    end->left == nullptr;
  }
  else if(!isLeftof(enddummy,end)){
    end->right == nullptr;
  }
  recc_heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}