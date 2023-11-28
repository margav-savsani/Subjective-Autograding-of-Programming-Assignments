#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include<iostream>
#endif

#ifndef GRAPH_BST_H
#include "graph.h"
#endif


void Graph:: markNodes(int s){
  if(marked[s]){
    return;
  }
  marked[s] = true;
  LinkedList *ele = nodes[s].adjacentList;
  while(ele != nullptr){
    markNodes(ele->store->value-1);
    ele = ele->next;
  }
}

void Graph::findSources(){
  for(int i=0; i<numNodes; i++){
    // cout << i << endl;
    if(marked[i])
      continue;
    else{
      LinkedList *ele = nodes[i].adjacentList;
      while(ele != nullptr){
        markNodes(ele->store->value-1);
        ele = ele->next;
      }
    }  
  }

  string output = "";
  for(int i=0; i<numNodes; i++){
    if(!marked[i]){
      output += to_string(i+1) + " ";
      sources[i] = true;
    }
  }
  output.pop_back();
  // outfile.open("output.txt");

  outfile << "Source nodes: " << output << endl;
  
}

void Graph::updateAsimilarpair(int n1, int n2){
      // cout << n1 << " " <<  n2 << endl;
      if(nodes[n1].SimilarTo == nullptr){
        nodes[n1].SimilarTo = new LinkedList(&nodes[n2]);
        // nodes[n1].adjListLastEle = nodes[n1].adjacentList;
      }  
      else{
        LinkedList *a = nodes[n1].SimilarTo;
          // cout << a->store->value-1 << endl;
        while(a->next != nullptr){
          if(a->store->value-1 == n2){
            return;
          }
          a = a->next;
        }
          if(a->store->value-1 == n2){
            return;
          }
        
        a->next = new LinkedList(&nodes[n2]);
        // nodes[n1].adjListLastEle = nodes[n1].adjListLastEle->next;
      }
      if(nodes[n2].SimilarFrom == nullptr){
        nodes[n2].SimilarFrom = new LinkedList(&nodes[n1]);
        // nodes[n2].FromAdjListLastEle = nodes[n2].FromAdjList;
      }  
      else{
        LinkedList *a = nodes[n2].SimilarFrom;
        while(a->next != NULL){
          if(a->store->value-1 == n1)
            return;
          a = a->next;
        }
        a->next = new LinkedList(&nodes[n1]);
        // nodes[n2].FromAdjListLastEle = nodes[n2].FromAdjListLastEle->next;
      }
}

void Graph::CheckandUpdateSimilarity(Node* x, Node* y){
  
  struct List{
    int val;
    List* next;
    List(int v){
      val = v;
      next = nullptr;
    }
  };

  List* ofX = new List(x->FromAdjList->store->value-1);
  List* ofX_last = ofX;
  int lenX = 1;
  LinkedList* curr1 = x->FromAdjList->next;
  while(curr1 != nullptr){
    ofX_last->next = new List(curr1->store->value-1);
    ofX_last = ofX_last->next;
    lenX++;
    curr1 = curr1->next;
  }
  List* ofY = new List(y->FromAdjList->store->value-1);
  List* ofY_last = ofY;
  int lenY = 1;
  curr1 = y->FromAdjList->next;
  while(curr1 != nullptr){
    ofY_last->next = new List(curr1->store->value-1);
    ofY_last = ofY_last->next;
    lenY++;
    curr1 = curr1->next;
  }

  if(lenX != lenY)
    return;
  
  int mat[numNodes][numNodes];


  curr1 = x->FromAdjList;
  while(curr1 != NULL){
    // if(curr1 == c){
    //   curr1 = curr1->next;
    //   continue;
    // }

    // bool found = false;

    LinkedList *someSim = curr1->store->SimilarTo;
    while(someSim != NULL){
      // bool foundInlist = false;
      List* ofX_var = ofX;
      while(ofX_var != NULL){

        if(ofX_var->val == someSim->store->value-1){
          bool f2=false;
          LinkedList* currrr = nodes[ofX_var->val].SimilarTo;
          while(currrr != NULL){
            if(currrr->store == someSim->store){
              mat[curr1->store->value-1][currrr->store->value-1] = 1000;
              break;
            }
            currrr = currrr->next;
          }
        }
        ofX_var = ofX_var->next;
      }
      someSim = someSim->next;
    }
    
    curr1 = curr1->next;
  }

  curr1 = y->FromAdjList;
  while(curr1 != NULL){
    // if(curr1 == c){
    //   curr1 = curr1->next;
    //   continue;
    // }

    // bool found = false;

    LinkedList *someSim = curr1->store->SimilarTo;
    while(someSim != NULL){
      // bool foundInlist = false;
      List* ofY_var = ofY;
      while(ofY_var != NULL){

        if(ofY_var->val == someSim->store->value-1){
          bool f2=false;
          LinkedList* currrr = nodes[ofY_var->val].SimilarTo;
          while(currrr != NULL){
            if(currrr->store == someSim->store){
              mat[currrr->store->value-1][curr1->store->value-1] = 1000;
              break;
            }
            currrr = currrr->next;
          }
        }
        ofY_var = ofY_var->next;
      }
      someSim = someSim->next;
    }
    
    curr1 = curr1->next;
  }


  bool found = true;
  List *ofY_ = ofY;
  while(ofY_ != NULL){
    List* ofX_ = ofX;
    while(ofX_ != NULL){
      if(mat[ofX_->val][ofY_->val] != 1000){
        found = false;
        break;
      }
      ofX_ = ofX_->next;
    }
    if(!found)
      break;
    ofY_ = ofY_->next;
  }

if(found){
  updateAsimilarpair(x->value-1, y->value-1);
  updateAsimilarpair(y->value-1, x->value-1);
}
return;

}

