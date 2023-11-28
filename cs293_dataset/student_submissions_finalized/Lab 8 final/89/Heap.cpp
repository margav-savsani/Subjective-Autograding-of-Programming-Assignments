#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

int a=0;  //variable that tells about no of nodes present in the heap
int b=0;

template<typename T>
void Heap<T>::Insert(TreeNode<T>* &Z, T x, int i){
   if(i==1)                    // i = index of the node when heap is stored as array 
      {                      
        Z=new TreeNode(x);
        return;
        }  
   else if(i==2)
       {
         Z->left=new TreeNode(x); 
         return;
         }
   else if(i==3)
       {
         Z->right=new TreeNode(x);
         return;
        }         
   int a=i;
   int c=i;
   int d=i;  // variable d is going to store the greatest number of the form 2^x which is less than i 
   
   while(c!=2 && c!=3)    // if c=2, the node we are going to insert will be in the left subtree 
      c=c/2;              //    and if c=3 it will be in the right subtree, taking Z as root node
      
   int b=0;
   while(true)
    {
      b=0;	
      while(a!=1)
       {
         if(a%2!=0) {b=1;break;}
         a=a/2;
         }
       if(b==1) {d--;a=d;continue;}
       if(b==0) break; 
     }  
    if(c==2)  
    {                              // calling Insert function in the left sub tree  
     Insert(Z->left,x,i-d/2);      //i-d/2 is the index of node we are going to insert when heap is stored as array taking Z->left as root (left subtree) 
     Heapify(Z->left);
     }
   else
    {                             // calling Insert function in the right subtree 
     Insert(Z->right,x,i-d);      //i-d/2 is the index of node we are going to insert when heap is stored as array taking Z->right as root (right subtree) 
     Heapify(Z->right);
     }

   return;
}

template<typename T>
void Heap<T>::insert(T obj) {
   if(b==1)
    {               // if we are going to insert the first node, we have to make sure that a=0; and pointer to root is null 
      root=NULL;
      a=0;
      b=0;
     } 
     a++;
     Insert(root,obj,a);
     Heapify(root);
  //   printHeap(root);   
  return;
}

template<typename T>
T Heap<T>::del(TreeNode<T>* Z, int i) {
   if(i==2) 
     {
       T obj=Z->left->object;
       Z->left=NULL; 
       return obj;
      } 
   if(i==3)
    {
        T obj=Z->right->object;
        Z->right=NULL;
        return obj; 
      }	
      
   int a=i;
   int c=i;
   int d=i;
   while(c!=2 && c!=3)        // if c=2, the node we are going to delete is in the left subtree and if c=3
      c=c/2;                  //   it is in the right subtree, taking Z as root node 
                    
    int b=0;
   while(true)
    {
      b=0;	
      while(a!=1)
       {
         if(a%2!=0) {b=1;break;}
         a=a/2;
        }
      if(b==1) 
        {
          d--;
          a=d;
          continue;
         }
      if(b==0) break; 
    }  
   if(c==2)                          
      return del(Z->left,i-d/2);    // calling del function in the left sub tree  
   else
      return del(Z->right,i-d);     // calling del function in the right sub tree 
   
  }      

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  b=1;
  if(a==1) 
    {
      root=NULL;a--;
      return;
     } 
  T obj=del(root,a);     //del(root,a) returns object of the last inserted node
  root->object=obj;      //storing the object of the last inserted node in the root node  
  a--;                   // decreasing variable a as we have deleted a node
  
  Heapify(root);
 // printHeap(root);  
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
 // insert your code here
  static string s = "";
  static int recursion_level=0;
  static bool l = false;	
  recursion_level++;
  if(recursion_level==1)
  {  
    s="";
    l=false;
   }
  if(node!=NULL)
   {
     if(l) cout<<s<<"|--"<<node->object<<"\n";
     else cout<<s<<"|__"<<node->object<<"\n";
     string str=s;	
     s=s+" ";	
     l=true;
     printHeap(node->left);
     str=str+" ";
     s=str;
     l=false;
     printHeap(node->right);
    }
  recursion_level--;
  return;     
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T>* &node){
   if(node==NULL || node->left==NULL) return;
   if(node->right==NULL)
    { 
      if(node->object < node->left->object) 
        { 
           T X = node->object;
           node->object=node->left->object;
           node->left->object=X;        
          } 
        return;
      }
       
   if((node->object < node->left->object) || (node->object < node->right->object))
       {
         T X = node->object;
         if(node->right->object < node->left->object)
             {                                           // if rating of the object in the left node is greater, we swap objects of the parent and the left child 
               node->object=node->left->object;
               node->left->object=X;
                Heapify(node->left); 
               }
         else if(node->left->object < node->right->object)      
             {                                          // if rating of the object in the right node is greater, we swap objects of the parent and the right child  
               node->object=node->right->object;
               node->right->object=X; 
               Heapify(node->right);            
              }
          else
            { 
               node->object=node->left->object;
               node->left->object=X;
                Heapify(node->left); 
               }                 
         }
   else return;          

}  
