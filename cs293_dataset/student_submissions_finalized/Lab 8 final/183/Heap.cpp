#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
TreeNode<T> *Heap<T>::find(int l,TreeNode<T> *node,TreeNode<T> *prev,int p){
  if((node==NULL)&&(l==p)){return prev;}
  if(node==NULL){return NULL;}
  TreeNode<T> *x=find(l+1,node->left,node,p);
  if(x!=NULL){return x;}
  x=find(l+1,node->right,node,p);
  if(x!=NULL){return x;}
  return NULL;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *z=root;
  TreeNode<T> *prev=NULL;
  TreeNode<T> *h;
  if(z==NULL){root=new TreeNode<T> (obj);
              h=root;
              //printHeap(root);cout<<endl;
              return;
              }
  else{
      int p=-1;
      while(z!=NULL){
        prev=z;
        z=z->left;
        p++;
      }
      z=root;
      TreeNode<T> *x=find(0,z,NULL,p);
      if(x==NULL){
                  prev->left=new TreeNode<T> (obj);
                  prev->left->parent=prev;
                  h=prev->left;
                  }
      else{
        
        prev=x;
        if(prev->left==NULL){ prev->left=new TreeNode<T> (obj);
                              prev->left->parent=prev;
                              h=prev->left;
                            }
        else if(prev->right==NULL){prev->right=new TreeNode<T> (obj);
                              prev->right->parent=prev;
                              h=prev->right;
                              }
      }
  }
  while(true){
    if(h->parent==NULL){break;}
    if(h->parent->object<h->object){
                                  T o=h->object;
                                  h->object=h->parent->object;
                                  h->parent->object=o;
                                  }
    else{break;}
    h=h->parent;
  }
  //printHeap(root);cout<<endl;
  return;
}

template<typename T>
TreeNode<T> *Heap<T>::findl(int l,TreeNode<T> *node,TreeNode<T> *prev){
  if((l==0)&&(node==NULL)){return prev;}
  if(l==0){return node;}
  else{
    TreeNode<T> *x=findl(l-1,node->left,prev);
    if(x==prev){return x;}
    if(x!=NULL) prev=x;
    x=findl(l-1,node->right,prev);
    if(x==prev){return x;}
    if(x!=NULL) prev=x;
    return prev;
    }
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  int l=-1;
  TreeNode<T> *z=root;
  if(root->left==NULL && root->right==NULL){root=NULL;return;}
  while(z!=NULL){z=z->left;l++;}
  TreeNode<T> *x=root;
  TreeNode<T> *p=findl(l,x,NULL);
  root->object=p->object;
  if(p->parent->right==NULL){p->parent->left=NULL;}
  else{p->parent->right=NULL;}
  delete(p);
  x=root;
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
  //printHeap(root);
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  static string pre = "";
  static bool left = false;
  static int recursion_level = 0;
  if(node==nullptr){return;}

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
      left=false;
      x = x + "   ";
      pre=x;
      printHeap(node->right);
  }
  recursion_level--;

  return;
}