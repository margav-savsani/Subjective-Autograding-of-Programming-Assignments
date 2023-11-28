#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

BST::BST(){ // default constructor
    this->root = NULL;
}
BST::BST(TreeNode *root) { // constructor with a root given
    this->root = root;
}

bool BST::insert(int price) {  // inserting the node into the bst tree
        TreeNode *x,*y,*z;
        x = root;
        y = NULL;
        z = new TreeNode(price);
        while(x != NULL) { // if x != nullptr
            y = x;
            if(z->price < x->price) { // comparing nodes to insert
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->parent = y; // traversing down the tree
        if(y == NULL) { // if y == nullptr
            root = z;
            return true;
        }
        else if(z->price < y->price) { // comparing nodes to insert
                 y->left = z;
                 return true; 
        }
        else {
                y->right = z;
                return true;
        }
        return false; // can't insert into the tree
}

void BST::printBST(const string& prefix, bool isLeft=false) {
    if( root != nullptr )
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->price<< endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}


bool Graph::st_find(int n) { // finding a node in the stack

  list<Node> *tmp = stack; // tmp pointer 
  bool is_present = false; // initialising the bool variable
  while(tmp!=nullptr) { // if the stack is not empty
    if((tmp->object).value == n){
      is_present = true; // node is present in the stack
      break;
    }
    tmp = tmp->prev; // moving from back to the first
  }
  if(is_present==true) { // if the node is present in the stack
    if(tmp!=nullptr){
      list<Node> *n = tmp->prev; // removing the cycle
      stack = n;
    }
    // stack = tmp->prev;
  }
  while(tmp!=nullptr){ // assigning the in_cycle value of nodes in the cycle as true
    nodes[(tmp->object).value-1].in_cycle = true;
    tmp = tmp->next;
  }
  return is_present; 
}

// Add code as appropriate for your implementation
void Graph::my_DFS(Node n,Node parent){

  visited[n.value-1]+=1; // incrementing the visited count
  my_BST.insert(n.value); // inserting into the bst tree

  list<Node> *adj = n.adj_head;

  while(adj!=nullptr) { // if adj is not empty

    int val = adj->object.value;
    if(val != parent.value){
      if(visited[val-1]!=0 ) { // if the node is already visited
        if(stack!=nullptr){
            if(stack->prev !=nullptr){
              if((stack->prev->object).value != val) st_find(val); // checking for the cycle
              // cycle existance is co-related with the existance of back-edges from desc to ancestors
            }
        }    
      }

      if(visited[val-1] <2)  { // dfs is called only when it is visited atmost one time
         if(stack == nullptr){
          stack = new list<Node> (nodes[val-1]); // adding new node to empty stack
         }
         if(stack!=nullptr){
          stack->next = new list<Node> (nodes[val-1]); // adding the node into the stack
          stack->next->prev = stack;
          stack = stack->next; // updating the stack pointer
         }
          my_DFS(nodes[val-1],n); // calling the dfs on unvisited/one time visited child node
          if(stack!=nullptr){ // removing the last node while back-tracing
            stack = stack->prev;
            if(stack!=nullptr) {
              stack->next = nullptr;
            }
          }
      }
    }
    adj = adj->next; // iterating over the adj
  }
  return;
}

void Graph::modifiedDFS() {    
  for(int i=0;i<numNodes;i++){ // iterating all the nodes
    if(visited[i]==0){ // calling the dfs only if it is unvisited
      stack = new list<Node> (nodes[i]);
      my_DFS(nodes[i],Node(0));
      stack = nullptr; // clearing the stack after the dfs on one connnected component
      cnt++; // increasing the number of connected components
      if(all==nullptr){
        all = new list<BST> (my_BST);
      }
      else{ // pushing the trees into the bst linled list
        all->next = new list<BST> (my_BST);
        all->next->prev = all;
        all = all->next;
      }
      my_BST = BST(); // clearing the bst tree for future use
    }
  }
  return;
}

void Graph::printResults() {
  int once = 0,twice = 0, n_cycle=0;
  for(int i=0;i<numNodes;i++){
    if(nodes[i].in_cycle == true) n_cycle++; // no of nodes in the cycle
    if(visited[i]==1) once++; // once visited
    else if(visited[i]==2) twice++; // twice visited
    else cout <<"error in the algo!!"<<endl; // maximum not possible
  }
  cout << "Number of nodes in cycle = "<<n_cycle<<endl;
  cout << "Number of connected components in the given graph = "<<cnt<<endl;
  cout << "Number of nodes visited once = "<<once<<endl;
  cout << "Number of nodes visied twice = "<<twice<<endl;
  while(all!=nullptr){
    cout << "===================="<<endl;
    (all->object).printBST("");
    
    all = all->prev;
  }
  
  return;
}

#endif
