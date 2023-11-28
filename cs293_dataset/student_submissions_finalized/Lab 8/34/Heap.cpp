#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  count++;
  if(root == nullptr){
    root = new TreeNode<T>(obj);
    return;
  }
  // Tree with only one child
  int demo_count = count;
  TreeNode<int> *bin = new TreeNode<int>(demo_count % 2);
  demo_count = demo_count/2;
  while(demo_count/2 != 0){
    bin->left = new TreeNode<int>(demo_count % 2);
    bin = bin->left;
    demo_count /= 2;
  }
  TreeNode<T> *curr = root;
  while(bin->parent != nullptr){
    if(bin->object == 0){
      curr = curr->left;
    }
    else curr = curr->right;
    bin = bin->parent;
  }
  if(bin->object == 0){
    curr->left = new TreeNode<T>(obj);
    curr->left->parent = curr;
    curr = curr->left;
  }
  else{
    curr->right = new TreeNode<T>(obj);
    curr->right->parent = curr;
    curr = curr->right;
  }
  while(curr->parent != nullptr){
    if(curr->parent->object < curr->object){
      T temp = curr->object;
      curr->object = curr->parent->object;
      curr->parent->object = temp;
      curr = curr->parent;
    }
    else break;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  int demo_count = count;
  TreeNode<int> *bin = new TreeNode<int>(demo_count % 2);
  demo_count = demo_count/2;
  while(demo_count/2 != 0){
    bin->left = new TreeNode<int>(demo_count % 2);
    bin = bin->left;
    demo_count /= 2;
  }
  TreeNode<T> *curr = root;
  while(bin != nullptr){
    if(bin->object == 0){
      curr = curr->left;
    }
    else curr = curr->right;
    bin = bin->parent;
  }
  root->object = curr->object;
  if(curr->parent->left == curr){
    curr->parent->left = nullptr;
    curr->parent = nullptr;
  }
  else{
    curr->parent->right = nullptr;
    curr->parent = nullptr;  
  }
  delete curr;
  curr = root;
  bool done = false;
  while(!(curr->left == nullptr || curr->right == nullptr)){
    T max;
    bool isLeft = false;
    if(curr->left->object > curr->right->object){
      max = curr->left->object;
      isLeft = true;
    }
    else max = curr->right->object;
    if(curr->object < max){
      if(isLeft){
        curr->left->object = curr->object;
        curr->object = max;
        curr = curr->left;
      }
      else{
        curr->left->object = curr->object;
        curr->object = max;
        curr = curr->left;
      }
    }
    else done = true;break;
  }
  if(!done){
    if(curr->left == nullptr){
      if(curr->right->object > curr->object){
        T temp = curr->object;
        curr->object = curr->right->object;
        curr->right->object = temp;
      }
    }
    else{
      if(curr->left->object > curr->object){
        T temp = curr->object;
        curr->object = curr->left->object;
        curr->left->object = temp;
      }
    }
  }
  count--;
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  Heap<T> demo = *root;
  
  return;
}
template<typename T>
void Heap<T>::printTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

  
int main(){
  Heap<int> *H = new Heap<int>();
  cout << "use 100 to insert and 200 to delete and 300 to getMax and 0 to exit : " << endl;
  int command;
  while(true){
    cin >> command;
    if(command == 100){
      cout << "Enter the num\n";
      int p;
      cin >> p;
      H->insert(p);
    }
    else if(command == 200){
      H->delMax();
    }
    else if(command == 300){
      cout << "the max is : " << H->getMax() << endl;
    }
    else if(command == 0){
      return 0;
    }
    else if(command == 400){
      H->printTree(H->getRoot(), "", false);
    }
    else{
      cout << "Invalid command\n";
    }
  }
}