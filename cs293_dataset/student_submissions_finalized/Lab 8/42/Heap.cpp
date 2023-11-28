#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <vector>


template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here

  TreeNode* ins = new TreeNode<T>(obj);
  TreeNode* pos_ins = root;

  if (size == 0){
    root = T;
    size++;
    return;
  }

  vector<bool> bin;
  bool found = false;
  int n = size+1;
  while (n != 0){
    bin.append(n%2);
    n = n/2;
  }
  if (bin[bin.size() - 1] == 0) return;
  for(int i=bin.size()-2;i>=0;i--){
    if (i!=0){
      if (bin[i]) pos_ins = pos_ins->right;
      else pos_ins = pos_ins->left;
      if (!found){
        if (pos_ins->object < ins->object){
          ins->object = pos_ins->object;
          pos_ins->object = obj;
          found = true;
        }
      }
      else{
        
      }
    }

  }
  


  return;
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here

  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  // insert your code here

  return;
}
