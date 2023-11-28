#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"


#endif
#include<math.h>
template<typename T> void printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}

template<typename T>
void Heap<T>::swap(TreeNode<T> *A, TreeNode<T> *B)
{
  T tmp = A->object;
  A->object = B->object;
  B->object = tmp;

  return;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr) //Insertion when Heap is empty.
  {
    root = new TreeNode<T>(obj);
    return;
  }
  else
  {
    if(root->left == nullptr) //Base case 1: Reached a leaf node.
    {
      root->lastlevel = 1; //We add left child to this leafnode,height becomes 1
      root->nodesAtLastLevel=0;
      TreeNode<T> *n = new TreeNode<T>(obj);
      n->parent = root;
      root->left = n;
      root->nodesAtLastLevel++; //Nodes at base become 1.
      if(root->object < root->left->object) this->swap(root, root->left); //Swapping in order to satisfy Max-Heap property.
      
      return; 
    }
    if(root->right == nullptr) //Base Case 2: We reach a node who doesn't have a right child.
    {
      TreeNode<T> *n = new TreeNode<T>(obj);
      n->parent = root;
      root->right = n;
      root->nodesAtLastLevel++; //Height remains same. Number of nodes at base increasesby 1, becomes 2.
      if(root->object < root->right->object) this->swap(root, root->right); //Swapping in order to satisfy Max-Heap property.
      return; 
    }
    if(root->nodesAtLastLevel== int(pow(2,root->lastlevel)+0.001))
     // Since last level is height, max no.of nodes at height are 2^lastlevel. This conditions implies that no more nodes
      // can be added at this height, and we get the indication to add nodesat next level, i.e., increase the height.
    {
      TreeNode<T> *curr =root;
      root = root->left; //To satisfy left filled property, we keep moving left.
      this->insert(obj); //Recursion
      root = curr;
      root->lastlevel = root->left->lastlevel + 1; //Updating height.
      root->nodesAtLastLevel=1; //Since a node was added at a new height, no. of nodes at lastlevel is 1.
      if(root->object < root->left->object) this->swap(root, root->left); //Swapping in order to satisfy Max-Heap property.
      return;
    }
    else if(root->nodesAtLastLevel < int(pow(2,root->lastlevel)+0.001)/2) 
    // If the lastlevel is filled less than half the capacity, we can add a node in left subtree. This condition tells us exactly this.
    {
      TreeNode<T> *curr =root;//Storing original root
      root = root->left; //Moving into left subtree
      this->insert(obj);//Recursion
      root = curr;//Restoring root to original root.
      root->nodesAtLastLevel++; //Condition for checking a fully filled lastlevel is already checked, so we skip height increment check.
      if(root->object < root->left->object) this->swap(root, root->left);//Swapping in order to satisfy Max-Heap property.
      return;
    }
    else
    {
      // If the lastlevel is filled equal to or more than half,  we can add new node in right subtree.
      TreeNode<T> *curr =root;
      root = root->right;
      this->insert(obj);
      root = curr;
      root->nodesAtLastLevel++;
      if(root->object < root->right->object) this->swap(root, root->right);
      return;
    }
  }

}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *A)
{
  if(A->left==nullptr) return;
  if(A->right==nullptr)
  {
    if(A->object < A->left->object) swap(A, A->left);
    
    return;
  }
  if(A->left->object < A->right->object)
  {
    
    swap(A,A->right);
    
    TreeNode<T> *curr = A;
    A = A->right;
    Heapify(A);
    A = curr;
    return;
  }
  else{
    
    swap(A, A->left);

    TreeNode<T> *curr = A;
    A = A->left;
    Heapify(A);
    A = curr;
    return;
  }
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode<T> *curr = root;
  if(curr==nullptr) return;
  while(curr->left != nullptr || curr->right !=nullptr)
  {
    if(curr->left==nullptr) break;
    if(curr->nodesAtLastLevel == int(pow(2,curr->lastlevel) + 0.001))
    {
      curr = curr->right;
    }
    else if(curr->nodesAtLastLevel <= int(pow(2,curr->lastlevel)+0.001)/2)
    {
      curr = curr->left;
    }
    else curr = curr->right;

  }

  if(curr==root)
  {
    delete curr;
    root=nullptr;
    return;
  }

  swap(curr, root);

  TreeNode<T> *tmp = curr->parent;


  if(tmp->right==curr)
  {
    tmp->right=nullptr;
    delete curr;
    tmp->nodesAtLastLevel=1;
  }
  else
  {
    tmp->left=nullptr;
    delete curr;
    tmp->lastlevel=0;
    tmp->nodesAtLastLevel=0;
  }

  tmp = tmp->parent;

  if(tmp==nullptr) return;

  while(tmp->parent != nullptr)
  {
    tmp->lastlevel=tmp->left->lastlevel + 1;
    tmp->nodesAtLastLevel--;
    if(tmp->left !=nullptr && tmp->nodesAtLastLevel==0)
    {
      tmp->nodesAtLastLevel = int(pow(2, tmp->lastlevel) + 0.001);
    }
    tmp = tmp->parent;
  }
  tmp->lastlevel=tmp->left->lastlevel + 1;
  tmp->nodesAtLastLevel--;
  if(tmp->left !=nullptr && tmp->nodesAtLastLevel==0)
    {
      tmp->nodesAtLastLevel = int(pow(2, tmp->lastlevel) + 0.001);
    }

  Heapify(root);
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  printBinaryTree(node, " ", false);
  return;
}

template<typename T>
TreeNode<T>* Heap<T>::getRoot()
{
  return this->root;
}


