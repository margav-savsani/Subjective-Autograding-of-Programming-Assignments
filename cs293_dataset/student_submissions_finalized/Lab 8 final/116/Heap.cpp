#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


template<typename T>
void swap(TreeNode<T>* node)
{
  TreeNode<T>* current= node;
  TreeNode<T>* parentOfcurrent=current->parent;
  while(parentOfcurrent!=nullptr)
  {
    if(current->object.rating >parentOfcurrent->object.rating)
    {
      T temp=current->object;
      current->object=parentOfcurrent->object;
      parentOfcurrent->object=temp;
  
     }
    else 
    return;
    current = parentOfcurrent;
    parentOfcurrent=current->parent; 
  }
 
}
template<typename T>
void Heapify(TreeNode<T>* node)
{
  TreeNode<T>* current= node;
  while(!((current->right < current) && (current->left < current )))
  {

  
    if(current->left->object < current->right->object){
      T temp=current->object;
      current->object=current->right->object;

      current->right->object=temp;
      current=current->right; 
    }
    else
    {
      T temp=current->object;
      current->object=current->left->object;

      current->left->object=temp;
      current=current->left;
    }
  }
  return;

}

template<typename T>
void Heap<T>::insert(T obj) 
{
  // insert your code here
  
  if(root==nullptr){
    root=new TreeNode<T> (obj);
    LastNode =root;
    Nodes++;
    return ;
  }
              
  TreeNode<T>* lNode=LastNode;
  TreeNode<T>* Pnode=nullptr;
  TreeNode<T>* current=root;
  TreeNode<T>* ParOf = nullptr;

  int level = log2(Nodes+1); //level in which node is going to be insert
  double nodes = pow(2,level); // nodes in that level
  double temp = Nodes -(pow(2,level)-1);

  if(temp == 0){
    while(current!=nullptr)
    ParOf = current;
    current=current->left;
  }

  
  else if(temp == nodes/2)
  {
    current=root->right;
    while(current!=nullptr){
      ParOf = current;
      current=current->left;
    }
  }
  else
  {
    while(current!=nullptr)
    {
      
      Pnode=lNode->parent;
      if(lNode == Pnode->right)
      {
        lNode=Pnode;
          
      }
      else
      {
        lNode=Pnode->right;
        current=lNode;
        while(current!=nullptr){
          ParOf = current;
          current=current->left;
        }
      }
    }  
  }

   
   
  if (current==nullptr)
  {  
    current=new TreeNode<T> (obj);
    if (ParOf->left==nullptr)
    {
      ParOf->left=current;
      LastNode=current;
      Nodes++;
    
    }

    else
   {
      Pnode->right=current;
      LastNode=current;
      Nodes++;
    }
  }

   
  
  TreeNode<T>* x= current;
  if(Pnode->object.rating >= x->object.rating)
  {
    return;
  }
  else 
  {
    swap(x);
    return;
  }  
   
}


template<typename T>
void Heap<T>::delMax() 
{

  // insert your code here
  TreeNode<T>* lNode = LastNode;
  if(LastNode==nullptr)
    return;
  
  else
  {
    TreeNode<T>* current=root;

    //swapping the objects.   
    T temp = current->object;
    current->object=LastNode->object;
    LastNode->object=temp;
    Nodes--;
    int level = log2(Nodes+1);
    double nodes = pow(2,level); 
    double p = Nodes -(pow(2,level)-1);
    
    if(p == 0){
      TreeNode<T>* lst = nullptr;
      while(current != nullptr)
      {
        lst = current;
        lNode = lst;
        current = current->right;
      }

    }
    else if(p == nodes/2)
    {
      
    current=current->left;
    while(current!=nullptr)
    {

      lNode =current;
      current=current->right;

    }
    }
    else
    { TreeNode<T>* Pnode = nullptr;
      while(current != nullptr){
      {
        Pnode=lNode->parent;
        if(lNode == Pnode->right)
        {
        lNode=Pnode->left;
        if(lNode->left != nullptr)
        {

          lNode = lNode->left;
          current =lNode->right;
        }
        else
        current = current->left; 
          
        }
        else
        {
          lNode = Pnode;
        
          while(current!=nullptr)
          {
            lNode = current;
            current=current->right;
          }

        }
      } 
    }  
  }
  TreeNode<T>* pNode=LastNode->parent;
  if(pNode->right ==LastNode){
    pNode->right==nullptr;
    LastNode = lNode;
  }

  if(pNode->left == LastNode){
    pNode->left==nullptr;
    LastNode = lNode;
  }
  Heapify(current);
}

return;
}


template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  if(node != nullptr )   {
   TreeNode<T>* curr = node;

    // print the value of the node

    cout << node->object << "|  ";
    curr = curr->left;
    // enter the next tree level - left and right branch
    printHeap(curr);
    curr = curr->right;
    printHeap(curr);

  }
  else 
  return;
}

  
