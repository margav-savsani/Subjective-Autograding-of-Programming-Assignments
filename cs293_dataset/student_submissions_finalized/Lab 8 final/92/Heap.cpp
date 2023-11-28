#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

int *Convert(int n)
{
  int i = 0, s = n;
  while (n > 0)
  {
    n = n / 2;
    i = i + 1;
  } // to find number of digits in the binary conversion
  int *arr = new int[i];
  for (int j = 0; j < i; j++)
  {
    arr[j] = s % 2;
    s = s / 2;
  } // inserting each digit into the array
  return arr;
}
template <typename T>
TreeNode<T> *find(int n, TreeNode<T> *s)
{ // to find the last node in the heap
  int a = n, d = 0;
  while (a > 0)
  {
    a = a / 2;
    d = d + 1;
  }
  int *temp = new int[d]; // to find number of digits in the number
  int b = n;
  temp = Convert(b);
  int t[d];
  for (int j = 0; j < d; j++)
  {
    t[j] = temp[d - j - 1];
  }
  TreeNode<T> *c = s;
  int g = 1, k = 1; // c is the last node
  while (k < d)
  {
    if (t[g] == 0)
    {
      c = c->left;
    }
    else
    {
      c = c->right;
    }
    g = g + 1;
    k = k + 1;
  }
  return c;
}

template <typename T>
void Heapify(TreeNode<T> *k)
{if (k->right != NULL && k->left != NULL){
  if (k->left->object < k->object && k->right->object < k->object){Heapify(k->right);Heapify(k->left);}
  else if (k->left->object < k->right->object){T te = k->object;
        k->object = k->right->object;k->right->object = te;
        Heapify(k->right);}
  else{T te = k->object;k->object = k->left->object;k->left->object = te;Heapify(k->left);}}
else if (k->right == NULL && k->left != NULL){
  if (k->object < k->left->object){T te = k->object;k->object = k->left->object;k->left->object = te;
      return;}}
else{return;}}

template <typename T>
void Heap<T>::insert(T obj)
{
  if (root ==NULL)
  {root = new TreeNode<T>(obj);n = 1;return;}
  else{TreeNode<T> *c = root;//root of the heap
    int b = 0,a = n + 1;
    while (a>0){a = a / 2;b = b + 1;}//number of digits in the binary conversion
    int *as = new int[b];
    as = Convert(n + 1);
    int sa[b];
    for (int z = 0; z < b; z++)
    {sa[z] = as[b - 1 - z];}//reversing the order recieved from convert function
    int k = 1,l = 1;
    while (k<b - 1){
      if (sa[l] == 1)
      {c = c->right;l = l + 1;k = k + 1;}
      else{c = c->left;l = l + 1;k = k + 1;}}//find ing the location of the node at which it is to be inserted.
    if (sa[l] == 1)
    {
      TreeNode<T> *p = new TreeNode<T>(obj);//inserting the node
      c->right = p;c->right->parent = c;
      n = n + 1;
      int v = 1;
      while (v < n){v = v * 2;}
      v = v / 2;int k = v - 1;
      while (k != 0)
      {Heapify(find(k, root));k = k - 1;}
      return;}
    else{//inserting the node
      TreeNode<T> *p = new TreeNode<T>(obj);//inserting the node
      c->left = p;
      c->left->parent = c;
      n = n + 1;
      int v = 1;
      while (v < n)
      {v = v * 2;}
      v = v / 2;
      int k = v - 1;
      while (k != 0)
      {Heapify(find(k, root));k = k - 1;}//inserting the node
      return;}}//return after inserting
  return;}
template <typename T>
void Heap<T>::delMax()
{
  int a = n;
  if (n == 0){return;}//if no element is in the heap
  if (n == 1){root = NULL;n--;return;}//if the heap has only 1 element
  TreeNode<T> *c = find(a, root);//replacing the lower right number to be the root
  root->object = c->object;//replacing root
  if (c->parent->right == c){c->parent->right = NULL;}//changing conditions of the lower element
  else{c->parent->left = NULL;}
  Heapify(root);//then heapifying the heap
  n--;}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{{static string prefix = "";
    static bool n = 0;
    if (node == root){prefix = "";n = 0;}
    if (node != NULL){cout << prefix;
      if (n == 1){cout << ("|--");}
      if (n == 0){cout << ("|__");}
      // print the value of the node
      cout << node->object << endl;
      bool a = n;
      string mys = prefix;
      prefix = mys + (a ? "│   " : "    ");
      n = 1;
      // enter the next tree level - left and right branch
      printHeap(node->left);
      n = 0;
      prefix = mys + (a ? "│   " : "    ");
      printHeap(node->right);
    }
  }
  // Here I used the static concept to keep the prefix and alter it in iterative way
  //   cout << prefix;

  //       cout << (isLeft ? "|--" : "|__" );

  //       // print the value of the node
  //       cout << root->JourneyCode << endl;
  //       TreeNode *curr = root;
  //       root = root->left;
  //       // enter the next tree level - left and right branch
  //       printBST( prefix + (isLeft ? "│   " : "    "), true);
  //       root = curr->right;
  //       printBST( prefix + (isLeft ? "│   " : "    "), false);
  //       root = curr;
  // insert your code here

  return;
}
