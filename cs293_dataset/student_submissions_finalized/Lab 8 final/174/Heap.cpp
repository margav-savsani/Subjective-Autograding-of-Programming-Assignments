#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include<vector>

template<typename T>
void Heap<T>::swap(TreeNode<T>* a, TreeNode<T>* b){  //swapping two nodes by inter changing their objects
  T temp=a->object;
  a->object=b->object;
  b->object=temp;
  return;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T>* p){             //Heapifying the tree
  while(p!=NULL){
    if(p->right!=NULL){
      if(p->left->object < p->right->object && p->object < p->right->object){swap(p,p->right);} //right child has higher rating
      if(p->right->object < p->left->object && p->object < p->left->object){swap(p,p->left);}   //left child has higher rating
    }
    else{
      if(p->object < p->left->object){swap(p,p->left);}  //left child has higher rating
    }
    p=p->parent;
  }
  return;
}

template<typename T>
void Heap<T>::heapify2(){
  TreeNode<T>* p;
  p=root;
  while(p!=NULL){
    if(p->right!=NULL){
      if(p->left->object < p->right->object && p->object < p->right->object){ //right child has higher rating
        swap(p,p->right); 
        p=p->right;
      }
      if(p->right->object < p->left->object && p->object < p->left->object){  //left child has higher rating
        swap(p,p->left);
        p=p->left;  
      }
    }
    else{
      if(p->object < p->left->object){  //left child has higher rating
        swap(p,p->left);
        p=p->left;  
      }
    }
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T>* x;
  x=new TreeNode<T>(obj);   //creating a new Treenode
  if(k==0){
    root=x;
    k=1;
    return;
  }
  vector<int> a;
  int p=k+1;
  while(p!=1){
    if(p%2==1){a.push_back(1);}   //vector to track the path where a new node to be inserted
    else{a.push_back(0);}
    p=p/2;
  }
  TreeNode<T>* tra;              //treenode for traversal
  tra=root;
  for(int i=a.size()-1; i>0; i--){
    if(a[i]==0){tra=tra->left;}
    else{tra=tra->right;}
  }
  if(tra->left==NULL){tra->left=x;}
  else{tra->right=x;}
  k=k+1;
  heapify(tra);       //heapifying the heap
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  vector<int> a;
  int p=k; 
  if(p==0){return;}  //heap is empty
  if(p==1){          //heap has only root
    root=NULL;
    k=k-1;
    return;
  }
  while(p!=1){
    if(p%2==1){a.push_back(1);}  //vector to track the path where a new node to be deleted
    else{a.push_back(0);}
    p=p/2;
  }
  TreeNode<T>* tra;
  tra=root;
  for(int i=a.size()-1; i>=0; i--){   //traversal to node to be deleted
    if(a[i]==0){tra=tra->left;}
    else{tra=tra->right;}
  }
  swap(root,tra);             //swapping root with last element
  if(tra->parent->left==tra){     //deleting the node
    tra->parent->left=NULL;
  }  
  else{tra->parent->right=NULL;}
  heapify2();                 //heapifying the heap
  k=k-1;
  return;
}

template<typename T>
void Heap<T>::print(TreeNode<T> *r, const string& prefix, bool isLeft)
{
  if( r != nullptr )   {   //heap non-empty case
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    r->object;
    cout << endl;
    TreeNode<T> *curr = r;
    r = r->left;
    // enter the next tree level - left and right branch
    print(r, prefix + (isLeft ? "│   " : "    "), true);  //printing left one
    r = curr->right;
    print(r, prefix + (isLeft ? "│   " : "    "), false); //printing right one
    r = curr;
  }
  else {
    cout << "NULL heap" << endl;
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  print(root, "", false);  //calling function print that prints the heap
}
