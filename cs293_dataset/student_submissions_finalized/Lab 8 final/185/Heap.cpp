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
  TreeNode<T> *new_node = new TreeNode<T>(obj); //new node to be inserted. right now it's parent is nullptr
  T temp;
  TreeNode<T> *extra;
  
  if(root == nullptr){
    root = new TreeNode<T>(obj);  //creates the root if root is initially a nullpointer.
    last = root;  //"last" stores the last node inserted int he heap
    x++;  //x stores (total number of nodes + 1) to find the next number of node to be inserted.
    m = 0;  //m stores the total number of elements in the "arr" where "arr" stores the digits in binary representation of x.
            //update m again to 0 after successfull insertion 
    return;
  }
  
  int *arr = bin_arr(x);

  if(current->left != nullptr && current->right != nullptr){
    
    for(int i = m-2; i>-1; i--){  //we iterate through the digits of the binary represntation of the number of node that is being inserted
                                  //for example: if the 8th node is being inserted (i.e, the tree already contains 7 nodes including root), then arr stores [1, 0, 0, 0]. But we iterate only through [0,0,0]
                                  // "for" loop makes sure that if arr[i] is 0, then move to the left child of the current node or else if arr[i] is 1, then move to right child of the current node.
                                  //this process helps us in reaching the node where the given node will be inserted as one of the child of the that node.
      if(arr[i]==0){
        if(current->left != nullptr){  //if arr[i] is 0 and left child of current is not nullptr then current = current->left
          current = current->left;
        }
        else{                     // when we reach the position where the node is to be inserted (i.e, left pointer of the node is nullptr), set the parent of the new_node to the current node and insert it.
          new_node->parent = current;  //set the parent of the new node as current and insert it as current->left
          current->left = new_node;
          x++;      // update the total number of nodes+1
          last = current->left;  //update the "last" node in the heap which is the newly inserted node
          extra = current->left;
          Heapify(extra);    //heapify the newly inserted node i.e, swap the object of newly inserted node and it's parent if value of it's object is gretaer than it's parent's object. do it till the this condition becomes false
          //printHeap(root);   //to print the heap and check the process
          return;
        }
      }
      else if(arr[i]==1){   
        if(current->right != nullptr){   //if arr[i] is 1 and right child of current is not nullptr then current = current->right
          current = current->right;  
        }
        else{    // when we reach the position where the node is to be inserted (i.e, right pointer/child of the node is nullptr), set the parent of the new_node to the current node and insert it.
          new_node->parent = current;  //set the parent of the new node as current and insert it as current->right
          current->right = new_node;
          x++;  // update the total number of nodes+1
          last = current->right;  //update the "last" node in the heap which is the newly inserted node
          extra = current->right;
          Heapify(extra);    //heapify the newly inserted node i.e, swap the object of newly inserted node and it's parent if value of it's object is gretaer than it's parent's object. do it till the this condition becomes false
          //printHeap(root);   //to print the heap and check the process
          return;
        }
      }
    }
  }
  if(current->left == nullptr && current->right == nullptr){  //base case : if left and right child of current node are nullpoiter then insert the new_node as the left child of the current_node.
    new_node->parent = current;   //set the parent of the new node as current and insert it as current->left
    current->left = new_node;
    last = current->left;  //update the "last" node in the heap which is the newly inserted node
    extra = current->left;
    x++;  //// update the total number of nodes+1
    Heapify(extra);   //heapify the newly inserted node i.e, swap the object of newly inserted node and it's parent if value of it's object is gretaer than it's parent's object. do it till the this condition becomes false
    return;
  }
  else if(current->left != nullptr && current->right == nullptr){ //base case: if right child of current node is nullpoiter and left child is not nullpointer then insert the new_node as the left child of the current_node.
    new_node->parent = current;   ////set the parent of the new node as current and insert it as current->right
    current->right = new_node;
    x++;  //// update the total number of nodes+1
    last = current->right;   //update the "last" node in the heap which is the newly inserted node
    extra = current->right;
    Heapify(extra);   //heapify the newly inserted node i.e, swap the object of newly inserted node and it's parent if value of it's object is gretaer than it's parent's object. do it till the this condition becomes false
    return;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  //cout << "last" << last->object << endl;  //to check whether my last node is correct or not
  
  TreeNode<T> *new_root = last;
  TreeNode<T> *new_last = root;
  TreeNode<T> *current = root;

  if(new_last == new_root){  //if heap contains only root, then delete root and return
    root = nullptr;
    return;
  }

  root->object = last->object;  //replace object of root with object of the last node. we will delete the last node in next step.

  int *arr = bin_arr(x-2);  //store the traversing array(to traverse till current second last node) to update the last node with second last node.

  // for(int l=m-2; l>-1; l--){
  //   cout << arr[l] << " " ;  }   //to check whether the traversing array is accurate or not


  if(last->parent->right == last){  //if the last node is the right child of it's parent(we will simply update the last date with the left child of the parent of current last node)
    TreeNode<T> *save = last->parent->left ;
    new_root->parent->right = nullptr;   //delete the last node
    Heapify_del(root);  //heapify the root if unbalanced(not a heap)
    last = save;    //update the last node as the second last node
    m = 0;  //again initialise m to 0
    x = x-1;  //decrease the number of nodes to traverse
    return;  //node successfully deleted. now return
  }

  else if(last->parent->left == last){  //if the last node is the left child of it's parent(we will find the second last node and update the last date with it)

    new_root->parent->left = nullptr;  //first delete the last node
    
    for(int i = m-2; i>-1; i--){    //traverse the heap to get to the next last node
                                    //if arr[i]=0, go to the left child or else if 1 then go to the right child
    
      if(arr[i]==0){
        if(current->left != nullptr){
          current = current->left;
        }
      }
      else if(arr[i]==1){
        
        if(current->right != nullptr){
          current = current->right;
        }
        }
      if(current->left == nullptr && current->right == nullptr){  // if both the children of node becomes empty while traversing,  we reach the next last node
        Heapify_del(root); //heapify the root
        last = current;  //and update the last node pointer with the current node
        m = 0;  //again initialise m to 0
        x = x-1;  //decrease the number of nodes to traverse
        return;  //node successfully deleted. now return
      }

      }
    }
  return;
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node) {  //this heapify checks if isHeap from bottom (where the new node is inserted) to top 
                                            //used while inserting since we insert at last and then heapify
  T temp;
  while(true){
    if(node->parent != nullptr){  
      if(node->parent->object < node->object){  //while parent of node is not a nullptr and node->parent->object < node->object, then their objects
        temp = node->object;
        node->object = node->parent->object;
        node->parent->object = temp;
        node = node->parent;  //move pointer of node it's parent
      }
      else{  //if at any point the condition (node->parent->object < node->object) becomes false i.e, above that point it is already a heap since the change(insertion) was only made at bottom, then update the value of m to 0 and return. heapify is complete
        m = 0;
        return;
      }
    }
    else{  //if the parent of the node becomes null, update the value of m to 0 then return. heapify is complete
      m = 0;
      return;
    }
    }
  
   return;
}

