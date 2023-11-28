#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
void exchange(TreeNode<T> *A, TreeNode<T> *B){// This is my own swap function to exchange objects of A,B by creating new variable c.
  T c = A->object;
  A->object = B->object;
  B->object = c;
}
template<typename T>
void Heapify(TreeNode<T> *node){// This function will check max Heap property at every and node if not satisfied at any then it swaps the elements accordingly.
  if(node->left == nullptr && node->right == nullptr){
    return;
  }
  else if(node->left != nullptr && node->right == nullptr){
    if(node->object < node->left->object){
      exchange(node, node->left);// swapping left child of node.
    }
    else{
      return;// If heap property is satisfied
    }
  }
  else{
    if(node->left->object < node->object && node->right->object < node->object){
      return;
    }
    else if(node->object < node->left->object && node->right->object < node->object){
      exchange(node, node->left);// swapping left child of node.
      Heapify(node->left);// recursive call with left child of node.
    }
    else if(node->object < node->right->object && node->left->object < node->object){
      exchange(node, node->right);// swapping right child of node.
      Heapify(node->right);// recursive call with right child of node.
    }
    else if(node->object < node->right->object && node->object < node->left->object){
      if(node->left->object < node->right->object){
        exchange(node, node->right);// swapping right child of node.
         Heapify(node->right);// recursive call with right child of node.
      }
      else{
        exchange(node, node->left);// swapping left child of node.
        Heapify(node->left);// recursive call with left child of node.
      }
    }
  }  
}

int count = 0;
template<typename T>
void Heap<T>::insert(T obj) {// Inserts the element travsersal is done by getting count of nodes.
  TreeNode<T> *x = root;
  TreeNode<T> *x1 = new TreeNode<T>(obj);
  TreeNode<T> *z = nullptr;
  count++;
  int *arr = new int();// creates an array of 0,1.
  int y = count;
  int sz = 0;
  x = root;
  if(root == nullptr){
    root = x1;// inserting root.
    return;
  }
  while(y != 1){
    arr[sz] = y%2;
    y = y/2;
    sz++;
  }
  for(int i=0;i<(sz/2);i++){
    int a;
    a = arr[sz-i-1];
    arr[sz-i-1] = arr[i];
    arr[i] = a;
  }
  for(int k=0;k<sz;k++){
    z = x;
    if(arr[k] == 0){
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  if(z->left == nullptr){// checking if left child is empty and assigining x1.
    z->left = x1;
    x1->parent = z;
  }
  else{// checking if right child is empty and assigining x1.
    z->right = x1;
    x1->parent = z;
  }
  for(int k=0;k<sz;k++){
    if(x1->parent->object < x1->object){// maintaining the heap property.
      exchange(x1, x1->parent);
    }
    x1 = x1->parent;
  }
  return;
  }

template<typename T>
T Heap<T>::delMax(){// Will delete the root and will put last element in root and perform Heapify.
  T a = root->object;
  TreeNode<T> *x = root;
  TreeNode<T> *z = nullptr;
  int *arr;
  int y = count;
  arr = new int();// An array of 0, 1's.
  int sz = 0;
  if(root->left == nullptr && root->right == nullptr){// if single element is present then delete it.
    root = nullptr;
    count--;
    return a;
  }
   while(y != 1){
    arr[sz] = y%2;
    y = y/2;
    sz++;
  }
  for(int i=0;i<(sz/2);i++){// Used for traversal along the heap.
    int a;
    a = arr[sz-i-1];
    arr[sz-i-1] = arr[i];
    arr[i] = a;
  }
  for(int i=0;i<sz;i++){// Traversing along tree.
    z = x;
    if(arr[i] == 0){
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  exchange(x, root);// Exchanging the objects of root and x.
  if(z->left == x){// Checking whether x is left or right child of z.
    z->left = nullptr;
  }
  else{
    z->right = nullptr;
  }
  count--;
  Heapify(root);// Heapify to maintain the Heap property of BinaryTree.
  return a;// Returns the object of root.
}

template<typename T>
void Heap<T>::printHeap(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printHeap( prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
        printHeap( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

// int main(){
//   cout << "starting heap for int" << endl;
//   Heap<int> A;
//   while(true){
//     int a;
//     cin >> a;
//     if(a == 1){
//       int b;
//       cin >> b;
//       A.insert(b);
//     }
//     if(a == 2){
//       cout << A.getMax() << " Largest value";
//       continue;
//     }
//     if(a == 3){
//       cout << A.delMax() << "Deleted";
//     }
//     if(a == 4){
//       A.printHeap(A.root);
//     }
//     if(a == 5){
//       break;
//     }
//   }
// }

  
