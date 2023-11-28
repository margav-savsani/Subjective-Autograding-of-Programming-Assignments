#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif







// template <typename T>
// void Heap<T>::insert(T obj)
// {
// 	// insert your code here

// 	return;
// }

template <typename T>
void Heap<T>::insert(T t)
{
    if (noOfNodes == 0)
    {
        root = new TreeNode<T>(t);
        noOfNodes = 1;
        lastNode = root;
        return;
    }
    lastNode = getNFI(t);
    T temp = lastNode->object;
    TreeNode<T> *pNode = lastNode->parent;
    TreeNode<T> *cNode = lastNode;
    while (pNode->object < temp)
    {
        cNode->object = pNode->object;
        cNode = pNode;
        pNode = pNode->parent;
        if (pNode == nullptr)
        {
            break;
        }
    }
    cNode->object = temp;
    noOfNodes++;
    return;
}





template <typename T>
TreeNode<T> *Heap<T>::getNFI(T t)
{
    TreeNode<T> *nfi;
    TreeNode<T> *c = lastNode->parent;

    if (c == nullptr)
    {
        nfi = new TreeNode<T>(t);
        nfi->parent = root;
        root->left = nfi;
        return nfi;
    }

    TreeNode<T> *Cchild = lastNode;
    while (c->parent != nullptr && lastNode != c->left)
    {
        if (c->parent->left == c)
        {
            Cchild = c;
            c = c->parent;
            break;
        }

        Cchild = c;
        c = c->parent;
    }

    if (Cchild == c->right)
    {
        TreeNode<T> *k = leftmostNode(c);
        k->left = new TreeNode<T>(t);
        k->left->parent = k;
        nfi = k->left;
    }
    else
    {

        if (c->right == nullptr)
        {
            c->right = new TreeNode<T>(t);
            c->right->parent = c;
            nfi = c->right;
        }
        else
        {
            assert(c->left != nullptr);
            TreeNode<T> *k = leftmostNode(c->right);
            k->left = new TreeNode<T>(t);
            k->left->parent = k;
            nfi = k->left;
        }
    }
    return nfi;
}










template <typename T>
TreeNode<T> *Heap<T>::leftmostNode(TreeNode<T> *node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }

    return node;
}






template <typename T>
void Heap<T>::delMax()
{
    if (root == nullptr)
        return;
    if (root->left == nullptr)
    {
        root = nullptr;
        lastNode = nullptr;
        return;
    }
    if (root->right == nullptr)
    {
        root = root->left;
        root->parent = nullptr;
        lastNode = root;
        return;
    }
    if ( root->left->left == nullptr )
    {
        root->object = root->right->object;
        root->right = nullptr;

        if(root->object < root->left->object){
            T temp = root->object;
            root->object = root->left->object;
            root->left->object = temp;
        }
        lastNode = root->left;
        return;
    }

    root->object = lastNode->object;

    if (lastNode->parent->left == lastNode)
    {

        TreeNode<T> *temp = goBack(lastNode);
        lastNode->parent->left = nullptr;
        lastNode = temp;
    }
    else
    {
        lastNode->parent->right = nullptr;
        lastNode = lastNode->parent->left;
    }

    TreeNode<T> *currNode = root;
    TreeNode<T> *kNode = root;
    T temp = root->object;
    while (temp < MaxObj(currNode->left->object, currNode->right->object))
    {
        T maxVal = MaxObj(currNode->left->object, currNode->right->object);
		T a = currNode->left->object;
		T b = maxVal;
        if (!(a < b) && !(b < a))
        {
            kNode = currNode->left;
        }
        else
        {
            kNode = currNode->right;
        }
        currNode->object = maxVal;
        currNode = kNode;
        if (currNode->right == nullptr)
        {
            currNode->object = temp;
            return;
        }
    }
    currNode->object = temp;
    return;
}





template <typename T>
T Heap<T>::MaxObj(T a, T b){
	if(a < b){
		return b;
	}
	else{
		return a;
	}
}







template <typename T>
TreeNode<T> *Heap<T>::goBack(TreeNode<T> *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->parent == nullptr)
    {
        return node;
    }

    TreeNode<T> *pNode = node->parent->parent;
    TreeNode<T> *cNode = node->parent;

    if (pNode == nullptr)
    {
        if (node->parent->left == node)
            return node;
        else
            return node->parent->left;
    }

    while (true)
    {
        if (cNode != pNode->left)
        {
            cNode = pNode->left;
            while (cNode->right != nullptr)
            {
                cNode = cNode->right;
            }
            return cNode;
            break;
        }
        cNode = pNode;
        pNode = pNode->parent;
        if (pNode == nullptr)
        {
            while (cNode->right != nullptr)
            {
                cNode = cNode->right;
            }
            return cNode;
            break;
        }
    }
}





template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

    MyPrint("", false);

    return;
}









template <typename T>
void Heap<T>::MyPrint(const string &prefix, bool isLeft)
{
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the root
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        MyPrint(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        MyPrint(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}





