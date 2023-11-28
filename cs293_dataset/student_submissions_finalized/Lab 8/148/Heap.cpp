#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

    if(lastfilled == nullptr){
        root = new T(obj);
        lastfilled = root;
        return;
    }
    if (lastfilled == root){
        root->left == new T(obj);
        lastfilled = root->left;
        return;
    }
    if(lastfilled == lastfilled->parent->left){
        lastfilled->parent->right = new T(obj);
        lastfilled = lastfilled->parent->right;
        return;
    }
    if(lastfilled == lastfilled->parent->right){
        while(lastfilled->parent!= nullptr && lastfilled == lastfilled->parent->right){
            lastfilled = lastfilled->parent;
        }
        if(lastfilled->parent != nullptr){
            lastfilled = lastfilled->parent->right;
            if(lastfilled == nullptr){
                lastfilled = lastfilled->parent;
                lastfilled->right = new T(obj);
                lastfilled = lastfilled->right;
            }
            else{
                while(lastfilled->left != nullptr){
                    lastfilled = lastfilled->left;
                }
                lastfilled->left = new T(obj);
                lastfilled = lastfilled->left;
            }
        }
        else{
            lastfilled = root->left;
            if(lastfilled == nullptr){
                root->left = new T(obj);
                lastfilled = root->left;
            }
            while(lastfilled->left != nullptr){
                lastfilled = lastfilled->left;
            }
            lastfilled->left = new T(obj);
            lastfilled = lastfilled->left;
        }
    }

    // Float lastfilled

    TreeNode<T> currNode* = lastfilled;
    while(currNode->parent != nullptr && currNode->object > currNode->parent->object){
        std::swap(currNode->object, currNode->parent->object);
        currNode = currNode->parent;
    } 

  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  
  if(root == nullptr) return; //Error
  root->object =lastfilled->object;
  if(lastfilled== root) root = lastfilled = nullptr;
  else{
    if(lastfilled== lastfilled->parent->right) {
            TreeNode<T> *newLastfilled = lastfilled->parent->left;
            lastfilled->parent->right = nullptr;
            delete lastfilled;
            lastfilled = newLastfilled;

    }
    if(lastfilled == lastfilled->parent->left){
            lastfilled->parent->left = nullptr;
            TreeNode<T> oldLastFilled = lastfilled;
        while(lastfilled->parent != nullptr && lastfilled == lastfilled->parent->left){
            lastfilled = lastfilled->parent;
        }
        if(lastfilled->parent == nullptr){
            while(lastfilled->right != nullptr){
                lastfilled = lastfilled->right;
            }
            while(lastfilled->left != nullptr){
                lastfilled = lastfilled->right;
            }
        }
        else{
            lastfilled = lastfilled->parent->right;
            while(lastfilled->left != nullptr){
                lastfilled = lastfilled->left;
            }
        }

        delete oldLastFilled;
    }
  }
  heapify(root);

  return;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node) {
        if(node->left == node->right == nullptr){
            return;
        }
        if(node->object < node->left->object){
                // Node-> left will always be nullptr
            std::swap(node->object, node->left->object);
            this->heapify(node->left);
            return;
        }
        if(node->right->object > node->object){
            
            std::swap(node->object, node->right->object);
            this->heapify(node->right);
            return;
        }
}
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  node = root;
  while(node->object > 50){
  
  cout << node->object  << endl;
  this->delmax();
  node = root;
  }

  return;
}

  
