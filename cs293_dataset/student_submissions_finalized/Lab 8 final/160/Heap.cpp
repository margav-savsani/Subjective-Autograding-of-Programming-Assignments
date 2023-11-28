#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {

	if(root==nullptr){
		root=new TreeNode<T>(obj);
		last=root;
		return;
	}
	else{
		if(last->parent==nullptr) {
			root->left=new TreeNode<T>(obj);
			root->left->parent=root;
			last=last->left;
		}
		else{
			if(last->parent->left==last){
				last->parent->right=new TreeNode<T>(obj);
				last->parent->right->parent=last->parent;
				last=last->parent->right;
			}
			else if(last->parent->right==last){
				TreeNode<T> *c=last;

				while(c->parent!=NULL){
					if(c->parent->left!=c) break;
					c=c->parent;
				}
				if(c->parent!=nullptr){
					c=c->parent;
					c->right;
					while(c->left!=nullptr){
						c=c->left;
					}
					c->left=new TreeNode<T>(obj);
					c->left->parent=c;
					last=c->left;
				}
				else{
					while(c->left!=nullptr){
						c=c->left;
					}
					c->left=new TreeNode<T>(obj);
					c->left->parent=c;
					last=c->left;				
				}
			}
		}
	}
	x++;
	heapify(root);

	return;
}
template<typename T>
void heapify(TreeNode<T> *node){
	if(node==nullptr) return;
	if(node->left==nullptr) return;
	else if(node->right!=nullptr){
		if(node->object<node->left->object&&node->right->object<node->left->object){
			T temp=node->left->object;
			node->left->object=node->object;
			node->object=temp;
		}
		else if(node->object<node->right->object&&node->left->object<node->right->object){
			T temp=node->right->object;
			node->right->object=node->object;
			node->object=temp;
		}
		else if(node->object<node->right->object){
			T temp=node->right->object;
			node->right->object=node->object;
			node->object=temp;
		}
	}
	else{
		if(node->object<node->left->object){
			T temp=node->left->object;
			node->left->object=node->object;
			node->object=temp;
		}		
	}
	heapify(node->left);
	heapify(node->right);
	if(node->left==nullptr) return;
	else if(node->right!=nullptr){
		if(node->object<node->left->object&&node->right->object<node->left->object){
			T temp=node->left->object;
			node->left->object=node->object;
			node->object=temp;
		}
		else if(node->object<node->right->object&&node->left->object<node->right->object){
			T temp=node->right->object;
			node->right->object=node->object;
			node->object=temp;
		}
		else if(node->object<node->right->object){
			T temp=node->right->object;
			node->right->object=node->object;
			node->object=temp;
		}
	}
	else{
		if(node->object<node->left->object){
			T temp=node->left->object;
			node->left->object=node->object;
			node->object=temp;
		}		
	}	
}

template<typename T>
void Heap<T>::delMax() {

	// insert your code here
	if(root==nullptr) return;
	root->object=last->object;
	if(last->parent==nullptr) {root=nullptr;return;}
	else if(last->parent->right==last){
		last->parent->right=nullptr;
	}
	else{
		last->parent->left=nullptr;
	}

	/*else if(last->parent->right==last) {
		last->parent->right=nullptr;
		last=last->parent->left;
	}
	else if(last->parent->left==last){
		TreeNode<T> *c=last;
		while(c->parent!=NULL){
			if(c->parent->right!=c) break;
			c=c->parent;
		}
		if(c->parent!=nullptr){
			c=c->parent;
			c->left;
			while(c->right!=nullptr){
				c=c->right;
			}
			last->parent->left=nullptr;
			last=c;
		}
		else{
			while(c->right!=nullptr){
				c=c->right;
			}
			last->parent->left=nullptr;
			last=c;			
		}
	}*/
	getLastNodeAndItsParent(root,height(root),NULL);
	x--;
	heapify(root);
	return;
}
template<typename T>
int height(TreeNode<T> *root)
{
    if (root == NULL)
        return 0;
 
    int lheight = height(root->left) + 1;
    int rheight = height(root->right) + 1;
 
    return max(lheight, rheight);
}
template<typename T>
void Heap<T>::getLastNodeAndItsParent(TreeNode<T> *root, int level, TreeNode<T> *parent)
{
    if (root == NULL)
        return;
 
    // The last processed node in
    // Level Order Traversal has to
    // be the node to be deleted.
    // This will store the last
    // processed node and its parent.
    if (level == 1)
    {
        last = root;
    }
    getLastNodeAndItsParent(root->left, level - 1, root);
    getLastNodeAndItsParent(root->right, level - 1, root);
}

template<typename T>
void Heap<T>::printHeap(const string prefix,bool isLeft) {

	// insert your code here
	if( root != nullptr )
	{
		cout << prefix;

		cout << (isLeft ? "|--" : "|__" );

		// print the value of the node
		cout << '('<< root->object<<')' << endl;
		TreeNode<T> *curr = root;
		root = root->left;
		// enter the next tree level - left and right branch
		printHeap( prefix + (isLeft ? "│   " : "    "), true);
		root = curr->right;
		printHeap( prefix + (isLeft ? "│   " : "    "), false);
		root = curr;
	}	
	return;
}
