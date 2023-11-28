#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
int Heap<T>::decimalToBinary(int N)
{
    // To store the binary number
    long int B_Number = 0;
    int cnt = 0;
    while (N != 0) {
        int rem = N % 2;
        long int c = pow(10, cnt);
        B_Number += rem * c;
        N /= 2;
        // Count used to store exponent value
        cnt++;
    }
    return B_Number;
}

template<typename T>
void Heap<T>::insertheapify(TreeNode<T> *node){
  if(node == root){
    return ;
  }
    if( node->parent->object < node->object ){
      Review temp = node->object;
      node->object = node->parent->object;
      node->parent->object= temp;
      insertheapify(node->parent);
    }
  return ;
}


template<typename T>
void Heap<T>::insert(T obj) {

n=n+1;

int num = decimalToBinary(n);
// declaring output string stream
ostringstream str1;
// Sending a number as a stream into output
// string
str1 << num;
// the str() converts number into string
string heap = str1.str();
int p = heap.length(); 
// insert your code here
TreeNode<T> *x =  new TreeNode<T> (obj);
TreeNode<T> *y;

if(p==1){
  root = x;
  return ;
}
TreeNode<T> *t = root;
for(int i=1;i<p;i++){

  if(heap[i]==0){
    y=t;
    t=t->left;
  }
  else{
    y=t;
    t=t->right;
  } 
}
 
if(heap[p-1]==1){
  y->left=x;
  x->parent = y;
} 
else{
  y->right=x;
  x->parent = y;}

insertheapify(x);


}


template<typename T>
TreeNode<T>* Heap<T>::find(){
int num = decimalToBinary(n);
ostringstream str1;
str1 << num;
// the str() converts number into string
string heap = str1.str();
int p = heap.length(); 
// insert your code here
TreeNode<T> *y;
 
 TreeNode<T> *t = root;
for(int i=1;i<p;i++){

  if(heap[i]==0){
    y=t;
    t=t->left;
  }
  else{
    y=t;
    t=t->right;
  } 
}
 return t;
}



template<typename T>
void Heap<T>::  Heapify(TreeNode<T> *node){
  TreeNode<T> *left;
  TreeNode<T> *right;
  left=node->left;
  right = node->right;
  if(node == NULL){
    return ;
  }
  if(left == NULL && right == NULL){
    return ;
  }
  
  else if(left == NULL || right == NULL){
   
    if (left!=NULL && node->object < left->object){ 
      
    Review temp = node->object;
    node->object = left->object;
    left->object= temp;
    Heapify(left);}
    if (right!=NULL && node->object < right->object){ 

    Review temp = node->object;
    node->object = right->object;
    right->object= temp;
    Heapify(right);}
    return ; 
  }
  else if(node->object<left->object){
    if(left->object<right->object){
    Review temp = node->object;
    node->object = right->object;
    right->object= temp;
    Heapify(right);
    }
    else{
    Review temp = node->object;
    node->object = left->object;
    left->object= temp;
    Heapify(left);  
    }
    return ;
  }
  else if(node->object<right->object){
    if(right->object<left->object){
    Review temp = node->object;
    node->object = left->object;
    left->object= temp;
    Heapify(left);
    }
    else{
    Review temp = node->object;
    node->object = right->object;
    right->object= temp;
    Heapify(right); 
    }
  }
  
  }


template<typename T>
void Heap<T>::delMax() {
 if(root->left==NULL&&root->right==NULL){
    root=nullptr;
  }
TreeNode<T> *p; 
  p=find();
  Review obj = p->object;
  root->object = obj;
  p=nullptr;
  
  Heapify(root);
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(const string& prefix, bool isLeft)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object<< endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printHeap( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printHeap( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

