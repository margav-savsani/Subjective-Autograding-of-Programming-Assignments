#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
void swap(TreeNode<T> *pa,TreeNode<T> *ch){
  if(ch->parent==pa){
    TreeNode<T> *pap=pa->parent;
    TreeNode<T> *pal=pa->left;
    TreeNode<T> *par=pa->right;
    TreeNode<T> *chl=ch->left;
    TreeNode<T> *chr=ch->right;
    TreeNode<T> *p=pa;
    chl->parent=pa;
    chr->parent=pa;
    pa->left=chl;
    pa->right=chr;
    pa->parent=ch;
    if(pal==ch){
      ch->left=pa;
      ch->right=par;
      par->parent=ch;
    }
    if(par==ch){
      ch->left=pal;
      pal->parent=ch;
      ch->right=pa;
    }
    ch->parent=pap;
    if(pap!=nullptr){
      if(pap->right==p){
        pap->right=ch;
      }
      else if(pap->left==p){
        pap->left=ch;
      }
    }
  }
}

template<typename T>
TreeNode<T> * nullchild(TreeNode<T> *node){
  if(node->left==nullptr){return node;}
}
template<typename T>
void heapify(TreeNode<T> *node){
  if(node==nullptr){return;}
  TreeNode<T> *nl=node->left;
  TreeNode<T> *nr=node->right;

  if(!(node->object >= nl->object && node->object >= nr->object)){
    if(nl->object > nr->object){
      swap(node,nl);
      heapify(node);
    }
    else{
      swap(node,nr);
      heapify(node);
    }
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root==nullptr){root=new TreeNode(obj); return;}
  if(root->left==nullptr){
    TreeNode<T> *x=new TreeNode(obj);
    root->left=x; 
    if(x>root){
      swap(root,x);
    }
    return;
  }
  if(root->right==nullptr){
    TreeNode<T> *x=new TreeNode(obj);
    root->right=x; 
    if(x>root){
      swap(root,x);
    }
    return;
  }

  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
