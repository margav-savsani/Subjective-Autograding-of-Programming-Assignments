#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Function to insert a node into tree
void BST::insert(int nV){
  Treenode *currnode = root, *parentOfCurrNode = nullptr;
  while(currnode != nullptr){
    if(currnode->nodeValue <= nV){
      parentOfCurrNode = currnode;
      currnode = currnode->right;
    }else{
      parentOfCurrNode = currnode;
      currnode = currnode->left;
    }
  }
  Treenode *z = new Treenode(nV);
  z->parent=parentOfCurrNode;
  if(parentOfCurrNode != nullptr){
    if(parentOfCurrNode->nodeValue <= nV)parentOfCurrNode->right=z;
    else parentOfCurrNode->left =z;
  }
  if(root==nullptr)root=z;
}

// Function to print the BST
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->nodeValue << endl;
        Treenode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

// Checking whether an edge is present already in the graph
bool Graph::edgePresent(int n1, int n2){
  listOfObjects<Node> *poin = nodes[n1].adj;
  while(poin != nullptr){
    if(poin->object.value == nodes[n2].value)return true;
    poin = poin->next;
  }
  return false;
}

// Inserting a new undirected edge in the graph
void Graph::addEdge(int n1, int n2){
  if(nodes[n1].adj == nullptr){
    nodes[n1].adj = new listOfObjects<Node>(nodes[n2]);
    nodes[n1].tail = nodes[n1].adj;
  }else{
    nodes[n1].tail->next = new listOfObjects<Node>(nodes[n2]);
    nodes[n1].tail = nodes[n1].tail->next;
  }

  if(nodes[n2].adj == nullptr){
    nodes[n2].adj = new listOfObjects<Node>(nodes[n1]);
    nodes[n2].tail = nodes[n2].adj;
  }else{
    nodes[n2].tail->next = new listOfObjects<Node>(nodes[n1]);
    nodes[n2].tail = nodes[n2].tail->next;
  }
  return;
}

// Removing a directed ege in the graph
void Graph::removeEdge(int n1, int n2){
  if(!edgePresent(n1,n2)){
    return;
  }
  if(nodes[n1].adj->object.value == nodes[n2].value){
    nodes[n1].adj = nodes[n1].adj->next;
    return;
  }
  listOfObjects<Node> *poin = nodes[n1].adj;
  while(poin->next->object.value != nodes[n2].value){
    poin = poin->next;
  }
  poin->next = poin->next->next;
  return;
}

// A dfs function to call it recursively
void Graph::dfs(int n, BST *btree,int b){
  if(b==0){
  cntvisit[n] = true;
  nodes[n].cnt = coun++;
  if(nodes[n].adj == nullptr)return;
  listOfObjects<Node> *poin = nodes[n].adj;
  while(poin != nullptr){
    if(cntvisit[poin->object.idx]==true && nodes[poin->object.idx].cnt < nodes[n].cnt && poin->object.idx != nodes[n].pindx ){
      int curridx = n;
      int finalidx = poin->object.idx;
      nodes[curridx].inCycle = true;
      nodes[finalidx].inCycle =true;
      while(curridx != finalidx){
        nodes[curridx].inCycle = true;
        curridx = nodes[curridx].pindx;
      }
    }
    if(cntvisit[poin->object.idx]==false){
      nodes[poin->object.idx].pindx = n;
      dfs(poin->object.idx,btree,0);
    }
    poin = poin->next;
  }
  coun--;
  }else{
    visited[n]++;
    btree->insert(nodes[n].value);
    if(nodes[n].adj == nullptr)return;
    listOfObjects<Node> *poin = nodes[n].adj;
    while(poin != nullptr){
      if(visited[poin->object.idx] <2 && edgePresent(n,poin->object.idx)){
        //cout << "from "<<nodes[n].value << " to "<< nodes[poin->object.idx].value<<endl;
        nodes[poin->object.idx].pindx = n;
        removeEdge(poin->object.idx,n);
        dfs(poin->object.idx,btree,1);
        removeEdge(n,poin->object.idx);
      }
      poin = poin->next;
    }
  }
  return;
}

void Graph::modifiedDFS() {
  // Funtion to apply dfs for one node each connected component
  for(int i = 0; i < numNodes; i++){
    if(visited[i]==0){
      BST *btree= new BST;
      coun =0;
      dfs(i,btree,0);
      dfs(i,btree,1);
      if(bsl == nullptr){
        bsl = new listOfObjects<BST *>(btree);
      }else{
        listOfObjects<BST *> *pointr = bsl;
        while(pointr->next !=nullptr){
          pointr = pointr->next;
        }
        pointr->next = new listOfObjects<BST *>(btree);
      }
    }
  }
  return;
}


// Printing the results appropriately
void Graph::printResults() {
  int con = 0;
  int sin = 0;
  int dou = 0;
  int cyc = 0;
  for(int i=0; i<numNodes; i++){
    if(visited[i] == 1)sin++;
    if(visited[i] == 2)dou++;
    if(nodes[i].inCycle)cyc++;
  }
  listOfObjects<BST *> *po = bsl;
  while(bsl != nullptr){
    con++;
    bsl = bsl->next;
  }
  cout << "No of connected components = " << con <<endl;
  cout << "No of nodes visited once = " << sin << endl;
  cout << "No of nodes visited twice = " << dou << endl;
  cout << "No of nodes that are present in a cycle = "<< cyc<<endl;
  if(cyc != 0){
  cout << "\nValues of nodes that are present in a cycle: ";
  for(int i=0; i<numNodes; i++){
    if(nodes[i].inCycle)cout<<nodes[i].value<<" ";
  }}
  cout<<"\n\n";

  bsl =po;
  int t=0;
  while(bsl != nullptr){
    t++;
    cout << "Component number " << t <<endl<<endl;
    bsl->object->printBST("");
    cout<<endl;
    bsl = bsl->next;
  }
  return;
}

#endif
