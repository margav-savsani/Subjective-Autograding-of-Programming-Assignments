#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
Heap<T>::~Heap(){
  recursiveDeleteNode(root);
}

template<typename T>
void Heap<T>::insert(T obj) {
  //Create new tree if root is null
  if(root == nullptr){
    root = new TreeNode<T>(obj);
    lastNode = root;
    return;
  }
  //Find parent node in which to add new node as child
  TreeNode<T>* nextParent = lastNode;
  //Go back from last node till you can go right
  while(true){
    //If new level is to be added
    if(nextParent == root){
      while(nextParent->left != nullptr){
        nextParent = nextParent->left;
      }

      nextParent->left = new TreeNode<T>(obj);
      lastNode = nextParent->left;
      lastNode->parent = nextParent;
      //Once new node is created, keep swapping element with parent till heap property satisfied
      TreeNode<T>* currNode = lastNode;
      TreeNode<T>* parentNode = lastNode->parent;

      while(parentNode != nullptr){
        if(currNode->object < parentNode->object){
          break;
        }
        swap(currNode->object, parentNode->object);

        currNode = currNode->parent;
        parentNode = parentNode->parent;
      }
      return;
    }
    //If can go right
    if(nextParent->parent->left == nextParent){
      nextParent = nextParent->parent;
      break;
    }

    nextParent = nextParent->parent;
  }
  //Add new Node if can be done in right
  if(nextParent->right == nullptr){
    nextParent->right = new TreeNode<T>(obj);
    lastNode = nextParent->right;
    lastNode->parent = nextParent;
  }
  //Else go down till child is nullptr
  else{
    nextParent = nextParent->right;

    while(nextParent->left != nullptr){
      nextParent = nextParent->left;
    }

    nextParent->left = new TreeNode<T>(obj);
    lastNode = nextParent->left;
    lastNode->parent = nextParent;
  }
  //Swap operations
  TreeNode<T>* currNode = lastNode;
  TreeNode<T>* parentNode = lastNode->parent;

  while(parentNode != nullptr){
    if(currNode->object < parentNode->object){
      break;
    }
    swap(currNode->object, parentNode->object);
    
    currNode = currNode->parent;
    parentNode = parentNode->parent;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  //Edge case
  if(root == nullptr){
    return;
  }
  //If root to be deleted
  if(root == lastNode){
    delete root;
    lastNode = nullptr;
    root = nullptr;
    return;
  }
  //Swap last node with top node and heapify and update lastNode after deleting it
  swap(root->object, lastNode->object);
  TreeNode<T>* parentNode = lastNode->parent;
  if(parentNode->left == lastNode){
    parentNode->left = nullptr;
    delete lastNode;
    Heapify(root);
    while(true){
      //If last level deleted
      if (parentNode == root){
        while(parentNode->right != nullptr){
          parentNode = parentNode->right;
        }
        lastNode = parentNode;
        return;
      }

      if (parentNode->parent->right == parentNode){
        parentNode = parentNode->parent;
        break;
      }

      parentNode = parentNode->parent;
    }

    parentNode = parentNode->left;
    while(parentNode->right != nullptr){
      parentNode = parentNode->right;
    }

    lastNode = parentNode;
    return;
  }

  else{
    parentNode->right = nullptr;
    delete lastNode;
    lastNode = parentNode->left;
    Heapify(root);
    return;
  }

}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  printBinaryTree(root, "", false);

  if(lastNode != nullptr)
    std::cout << "Last Node Points to: " << lastNode->object << endl;
}

template<typename T>
void printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft)
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
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  
}

//Heapify procedure
template<typename T>
void Heapify(TreeNode<T>* node){
  //If end reached return
  if(node->left == nullptr && node->right == nullptr){
    return;
  }
  //If right is null
  else if(node->right == nullptr){
    if(node->object < node->left->object){
      swap(node->left->object, node->object);
      return;
    }
  }
  //If end not reahed
  else{
    //If heap property satisfied
    if(node->left->object < node->object && node->right->object < node->object){
      return;
    }

    else{
      //Swap with max of child and recurse
      if(node->right->object < node->left->object){
        swap(node->left->object, node->object);
        Heapify(node->left);
      }

      else{
        swap(node->right->object, node->object);
        Heapify(node->right);
      }
    }
  }
}

template<typename T>
void recursiveDeleteNode(TreeNode<T>* node){
  if(node ==  nullptr){
    return;
  }

  recursiveDeleteNode(node->left);
  recursiveDeleteNode(node->right);

  delete node;
}
