#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
// #include<iostream>
// using namespace std;
template<typename T>
void Heap<T>::insert(T obj)
{
	TreeNode<T>* NewNode= new TreeNode<T>(obj);
	if(root==NULL)
	{
		root=NewNode;
		return;
	}
	TreeNode<T>* parentNode= nextleaf(root);
	if(parentNode->left==NULL)
	{
		parentNode->left=NewNode;
		NewNode->parent=parentNode;
	}
	else if(parentNode->right==NULL)
	{
		parentNode->right=NewNode;
		NewNode->parent=parentNode;
	}
	else
	{
		cout<<"Error Occured"<<endl;
	}
	heapify_for_insert(NewNode);
	return;
}

template<typename T>
T Heap<T>::delMax()
{
	T obj;
	if(root==NULL)
	{
		return obj;
	}
	if(height(root)==1)
	{
		obj=root->object;
		delete root;
		root=NULL;
		return obj;
	}
	TreeNode<T>* iterator=leaf(root);
	if(iterator->parent->left==iterator)
	{
		root->object=iterator->object;
		iterator->parent->left=NULL;
		obj=iterator->object;
		delete iterator;
		heapify(root);
	}
	else if(iterator->parent->right==iterator)
	{
		root->object=iterator->object;
		iterator->parent->right=NULL;
		obj=iterator->object;
		delete iterator;
		heapify(root);
	}
	return obj;
}

template<typename T>
void Heap<T>::Interchange(TreeNode<T>* node1,TreeNode<T>* node2)
{
	if(node1==NULL||node2==NULL)
	{
		return;
	}
	else
	{
		TreeNode<T>* node3=new TreeNode<T>(node1->object);
		node1->object=node2->object;
		node2->object=node3->object;
		return;
	}
}

template<typename T>
void Heap<T>::heapify(TreeNode<T>* node)
{
	//verify node and node->right and node->left 
	if(node==NULL)
	{
		return;
	}
	if(node->left==NULL && node->right==NULL)
	{
		return;
	}
	if(node->right==NULL)
	{
		if(node->object<node->left->object)
		{
			Interchange(node,node->left);
		}
		return;
	}
	if(node->object < node->left->object && !(node->object < node->right->object))
	{
		Interchange(node->left,node);
		heapify(node->left);
		return;
	}
	if(node->object < node->right->object && !(node->object < node->left->object))
	{
		Interchange(node->right,node);
		heapify(node->right);
		return;
	}
	if(node->object < node->left->object && node->object < node->right->object)
	{
		if(!(node->left->object < node->right->object))
		{
			Interchange(node->left,node);
			heapify(node->left);
		}
		else if(!(node->right->object < node->left->object))
		{
			Interchange(node->right,node);
			heapify(node->right);
		}
	}
}

template<typename T>
int Heap<T>::height(TreeNode<T> *node)
{
	if(node==NULL)
	{
		return 0;
	}
	return 1+height(node->left);
}

template<typename T>
bool Heap<T>::isTreeFull(TreeNode<T> * node)
{
	if(node==NULL)
	{
		return 0;
	}
	TreeNode<T>* iterator=node;
	int i=0;
	while(iterator!=NULL)
	{
		iterator=iterator->left;
		i++;
	}
	iterator=node;
	while(iterator!=NULL)
	{
		iterator=iterator->right;
		i--;
	}
	return (i==0);
}

template<typename T>
TreeNode<T>* Heap<T>::leaf(TreeNode<T> *node)
{
	if(node==NULL)
	{
		return NULL;
	}
	if(node->left==NULL && node->right==NULL)
	{
		return node;
	}
	if(height(node->left)==height(node->right))
	{
		return leaf(node->right);
	}
	if(height(node->left)==1+height(node->right))
	{
		return leaf(node->left);
	}
	return NULL;
}

template<typename T>
TreeNode<T>* Heap<T>::nextleaf(TreeNode<T>* node)
{
	if(node==NULL)
	{
		return NULL;
	}
	if(node->left==NULL||node->right==NULL)
	{
		return node;
	}
	if(isTreeFull(node->left)&&isTreeFull(node->right))
	{
		if(height(node->left)==height(node->right))
		{
			return nextleaf(node->left);
		}
		else if(height(node->left)==1+height(node->right))
		{
			return nextleaf(node->right);
		}
	}
	if(isTreeFull(node->left)&& !isTreeFull(node->right))
	{
		return nextleaf(node->right);
	}
	if(!isTreeFull(node->left))
	{
		return nextleaf(node->left);
	}
	cout <<"something is fishy"<<endl;
	return NULL;
}

template<typename T>
void Heap<T>::heapify_for_insert(TreeNode<T>* node)
{
	if(node==NULL||node->parent==NULL)
	{
		return;
	}
	while(node->parent!=NULL)
	{
		heapify(node->parent);
		node=node->parent;
	}
	return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
	TreeNode<T>* dummy=root;
	root=node;
	print("",false);
	root=dummy;
	return;
}

template<typename T>
void Heap<T>::print(string prefix, bool isLeft)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T>* curr=root;
        root = root->left;
        // enter the next tree level - left and right branch
        print ( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        print ( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
	return;
}

// int main()
// {
// 	cout<<"starting heap for int"<<endl;
// 	Heap<int> A;
// 	while(true)
// 	{
// 		cout << "1 for Insert\n2 for deleting maximum\n3 for printing heap\n";
// 		int a;
// 		cin >> a;
// 		if(a==1)
// 		{
// 			int b;
// 			cin >> b; 
// 			A.insert(b);
// 			continue;
// 		}
// 		if(a==2)
// 		{
// 			A.delMax();
// 			continue;
// 		}
// 		if(a==3)
// 		{
// 			A.printHeap(A.root);
// 			continue;
// 		}
// 		if(a==4)
// 		{
// 			break;
// 		}
// 	}
// }