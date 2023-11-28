#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *ins_node = new TreeNode<T> (obj);

  if(root==nullptr){
    root = ins_node;
    tail = root;
  }
  
  else if(tail->left==nullptr){ 
    tail->left = ins_node; //heaps are left filed
    tail->left->parent = tail;
    Heapify(tail->left);
  }

  else{
    tail->right = ins_node;
    tail->right->parent = tail;
    Heapify(tail->right);
    TreeNode<T> *temp;
    temp = tail;
    findTail(tail); //finding the new tail (both of its children are full)
    tail->prevTail = temp;
  }
  nodes++; //increasing the number of nodes
  return;
}

template<typename T>
void Heap<T>::findTail(TreeNode<T> *node){ //finds the tail of the heap
  if(node->parent==nullptr){
    tail = node;
    while(tail->left!=nullptr){
      tail=tail->left;
    }
  }
  else if(node->parent->left==node){
    tail=node->parent->right;
    while(tail->left!=nullptr){
      tail=tail->left;
    }
  }
  else{
    findTail(node->parent); 
  }
}

template<typename T>
void Heap<T>::delMax() { //deletes the root of heap by exchanging it with last element and calling heapifydown to make it satisfy the heap condition

  // insert your code here
  if(root==nullptr){
    return;
  }
  if(root==tail){
    if(tail->left==nullptr){ //only root is present
      root=nullptr; 
      tail=nullptr;
    }
    else if(tail->right==nullptr){ //only two elements, so second is made root
      TreeNode<T> *node1=tail->left;
      
      root=nullptr;
      //delete tail;
      root=node1;
      tail=node1;
      root->parent=nullptr;
    }
    else{ //3 present
      if(tail->right->object < tail->left->object){ //left child will become root
        TreeNode<T> *node1=tail->right;
        TreeNode<T> *node2=tail->left;
        root=nullptr;
        //delete root;
        //delete tail;
        root=node2;
        root->parent=nullptr;
        tail=root;
        node1->parent=root;
        root->left=node1;
        root->right=nullptr;
      }
      else{
        TreeNode<T> *node1=tail->right;
        TreeNode<T> *node2=tail->left;
        delete root;
        //delete tail;
        root=node1;
        root->parent=nullptr;
        tail=root;
        node2->parent=root;
        root->left=node2;
        root->right=nullptr;
      }
    }
  }
  else{
    if(tail->right!=nullptr){
      Swap(root,tail->right);
      tail->right=nullptr;
      HeapifyDown(root);
    }
    else if(tail->left!=nullptr){
      Swap(root,tail->left);
      tail->left=nullptr;
      HeapifyDown(root);
    }
    else{
      
      tail = tail->prevTail;
      delMax();
      nodes++;
    }
  }
  nodes--;
  return;
}


template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node) { //move up the tree from a node till it satisfies heap condition
  if(node->parent==nullptr){
    return;
  }
    
  if(node->parent->object < node->object){
    //cout<<node->parent->object<<" "<<node->object<<endl;
    Swap(node->parent,node);
    Heapify(node->parent);
  }
  return;
}
  

template<typename T> 
void Heap<T>::Swap(TreeNode<T> *node1, TreeNode<T> *node2){ //swaps the object stored in the node(not the pointer)
  T object1 = node1->object;
  node1->object = node2->object;
  node2->object = object1;
}

template<typename T>
void Heap<T>::HeapifyDown(TreeNode<T> *node){ //move down from a node till the tree satisfies heap condition
  while(true){ 
    if(node==nullptr || node->left==nullptr){
      return;
    }
    else if(node->right==nullptr){
      if(node->object < node->left->object){
        Swap(node,node->left);
        node=node->left;
        continue;
      }
      else{
        break;
      }
    }
     else{
       if((node->object < node->left->object)&&(node->object < node->right->object)){
         if(node->right->object < node->left->object){
           Swap(node,node->left);
           node=node->left;
           continue;
         }
         else{
           Swap(node,node->right);
           node=node->right;
           continue;
         }
       }
       else if(node->object < node->left->object){
         Swap(node,node->left);
         node=node->left;
         continue;
       }
       else if(node->object < node->right->object){
         Swap(node,node->right);
         node=node->right;
         continue;
       }
       else{
         break;
       }
     }
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) { //prints the heap
 static int node_num=0;
  // insert your code here
  if(node!=nullptr){
    if(node->parent==nullptr){
      cout<<node->object<<endl;
    }
    else{ 
      if(node->parent->left==node){
        for(int i=0; i<(node_num+1)/2;i++){ 
          cout<<" ";
        }
        cout<<"|--";
      }
      else{
        for(int i=0; i<(node_num+1)/2;i++){ 
          cout<<" ";
        }
        cout<<"|__";
      }
      cout<<node->object<<endl;
    }
    int x=node_num;
    node_num=2*node_num+1;
    printHeap(node->left);
    node_num=node_num+1;
    printHeap(node->right);  
    node_num=x;
  }
  
}



//------------------------------------------------------------//
// ignore please

  //while(true){ 
    // else if(node->right==nullptr){
    //   if(node->left->object > node->object){
    //     Swap(node,node->left);
    //     continue;
    //   }
    //   else{
    //     break;
    //   }
    // }
    // else{
    //   if((node->left->object>node->object)&&(node->right->object>node->object)){
    //     if(node->left->object > node->right->object){
    //       Swap(node,node->left);
    //       continue;
    //     }
    //     else{
    //       Swap(node,node->right);
    //       continue;
    //     }
    //   }
    //   else if(node->left->object>node->object){
    //     Swap(node,node->left);
    //     continue;
    //   }
    //   else if(node->right->object>node->object){
    //     Swap(node,node->right);
    //     continue;
    //   }
    //   else{
    //     break;
    //   }
    // }
  //}


  // tail->object = ins_node->object;
  // nodes++;
  
  // if(ceil(log2(nodes+1))==floor(log2(nodes+1)){ //number of nodes in the tree currently is of form 2^n - 1 if this condition is satisfied
  //   TreeNode * trav = root;
  //   while(trav!=nullptr){
  //     trav = trav->left;
  //   }
  //   tail = trav;  //tail will be the first node of next level if the tree is full
  //   tail->parent = trav->parent;
  // } 
  // else if(nodes%2==0){
  //   tail = tail->parent->right;
  // }
  // else{
    
  // }

  //tail->parent = ins_node->parent;
      /*TreeNode<T> *trav=root;
      int binarynum[64];
      int nodes_cp=2*nodes-1;
      cout<<nodes_cp<<" ";
      int i=0;
      while(nodes_cp>0){
        binarynum[i]=nodes_cp%2;
        nodes_cp=nodes_cp/2;
        i++;
      }
      for(int j=i-2; j>=0;j--){
        if(binarynum[j]==1){
          trav=trav->right;
        }
        else{
          cout<<j<<endl;
          trav=trav->left;
        }
      }
      Swap(root,trav);
      tail=trav->parent;
      tail->right=nullptr;
      HeapifyDown(root);*/