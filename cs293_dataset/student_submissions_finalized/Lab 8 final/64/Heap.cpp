#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


//Tail here is defined as the node in the heap where the new node should be inserted.
//If the heap is empty then tail is null.
//If the heap has only one node then tail is the root node.
//If the heap has three nodes then tail if the leftmost node i.e. the left child of root
//because the new node should be inserted as the child of this node.

//Function to set tail of the node
template<typename T>
void Heap<T>::setTail(TreeNode<T> *node){

    //First case if the parent of node is null i.e. node is root then tail is left most node in the heap.
    //Beacuse we call setTail function on root only when the Heap is complete Binary Tree
    if(node->parent == nullptr){
        tail = node;
        while(tail->left != nullptr){
            tail = tail->left;
        }
    }

    //If the node is the left child of its parent then the tail would be the leftmost child of 
    //right child of the its parent
    else if(node->parent->left == node){
        tail = node->parent->right;
        while(tail->left != nullptr){
            tail = tail->left;
        }
    }
    //If the node is the right child of its parent then the tail now would be the setTail of its parent
    else if(node->parent->right == node){
        setTail(node->parent);
    }
}

//Function to swap the data of the two nodes
template<typename T>
void Heap<T>::swapNodeData(TreeNode<T>* a, TreeNode<T>* b){
    T temp = a->object;
    a->object = b->object;
    b->object = temp;
}


//Function to exchange the node data of the node with its parent recursively upto the point till
//the condition of maxHeapify is satisfied.
template<typename T>
void Heap<T>::maxHeapify(TreeNode<T>* node){
    if(node->parent != nullptr){
        if(node->parent->object < node->object){
            swapNodeData(node->parent, node);
            maxHeapify(node->parent);
        }
    }
}


//Function to insert a new node in the Heap
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
    //If initially the heap is null then create new node and assign it to root
    if(root == nullptr){
        root = new TreeNode<T>(obj);
        tail = root;
    }
    //If left child of tail is null then insert a new node here and run the function maxHeapify on it
    //so that the condition of heap is satisfied, tail should not be changed in this case
    else if(tail->left == nullptr){
        tail->left = new TreeNode<T>(obj);
        tail->left->parent = tail;
        maxHeapify(tail->left);
    //If the right of tail is null then insert new node here and run maxHeapify function on it
    //Then set the tail to a new node
    }else {
        tail->right = new TreeNode<T>(obj);
        tail->right->parent = tail;
        maxHeapify(tail->right);
        TreeNode<T> *prevTail = tail;
        setTail(tail);
        tail->prevTail = prevTail;
    }
  return;
}


//Function of Heapify as discussed in Prof. Naveen garg's lectures
template<typename T>
void Heap<T>::revMaxHeapify(TreeNode<T>* node){
    if(node == nullptr || node->left == nullptr)
      return;
    TreeNode<T>* max = node->left;
    if(node->right != nullptr && max->object < node->right->object){
        max = node->right;
    }
    if(node->object < max->object){
        swapNodeData(node, max);
        revMaxHeapify(max);
    }
}


//Function to delete the root of the Heap
template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(root == nullptr) {
      return;
  }
  //If tail is root
  if(tail == root){
    //If the heap contains only root then simply delete it
    if(root->left==nullptr && root->right==nullptr){
      tail = nullptr;
      root = nullptr;
      return;
    //If root has both left and right child then swap root with the max of left and right child
    //and delete the selected node
    }else if(root->right!=nullptr){
        swapNodeData(root, root->right);
        root->right=nullptr;
        if(root->object < root->left->object){
            swapNodeData(root, root->left);
            return;
        }
        return;
    //If heap contains only left child then delete root and make its left child the root
    }else if(root->left != nullptr){
        swapNodeData(root, root->left);
        root->left=nullptr;
        return;
    }
  }
  //If tail is not root
  else {
      //If tail has both left and right child then swap right child with root
      //and run heapify on the root
      if (tail->right != nullptr){
          swapNodeData(tail->right, root);
          tail->right = nullptr;
          revMaxHeapify(root);
      }
      //if tail has only left child then swap it with root and run heapify on root
      else if(tail->left != nullptr) {
          swapNodeData(tail->left, root);
          tail->left = nullptr;
          revMaxHeapify(root);
      }
      //if tail has no child then go to the node which was previously tail and now run delMax on root
      else {
          tail = tail->prevTail;
          delMax();
      }
  }
  return;
}



template<typename T>
void Heap<T>::print(TreeNode<T> *root, const string& prefix, bool isLeft){
    if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    print(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    print(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    ;
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
//   insert your code here
  static string prefix = "";
  print(node, prefix, false);
}