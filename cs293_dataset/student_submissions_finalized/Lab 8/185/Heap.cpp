#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *current = root;
  TreeNode<T> *new_node = new TreeNode<T>(obj);
  TreeNode<T> *temp;
  TreeNode<T> *extra;
  //TreeNode<T> last = new TreeNode(nullptr);
  
  if(root == nullptr){
    root = new TreeNode<T>(obj);  //creates the root if root is initially a nullpointer.
    x++;  //x stores (total number of nodes + 1) to find the next number of node to be inserted.
    return;
  }
  int r = 0;
  int b_num = 0;
  int prod = 1;
  //int num = 0;
  //int drop = 0;

  while(x != 0){   //b_num is binary representation of x
    r = x%2;
    b_num += r*prod;
    x = x/2;
    prod *= 10;
  }
  // while (b_num > 0){  //reverse b_num and store it in num
  //   num = num*10 + b_num%10;
  //   b_num = b_num/10;
  // }

  int a,b;
  int arr[5];
  int m = 0;

  while(b_num != 0){  //arr stores the individual digits of the number b_num
    a = b_num%10;
    arr[m] = a;
    m++;
    b_num = b_num/10;
  }

  while(current->left != nullptr && current->right != nullptr){
    
    for(int i = m-2; i>-1; i--){  //we iterate through the digits of the binary represntation of the number of node that is being inserted
                                  //if the 8th node is being inserted (i.e, the tree already contains 7 nodes including root), then arr stores [1, 0, 0, 0]. But we iterate only through [0,0,0]
                                  // for loop makes sure that of arr[i] is 0, then move to the left child of the current node or else if arr[i] is 1, then move to right child of the current node.
                                  //this process helps us in reaching the last node where the given node will be inserted as one of the child of the current node.
      if(arr[i]==0){
        if(current->left != nullptr){
          current = current->left;
        }
        else{                     // when we reach the position where the node is to be inserted, set the parent of the new_node to the current node and insert it.
          new_node->parent = current;
          current->left = new_node;
          x++;      // update the total number of nodes+1
          extra = current->left;
          for(int j=0; j<x-2; j++){
            if(extra->parent->object < extra->object){
              temp->object = extra->object;
              extra->object = extra->parent->object;
              extra->parent->object = temp->object;
              extra = extra->parent;
            }
            else{
              return;
            }
          }
        }
      }
      else if(arr[i]==1){
        if(current->right != nullptr){
          current = current->right;
        }
        else{
          new_node->parent = current;
          current->right = new_node;
          x++;
          extra = current->right;
          for(int j=0; j<x-2; j++){
            if(extra->parent->object < extra->object){
              temp->object = extra->object;
              extra->object = extra->parent->object;
              extra->parent->object = temp->object;
              extra = extra->parent;
            }
            else{
              return;
            }
          }
        }
      }
    }
  }
  if(current->left == nullptr && current->right == nullptr){  //base case : if left and right child of current node are nullpoiter then insert the new_node as the left child of the current_node.
    new_node->parent = current;
    current->left = new_node;
    extra = current->left;
    x++;  //// update the total number of nodes+1
    for(int j=0; j<x-2; j++){
      if(extra->parent->object < extra->object){
        temp->object = extra->object;
        extra->object = extra->parent->object;
        extra->parent->object = temp->object;
        extra = extra->parent;
      }
      else{
        return;
      }
    }
  }
  else if(current->left != nullptr && current->right == nullptr){ //base case: if right child of current node is nullpoiter and left child is not nullpointer then insert the new_node as the left child of the current_node.
    new_node->parent = current;
    current->right = new_node;
    x++;  //// update the total number of nodes+1
    extra = current->right;
    for(int j=0; j<x-2; j++){
      if(extra->parent->object < extra->object){
        temp->object = extra->object;
        extra->object = extra->parent->object;
        extra->parent->object = temp->object;
        extra = extra->parent;
      }
      else{
        return;
      }
    }

  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  



  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // int r = 0;
  // int b_num = 0;
  // int prod = 1;

  // while(x != 0){   //b_num is binary representation of x
  //   r = x%2;
  //   b_num += r*prod;
  //   x = x/2;
  //   prod *= 10;
  // }

  // int a,b;
  // int arr[5];
  // int m = 0;

  // while(b_num != 0){  //arr stores the individual digits of the number b_num
  //   a = b_num%10;
  //   arr[m] = a;
  //   m++;
  //   b_num = b_num/10;
  // }

  // TreeNode<T> *current = root;



  // for(int i = m-2; i>-1; i--){  //we iterate through the digits of the binary represntation of the number of node that is being inserted
  //                                 //if the 8th node is being inserted (i.e, the tree already contains 7 nodes including root), then arr stores [1, 0, 0, 0]. But we iterate only through [0,0,0]
  //                                 // for loop makes sure that of arr[i] is 0, then move to the left child of the current node or else if arr[i] is 1, then move to right child of the current node.
  //                                 //this process helps us in reaching the last node where the given node will be inserted as one of the child of the current node.
  //     if(arr[i]==0){
  //       if(current->left != nullptr){
  //         current = current->left;
  //       }
  //       else{                     // when we reach the position where the node is to be inserted, set the parent of the new_node to the current node and insert it.
  //         new_node->parent = current;
  //         current->left = new_node;
  //         x++;      // update the total number of nodes+1
  //         return;
  //       }
  //     }
  //     else if(arr[i]==1){
  //       if(current->right != nullptr){
  //         current = current->right;
  //       }
  //       else{
  //         new_node->parent = current;
  //         current->right = new_node;
  //         x++;
  //         return;
  //       }
  //     }
  //   }

   return;
}

// template<typename T>
// int Heap<T>::height(TreeNode<T> node){
//   if (node->left != NULL && node->right != NULL){
//     return 1 + max(height(node->left), height(node->right));
//   }
//   else if (node->left != NULL && node->right == NULL){
//     return 1 + height(nod->left);
//   }
//   // else if (nod->left == NULL && nod->right != NULL){
//   //   return 1 + height(nod->right);
//   // }
//   return 0;
// }

// template<typename T>
// int Heap<T>::bal_fac(TreeNode<T> node){
  
//   if(node == NULL){
//     return 0;
//   }
//   if (node->left != NULL && node->right != NULL){
//     int lh = height(node->left);
//     int rh = height(node->right);
//     return lh - rh;
//   }
//   else if (node->left != NULL && node->right == NULL){
//     int lh = height(node->left);
//     return lh;
//   }
//   // else if (nodd->left == NULL && nodd->right != NULL){
//   //   int rh = nodd->right->height;
//   //   return -rh;
//   // }
//   return 0;
// }

  
