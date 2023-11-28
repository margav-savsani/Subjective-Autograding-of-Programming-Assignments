#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

int visited[100];
int connected =0;
int cyc =0;
bool cy= false;
int firstparent[100]={-1};

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {

  for (int i =0; i<numNodes; i++){
    if( visited[nodes[i].value]>=1 ){ // to check if all non connected componenets are covered 
      continue;
    }
  BST *b1 = new BST();
  b1->insert(nodes[i].value); // insertion into bst 
  visited[nodes[i].value]=1; // update the visited value of the node
  firstparent[nodes[i].value]=-1; // first parent is actually null of the node from where we staart
  DFS(nodes[i], b1, 0, cy);

  for (int i =0 ; i<numNodes; i++){  
    if (visited[nodes[i].value]==2){ //calculate number of cycles present in the graph
        cyc ++;
    }
  }
  memset(visited,0,100); // reinitilaise all visited values of nodes
  visited[nodes[i].value]=1;
  DFS2(nodes[i],0,b1); 
  b1->printBST("",false); // printing the bst
  connected ++; // keep a count of the connected component 
  b1->~BST();}   // deallocate  memory 

  return;
}

void Graph:: DFS(Node & node, BST *b1 ,int pred, bool & yescycle){
adjacent *tolist =node.adjacencylist;
 while(tolist!= nullptr){
  if (firstparent[tolist->value] ==0) // update the value of the first parent of each node 
    {firstparent[tolist->value]= node.value; // when visited the first time 
 }

  adjacent *back =node.backtrack; 
  bool already= false; // to check if the adjacent node is in the back tracked list of parent node
  while(back!= nullptr){
      if (back->value == tolist->value){
          already = true;
          break; // node found in backtrack list 
        }
       back = back->next; // iterate
  }
  if (visited[tolist->value]!=2 && tolist->value != pred  && tolist->value != firstparent[node.value] && already==false){ 
    
    visited[tolist->value]++;
    DFS(nodes[tolist->value-1],b1, node.value, yescycle);
    adjacent * newneighbour =  new adjacent(tolist->value);
    newneighbour->next=node.backtrack; // after the dfs is complete for the adjacent node 
    node.backtrack =newneighbour; // add it to the backtracked list

  }
  
  tolist = tolist->next;
  }
}

void Graph::DFS2(Node & node ,int pred, BST *b1){
  adjacent *tolist =node.adjacencylist;
 while(tolist!= nullptr){
  if (firstparent[tolist->value] ==0) // update the value of the first parent f each node 
    {firstparent[tolist->value]= node.value; // when visited the first time 
 }

  if (visited[tolist->value]!=2 && tolist->value != pred  && tolist->value != firstparent[node.value] ){ 
    visited[tolist->value]++; // update the value of the visited frequency
    b1->insert(tolist->value); // insert into the binary tree
    DFS2(nodes[tolist->value-1], node.value,b1); // recursive call 
  }
  
  tolist = tolist->next;
  }

}


void Graph::printResults() {
  cout<<"No of components "<<connected<<endl; // printing the relevant information
  int two =0;
  for (int i =0 ; i<numNodes; i++){  
    if (visited[nodes[i].value]==2){
        two ++;
    }
  }
  cout<<"visited once "<<numNodes - two<<endl;
  cout<<"Visited twice "<<two<<endl;
  cout<<"No of nodes in a cycle "<<cyc<<endl;
 return;
}

    
BST::BST(){root = NULL; }
BST::BST(TreeNode *root){this->root = root; }

bool BST::insert( int price) { 
    // Adding the first node
    if(root == NULL){
        root = new TreeNode(price,NULL,NULL,NULL);
        return true;
    }
    // Checking if similar node already exists
    //if(find(JourneyCode,price))return false;
    TreeNode *curr = root;
    while(true){
        curr->sizeOfTree++; // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(price > curr->price){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(price,NULL,NULL,curr);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(price,NULL,NULL,curr);
                break;
                
            }
        }
    }
  //  this->printBST("",false);
    return true;

}

void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;
        string a ="│   ";

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << '('<<root->price<<')' << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? a : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? a : "    "), false);
        root = curr;
    }
}

#endif
