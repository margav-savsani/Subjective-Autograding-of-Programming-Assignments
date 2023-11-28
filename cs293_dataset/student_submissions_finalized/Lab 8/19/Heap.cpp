#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  cout << "no.of inserts" << endl;
  if(count == 0){
    root = new TreeNode<T>(obj);
    count ++;
    return;
    cout << "first step" ;
  }
  
  TreeNode<T> *a;
  a = root;
  count ++;
  int binaryNum[32];
  int i = 0;

  int size = count;

  while (size > 0) {
    binaryNum[i] = size % 2;
    size = size / 2;
    i++;
  }
  cout << "count = " << count ;

  for (int j = i - 1; j >= 0; j--){
    cout << j << endl;
    //cout << "reached here" << endl;
    if(binaryNum[j] == 0 && j != 1){
      a = a->left;
      cout << "1 st case" << endl;
    }
    else if(binaryNum[j] == 1 && j != 1){
      a = a->right;
      cout << "2 nd case" << endl;
    }
    else if(j == 1 && binaryNum[j] == 0){
      cout << "3 rd case" << endl;
      a->left = new TreeNode<T>(obj);
      a->left->parent = a;
      break;
    }
    else if(j == 1 && binaryNum[j] == 1){
      cout << "4 th case" << endl;
      // << a->right->object << endl;
      a->right = new TreeNode<T>(obj);
      cout << a->right->object << endl;
      a->right->parent = a;
      break;
    }
  }
  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  printHeap_recursive(root,"", false);

  return;
}
template<typename T>
void printHeap_recursive(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )  {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << (root->object);
    cout << endl;
    TreeNode<T>*curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printHeap_recursive(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeap_recursive(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}
  
