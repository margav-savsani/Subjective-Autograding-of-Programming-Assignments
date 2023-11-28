#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

//some extra headers
#include <vector>

using namespace std;

#ifndef HEAP_H
#include "Heap.h"
#endif

//utility function to swap objects
template<typename T>
void Heap<T>::swap_objects(TreeNode<T> *a,TreeNode<T> *b)
{
  T temp = a->object;
  a->object = b->object;
  b->object = temp;
  return;
}
//swaps only objects not pointers

//utility function to convert a number into binary
template<typename T>
vector<int> Heap<T>::tobin(int n)
{
    vector<int> bin;
    //convert to binary
    while(n > 0)
    {
        bin.push_back(n%2);
        n/=2;
    }
    bin.pop_back();
    //remove last elem

    //reverse to get the original form of binary
    for (auto first = bin.begin(), last=bin.end()-1; first<last; first++,last--) 
    {
        swap(*first, *last);
    }

    return bin;
}
//the binary number is stored in a vector

//utility function to get node at position
template<typename T>
TreeNode<T>* Heap<T>::getnode(int n)
{
  vector<int> k = tobin(n);
  TreeNode<T> *trav = root;
  for(int i=0; i<k.size(); i++)
  {
    if(k[i] == 0) trav = trav->left;
    else trav = trav->right;
  }
  return trav;
}
//returns node at that position

//insert a new node
template<typename T>
void Heap<T>::insert(T obj) 
{
  //node to be inserted
  TreeNode<T>* new_node = new TreeNode<T>(obj);
  size++;

  // insert your code here

  //root==NULL case
  if(!root)
  {
    root=new_node;
  }
  //when heap is empty
  
  else
  {
    vector<int> k = tobin(size);
    TreeNode<T>*curr = root;

    //traverse upto parent
    for(int i=0; i < k.size()-1; i++)
    {
      if(k[i] == 0) curr=curr->left;
      else curr=curr->right;
    }

    //insert
    if(k.back() == 0)
    {
      curr->left = new_node;
      new_node->parent = curr;
    }
    else
    {
      curr->right = new_node;
      new_node->parent=curr;
    }

    //Heapify for all nodes from last node
    for(int i = size; i>1; i--)
    {
      Heapify(getnode(i));
    }

    Heapify(root);

  }

  return;
}
//new node inserted and heapified to maintain heap property

//delete root
template<typename T>
void Heap<T>::delMax() 
{
   // insert your code here

  if(size == 1)
  {
     root=NULL;
     size--;
     return;
  }

  vector<int> k = tobin(size);
  //parent of last node
  TreeNode<T>* par = root;

  //traverse till parent is found
  for(int i=0; i < k.size()-1; i++)
  {
    if(k[i]==0) par = par->left;
    else par = par->right;
  }

  //swap last object with root and delete last_node
  if(k.back()==0)
  {
    swap_objects(root, par->left);
    par->left = NULL;
  }
  else
  {
    swap_objects(root, par->right);
    par->right = NULL;
  }

  size--;

  //heapify
  Heapify(root);
  //only on root since left and right are anywys heaps for root

  return;
}

//heapify
template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
  //if no child
  if(!node->left && !node->right) return;

  //if single child
  //left child
  else if (node->left && !node->right)
  {
    if(node->object < node->left->object)
    {
      swap_objects(node, node->left);
      return;
    }
    else return;
  }
  //right child
  else if (node->right && !node->left)
  {
    if(node->object < node->right->object)
    {
      swap_objects(node, node->right);
      return;
    }
    else return;
  }
  //both child
  else if(node->left!=NULL && node->right!=NULL)
  {
    //find max of both child and proceed
    //when max is left
    if(node->right->object < node->left->object)
    {
      if(node->object < node->left->object)
      {
        swap_objects(node, node->left);
        Heapify(node->left);
        return;
      }
      return;
    }
    //when max is right
    else
    {
      if(node->object < node->right->object)
      {
        swap_objects(node, node->right);
        Heapify(node->right);
        return;
      }
      return;
    }
  }
  else  return;
}

//print heap similar to print in Tree.h of previous labs
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) 
{
  // insert your code here

  //static variables
  static string prefix = "";
  static bool isleft = false;
  static int recursion_level = 0;

  recursion_level++;

  if (node != nullptr)
  {
      cout << prefix;
      //left child
      if(isleft) cout << "|--";
      //right child
      else cout << "|__";
      cout << node->object << endl;

      if(isleft) prefix += "|  ";
      else prefix += "   ";

      isleft = true; printHeap(node->left);
      isleft = false;printHeap(node->right);
  }

  if (recursion_level == 1)
  {
      prefix = "";
      isleft = false;
  }

  recursion_level--;

  return;
}
//but recursive with only one argument since static variables are used

