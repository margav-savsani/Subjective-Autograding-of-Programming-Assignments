#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::DFS(Node *root, Node *prev, BST *DFST){
    if(root->num<2){
        //cout<<root->value<<endl;
        if(root->num==1){
            Journey * temporary= DFST->find(root->value);
            if(temporary->value!=prev->value){
                while(temporary!=nullptr){
                    nodes[temporary->value-1].Cycle=true;
                    temporary=temporary->parent;
                }
            }
        }
        DFST->insert(root->value);
        root->num++;
        listOfObjects<Node *> *curr=root->neighbours;
        while(curr!=nullptr){
            if(curr->object->value != prev->value){
                listOfObjects<Node *> *tempNeigh = curr->object->neighbours;
                if(tempNeigh!=nullptr){
                    if(tempNeigh->object->value == root->value){
                        curr->object->neighbours=curr->object->neighbours->next;
                    }
                    else{
                        if(tempNeigh->next!=nullptr){
                            while(tempNeigh->next!=nullptr && tempNeigh->next->object->value!=root->value){
                                tempNeigh=tempNeigh->next;
                            }
                            if(tempNeigh->next!=nullptr && tempNeigh->next->object->value==root->value){
                                tempNeigh->next=tempNeigh->next->next;
                            }
                        }
                    }
                }
                DFS(&nodes[curr->object->value-1], root, DFST);
                tempNeigh=curr->object->neighbours;
                if(tempNeigh==nullptr){
                    curr->object->neighbours=new listOfObjects<Node *>(new Node());
                    curr->object->neighbours->object=root;
                }
                else{
                    while(tempNeigh->next!=nullptr){
                        tempNeigh=tempNeigh->next;
                    }
                    tempNeigh->next=new listOfObjects<Node *>(new Node());
                    tempNeigh->next->object=root;
                }
            }
            curr=curr->next;
        }
    }
    else{

    }
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {

    //====================================================
    //  for(int i=0; i<numNodes; i++){
    //      listOfObjects<Node *> *curr=nodes[i].neighbours;
    //      while(curr!=nullptr){
    //         cout<<curr->object->value<<" ";
    //          curr=curr->next;
    //      }
    //      cout<<endl;
    //  }
    //====================================================


    listOfObjects<BST *> *curr= DFSTLL;
    int counter=0;
    for(int i=0; i<numNodes; i++){
        if(nodes[i].num==0){
            if(counter!=0){
                curr->next = new listOfObjects<BST *>(new BST());
                curr=curr->next;
            }
            connComp++;
            DFS(&nodes[i], &nodes[i], curr->object);
            counter++;
            
        }
    }

  return;
}

void Graph::printResults() {
    int numOnce=0;
    int numTwice=0;
    for(int i=0; i<numNodes; i++){
        if(nodes[i].Cycle==true){
            cycleNodes++;
        }
        if(nodes[i].num == 1){
            numOnce++;
        }
        else{
            numTwice++;
        }
    }
    cout<<"Connected components: "<<connComp<<endl;
    cout<<"Nodes visited once: "<<numOnce<<endl;
    cout<<"Nodes visited twice: "<<numTwice<<endl;
    cout<<"Nodes in cycles: "<<cycleNodes<<endl;
    cout<<endl;
    listOfObjects<BST *> *curr= DFSTLL;
    int i =1;
    while(curr!=nullptr){
        cout<<"BST "<<i<<endl;
        cout<<endl;
        curr->object->printBST("", false);
        curr=curr->next;
        i++;
        cout<<endl;
    }

  return;
}

#endif
