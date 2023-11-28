#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif


bool Graph::updateInCycle(int ind, int till){
  int storeind = ind;
  while(ind != till){
    ind = firstPredecessor[ind];
    if(ind == -1){
      return false;
    }
   // cout << " << " << ind; 
  }
  ind = storeind;
  while(ind != till){
    incycle[ind] = true;
    ind = firstPredecessor[ind];
   // cout << " << " << ind; 
  }
  return true;
}
void Graph::seeCommonANcestorAndUpdate(int to, int from){
  incycle[from] = true;
  incycle[to] = true;
  int ans=-1;
  int ancto = to;
  while(ancto!=-1){
    int ancfrom = from;
    bool found = false;
    while(ancfrom!=-1){
      if(ancto == ancfrom){
        ans = ancto;
        found = true;
        break;
      }
      ancfrom = firstPredecessor[ancfrom];
    }
    if(found)
      break;
    ancto = firstPredecessor[ancto];
  }

  incycle[ans] = true;
  while(to != ans){
    incycle[to] = true;
    to = firstPredecessor[to];
  }
  while(from != ans){
    incycle[from] = true;
    from = firstPredecessor[from];
  }
  
}

void Graph::ThisDFS(int ind, int from){
  if(visits[ind] == 2){
    return;
  }
  trees->insert(ind);
  visits[ind]++;
  LinkedList* currAdj = nodes[ind].adjacentList;
  while(currAdj != NULL){
    int adjInd = currAdj->store->value-1;
    if(adjInd == from){
      currAdj = currAdj->next;
      continue;
    }
    if(adjInd == firstPredecessor[ind]){
      currAdj = currAdj->next;
      continue;
    }
    if(visits[adjInd] && visits[ind]==1){
      incycle[adjInd] = true;
      // cout << "from " << ind << ", to" << adjInd << endl;
      // for(int i=0; i<numNodes; i++){
      //   cout << i << ":"<< firstPredecessor[i] << ";; ";
      // // }
      // cout << endl;
      if(!updateInCycle(ind, adjInd)){
        seeCommonANcestorAndUpdate(ind, adjInd);
      }
      ThisDFS(adjInd, ind);
    }
    else if(visits[adjInd] == 0){
      firstPredecessor[adjInd] = ind;
      // cout << adjInd << " aupdated " << ind << endl;
      ThisDFS(adjInd, ind);
    }
    else{
      ThisDFS(adjInd, ind);
    }
    currAdj = currAdj->next;
  }
}

bool BST::insert(int val){
  if(root == NULL){
    root = new BSTNode(val);
    // cout << root->value << endl;;
    return true;
  }
  BSTNode* curr = root;
  BSTNode* currpar = nullptr;
  bool right = false;
  while(curr != NULL){
    if(curr->value <= val){
      currpar = curr;
      curr = curr->left;
      right = false;
    }
    else{
      currpar = curr;
      curr = curr->right;
      right = true;
    }
  }
  // cout << currpar->value << endl;
  if(right){
    currpar->right = new BSTNode(val);
    currpar->right->parent = currpar;
  }
  else{
    currpar->left = new BSTNode(val);
    currpar->left->parent = currpar;
  }
  return true;
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  // index to start DFS
  while(UnvisitedNode() != -1){
    nConnectedComponents++;
    if(trees == nullptr)
      trees=new BST();
    ThisDFS(UnvisitedNode(), -1);
      trees->nextTree = new BST();
      trees->nextTree->prevTree = trees;
      trees = trees->nextTree;
  }
}

int Graph::UnvisitedNode(){
  for(int i=0; i<numNodes; i++){
    if(visits[i] == 0)
      return i;
  }
  return -1;
}



void Graph::printResults() {
  
  cout << "No. of connected components: " << nConnectedComponents << endl;
  int sum=0;
  int nincyc = 0;
  for(int i=0; i<numNodes; i++){
    sum += visits[i];
    nincyc += incycle[i];
  }
  cout << "No. of nodes visited once: " << 2*numNodes - sum << '\n';
  cout << "No. of nodes visited twice: " << sum - numNodes << '\n';
  cout << "No. of  nodes that are present in a cycle:" << nincyc << '\n';
  BST* curr = trees;
  while(curr->prevTree != nullptr){
    curr = curr->prevTree;

  }
  while(curr!=nullptr){
    // cout << "***************" << endl;
    // const string a = "";
    // curr->printBST(a, false);
    curr = curr->nextTree;
  }
  return;
}


void BST::printBST(const string& prefix, bool isLeft=false)
{
  BSTNode* curr = root;
  // while(curr!=nullptr){
  //   cout << curr->value << endl;
  //   curr = curr->left;
  // }
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        BSTNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
#endif
