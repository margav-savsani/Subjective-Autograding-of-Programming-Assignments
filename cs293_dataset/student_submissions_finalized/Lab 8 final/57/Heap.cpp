#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{
  if (ent == 0) // base case if ent=0
  {
    root = new TreeNode(obj);// making inserted object as a root.
    ent++;                   // increasing no of elements.
    return;
  }
  TreeNode<T> *present = root;
  ent++;
  int n = ent;
  int a[32], i=0;

  for (i = 0; n > 0; i++)
  {
    a[i] = n % 2;  // storing the no of elements in heap in binary representation
    n = n / 2;      // so that we can go to the place where we have to insert easyly.
  }
  for (i = i - 2; i >= 1; i--)
  {
    if (a[i] == 0)   // if the digit in binary representation is zero we have to take left branch.
    {
      present = present->left;
    };
    if (a[i] == 1)   // if the digit in binary representation is one we have to take right branch.
    {
      present = present->right;
    };
  }
  if (a[0] == 0)
  {
    present->left = new TreeNode(obj);
    present->left->parent = present; // inserting at the position so that it will not violate heap properties.
    present = present->left;
  }
  if (a[0] == 1)
  {
    present->right = new TreeNode(obj);
    present->right->parent = present; // inserting at the position so that it will not violate heap properties.
    present = present->right;
  }

  while (present != root)
  {
    if (!(present->object < present->parent->object))
    {
      swap(present->object, present->parent->object); // making sure that parent element has maximum value compared to its children.
      present = present->parent;
    }

    else
    {
      break;
    }
  }

  return;
}


template <typename T>
void Heap<T>::heapify(TreeNode<T> *curr)
{
  if (curr == nullptr) // checking heap property after swaping last entered element 
  {
    return;
  }
  if (curr->left == nullptr)// we reached end no more swaping required
  {
    return;
  }


  T tp = curr->object;
  T tl = curr->left->object;
  if (curr->right == nullptr)
  {
    if (tp < tl) // checking if its child is greater than parent then swaping
    {
      swap(curr->object, curr->left->object);
      return;
    }
    return;
  }

  else
  {
    T tr = curr->right->object;
    T k;
    if (tr < tl) // checking for maximum element among its children
    {
      k = tl;
    }
    else
    {
      k = tr;
    }
    if (k < tp)
    {
      return;
    }
    else
    {
      
      if (tl < tr)
      {
        swap(curr->object, curr->right->object); // swaping the currnode and maximum element among its children
        heapify(curr->right);return;
      }

      else
      {
        swap(curr->object, curr->left->object);
        heapify(curr->left);return;  // recursively calling this functions untill it reaches leaves.
      }
    }
  }
  return;
}


template <typename T>
void Heap<T>::delMax()
{
  if (ent == 0)
    return;
  if (ent == 1) // checking for base cases.
  {
    root == nullptr;
    ent = 0;
    return;
  };
  int n = ent;
  ent--;
  TreeNode<T> *present = root;
  int a[32], i;

  for (i = 0; n > 0; i++) //similar to insert converting the given no into decimal form.
  {
    a[i] = n % 2;         //so that we can reach the position of last element with which we will swap.
    n = n / 2;
  }
  for (i = i - 2; i >= 1; i--)
  {
    if (a[i] == 0)
    {
      present = present->left;
    };
    if (a[i] == 1)
    {
      present = present->right;
    };
  }
  if (a[0] == 0)
  {
    swap(present->left->object, root->object);// swaping last element and root
    TreeNode<T> *b = present->left; //deleting the last element and freeing up the space.
    delete(b); 
    present->left = nullptr;
            
  }
  if (a[0] == 1)
  {
    swap(present->right->object, root->object);// swaping last element and root
    TreeNode<T> *a = present->right;          //deleting the last element and freeing up the space.
    delete(a);
    present->right = nullptr;
  }
  heapify(root);                    //calling heapify so that after swaping it will not violate heap property.

  // insert your code here

  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  printHeap_recursive(node, "", false); // using functions which we used in our previous inlabs.

  return;
}



// insert your code here

template <typename T>
void printHeap_recursive(TreeNode<T> *root, const string &prefix, bool isLeft)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << (root->object);
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printHeap_recursive(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeap_recursive(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}
