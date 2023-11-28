#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

int computePow(int level){
  int pow = 1;
  int twop = 1;
  for (int i = 0; i < level; i++){
    pow = pow * 2;
  }
  return pow;
}

template<class T>
void update(TreeNode <T>* currNode){
  // function to update the values of level and numNodes for each parent on the path to root.
  TreeNode <T> *currparent = currNode->parent;

  while (currparent){
    currparent->level = currparent->left->level+ 1;
    currparent->numNodes++;
    currparent = currparent->parent;
  }
}

template<class T>
void heapify(TreeNode<T> * currNode){
  //bubble the largest value up till reached the correct position.
  TreeNode<T> * parentNode = currNode->parent;

  while(parentNode && parentNode->object < currNode->object ){
    T temp = parentNode->object;

    parentNode->object = currNode->object;
    currNode-> object = temp;

    currNode = parentNode;
    parentNode = parentNode->parent;

  }

  return;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert the node into the heap.
  

  //if root node then simply set root as the new node.
  TreeNode<T> *newNode = new TreeNode<T>(obj);
  if (root == nullptr){
    this->root = newNode;


    return;
  }

  TreeNode<T> * currNode = this->root;
  //find the lowest poisition to insert.
  while(true){
    //if left pointer is a null pointer then insert here
    if(!currNode->left){
      currNode->left = newNode;
      newNode->parent = currNode;
      currNode = currNode -> left;
      
      break;
    //if right pointer is a null pointer then insert here.
    } else if (!currNode->right){
      currNode->right = newNode;
      newNode->parent = currNode;
      currNode = currNode -> right;
      break;
      //otherwise check if we need to got to the left or right.
    } else {

      //check if the tree at the currNode is a complete binary tree.
      if (currNode->numNodes == computePow(currNode->level) - 1){
        while(currNode->left){
          currNode = currNode->left;
        }
      }
      //if not a complete binary tree, check if the left subtree is a complete binary tree.
      //if not go to the left
      else if (currNode->left->numNodes < computePow(currNode->left->level) - 1){
        currNode = currNode->left;
      //otherwise go to the right.
      } else {
        currNode = currNode->right;
      }

    }

    

    
  }
    //update level and numNodes for the tree.
    update<T>(currNode);
    //insert the node at the correct position.
    heapify<T>(currNode);

    //printHeap(this->root);

    return;

}

template<typename T>
T Heap<T>::delMax() {

  


  //find the lowest pointer to delete
  TreeNode<T> * currNode = root;
  T maxObj = root->object;

  //if root node is the only node, simply delete it.
  if (!root->left){
    this->root = nullptr;
    return maxObj;

  }


  
  while(true){
    //if lowest node found, break.
    if (currNode->left == nullptr){
      break;
    }

    //if right node empty then go to the left.
    if(!currNode->right){
      currNode = currNode->left;
      continue;
    }
    //otherwise check if the subtrees are at the same level.
    //if no, go to the left
    if(currNode->left->level > currNode->right->level){
      currNode = currNode->left;
    //otherwise go to the right.
    } else if (currNode->left->level == currNode->right->level){
      
      currNode = currNode->right;
      /*
      if (currNode->left->numNodes > 1) {
        currNode = currNode->right;

      } else if (currNode->left->numNodes == 1 && currNode->right->numNodes == 1) {
        currNode = currNode->right;

      }

      */


    }
  }
  //handling the base case for 2 levels.
  if (root->level == 2){
    this->root->object = currNode->object;
    //update the attributes of the root.
    if(root->left == currNode) {
      root->left = nullptr;
      root->level = 1;
      root->numNodes--;
    }
    else {
      //update the attributes of the root
      root->right = nullptr;
      root->numNodes--;
    } 
    delete currNode;


  } else {
    root->object = currNode->object;

     

    TreeNode<T> * pNode = currNode->parent;

    //update the values of numNodes and level for each node in the path to root.
    if (pNode->right == nullptr){
      
      pNode->numNodes--;
      pNode->level--;

    
    } else {
      pNode->numNodes--;
    }

    //update the value of pointers of parent of the currNode.
    if (currNode->parent->left == currNode) currNode->parent->left = nullptr;
    else currNode->parent->right = nullptr;

    //update the value of numNodes and level for all other testcases.
    while(pNode->parent){
      pNode = pNode->parent;
      //compare the value of the left child levels and the right child level.
      pNode->level = pNode->left->level > pNode->right->level ? pNode->left->level + 1 : pNode->right->level + 1;
      pNode->numNodes --;

    }


    //delete the lowest Node.
    delete currNode;  

  }
  //set currNode to root.
  currNode = root;

  //bubble the top element down to its intended position
  while(true){
    //base case
    if (currNode->left == nullptr) {

      break;
    }
    // base case
    else if (!currNode->right) {
      //compare value of the left child and the currNode.
      if (currNode->object < currNode->left->object) {
        //swap the values
        T temp = currNode->object;
        currNode->object = currNode->left->object;
        currNode->left->object = temp;
        currNode = currNode->left;
      } else {
        break;
      }
    }

     else {
      
      TreeNode<T> * largerPointer  = (currNode->left->object < currNode->right->object) ? currNode->right : currNode->left;
      //compare value of the currNode with the larger child.
      if (currNode->object < largerPointer->object){
        //if less, then swap the values.
        T temp = currNode->object;
        currNode->object = largerPointer->object;
        largerPointer->object = temp;
        currNode = largerPointer;
      } else {
        break;
      }
    }
    
  }

  //return the obj deleted.
  return maxObj;

  


  
}


//function to print the heap.
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  static string prefix = " ";
  static bool isLeft = true;
  bool isLeftCopy = isLeft;
  string copyPrefix = prefix;
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    isLeft = true;
    
    prefix = copyPrefix + (isLeftCopy ? "│   " : "    ");
    printHeap(root);
    root = curr->right;
    isLeft = false;
    prefix = copyPrefix + (isLeftCopy ? "│   " : "    ");
    printHeap(root);
    root = curr;
  
  }

  prefix = copyPrefix;
}
template<typename T>
void deleteHeap(TreeNode<T>* root){
  if (root){
    TreeNode<T> * left = root->left;
    TreeNode<T> * right = root->right;

    root->left = nullptr;
    root->parent = nullptr;
    root->right = nullptr;
    deleteHeap(left);
    deleteHeap(right);
    delete root;

    
  } 

  return;

}

template<typename T> Heap<T>::~Heap(){
  deleteHeap(root);
}





  