template<typename T>
void Heap<T>::Heapify_del(TreeNode<T> *node) {  //this heapify checks if heap from top to bottom
                                                // just like the heapify in the lectures
                                                //used while deleting since we delete(remove) from top and then heapify
                                                //checks if both the children of the node are smaller then the node, if not then swap the object of node with it's greater child
  T tem;
  while(true){
    if(node->left == nullptr && node->right == nullptr){  //when both the children becomes null i.e, we have reached the end and no more swaping needed.heapify is complete
      m = 0;
      //printHeap(root);   //to print the heap and check the process
      return;
    }
    else if(node->left != nullptr && node->right == nullptr){
      if(node->object < node->left->object){  
        tem = node->object;
        node->object = node->left->object;
        node->left->object = tem;
        node = node->left;
      }
      else{
        m = 0;
        //printHeap(root);   //to print the heap and check the process
        return;
      }
    }
    else if(node->left != nullptr && node->right != nullptr){
      if(node->object < node->left->object && node->object < node->right->object){
          if(node->left->object < node->right->object){
            tem = node->object;
            node->object = node->right->object;
            node->right->object = tem;
            node = node->right;
          }
          else{
            tem = node->object;
            node->object = node->left->object;
            node->left->object = tem;
            node = node->left;
          }
      }
      else if(node->object < node->left->object){
          tem = node->object;
          node->object = node->left->object;
          node->left->object = tem;
          node = node->left;
        }
      else if(node->object < node->right->object){
        tem = node->object;
            node->object = node->right->object;
            node->right->object = tem;
            node = node->right;
      }
      else{
        m = 0;
        //printHeap(root);   //to print the heap and check the process
        return;
      }
      }
  }
  return;
}




template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  printTheHeap(node, "", false);
  return;
}


template<typename T>
int* Heap<T>::bin_arr(int x){
  int r = 0;
  int b_num = 0;
  int prod = 1;

  while(x != 0){   //b_num is binary representation of x
    r = x%2;
    b_num += r*prod;
    x = x/2;
    prod *= 10;
  }

  int a,b;
  int* arr = new int[5];

  while(b_num != 0){  //arr stores the individual digits of the number b_num
    a = b_num%10;
    arr[m] = a;
    m++;
    b_num = b_num/10;
  }

  return arr;
}

template<typename T>
void Heap<T>::printTheHeap(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    root->printInfo();
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printTheHeap(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printTheHeap(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}

template<typename T>
void TreeNode<T>::printInfo()
  {
    cout << "[node " << this->object << "]";
  }

// template<typename T>
// void Heap<T>::print() { printTheHeap(root, "", false); return;}