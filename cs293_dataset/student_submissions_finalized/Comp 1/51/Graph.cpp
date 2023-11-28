#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

void Graph::modifiedDFS() {
  //checking size of adjacency if 0 prints no connections
  if(nodes[node1].adjacency.size()==0){
    cout<<"no connections"<<endl;
  }
  //intializing bst for base case
  if(recursion ==0){
    tree = new BST;
    tree->root = new TreeNode(node1+1);
  }
  //checking for cycle after every insertion
  int cyc_sz =cycle.size();
  if(!cycle_found){ 
  for(int i=0;i<cyc_sz;i++){
    if(cycle[i]==node1){
      cycle_found=true;
      cycle_length = cyc_sz-i;
  }}
    }
    
  cycle.push_back(node1);
  //iterating over adjacency to find nodes
  for(int i=0;i<nodes[node1].adjacency.size();i++){
    
  //checking if visited twice and notvisting the predcessor node if size>1
  if(visit_array[nodes[node1].adjacency[i]-1] != 2  && (nodes[node1].adjacency[i]!=node3+1 || nodes[node1].adjacency.size()==1)){
  visit_array[nodes[node1].adjacency[i]-1]++;
  
  tree->insert(nodes[node1].adjacency[i]);
  node3=node1;//using node3 as predecessor
  node1 = nodes[node1].adjacency[i]-1;
  //incresing recursion level to check use recursion level at the end to print
  recursion++;
  modifiedDFS();
  recursion--;
  
  }
  //reaching down to base to print the final bst 
  //printing cycle length 
  //
  if(recursion ==0){
  tree->printBST("",false);
    cout<<"NO OF CONNECTED COMPONENTS :"<<nodes[node2].adjacency.size()<<endl;
    int once =0;
    int twice =0;
    for(int i=0;i<numNodes;i++){
      if(visit_array[i]==1){
        once++;
      }
      if(visit_array[i]==2){
        twice++;
      }
    }
    //printing no of nodes visited once twice
    //prints cycle length 
    //updating variables like cycle_len=0 cycle to size 0 
    cout<<"NO OF NODES VISITED ONCE:"<<once<<endl;
    cout<<"NO OF NODES VISITED TWICE:"<<twice<<endl;
    cout<<"NO OF NODES IN CYCLE:"<<cycle_length<<endl;
    node1 = node2;
    tree = new BST;
    node3 = -3;
    tree->root = new TreeNode(node2+1);
    cycle.resize(0);
    cycle_found =false;
    set_arr();
  
  }


  }

}
//implementes this in recursion =0
void Graph::printResults() {
  
  }
  

//prints the bsttree
void BST::printBST(const string &prefix, bool isLeft){
  if (root != nullptr)
	{
		cout << prefix;

		cout << (isLeft ? "|--" : "|__");

		// print the value of the node
		cout << root->val << endl;
		TreeNode *curr = root;
		root = root->left;
		// enter the next tree level - left and right branch
		printBST(prefix + (isLeft ? "│   " : "    "), true);
		root = curr->right;
		printBST(prefix + (isLeft ? "│   " : "    "), false);
		root = curr;
	}
}

//inserts a value in bsttree
void BST::insert(int a){
 TreeNode* curr = root;
 if(root!=nullptr){ 
 if(a < root->val){
  
  if(root->left == nullptr){
    root->left = new TreeNode(a);
  }
  else{
    root = root->left;
    insert(a);
  }
 }
 else {
 if(root->right== nullptr){
    root->right = new TreeNode(a);
  }
  else{
    root = root->right;
    insert(a);
  }
 }
 }
 root = curr;
}
#endif
