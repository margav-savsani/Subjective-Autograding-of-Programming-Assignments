#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> *n,*currnode=root,*parentof;
  n=new TreeNode<T>(obj);
  if(noofnodes==0){root=n;noofnodes++;return;}
   /* an innovative method to find the last element if the heap from number of nodes stored */
  int residue=noofnodes-pow(2,getheightoftree()-1);
  bool binary[getheightoftree()];
  
  for (int i = 0; i < getheightoftree()-1; i++)
  {
    
    binary[i]=(residue%2==1);
    residue=(residue-binary[i])/2;
  }
  
  for(int i=getheightoftree()-1;i>=0;i--){
    if(binary[i]){parentof=currnode;currnode=currnode->right;}
    else {parentof=currnode;currnode=currnode->left;}
  }
  n->parent=parentof;
  if(binary[0]){parentof->right=n;}
  else parentof->left=n;
  noofnodes++;
  
  while(parentof!=root){
    if(n->object>parentof->object){
      swap(n->object,parentof->object);
      n=n->parent;
      parentof=parentof->parent;
    }
    else break;
  }
  if(parentof=root){
    if(n->object>root->object){
      swap(n->object,root->object);
    }
  }
  return;
}

template<typename T> T Heap<T>::delMax() {
  if(root==nullptr){return -1;}//returs -1 if heap is empty
  if(root->left==nullptr&&root->right==nullptr){T b=root->object;root=nullptr;noofnodes--;return b;}
  TreeNode<T> *currnode=root,*a;
  T b=root->object;
  /* an innovative method to find the last element if the heap from number of nodes stored */
  int residue=noofnodes-pow(2,getheightoftree()-1);
  bool binary[getheightoftree()];
  for (int i = 0; i < getheightoftree()-1; i++)
  {
    binary[i]=(residue%2==1);
    residue=(residue-binary[i])/2;
  }
  for(int i=getheightoftree()-1;i>=0;i--){
    if(binary[i]){ currnode=currnode->right;}
    else {currnode=currnode->left;}
  }
  swap(currnode->object,root->object);
  currnode=nullptr;
  noofnodes--;
  a=root;
  while(a!=nullptr){
    if(a->object<a->left->object && a->object<a->right->object){
      if(a->left->object<=a->right->object){
        swap(a->object,a->right->object);
        a=a->right;
      }
      else {
        swap(a->object,a->left->object);
        a=a->left;
      }
    }
    if(a->object>a->left->object && a->object<a->right->object){
      swap(a->object,a->right->object);
        a=a->right;
    }
    if(a->object<a->left->object && a->object>a->right->object){
      swap(a->object,a->left->object);
        a=a->left;
    }
  }

  return b;
}
template <typename T>
void printHeap(TreeNode<T> *node){
bool isLeft = false;
  if (node != nullptr)
  {
    cout << (isLeft ? "|--" : "|__");
    // print the value of the node
    cout << node->object << endl;
    TreeNode<T> *curr = node;
    node = node->left;
    isLeft = true;
    // enter the next tree level - left and right branch
    printHeap(node);
    node = curr->right;
    isLeft = false;
    printHeap(node);
    
  }
  return;
}
int main()
{
	cout<<"starting heap for int"<<endl;
	Heap<int> A;
	while(true)
	{
		cout << "1 for Insert\n2 for deleting maximum\n3 for printing heap\n";
		int a;
		cin >> a;
		if(a==1)
		{
			int b;
			cin >> b; 
			A.insert(b);
			continue;
		}
		if(a==2)
		{
			A.delMax();
			continue;
		}
		if(a==3)
		{
			//A.printHeap(A.getroot(),true);
			continue;
		}
		if(a==4)
		{
			break;
		}
	}
}
