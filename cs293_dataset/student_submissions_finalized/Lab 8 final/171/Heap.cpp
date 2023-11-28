#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heapify(TreeNode<T> *node){
  TreeNode<T> *x = node;
  while(true){
    if(((x->left==NULL)&&(x->right==NULL))) break;
    else if(x->right==NULL){
          if(x->object<x->left->object){
                      T o=x->left->object;
                      x->left->object=x->object;
                      x->object=o;
                      break;}
          else break;
    }
    else{
        if((x->object<x->left->object) || (x->object<x->right->object)){
              if(x->left->object<x->right->object){
                                          T o=x->right->object;
                                          x->right->object=x->object;
                                          x->object=o;
                                          x=x->right;}
              else{
                    T o=x->left->object;
                    x->left->object=x->object;
                    x->object=o;
                    x=x->left;
                    }
        }
        else break;
  }}
}

template<typename T>
TreeNode<T> * Heap<T>::findspace(TreeNode<T> *node,int l,TreeNode<T> *par,int h){
  if(node==NULL && l==h)
    return par;
  if(node==NULL)
    return NULL;
  TreeNode<T> *x = findspace(node->left,l+1,node,h);
  if(x!=NULL)
    return x;
  x = findspace(node->right,l+1,node,h);
  if(x!=NULL)
    return x;
  return NULL;
}

template<typename T>
void Heap<T>::insert(T obj) {
  int h = 0;
  TreeNode<T> *x = root;
  TreeNode<T> *par = NULL;
  TreeNode<T> *prev=NULL;
  while(x){
    par = x;
    h++;
    x=x->left;
  }
  if(root==NULL){
    root = new TreeNode<T> (obj);
    return;
  }
  x = root;
  
  TreeNode<T> *node = findspace(root,1,NULL,h);

  if(node==NULL){
    par->left = new TreeNode<T> (obj);
    par->left->parent = par;
    prev=par->left;
  }
  else{
    par = node;
    if(par->left==NULL){
      par->left = new TreeNode<T> (obj);
      par->left->parent = par;
      prev=par->left;
    }
    else if(par->right==NULL){
      par->right = new TreeNode<T> (obj);
      par->right->parent = par;
      prev=par->right;
    }
  }
  
  while(true){
    if(prev->parent==NULL) break;
    if(prev->parent->object<prev->object){
        T x=prev->object;
        prev->object = prev->parent->object;
        prev->parent->object = x; 
    }
    else{break;}
    prev = prev->parent;
  }
  printHeap(root);
  return;
}

template<typename T>
TreeNode<T> *Heap<T>::findl(int l,TreeNode<T> *node,TreeNode<T> *prev){
  if((l==0)&&(node==NULL))
    return prev;
  if(l==0)
    return node;
  else{
    TreeNode<T> *x=findl(l-1,node->left,prev);
    if(x==prev)
      return x;
    if(x!=NULL) 
      prev=x;

    x=findl(l-1,node->right,prev);
    if(x==prev)
      return x;
    if(x!=NULL) 
      prev=x;
    return prev;
  }
}

template<typename T>
void Heap<T>::delMax() {

  int l=-1;
  TreeNode<T> *x=root;

  if(root->left==NULL && root->right==NULL){
    root=NULL;
    return;
  }
  while(x){
    x=x->left;
    l++;
  }
  x = root;
  TreeNode<T> *p=findl(l,x,NULL);
  root->object=p->object;
  if(p->parent->right==NULL){p->parent->left=NULL;}
  else{p->parent->right=NULL;}
  delete(p);

  printHeap(root);
  Heapify(root);
  printHeap(root);
}


template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  static string pre = "";
  static bool left = false;
  static int recursion_level = 0;

  recursion_level++;
  if (recursion_level == 1)
  {
      pre = "";
      left = false;
  }

  if (node != nullptr)
  {
      if (left) cout << pre <<"|--" << node->object << "\n";
      else cout << pre << "|__" << node->object << "\n";
      string x=pre;
      pre = pre + "   ";
      left = true;
      printHeap(node->left);
      x=x+"   ";
      pre=x;
      left = false;
      printHeap(node->right);
  }
  recursion_level--;

  return;
}

  
