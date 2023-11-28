#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
TreeNode<T> * Heap<T>::findNextLoc(TreeNode<T> *node)
{
  //function to find the location of node which has entered after the given node
  TreeNode<T> *m = root;
  if(node == root)
  {
    m = node->left;
  }
  else if(node == node->parent->left)
  {
    m = node->parent->right;
  }
  else if(node == node->parent->right)
  {
    m = findNextLoc(node->parent)->left;
  }
  return m;
}
template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
  //function to implement heapify
  if(node->left == nullptr && node->right == nullptr)
  {
    return;
  }
  else if(node->right == nullptr)   //if right child is null
  {
     if(node->object < node->left->object)    //if value of left child is more than the node, swap 
     {
        T temp = node->left->object;
        node->left->object = node->object;
        node->object = temp;
        node = node->left;
     }
     else
     {
      return;
     }
  }
  else if(node->left == nullptr)    //if left child is null
  {
    if(node->object < node->right->object)    //if value of the  right child is more than the node, swap
     {
        T temp = node->right->object;
        node->right->object = node->object;
        node->object = temp;
        node = node->right;
     }
     else
     {
      return;
     }
  }
  else
  {
    if(node->object < node->left->object || node->object < node->right->object)   //if value of either of left child or right child is more that the node, swap
    {
      if(!(node->right->object < node->left->object))   //finding the maximum among left and right child 
      {
        T temp = node->right->object;
        node->right->object = node->object;
        node->object = temp;
        node = node->right;
      }
      else
      {
        T temp = node->left->object;
        node->left->object = node->object;
        node->object = temp;
        node = node->left;
      }
      Heapify(node);
    }
    else
    {
      return;
    }
  }
}
template<typename T>
void Heap<T>::insert(T obj) {
  //function to insert in heap
  if(root == NULL)    //creating a root,if null
  {
    root = new TreeNode<T>(obj);
  }
  else
  {
    TreeNode<T> *node = root;
    while(node->left != nullptr)    
    {
      node = node->left;
    }
    if(node->parent == nullptr)
    {
      if(node->left == nullptr)   //inserting the left child of the root 
      {
        node->left = new TreeNode<T>(obj);
        node->left->parent = node;
      }
      else
      {
        node->right = new TreeNode<T>(obj);   //inserting the right child of the root
        node->right->parent = node;
      }
    }
    else
    {
      node = node->parent;
      while(true)
      {
        if(node->left == NULL)    //inserting the left child of the node
        {
          node->left = new TreeNode<T>(obj);
          node->left->parent = node;
          node = node->left;
          break;
        }
        else if(node->right == NULL)    //inserting the right child of the node
        {
          node->right = new TreeNode<T>(obj);
          node->right->parent = node;
          node = node->right;
          break;
        }
        else
        {
          node = findNextLoc(node);   //finding the location to be inserted
        }
      }
    }
    while(true)
    {
      if(node->parent == NULL)    //swaping values after insert to restore the heap structures
      {
        break;
      }
      else if(node->parent->object < node->object)
      {
        T temp = node->object;
        node->object = node->parent->object;
        node->parent->object = temp;
      }
      node = node->parent;
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  //function to delete nodes
  if(root == nullptr)
  {
    return;
  }
  else
  {
    TreeNode<T> *node = root;
    while(node->left != NULL)
    {
      node = node->left;
    }
    if(node == root)
    {
      root = nullptr;
      return;
    }
    while(findNextLoc(node) != NULL)    //finding the last node in the heap
    {
      node = findNextLoc(node);
    }
    root->object = node->object;    //deleting the root
    if(node == node->parent->left)
    {
      node->parent->left = nullptr;
      node->parent = nullptr;
      node = nullptr;
    }
    else
    {
      node->parent->right = nullptr;
      node->parent = nullptr;
      node = nullptr;
    }
    Heapify(root);    //performing heapify to restore heap structure
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  //function to print heap
  // if(node != nullptr)
  // {
  //   static int reccLevel = -1;
  //   reccLevel++;
  //   static string prefix = "";
  //   static bool isLeft = false;
  //   bool isLeftval;
  //   isLeftval = isLeft;
  //   cout<<prefix;
  //   cout << (isLeft ? "|--" : "|__");
  //   cout<<node->object<<endl;
  //   prefix = prefix + (isLeft ? "|   " : "    ");
  //   isLeft = true;
  //   printHeap(node->left);
  //   isLeft = isLeftval;
  //   prefix = prefix + (isLeft ? "|   " : "    ");
  //   isLeft = false;
  //   printHeap(node->right);
  //   reccLevel--;
  //   if(reccLevel == -1)
  //   {
  //     prefix = "";
  //     isLeft = false;
  //   }
  // }
  printBinaryTree(node,"",false);

  return;
}

template<typename T>
void Heap<T>::reccDel(TreeNode<T> *root){\
  //function to recursively delete nodes
  if(findNextLoc(root) != nullptr)
  {
    reccDel(findNextLoc(root));
  }
  root = nullptr;
}

template<typename T>
void Heap<T>::printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout <<root->object<< endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  // else {
  //   cout << "NULL tree" << endl;
  // }
}

template<typename T>
TreeNode<T> *Heap<T>::getRoot(){
  //function to return the root
  return root;
}
