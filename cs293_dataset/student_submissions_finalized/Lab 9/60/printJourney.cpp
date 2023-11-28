#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  TreeNode<T> *S = new TreeNode<T>(obj);
  if (root == nullptr)
  {
    root = S;
    last = root;
    curr_num++;
    return;
  }
  else if(curr_num == 1)
  {
    root->left = S;
    last = root->left;
    curr_num++;
    return;
  }
  else
  {
    int num = floor(log2(curr_num));
    int max = pow(2, num - 1) - 1;
    if (last->parent->left == last && max != curr_num)
    {
      last = last->parent->right;
      last = S;
    }
    else if (last->parent->right == last && max == curr_num)
    {
      last = root;
      while (last->left != nullptr)
      {
        last = last->left;
      }
      last->left = S;
      last = last->left;
      
    }
    else if (last->parent->right == last && max != curr_num)
    {
      int i = curr_num;
      int j = curr_num + 1;
      while (i != j)
      {
        i = (i - 1) / 2;
        j = (j - 1) / 2;
        last = last->parent;
      }
      last = last->right;
      while (last->left != nullptr)
      {
        last = last->left;
      }
      last->left = S;
      last = last->left;
    }
    while ((last->parent->object < last->object) && (last->parent != nullptr))
    {
      Heap<T>::Swap(last, last->parent);
    }
    curr_num++;
    return;
  }
  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
