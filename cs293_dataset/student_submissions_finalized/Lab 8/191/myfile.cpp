#include<iostream>
using namespace std;


class TreeNode{
public:
	T object;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;

	TreeNode(int initObj)
	{
		object = initObj;
		left = right = parent = nullptr;
	}
	~TreeNode() { ; }
};

class Heap{
private:
	TreeNode *root;
	TreeNode *next;
public:
	Heap(){root = nullptr;next = nullptr;}
	~Heap(){;}
	
	void insert(int obj){
		
		if(next == nullptr){
			root = new TreeNode(obj);
			next = root;
			return;
		}
		if(next -> left == nullptr){
			next->left = new TreeNode(obj);
			next->left->parent = next;
			next = next->left;
		}else{
			next->right = new TreeNode(obj);
			next->right->parent = next;
			next = next->right;
		}
		auto currNode = next;
		while(currNode->parent != nullptr){
			if(currNode->parent->object < currNode->object){
				auto temp = currNode->object;
				currNode->object = currNode->parent->object;
				currNode->parent->object = temp;
				currNode = currNode->parent;
			}else{
				break;
			}
		}
		currNode = next;

		bool approach_root_right = true;
		while(currNode->parent != nullptr){
			if(currNode->parent->left == currNode){
				currNode = currNode->parent;
				approach_root_right = false;
				break;
			}else{
				currNode = currNode->parent;
			}
		}
		if(currNode ==root && approach_root_right){
			while(currNode->left != nullptr){
				currNode = currNode->left;
			}
			next = currNode;
		}
		else if(currNode->right ==nullptr){
			next = currNode;
		}
		else{
			currNode = currNode->right;
			while(currNode->left!= nullptr){
				currNode = currNode->left;
			}
			next = currNode;
		}
	}
	
	void print(const string& prefix= "", bool isLeft=false){
	
		if( root != nullptr )
		{
		    cout << prefix;

		    cout << (isLeft ? "|--" : "|__" );

		    // print the value of the node
		    cout << root->object<< endl;
		    TreeNode *curr = root;
		    root = root->left;
		    // enter the next tree level - left and right branch
		    print( prefix + (isLeft ? "│   " : "    "), true);
		    root = curr->right;
		    print( prefix + (isLeft ? "│   " : "    "), false);
		    root = curr;
		}

	}
};

int main(){
	Heap h;
	h.insert(8);
	h.insert(4);
	h.insert(5);
	h.insert(9);
	h.insert(10);
	h.insert(2);
	h.insert(11);
	h.insert(13);
	h.insert(14);
	h.insert(15);
	h.insert(21);
	h.insert(23);
	h.insert(24);
	h.insert(25);
	h.insert(26);
	h.insert(27);
	h.print();
}
