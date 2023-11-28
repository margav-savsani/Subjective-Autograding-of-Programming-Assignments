#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <cmath>
#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void swap(TreeNode<T>* n1,TreeNode<T>* n2){
  T tmp=n2->object;
  n2->object=n1->object;
  n1->object=tmp;
}

template<typename T>
void Heapify(TreeNode<T> *node){
  if(node!=nullptr){
    TreeNode<T>* nl=node->left;
    TreeNode<T>* nr=node->right;
    if(nl!=nullptr && nr!=nullptr){
      if(!((nl->object < node->object) && (nr->object < node->object))){
        if(nl<nr){
          swap(nr,node);
          Heapify(nr);
        }
        else if(nr<nl){
          swap(nl,node);
          Heapify(nl);
        }
      }
    }
    
    if(nr==nullptr){
      if(!(nr->object < node->object)){
        swap(nl,node);
      }
    }
  }

}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  if(root==nullptr){
    root=new TreeNode<T>(obj);
    root->pos=1;
    incmaxIndex();
    lastnode=root;
    return;
  }
  TreeNode<T> *tmproot=root;
  int inspos=1+getmaxIndex();
  TreeNode<T> *insnode;
  while(true){

    int height=int(log2(inspos/tmproot->pos));

    if(height==1){
      if(inspos%2==0){
        tmproot->left=new TreeNode<T>(obj);
        tmproot->left->pos=inspos;
        tmproot->left->parent=tmproot;
        lastnode=tmproot->left;
        incmaxIndex();
        insnode=tmproot->left;
        break;
      }
      if(inspos%2==1){
        tmproot->right=new TreeNode<T>(obj);
        tmproot->right->pos=inspos;
        tmproot->right->parent=tmproot;
        lastnode=tmproot->right;
        incmaxIndex();
        insnode=tmproot->right;
        break;
      }
    }

    int check=pow(2,height-1)*((2*tmproot->pos)+1);
    if(inspos<check){
      tmproot=tmproot->left;
    }
    else{
      tmproot=tmproot->right;
    }
  }
  while(insnode->parent!=nullptr){
    if(!(insnode<insnode->parent))
    {
      swap(insnode,insnode->parent);
      insnode=insnode->parent;
    }
    else{
      break;
    }
  }
  
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  root->object=lastnode->object;
  lastnode=nullptr;
  decmaxIndex();
  Heapify(root);
  return;
}

template<typename T>
void Heap<T>::print(TreeNode<T> *Node, const string& prefix, bool isLeft){
  // if (Node != nullptr){
  //   cout << prefix;
  //   cout << (isLeft ? "|--" : "|__");
  //   cout << Node->object<< endl;
  //   TreeNode<T> *curr = Node;
  //   TreeNode<T> *Nodel;
  //   TreeNode<T> *Noder;
  //   Nodel = Node->left;
  //   print(Nodel, prefix + (isLeft ? "|   " : "    "), true);
  //   Noder = Node->right;
  //   print(Noder, prefix + (isLeft ? "|   " : "    "), false);
  //   Node = curr;
  // }
  // else if (Node == nullptr){
  //   cout << "NULL tree";
  // }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  print(node, "", false);
  return;
}
  
