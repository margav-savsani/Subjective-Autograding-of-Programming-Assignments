#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

// implementation of a maxheap using a binary tree instead of an array.


template<typename T>
void Heap<T>::insert(const T &val){
    // address the case of the tree being empty.
    if (!root){
        root = new node(val, nullptr);
        size = 1;
        return;
    }

    // now we go down to the place that we need to add the node at.
    // To do this, we do the following:
    // each node has a number associated with it (1 (2 3) (4 5 6 7) (8 9 ... 15) ...).
    // write these numbers as their base 2 representations:
    // (1 1(0 1) 1(00 01 10 11) 1( 0(0(0 1) 1(0 1))  1(0(0 1) 1(0 1))) ) and so on.
    // clearly the digits after the leading (i.e. if index is i then i - 2^depth is what we're looking for) gives us the path to the node if 0 is go-left and 1 is go-right. Think about 101(three moves) to get to 1101 = 13. Hint: The most significant digit is exactly the first step taken from the root.

    size = size + 1; // update size. 
    // the index of the (virtual) element that we have to reach and insert at is now size.
    // get location of the node-to-add's location's parent.
    ptr parent = getLoc(size/2);
    ptr curr;
    if (size%2) curr = parent->right = new node(val, parent); else curr = parent->left = new node(val, parent);

    // now we must bubble our element up:
    while(curr->parent && curr->parent->object < curr->object){
        swapVals(curr, curr->parent);
        curr = curr->parent;
    }
    return;
}

template <typename T>
void Heap<T>::swapVals(ptr a, ptr b){
    const T tmp = a->object;
    a->object = b->object;
    b->object = tmp;
}

template <typename T>
void Heap<T>::delMax(){
    // must delete root basically.
    if (!root) 
        return;
    
    ptr nodeToDel = getLoc(size);
    if (nodeToDel == root){
      delete root; root = nullptr;
      size--; return;
    }
    swapVals(root, nodeToDel);
    
    ptr parent = nodeToDel->parent;
    if (parent->left == nodeToDel) parent->left = nullptr;
    else parent->right = nullptr;
    delete nodeToDel;
    size--;

    // heapify.
    heapify(root);
    return;
}

template <typename T>
void Heap<T>::heapify(ptr curr){
    // perfectly outlines the decision tree, nice!
    while(curr){
        if (curr->left && curr->object < curr->left->object){
            if (curr->right && curr->object < curr->right->object){
                if (curr->right->object < curr->left->object){
                    swapVals(curr, curr->left);
                    curr = curr->left;
                } 
                else{
                    swapVals(curr, curr->right);
                    curr = curr->right;
                }
            }
            else{
                swapVals(curr, curr->left);
                curr = curr->left;
            }
        }
        else if (curr->right && curr->object < curr->right->object){
            swapVals(curr, curr->right);
            curr = curr->right;
        }
        else break;
    }
}

// gets location of the node with index i >= 1. Does it recursively since the least significant digit of index is the LAST move to be done.
// the return value is nullptr if index > size.
template <typename T>
TreeNode<T>* Heap<T>::getLoc(int index){
    if (index > size) return nullptr; // always returned if size = 0, notice.
    if (index == 1) return root;

    ptr parent = getLoc(index / 2); // index <= size -> index/2 <= size and so parent is non-null.
    return (index%2)? parent->right: parent->left; // this works fine as long as index <= size, in which case the return value is non-null (an actual node of the heap).
    // it works fine even if we tweak it a bit and allow inputs for one more row(and then this will return nullptr, but we take care of this and ensure that index is < size otherwise we don't proceed.)
}

template <typename T>
void Heap<T>::printHeap(ptr root, const string &prefix, int index) const{
    // index is the index of the node in the heap.
    
    if (!root){
        cout << "Empty tree\n";
        return;
    }
    // dfs
    struct info{
        ptr root; string prefix; int index;
        info(ptr root, string prefix, int index): root(root), prefix(prefix), index(index){}
    };
    vector<info> toPrint; // in a recursive also we'd use a ptr and a preifx local variable, here we store it right here and make it faster.
    toPrint.push_back(info(root, prefix, index));
    while(toPrint.size()){
        info curr = toPrint.back(); toPrint.pop_back();
        cout << curr.prefix << ((curr.index %2)?"|__":"|--") << "(" << (curr.index) << ") " << curr.root->object << endl; // notice index is even iff left child (last bit zero, or just think)
        if (curr.root->right) toPrint.push_back(info(curr.root->right, curr.prefix + "   ", (curr.index)*2 + 1));
        if (curr.root->left) toPrint.push_back(info(curr.root->left, curr.prefix + "   ", (curr.index)*2));
    }
}

  
