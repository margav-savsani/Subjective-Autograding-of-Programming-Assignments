#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


// This function returns the address to the TreeNode
// given the index of the node, ordered as in Heap
// Eg. The root is ordered 1, Its left child is 2
// And the right child is 3 and so on..

// The logic we use here to locate a node with given 
// index is to change the base to 2, and the binary 
// representation of the index except the first 1
// is fetching us the position, starting from the root
// 0 means left, and 1 means right
template<typename T>
TreeNode<T>* Heap<T>::getNode(int index){
  vector<int> bits; //vector to store bits
  while(index!=0){  //Inserting binary digits into vector
    bits.push_back(index%2);
    index/=2;
  }
  TreeNode<T>* reqdNode = root;
  if(bits.size() == 1) return reqdNode; //If index = 1, return root
  // If index != 1, then travel through the tree
  // with 0 as left and 1 as right
  for(int i=bits.size()-2;i>=0;i--){
    if(bits[i]==0)reqdNode = reqdNode->left;
    else reqdNode = reqdNode->right;
  }
  return reqdNode;
}

// This function swaps the objects present in 
// nodeA and nodeB
template<typename T>
void Heap<T>::swap(TreeNode<T>* nodeA, TreeNode<T>* nodeB){
  T tmp = nodeA->object;
  nodeA->object = nodeB->object;
  nodeB->object = tmp;
}

// This method updates the heap tree upwards
// starting from currNode till the heap property
// is satisfied.
template<typename T>
void Heap<T>::updateUp(TreeNode<T>* currNode){
  while(currNode->parent != nullptr){
    // Keeping in mind it is a max heap, if the parent node
    // of currNode is smaller than currNode, then we swap them
    // and update currNode to its parent for the next iteration
    // we stop when either the currNode is root(that is currNode
    // ->parent == nullptr) or max heap property is satisfied(
    // that is why currNode->parent is greater than currNode)
    if(currNode->parent->object < currNode->object){
      swap(currNode, currNode->parent);
      currNode = currNode->parent;
    }
    else{
      break;
    }
  }
}

// Inserts a new node with object obj into the Heap
template<typename T>
void Heap<T>::insert(T obj) {
  // When the tree is empty,
  // create a new root with object obj
  if(num == 0){
    root = new TreeNode<T>(obj);
    num++; //Increment num
    return;
  }

  // When the tree has atleast one node
  TreeNode<T>* par = getNode((num+1)/2); // the parent of the node where the insertion shall happer
  num++; //increment num

  if(num%2==0){
    // if num is even, that means insertion
    // is to the left child of par
    par->left = new TreeNode<T>(obj,par);
    updateUp(par->left);
  }
  else{
    // if num is odd, that means insertion
    // is to the right child of par
    par->right = new TreeNode<T>(obj,par);
    updateUp(par->right);
  }
}

// A recursive function to restore the heap property of the 
// heap, starting from the node. This works only when the 
// left child and right child of node are heap balanced
// but the node spoils the balance as a whole
template<typename T>
void Heap<T>::Heapify(TreeNode<T>* node){

  // When left and right children of node are not nullptr
  if(node->left && node->right){
    if(node->right->object < node->object){
      if(node->left->object < node->object){
        // Heap property is satisfied
        return;
      }
      else{
        // left child is greater than node, hence swap them
        // and call heapify on left child
        swap(node, node->left);
        return Heapify(node->left);
      }
    }
    else{
      if(node->left->object < node->object){
        // right child is greater than node, hence swap them
        // and call heapify on right child
        swap(node,node->right);
        return Heapify(node->right);
      }
      else if(node->left->object < node->right->object){
        // both children are greater than node, but right child
        // is larger, hence swap node and right child and 
        // call heapify on right child
        swap(node,node->right);
        return Heapify(node->right);
      }
      else{
        // both children are greater than node, but leftt child
        // is larger, hence swap node and left child and 
        // call heapify on right child
        swap(node,node->left);
        return Heapify(node->left);
      }
    }
  }
  // When the right child is nullptr
  else if(node->left){
    if(node->left->object < node->object){
      // Heap property is satisfied
      return;
    }
    else{
      // left child is greater than node, hence swap them
      // and call heapify on left child
      swap(node, node->left);
      return Heapify(node->left);
    }
  }
  // When both are nullptr
  // Heap property is satisfied
  else return;

}

// Deleting the max element of the heap
template<typename T>
void Heap<T>::delMax() {
  // If only the root is left in the heap
  if(num == 1){
      root = nullptr;
      num = 0;
      return;
  }

  // Get the last node and swap it with the root node
  TreeNode<T>* last = getNode(num);
  swap(root,last);

  // Remove last node from the heap
  if(num%2==0){
    last->parent->left = nullptr;
  }
  else{
    last->parent->right = nullptr;
  }
  num--; //Decrementing num
  Heapify(root); // Heapify on root
}

template<typename T>
void Heap<T>::printHeapTree(TreeNode<T> *root, const string& prefix, bool isLeft){
  if(root != nullptr ){
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printHeapTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeapTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  printHeapTree(node,"",false);
  return;
}

  