void Graph::updateIffoundSimilar(int ind){

  // case III
  // only one incoming node
  if(nodes[ind].FromAdjList->next == nullptr){
    updateAsimilarpair(ind, nodes[ind].FromAdjList->store->value-1);
  }
  // case II
  LinkedList* aTakenNode = nodes[ind].FromAdjList;
  LinkedList *ASimilarToOfIncoming = aTakenNode->store->SimilarTo;
  while(ASimilarToOfIncoming != NULL){
    LinkedList *n1_ToSimilars = ASimilarToOfIncoming->store->SimilarTo;
    bool found = false;
    while(n1_ToSimilars != NULL){
      if(n1_ToSimilars == aTakenNode){
        found = true;
        break;
      }
      n1_ToSimilars = n1_ToSimilars->next;
    }
    if(found)
    {
      LinkedList *AToAdjOf_n1 = ASimilarToOfIncoming->store->adjacentList;
      while(AToAdjOf_n1 != NULL){
        CheckandUpdateSimilarity(AToAdjOf_n1->store, &nodes[ind]);
      }
    }
    ASimilarToOfIncoming = ASimilarToOfIncoming->next;
  }

}



void Graph::huntSimilars(int src){
  if(marked[src]){
    return;
  }
  marked[src] = true;
  updateIffoundSimilar(src);
  LinkedList *ele = nodes[src].adjacentList;
  while(ele != nullptr){
    markNodes(ele->store->value-1);
    ele = ele->next;
  }
}


void Graph::updateSimilars(){
  for(int mmm=0; mmm<2; mmm++)
  {
    for(int i=0; i<numNodes; i++)
      marked[i] = false;
    
    for(int i=0; i<numNodes; i++){
      if(!sources[i])
        continue;
      else{
        LinkedList *ele = nodes[i].adjacentList;
        while(ele != nullptr){
          huntSimilars(ele->store->value-1);
          ele = ele->next;
        }
      }
    }
  }


  // outfile.open("output.txt");

outfile << endl;
// outfile.close();
        // for(int j=0; j<numNodes; j++){
        //   LinkedList* a = nodes[j].SimilarTo;
        //   cout << j+1 << ": ";
        //   while(a!=nullptr){
        //     cout << a->store->value << "  ";
        //     a = a->next;
        //   }
        //   cout << endl;
        //   LinkedList* b = nodes[j].SimilarFrom;
        //   cout << j+1 << ": ";
        //   while(b!=nullptr){
        //     cout << b->store->value << "  ";
        //     b = b->next;
        //   }
        //   cout << endl;
        // }
}



void Graph::print(){

outfile.open("output.txt");

outfile << "Source nodes: ";
for(int j=0; j<numNodes; j++){
  if(sources[j]){
    outfile << j+1 << " ";
  }
}
outfile << "\n";

outfile << "Similar node pairs: ";
for(int j=0; j< numNodes; j++){
  LinkedList* a = nodes[j].SimilarTo;
  while(a!=nullptr){
    outfile << "(" << j+1 << ", " << a->store->value << ") "; 
    a = a->next;
  }
}
outfile<<endl;
outfile.close();
}
#endif