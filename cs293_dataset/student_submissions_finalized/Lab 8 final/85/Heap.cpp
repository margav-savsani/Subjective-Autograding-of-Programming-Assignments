#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::setend(TreeNode<T> *t){
   if(t->parent ==NULL){
    end =t;
    while(end->left != NULL){
      end= end->left;
    }
   }
   else if(t->parent->left == t){
    end = t->parent->right;
    while(end->left != NULL){
      end = end->left;
    }
   }
   else if(t->parent->right == t){
    setend(t->parent);
   }
}
template<typename T>
void Heap<T>::heapify(TreeNode<T> *t){
   if(t->parent != NULL){
    if(t->parent->object < t->object){
      T val = t->parent->object;
      t->parent->object=t->object;
      t->object = val;
      heapify(t->parent);
    }
   }
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
 
  TreeNode<T> *s=new TreeNode(obj);
  if(root==NULL){
     root=s;
     end=root;
  }
 else if(end->left == NULL){
  end->left= s;
  end->left->parent = end;
  heapify(end->left);
 }
 else{
  end->right = s;
  end->right->parent = end;
  heapify(end->right);
  TreeNode<T> *prevend = end;
  setend(end);
  end->prevend=prevend;
 }
}
template<typename T>
void Heap<T>::revheapify(TreeNode<T> *t){
 if(t==NULL || t->left==NULL){
  return;
 }
 TreeNode<T> *p = t->left;
 if(t->right != NULL && p->object < t->right->object){
  p= t->right;
 }
 if(t->object < p->object){
  T val = t->object;
      t->object=p->object;
      p->object= val;
      revheapify(p);
 }
}
template<typename T>
void Heap<T>::delMax() {

  // insert your code here
 
  if(root == NULL){
    return;}
    if(end == root){
      end = NULL;
      root = NULL;
    }
  else{
    if(end->right != NULL){
      T val = end->right->object;
      end->right->object=root->object;
      root->object = val;
      end->right = NULL;
      revheapify(root);
    }
    else if(end->left != NULL){
       T val = end->left->object;
      end->left->object=root->object;
      root->object = val;
      end->left = NULL;
      revheapify(root);
    }
    else{
      end=end->prevend;
      delMax();
    }
  }
  return;
}
template<typename T>
void Heap<T>::printt(TreeNode<T>* Node,const string &prefix, bool isLeft )
{
    if (Node != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << Node->object << endl;
        TreeNode<T> *curr = Node;
        Node = Node->left;
        // enter the next tree level - left and right branch
        printt(Node,prefix + (isLeft ? "│   " : "    "), true);
        Node = curr->right;
        printt(Node,prefix + (isLeft ? "│   " : "    "), false);
        Node= curr;
    }
}
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  printt(root,"",false);
  return;
}

  
