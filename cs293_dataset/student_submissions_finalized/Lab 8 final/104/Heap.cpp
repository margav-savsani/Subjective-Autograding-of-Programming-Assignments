#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{	
	// Creating new node
	TreeNode<T> *ptr = new TreeNode<T>(obj);

	// new node will be the last node
	last_node = ptr;

	// for later use
	TreeNode<T> *new_node = ptr;

	// for first insertion
	if (root == nullptr)
	{
		root = ptr;
		last_node = ptr;
		insert_pointer = ptr;
		return;
	}

	// inserting the new node

	// to the left
	if (insert_pointer->left == nullptr)
	{
		insert_pointer->left = ptr;
		ptr->parent = insert_pointer;
	}
	// to the right
	else
	{
		insert_pointer->right = ptr;
		ptr->parent = insert_pointer;
	}

	// pointer to parent of newly inserted node
	TreeNode<T> *papa_ptr = insert_pointer;

	// when we insert a node to get the next insertion point we go up and then right and then down
	// to get the point at which we turn right
	while (papa_ptr != nullptr)
	{	
		// the point at which we turn right
		if (papa_ptr->left == ptr)
		{
			break;
		}
		// else we go up
		else
		{
			papa_ptr = papa_ptr->parent;
			ptr = ptr->parent;
		}
	}

	// there is no point to turn right
	// this means the level is filled
	// and we go left-left-left.....
	if (papa_ptr == nullptr)
	{
		papa_ptr = root;
		while (papa_ptr->left != nullptr)
		{
			papa_ptr = papa_ptr->left;
		}
	}
	// else we go down and directed towards left
	// till we reach a node which have null children
	else
	{
		while (true)
		{
			if (papa_ptr->left == nullptr || papa_ptr->right == nullptr)
			{
				break;
			}

			if (papa_ptr->left != nullptr && papa_ptr->left != ptr)
			{
				papa_ptr = papa_ptr->left;
			}
			else
			{
				papa_ptr = papa_ptr->right;
			}
		}
	}

	// setting the new insert_pointer
	insert_pointer = papa_ptr;

	// shifting up the new inserted node
	TreeNode<T> *new_node_parent = new_node->parent;

	while(new_node_parent != nullptr){
		if(new_node_parent->object < new_node->object){
			T temp = new_node_parent->object;
			new_node_parent->object = new_node->object;
			new_node->object = temp;

			new_node = new_node->parent;
			new_node_parent = new_node_parent->parent;
		}
		else{
			break;
		}
	}

	return;
}

template <typename T>
void Heap<T>::delMax()
{	

	// if tree is empty
	if (root == nullptr)
	{
		return;
	}
	// if only 1 node is present
	else if (last_node == root)
	{
		delete last_node;
		last_node = nullptr;
		insert_pointer = nullptr;
		root = nullptr;
		return;
	}

	// putting last node value at the root
	root->object = last_node->object;

	// new insertion pointer
	insert_pointer = last_node->parent;

	// parent of new inserted node
	TreeNode<T> *papa_ptr = insert_pointer;

	// last node pointer
	TreeNode<T> *ptr = last_node;

	// getting the new last node
	// basically we go up and then left and then down
	while (papa_ptr != nullptr)
	{	
		// point at which we turn left
		if (papa_ptr->right == ptr)
		{
			break;
		}
		// else we go up
		else
		{
			papa_ptr = papa_ptr->parent;
			ptr = ptr->parent;
		}
	}

	// if it's nullptr then whole level has become empty
	// then we traverse towards right
	if (papa_ptr == nullptr)
	{	
		papa_ptr = root;
		while (papa_ptr->right != nullptr)
		{
			papa_ptr = papa_ptr->right;
		}
	}
	// in this case we go left
	// then go mostly towards right
	else
	{	
		while (true)
		{
			if (papa_ptr->left == nullptr && papa_ptr->right == nullptr)
			{
				break;
			}

			if (papa_ptr->right != nullptr && papa_ptr->right != ptr)
			{
				papa_ptr = papa_ptr->right;
			}
			else
			{
				papa_ptr = papa_ptr->left;
			}
		}
	}

	// making parent's child pointer null
	if (insert_pointer->left == last_node)
	{
		insert_pointer->left = nullptr;
	}
	else
	{
		insert_pointer->right = nullptr;
	}


	delete last_node;
	last_node = papa_ptr;

	ptr = root;

	// doing heapify
	while (true)
	{
		if (ptr->left != nullptr && ptr->right != nullptr)
		{
			if (ptr->right->object < ptr->left->object)
			{
				if (ptr->left->object < ptr->object)
				{
					break;
				}

				T temp = ptr->left->object;
				ptr->left->object = ptr->object;
				ptr->object = temp;
				ptr = ptr->left;
				
				continue;
			}
			else
			{
				if (ptr->right->object < ptr->object)
				{
					break;
				}

				T temp = ptr->right->object;
				ptr->right->object = ptr->object;
				ptr->object = temp;
				ptr = ptr->right;
				continue;
			}
		}
		else if (ptr->left != nullptr && ptr->right == nullptr)
		{
			if (ptr->left->object < ptr->object)
			{
				break;
			}

			T temp = ptr->left->object;
			ptr->left->object = ptr->object;
			ptr->object = temp;
			ptr = ptr->left;
			continue;
		}
		else if (ptr->left == nullptr && ptr->right != nullptr)
		{
			if (ptr->right->object < ptr->object)
			{
				break;
			}

			T temp = ptr->right->object;
			ptr->right->object = ptr->object;
			ptr->object = temp;
			ptr = ptr->right;
			continue;
		}
		else{
			break;
		}
	}
	return;
}

template <typename T> void printBST(TreeNode<T> *root ,const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        // enter the next tree level - left and right branch
        printBST(root->left ,prefix + (isLeft ? "│   " : "    "), true);
        printBST(root->right, prefix + (isLeft ? "│   " : "    "), false);
    }
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

	// insert your code here
	printBST(node, "");

	return;
}

template <typename T>
void destructorDelete(TreeNode<T> *node){

	if(node == nullptr){
		return;
	}

	if(node->left != nullptr){
		destructorDelete(node->left);
	}

	if(node->right != nullptr){
		destructorDelete(node->right);
	}

	delete node;
}

template <typename T> 
Heap<T>::~Heap(){
	destructorDelete(root);
}

