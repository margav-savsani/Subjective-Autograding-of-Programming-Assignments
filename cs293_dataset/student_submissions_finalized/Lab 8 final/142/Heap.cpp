#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template <typename T>
void print(TreeNode<T> *root, const string& prefix = "", bool isLeft = false)
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
    print(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    print(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  /*
  else {
    cout << "NULL tree" << endl;
  }
  */
}

template <typename T>
void Heap<T>::swap_obj(T &obj1, T &obj2)
{
  //function used to swap 2 objects given in input
  T temp = obj1;
  obj1 = obj2;
  obj2 = temp;
}

template <typename T>
void Heap<T>::heapify(TreeNode<T>* currNode)
{
  //base case
  if(currNode == nullptr)return;
  //
  else if(currNode->left!=nullptr && currNode->right == nullptr)
  {
    if(currNode->object < currNode->left->object)
      swap_obj(currNode->left->object, currNode->object);
      return;
  }
  if(currNode->left != nullptr && currNode->right != nullptr)
  {
    if(currNode->object < currNode->left->object && !(currNode->left->object < currNode->right->object) )
    {
      swap_obj(currNode->object, currNode->left->object);
      heapify(currNode->left);
    }
    else if(currNode->object < currNode->right->object && !(currNode->right->object < currNode->left->object))
    {
      swap_obj(currNode->object, currNode->right->object);
      heapify(currNode->right);
    }
  }
  // if(currNode->right != nullptr)
  // {
  //   if(currNode->object < currNode->right->object)
  //   {
  //     swap_obj(currNode->object, currNode->right->object);
  //     heapify(currNode->right);
  //   }
  // }
  else return;
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  //inserting the first element
  if(currLvl == -1)
  {
    TreeNode<T> *new_n = new TreeNode<T>(obj);
    root = new_n;
    last = root;
    currLvl++;
  }
  // inserting the second element
  else if(currLvl == 0 && root->left == nullptr)
  {
    TreeNode<T> *new_n = new TreeNode<T>(obj);
    root->left = new_n;  
    root->left->parent = root;
    last = new_n;
  }
  // inserting the third element
  else if(currLvl == 0 && root->left!= nullptr)
  {
    TreeNode<T> *new_n = new TreeNode<T>(obj);
    root->right = new_n;
    root->right->parent = root;
    last = new_n;
    currLvl++;
  }
  else if(last == last->parent->left)
  {
    TreeNode<T> *new_n = new TreeNode<T>(obj);
    last->parent->right = new_n;
    new_n->parent = last->parent;
    last = last->parent->right;
  }
  else if(n==round(pow(2,currLvl+1)-1))
  {
    int i = 0;
    TreeNode<T>* currNode = root;
    TreeNode<T> *new_n = new TreeNode<T>(obj);
    while(i < currLvl)
    {
      currNode = currNode->left;
      i++;
    }
    currNode->left = new_n;
    new_n->parent = currNode;
    last = new_n;
    currLvl++;
  }
  else
  {
    TreeNode<T> *new_n = new TreeNode<T>(obj);
    last->parent->parent->right->left = new_n;
    new_n->parent = last->parent->parent->right;
    last = last->parent->parent->right->left;
  }
  last->object = obj;
  n++;
  // cout << currLvl << endl;
  // heapify(root);
  TreeNode<T>* checkNode = new TreeNode<T>(obj);
  checkNode = last;
  while(true)
  {
    // heapify(checkNode);
    if(checkNode->parent == nullptr)break; 
    if(checkNode->parent->object < checkNode->object)
    {
      swap_obj(checkNode->object, checkNode->parent->object);
      checkNode = checkNode->parent;
    }
    else break;
  }
  //print(root);
  //cout <<"n:"<< n << endl;
  return;
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  root->object = last->object;
  if(currLvl == -1)
  {
    return;
  }
  else if(currLvl == 0)
  {
    root = nullptr;
    last = nullptr;
    currLvl--;
  }
  else if(currLvl == 1)
  {
    if(root->right == nullptr)
    {
      root->left = nullptr;
      last = root;
      currLvl--;
    }
    else if(root->right != nullptr)
    {
      root->right = nullptr;
      last = root->left;
    }
  }
  else if(last == last->parent->right )
  {
    last = last->parent->left;
    last->parent->right = nullptr; 
  }
  else if(n==round(pow(2,currLvl)))
  {
    cout << "here\n";
    int i = 0;
    TreeNode<T>* currNode = root;
    while(i < currLvl - 1)
    {
      currNode = currNode->right;
      i++;
    }
    last->parent->left = nullptr;
    last = currNode;
    currLvl--;
  }
  else
  {
    last = last->parent->parent->left->right;
    last->parent->parent->right->left = nullptr;
  }

  // if(last != root){
  //   if(last == last->parent->left)
  //   {
  //     last->parent->left = nullptr;
  //   }
  //   else
  //   {
  //     last->parent->right = nullptr;
  //   }
  //   heapify(root);
  // }
  // else root = nullptr;
  if(root!=nullptr)
  {
    heapify(root);
  }
  n--;
  //print(root);
  //cout <<"n:"<< n << endl;
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) 
{
  printBinaryTree(node,"",false);
}
  // insert your code here
//   bool isLeft;
//   cout << node->object << endl;
//   if(node->left != nullptr)
//   {
//     isLeft = true;
//     cout << "|--";
//     printHeap(node->left);
//   }
//   if(node->right != nullptr)
//   {
//     cout << "|__";
//     printHeap(node->right);
//   }
  
//   return;
// }

