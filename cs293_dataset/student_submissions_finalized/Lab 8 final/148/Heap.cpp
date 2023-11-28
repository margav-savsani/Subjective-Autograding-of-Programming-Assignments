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
        root = new TreeNode<T>(obj);
        lastfilled = root;
    }
    else if (lastfilled == root){
        root->left = new TreeNode<T>(obj);
        root->left->parent = root;
        lastfilled = root->left;
    }
    else if(lastfilled == lastfilled->parent->left){
        lastfilled->parent->right = new TreeNode<T>(obj);
        lastfilled->parent->right->parent = lastfilled->parent;
        lastfilled = lastfilled->parent->right;
    }
    else if(lastfilled == lastfilled->parent->right){
        while(lastfilled->parent!= nullptr && lastfilled == lastfilled->parent->right){
            lastfilled = lastfilled->parent;
        }
        if(lastfilled->parent != nullptr){
            lastfilled = lastfilled->parent->right;
            if(lastfilled == nullptr){
                lastfilled = lastfilled->parent;
                lastfilled->right = new TreeNode<T>(obj);
                lastfilled->right->parent = lastfilled;
                lastfilled = lastfilled->right;
            }
            else{
                while(lastfilled->left != nullptr){
                    lastfilled = lastfilled->left;
                }
                lastfilled->left = new TreeNode<T>(obj);
                lastfilled->left->parent = lastfilled;
                lastfilled = lastfilled->left;
            }
        }
        else{
            lastfilled = root->left;
            if(lastfilled == nullptr){
                root->left = new TreeNode<T>(obj);
                lastfilled = root->left;
                root->left->parent = root;
            }
            while(lastfilled->left != nullptr){
                lastfilled = lastfilled->left;
            }
            lastfilled->left = new TreeNode<T>(obj);
            lastfilled->left->parent = lastfilled;
            lastfilled = lastfilled->left;
        }
    }

    // Float lastfilled

    TreeNode<T> *currNode = lastfilled;
    while(currNode->parent != nullptr && currNode->parent->object < currNode->object){
        std::swap(currNode->object, currNode->parent->object);
        currNode = currNode->parent;
    } 


    /* printHeap(root); */
    return;
}

template<typename T>
void Heap<T>::delMax() {

        // insert your code here


        if(root == nullptr) return; //Error
        root->object =lastfilled->object;
        if(lastfilled== root) {
                delete root;
                root = lastfilled = nullptr;
        }
        else if(lastfilled== lastfilled->parent->right) {
                TreeNode<T> *newLastfilled = lastfilled->parent->left;
                lastfilled->parent->right = nullptr;
                delete lastfilled;
                lastfilled = newLastfilled;

        }
        else if(lastfilled == lastfilled->parent->left){
                lastfilled->parent->left = nullptr;
                TreeNode<T> *oldLastFilled = lastfilled;
                lastfilled = lastfilled->parent;
                while(lastfilled->parent != nullptr && lastfilled == lastfilled->parent->left){
                        lastfilled = lastfilled->parent;
                }
                if(lastfilled->parent == nullptr){
                        while(lastfilled->right != nullptr){
                                lastfilled = lastfilled->right;
                        }
                        while(lastfilled->left != nullptr){
                                lastfilled = lastfilled->left;
                        }
                }
                else{
                        lastfilled = lastfilled->parent->left;
                        while(lastfilled->right!= nullptr){
                                lastfilled = lastfilled->right;
                        }
                }

                delete oldLastFilled;
        }
        heapify(root);

        return;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node) {
        if(node->left == node->right &&  node->right == nullptr){
                return;
        }
        if(node->object < node->left->object){
                // Node-> left will always be nullptr
                std::swap(node->object, node->left->object);
                this->heapify(node->left);
                return;
        }
        if(node->right == nullptr){
                return;
        }
        if(node->object < node->right->object){

                std::swap(node->object, node->right->object);
                this->heapify(node->right);
                return;
        }
}
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

        // insert your code here

        printHeapRecursive(node, "");

}


        template<typename T>
void Heap<T>::printHeapRecursive(TreeNode<T> *node,const string& prefix, bool isLeft)
{
        if( node != nullptr )
        {
                cout << prefix;

                cout << (isLeft ? "|--" : "|__" );

                // print the value of the node
                cout << node->object<< endl;
                // enter the next tree level - left and right branch
                printHeapRecursive(node->left, prefix + (isLeft ? "│   " : "    "), true);
                printHeapRecursive(node->right, prefix + (isLeft ? "│   " : "    "), false);
        }
}
