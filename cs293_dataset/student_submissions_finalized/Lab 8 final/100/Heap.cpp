#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

//finds binary representation of the number given to it in form of string
string buildBinary(int num){
  string res="";
  int x=num;
  while(x>0){
    res = to_string(x%2) + res;
    x/=2;
  }
  return res;
}

//updates the ordering of nodes after adding a new node to heap
template<typename T>
void update(TreeNode<T>* curr,TreeNode<T>* root){
  while(curr!=root){
    if(curr->parent->object < curr->object){
      swap(curr->object,curr->parent->object);
      curr=curr->parent;
    }else return;
  }
}

//returns the node on which insertion or deletion can be done by taking binary format of
//its parent node
template<typename T>
TreeNode<T>* getFreeNode(string path,TreeNode<T> *node){
  if(path=="0")return node;
  if(node==nullptr)return nullptr;
  for(int i=1; i<path.length();i++){
    if(path[i]=='0')node=node->left;          //moves to left node in heap
    else node=node->right;
  }
  return node;
}

//inserts a new node with given data as arguments 
//for this it finds binary representation of number of nodes currently present in heap
//and goes to the position of parent node where next node should be inserted.
template<typename T>
void Heap<T>::insert(T obj) {
  if(root==nullptr){
    root=new TreeNode<T>(obj);
    numNodes++;
    return;
  }

  string s=buildBinary((numNodes+1)/2);                   //finds binary representation
  TreeNode<T>* node=getFreeNode(s,root);                //finds parent node
  TreeNode<T>* curr , *newNode=new TreeNode<T>(obj);

  if(node->left==nullptr){
    node->left=newNode;
    newNode->parent=node;
    curr=newNode;
    numNodes++;
  }
  else {
    node->right=newNode;
    newNode->parent=node;
    curr=newNode;
    numNodes++;
  }
  update(curr,root);                      //updates the heap
}

//Heapifies heap to maintain heap properties voilated due to deletion of nodes
template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  if(node==nullptr)return;
  if(node->left==nullptr)return;
  if(node->right==nullptr){
    if(node->object < node->left->object)
      swap(node->object,node->left->object);
      heapify(node->left);
  }
  else{
    if(node->left->object<node->right->object){
      if(node->object < node->right->object){
        swap(node->object,node->right->object);
        heapify(node->right);
      }
    }
    else{
      if(node->object < node->left->object){
        swap(node->object,node->left->object);
        heapify(node->left);
      }
    }
  }
}

//deletes maximum node i.e. root from heap
template<typename T>
void Heap<T>::delMax() {
  if(numNodes<=0)return;
  if(numNodes==1){
    root=nullptr;
    numNodes--;
    return;
  }
  string s=buildBinary(numNodes/2);
  TreeNode<T>* node=getFreeNode(s,root);
  if(node->right!=nullptr){
    swap(root->object,node->right->object);
    node->right=nullptr;
    numNodes--;
  }else{
    swap(root->object,node->left->object);
    node->left=nullptr;
    numNodes--;
  }
  heapify(root);

  return;
}

//prints data of all nodes reccursively in well structured format
template<typename T>
void printAll(TreeNode<T> *node, const string& prefix, bool isLeft){
   if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;
        
        printAll(node->left, prefix + (isLeft ? "│   " : "    "), true);
        printAll(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }     
}

//prints the heap
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  printAll(node,"", false);
  
}

  
