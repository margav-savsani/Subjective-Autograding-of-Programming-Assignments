#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<string.h>

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::HeapifyUp(TreeNode<T>* node){//from down to up

    T obj;
    if(node!=root){
      // cout<<node->parent->object<<endl;
      if( node->parent->object < node->object ){
        // cout<<"uu"<<endl;
        obj = node->object;
        node->object = node->parent->object;
        node->parent->object = obj;
        node = node->parent;
        HeapifyUp(node);
      }
    }
  
}

template<typename T>
void Heap<T>::HeapifyDown(TreeNode<T> *node){
  TreeNode<T> *temp1, *temp2;
  if(node->left == nullptr ) return;
  if(node->right == nullptr){
    if( node->object < node->left->object ){
      T obj = node->object;
      node->object = node->left->object;
      node->left->object = obj;
    }
    return ;
  }
  else{
    if(node->right->object < node->left->object ){
      T obj = node->object;
      node->object = node->left->object;
      node->left->object = obj;
      HeapifyDown(node->left);
    }
    else{
      T obj = node->object;
      node->object = node->right->object;
      node->right->object = obj;
      HeapifyDown(node->right);
    }
    
  }
}

template<typename T>
void Heap<T>::insert(T obj) {

  if(noOfNodes==0){
    root = new TreeNode<T>(obj);
    noOfNodes++;
    lastNode = root;
    return ;
  }
    noOfNodes++;
    int binaryNum[32];
 
    int i = 0;
    int n = Heap<T>::noOfNodes;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = int(n / 2);
        i++;
    } 
 
    // printing binary array in reverse order
    TreeNode<T> *tempDum = root;
    TreeNode<T> *temp = root;
    bool left = true;
    for (int j = i-1-1 ; j >= 0 && tempDum!=NULL; j--){
      temp = tempDum;
      if(binaryNum[j]==0){
        tempDum = tempDum->left;
        left = true;
      }
      if(binaryNum[j]==1){
        tempDum = tempDum->right;
        left = false;
      }
    }
    if(left){
      temp->left = new TreeNode<T>(obj);
      temp->left->parent = temp;
      lastNode = temp->left;
      Heap<T>::HeapifyUp(temp->left);
    }
    else{
      temp->right = new TreeNode<T>(obj);
      temp->right->parent = temp;
      lastNode = temp->right;
      Heap<T>::HeapifyUp(temp->right);
    }    
  // Heap<T>::printHeap(root);
  return;
}

template<typename T>
void Heap<T>::delMax() {

  if(noOfNodes==0){
    return ;
  }
  if(noOfNodes==1){
    root = nullptr;
    lastNode = nullptr;
    noOfNodes--;
    return;
  }

  T obj = root->object;
  root->object = lastNode->object;
  lastNode->object = obj;

  noOfNodes--;

  int binaryNum[32];
 
    int i = 0;
    int n = Heap<T>::noOfNodes;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = int(n / 2);
        i++;
    } 

    // printing binary array in reverse order
    TreeNode<T> *tempDum = root;
    TreeNode<T> *temp = root;
    bool left = true;
    for (int j = i-1-1 ; j >= 0 && tempDum!=NULL; j--){
      temp = tempDum;
      if(binaryNum[j]==0){
        tempDum = tempDum->left;
        left = true;
      }
      if(binaryNum[j]==1){
        tempDum = tempDum->right;
        left = false;
      }
    }
    if(left){
      lastNode = temp->left;
    }
    else{
      lastNode = temp->right;
    }    
    HeapifyDown(root);

  return;
}

template<typename T>
void Heap<T>:: printHeap(TreeNode<T> *root){

  static bool isLeft = true;
  static string thresh=" "; 
  // static string th = thresh;
  // static bool isl = isLeft;
  string th = thresh;
  bool isl = isLeft;
  static int r=0;
  r++;
    if(r==0){
      th = thresh = "";
      isl = isLeft = true;
      cout<<endl;
      // root = this->root;
    }
    if( root != nullptr )
    {
      // cout<<root->object<<endl;
        cout << thresh;
        if(r!=1)
        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch 
        th = thresh;
        isl = isLeft;
        if(r!=1)
        thresh = thresh + (isLeft ? "│   " : "    ");
        isLeft = true;
        printHeap( root);
        // r--;
        root = curr->right;
        if(r!=1)
        thresh = th + (isl ? "│   " : "    ");
        isLeft = false;
        printHeap(root);
        // r--;
        this->root = curr;
        thresh = th;
        isLeft = true;
        // root = curr;
    }
    r--;
}

// template<typename T>
// void Heap<T>::printHeap(TreeNode<T> *node) {

//   // insert your code here

//    displayAboveThresh("", true);

//   return;
// }
// template<typename T>
//   void Heap<T>::displayAboveThresh(const string &  thresh, bool isLeft){
    
//          if( root != nullptr )
//     {
//       // cout<<root->object<<endl;
//         cout << thresh;

//         cout << (isLeft ? "|--" : "|__" );

//         // print the value of the node
//         cout << root->object << endl;
//         TreeNode<T> *curr = root;
//         root = root->left;
//         // enter the next tree level - left and right branch
//         displayAboveThresh( thresh + (isLeft ? "│   " : "    "), true);
//         root = curr->right;
//         displayAboveThresh( thresh + (isLeft ? "│   " : "    "), false);
//         root = curr;
//     }
//   }


template<typename T>
void Heap<T>::DestroyRecursive(TreeNode<T> *&node)
{
    if (node)
    {
        DestroyRecursive(node->left);
        DestroyRecursive(node->right);
        delete node;
        // cout<<"deleted\n";
    }
}

// template<typename T>
// Heap<T>::~Heap()
// {
//     DestroyRecursive(root);
// }

// int main(){
//   Heap<int> *h = new Heap<int>();
//   h->insert(5);
//   h->insert(6);
//   h->insert(7);
//   h->insert(8);
//   h->printHeap(h->root);
  
// }

  
