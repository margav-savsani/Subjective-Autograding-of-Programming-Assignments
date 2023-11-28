#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <class T>
TreeNode<T> *Heap<T>::getNodeByIndex(int i) {
    while (i > 0) {
        path.push(i%2==0);
        i/=2;
    }
    TreeNode<T> *head = root;
    while (!path.empty()){
        int dir = path.top();
        path.pop();
        head = (dir==1 ? head->right : head->left);
    }
    return head;
}

template <typename T>
void Heap<T>::insert(T obj) {
    // insert your code here
    if (count==0){
        root = new TreeNode<T>(obj);
        count++;
        return;
    }
    int par = count/2;
    TreeNode<T> newNode = new TreeNode<T>(obj);
    TreeNode<T>* parent = getNodeByIndex(par);
    if (count%2==0){
        parent->right = newNode;
    }
    else {
        parent->left = newNode;
    }
    newNode->parent = parent;
    count++;
    return;
}

template <typename T>
void Heap<T>::delMax()
{

    // insert your code here

    return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

    // insert your code here
    TreeNode<T> *head = root;
    nodes.push(head);
    while(!nodes.empty()){
        if (nodes.front()==nullptr){
            nodes.pop();
            continue;
        }
        cout<<nodes.front()->object<<endl;
        nodes.push(nodes.front()->left);
        nodes.push(nodes.front()->right);
        nodes.pop();
    }

    return;
}
