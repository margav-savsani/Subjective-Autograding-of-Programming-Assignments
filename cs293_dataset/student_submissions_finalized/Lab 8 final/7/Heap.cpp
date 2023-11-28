#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T> void Heap<T>::heapify(TreeNode<T> *node){
    
    T tempObj;
    
    if(node->parent == nullptr){
      return;
    }
    
    // moving last object up till the conditions are satisfied.
    else {
        if(node->parent->object < node->object){
            tempObj = node->object;
            node->object = node->parent->object;
            node->parent->object = tempObj;
            
            heapify(node->parent);
        }
        else {
            return;
        }
    }
    
}

template<typename T> void Heap<T>::insert(T obj) {
  
      
if(root != nullptr){

  if(last->parent == nullptr){   // When last node is the root.

    last->left = new TreeNode<T>(obj);
    last->left->parent = last;
    last = last->left;
      
      heapify(last);
    
  }
  else{
      // Case 1: last is left child.
    if(last == last->parent->left){
      last->parent->right = new TreeNode<T>(obj);
        last->parent->right->parent = last->parent;
      last = last->parent->right;

      heapify(last);
      
    }
    // case 2: last is right child.
    else if(last == last->parent->right){  // Last is a right child.
        
      TreeNode<T> *curr;
      curr = last;
        
      while(curr != nullptr){
            // case: curr parent is a root.
        if(curr->parent == nullptr){
          while(curr  != nullptr){
            if(curr->left == nullptr){
              curr->left = new TreeNode<T>(obj);
              curr->left->parent = curr;  // parent updation.
              last = curr->left;  // last node updation.
              heapify(last);
              curr = nullptr;
            }    
            else{
              curr = curr->left;
            }
          }
        }
            // case: curr parent is not a root.
        else if(curr->parent != nullptr){
                // case: curr is a left child.
          if(curr == curr->parent->left){
            curr = curr->parent->right;
            while(curr != nullptr){
                        // curr left is a nullptr.
              if(curr->left == nullptr){
                curr->left = new TreeNode<T>(obj);
                curr->left->parent = curr;  // parent updation.
                last = curr->left;  // last node updation.
                heapify(last);
                curr = nullptr;
              }
              else{
                curr = curr->left;
              }
            }
          }
                // case: curr is a right child.
          else if(curr == curr->parent->right){
            curr = curr->parent;
          }
        }
      }
    }
  }

}
            
  else if(root == nullptr){
    root = new TreeNode<T>(obj);
    last = root;
  }
  return;

}

template<typename T> void Heap<T>::heapify_root(TreeNode<T> *node){
    
    T t;
    
    if(node == nullptr){
        return;
    }
    
    else {
        if(node->left == nullptr){
            return;
        }
        else if(node->right == nullptr){
            if(node->object < node->left->object){
                t = node->object;
                node->object = node->left->object;
                node->left->object = t;
                return heapify_root(node->left);
                
            }
            else {
                return;
            }
            
        }
        
        else {
            if((node->object < node->left->object)  &&  (node->object < node->right->object)){
                if(node->left->object < node->right->object){
                    t = node->object;
                    node->object = node->right->object;
                    node->right->object = t;
                    
                    heapify_root(node->right);
                }
                // if(node->right->object <= node->left->object)
                else {
                    t = node->object;
                    node->object = node->left->object;
                    node->left->object = t;
                    
                    heapify_root(node->left);
                }
            }
            
            // if node is less than left then swaping the object with it.
            else if(node->object < node->left->object){
                t = node->object;
                node->object = node->left->object;
                node->left->object = t;
                
                heapify_root(node->left);
            }
            
            // if node is less than right then swaping it.
            else if(node->object < node->right->object){
                t = node->object;
                node->object = node->right->object;
                node->right->object = t;
                
                heapify_root(node->right);
            }
            else {
                return;
            }
        }
    }
    //printHeap(root);
    return;
}

    
    
template<typename T> 
void Heap<T>::delMax() {   // Check whether the return type should be void or T.
    
    if(root == nullptr){
        return;
    }
    
    if(root == last){
        root = nullptr;
        last = nullptr;
        return;
    }
    
  root->object = last->object;

  // -------***last node updation***----------
    
    // When last is a right child.
    
    
    
  if(last == last->parent->right){
      
      last = last->parent->left;
    last->parent->right = nullptr;
      //printHeap();
    
  }
    
    // When last is a left child.
  else if(last == last->parent->left){
      
      // when parent of last is a root.
      if(last->parent->parent == nullptr){
          last = last->parent;
          last->left = nullptr;
          //printHeap();
      }
    
      // When last->parent is a right child.
      else if(last->parent == last->parent->parent->right){
        //last->parent->left = nullptr;
        last = last->parent->parent->left->right;
          last->parent->parent->right->left = nullptr;
          //printHeap();
      }
      
      
    // If last->parent is a left child.
    else if(last->parent == last->parent->parent->left){
        TreeNode<T> *c;
        
        c = last;
    
        while(c != nullptr){
            // when c is the root.
            if(c->parent->parent == nullptr){
                c = c->parent;
                while(c->right != nullptr){
                    c = c->right;
                }
                last->parent->left = nullptr;
                last = c;
                c = nullptr;
                break;
            }
            
            // If parent of c is a right child.
            else if(c->parent == c->parent->parent->right){
                c = c->parent->parent->left;
                while(c->right != nullptr){
                    c = c->right;
                }
                last->parent->left = nullptr;
                last = c;
                c = nullptr;
                break;
            }
            else if(c->parent == c->parent->parent->left){
                c = c->parent;
            }
            else {
                c = c->parent;
            }
        }
        
    }
    
      //last->parent->left = nullptr;
  }

  // heapify.
    
    heapify_root(root);
    
            
 
    
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
   
    
    static string s = "";
    //static bool isLeft;
    string p;
    string q;
    
    if(node == nullptr){
        return;
    }
    else if(node->parent == nullptr){
        cout << "|__" << node->object << endl;
        q = s;
        s = s + "  ";
        p = s;
        printHeap(node->left);
        s = p;
        printHeap(node->right);
        s = q;
    }
    
    else if(node == node->parent->left){
        cout << s + "|--" << node->object << endl;
        q = s;
        s = s + "|  ";
        p = s;
        printHeap(node->left);
        s = p;
        printHeap(node->right);
        s = q;
    }
    
    else if(node == node->parent->right){
        cout << s + "|__" << node->object << endl;
        q = s;
        s = s + "   ";
        p = s;
        printHeap(node->left);
        s = p;
        printHeap(node->right);
        s = q;
    }
    
    
  
  return;
}









  
