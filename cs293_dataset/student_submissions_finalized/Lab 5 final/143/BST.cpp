#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST
bool BST::insert(int jrnyCode, int price)
{
  TreeNode *x;
  x = this->root;
  if(x==nullptr){  //first insertion
    x = new TreeNode(jrnyCode,price);
    root=x;
    root->height=0; //setting the root height to 0
  }
  else{
    while(true){ 
      TreeNode *y;
      y = new TreeNode(jrnyCode,price); //treenode created so as to use BSTLessThan
      if(BSTLessThan(y,x)){ 
        if(x->left==nullptr){
          updateBSTParentChild(y,x,true); //updating parent child
          y->height=0;
          x = x->left;
          break;
        }
        else{
          x = x->left;
        }
      }   
      else if(BSTLessThan(x,y)){
        if(x->right==nullptr){
            updateBSTParentChild(y,x,false); //updating parent child
            y->height=0;
            x = x->right;
            break;
        }
        else{
            x = x->right;
        }
      }   
      else{
        return false;
      }
    }
  }
  while(x->parent!=nullptr){
    if(x->parent->height>=(x->height+1)){ //increasing the height till there is no further requirement 
      break;
    }
    else{
      x->parent->height = x->height+1; 
      x = x->parent;
    }
  }


  return true;
}
// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode) //finding if the particular journeycode is present or not
{
  TreeNode *x;
  x = this->root;
  TreeNode *y;
  y = new TreeNode(jrnyCode,0); //TreeNode created to compare journeycode
    while(true){
      if(x==nullptr){
        break;
      }
      if(x->journeycode()==jrnyCode){
        return x->Price();
      }
      else if(BSTLessThan(y,x)){ 
        x = x->left;
      }
      else if(BSTLessThan(x,y)){
        x= x->right;
      }
    }
  return -1;
}
TreeNode* BST::successor(TreeNode *ele){ //finding the successor of an element
  if(ele->right!=nullptr){
    ele = ele->right;
    while(true){
      if(ele->left==nullptr){
        return ele;
      }  
      else{
        ele = ele->left;
      }
    }
  }
  TreeNode *y;
  y = ele->parent;
  while(y!=nullptr && y->right==ele){
    ele = y;
    if(y!=root){
      y = y->parent;
    }
    else{
      y=nullptr;
    }
  }
  return y;
}

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.
bool BST::remove(int jrnyCode)
{
  TreeNode *x;
  x = root;
  TreeNode *z;
  z = new TreeNode(jrnyCode,0);
  while(true){
    if(x==nullptr){
      return false;
    }
    if(x->journeycode()==jrnyCode){
      break;
    }
    else if(BSTLessThan(z,x)){ 
      x = x->left;
    }
    else if(BSTLessThan(x,z)){
      x = x->right;
    }
  } //finding the journeycode
  TreeNode *y,*d,*c;
  c=x;
  if(x->left==nullptr || x->right==nullptr){ //updating the height before deletion
    y = x;
    while(c->parent!=nullptr){
      if(c!=root){
        if(c==c->parent->left && c->parent->right!=nullptr){
          if(c->parent->height!=c->parent->right->height+1){
            c->parent->height = c->parent->height -1;
            c=c->parent;
          }
          else{
            break;
          }
        }
        else if(c==c->parent->left && c->parent->right==nullptr){
          c->parent->height = c->parent->height -1;
          c=c->parent;
        }
        else if(c==c->parent->right && c->parent->left!=nullptr){
          if(c->parent->height!=c->parent->left->height+1){
            c->parent->height = c->parent->height -1;
            c=c->parent;
          }
          else{
            break;
          }
        }
        else if(c==c->parent->right && c->parent->left==nullptr){
          c->parent->height = c->parent->height -1;
          c=c->parent;
        }
      }
    }
  }
  else{
    y =successor(x);
    if(y==x->right){
      while(c->parent!=nullptr){
        if(c!=root){
          if(c->left==nullptr || c->height != c->left->height +1){
            if(c==c->parent->left && c->parent->right!=nullptr){
              if(c->parent->height!=c->parent->right->height+1){
                c->parent->height = c->parent->height -1;
                c=c->parent;
              }
              else{
                break;
              }
            }
            else if(c==c->parent->left && c->parent->right==nullptr){
              c->parent->height = c->parent->height -1;
              c=c->parent;
            }
            else if(c==c->parent->right && c->parent->left!=nullptr){
              if(c->parent->height!=c->parent->left->height+1){
                c->parent->height = c->parent->height -1;
                c=c->parent;
              }
              else{
                break;
              }
            }
            else if(c==c->parent->right && c->parent->left==nullptr){
              c->parent->height = c->parent->height -1;
              c=c->parent;
            }
          }
          else{
            break;
          }
        }
      }
    }
  }
  if(y->left!=nullptr){
    d = y->left;
  }
  else{
    d = y->right;
  }
  if(d!=nullptr){
    d->parent=y->parent;
  }
  if(y->parent==nullptr){
    root =d;
  }
  else if(y->parent->left==y){
    y->parent->left =d;
  }
  else{
    y->parent->right=d;
  }
  if(y!=x){
      x->setjc(y->journeycode());
      x->setp(y->Price());
  }
  
  
  return true;
}


