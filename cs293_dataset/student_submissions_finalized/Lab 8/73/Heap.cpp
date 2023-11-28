#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
void swap( TreeNode<T> *node1,TreeNode<T> *node2)
{
  T sample=node1->object;
  node1->object=node2->object;
  node2->object=sample;

}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode *node=new TreeNode(obj);
  if (root == nullptr)
  {
    num++;
    root=node;
    return;
  }
  int h=getHeight();
  int p=1;
  for(int i=0;i<h-1;i++)
    p=p*2;
  int way=num-p+1;
  bool *path=new bool[h];
  for (int i=0;i<h;i++)
  {
    path[i]=way%2;
    way=way/2;
  }
  TreeNode *sample=root;
  for (int i=h-1;i>0;i--)
  {
    if (path[i])
      sample=sample->right;
    else
      sample=sample->left;
  }
  if (path[i])
    sample->right=node;
  else
    sample->left=node;
  node->parent=sample;

  num++;
  for (node->parent != nullptr)
  {
    if (node->parent->object < node->object)
      swap(node,node->parent);
    node=node->parent;
  }
  return;
}
template<typename T>
int Heap<T>::getHeight()
{
  if (root == nullptr)
    return 0;
  if (root->left == nullptr)
    return 1;
  int h=0,p=1;
  while(num>p-1)
  {
    h++;
    p=p*2;
  }
  return h;
}
template<typename T>
T Heap<T>::delMax() {
  
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

  
