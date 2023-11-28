#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;


struct Node {
    int key; 
    struct Node* left;
    struct Node* right;
    int height;
    };

int getheight(  Node* n){
        if (n == NULL)
        {
           return 0;
        }
        return n->height;
}

struct Node* createNode(int key)
{
   struct Node* node = (struct Node* )malloc (sizeof(struct Node));
    node->key = key;
   node->left = NULL;
   node->right = NULL;
   node->height = 1;
   return node;


};
int get_balance_factor(struct Node* n){
    if (n == NULL)
    {
        return 0;
    }
    return (getheight(n->left)-getheight(n->right) + 1);

}
struct Node* rightrotate(struct Node *y){
    struct Node* x = y->left;
    struct Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = (max(getheight(y->right),getheight(y->right)))+1;
    x->height = (max(getheight(y->right),getheight(y->right)))+1;
    return x;
}

struct Node* leftrotate(struct Node *x){
    struct Node* y = x->right;
    struct Node* T2 = y->left;
    
    y->left = x;
    x->right = T2;

    y->height = (max(getheight(y->right),getheight(y->right)));
    x->height = (max(getheight(y->right),getheight(y->right)));
    return y;
}

struct Node* insert(struct Node* node,int key)
{
  if(node == NULL)
      return createNode(key);
  if(key<node->key)
      node->left = insert(node->left ,key);
  else if (key>node->key)
      node->right = insert(node->right,key);
      return node;

  node->height = 1 + max(getheight(node->left), getheight(node->right) );
  int bf = get_balance_factor(node);

  //left left case       
  if(bf>1 && key<node->left->key){
    rightrotate(node);
    return rightrotate(node); 
     } 

  // right right case
  if(bf>1 && key<node->left->key){
    rightrotate(node);
    return rightrotate(node); 
     } 
  // left  right case
 if(bf > 1 && key>node->left->key){
     node->left = leftrotate(node->left);
     leftrotate(node);
    return leftrotate(node); 
     }     

 // right left  case

 if(bf<-1 &&  key< node->right->key){
node->right = rightrotate(node->right);
     leftrotate(node);
    return leftrotate(node); 
     }   

return node;


}
int main(){
    struct Node* root = NULL;
    root = insert(root,3); 
    root = insert(root,4);
    root = insert(root,5);
    root = insert(root,6);
    root = insert(root,7);
    root = insert(root,clear
    8);
  
  
  
  return 0;  
}