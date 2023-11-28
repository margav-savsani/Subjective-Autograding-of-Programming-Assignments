//Graph Functions File
#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

using namespace std;
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

//Finds for the given node a inside the linked list t
//Returns true if it is present and false otherwise
bool find(listOfObjects<Node*> *t, Node * a){
    int k = a->value;
    listOfObjects<Node*> *curr;
    curr=t;
    while(curr!=nullptr){
        //Returning true if found
        if(curr->object->value==k){
            return true;
        }
        curr=curr->next;
    }
    //False otherwise
    return false;
}

//Returns the maximum of two integers
int getmax(int a, int b){
    if(a>b) return a;
    return b;
}
//Returns the minimum of two integers
int getmin(int a, int b){
    if(a<b) return a;
    return b;
}

//Merges two linked lists of typename T and returns it
template <typename T>
listOfObjects<T>* mergelist(listOfObjects<T> *a, listOfObjects<T> *b){
    listOfObjects<T> *newList;
    //If a is empty returning b
    if(a==nullptr) {
        return b;
    }
    //If b is empty returning a
    if(b==nullptr){
        return a;
    }
    //If a and b are same returning one of them
    if (a==b) return a;
    newList=a;
    listOfObjects<T> *curr;
    curr=newList;
    while (curr->next!=nullptr)
    {
        curr=curr->next;
    }
    curr->next=b;
    //Otherwise returning the mergedList
    return newList;
}

//Adds a directed edge from node valued n1 to node valued n2
void Graph::addDirectedEdge(int n1, int n2){
    //If there does not exists a directed edge from n1 to n2
    if(!nodes[n1-1].isoutNeighbour(nodes[n2-1])){
        //Adding a directed edge by updating the outadjacency List of n1 and inAdjacency List of n2
        nodes[n1-1].addoutNeighbour(&nodes[n2-1]);
        nodes[n2-1].addinNeighbour(&nodes[n1-1]);
    }
}

//Adds (n1,n2) pair to listofSimilars and also the node valued n2 in the similar list of node valued n1
void Graph::addSimilar(int n1, int n2){
    //If n2 is not alredy in the similar list then
    if(!nodes[n1-1].isSimilar(nodes[n2-1])){
        //Adding n2 in the similar list of n1
        nodes[n1-1].addsimilar(&nodes[n2-1]);
        //Also adding the Ordered apir n1,n2 to the listofSimilars
        OrderedPair *op = new OrderedPair(n1,n2);
        if(listofSimilars==nullptr){
            listofSimilars=new listOfObjects<OrderedPair*>(op);
            return;
        }
        listOfObjects<OrderedPair*> *curr;
        curr=listofSimilars;
        while(curr->next!=nullptr){
            curr=curr->next;
        }
        curr->next=new listOfObjects<OrderedPair*>(op);
        return;
    }
}

//Prints all the Source Nodes
void Graph::printSourceNodes(){
    graphFile<<"Source nodes: ";
    for(int i=0;i<numNodes;i++){
        //If its inadjacency list is empty
        if(nodes[i].inadjnodes==nullptr){
            nodes[i].isSource=true;
            graphFile<<nodes[i].value<<" ";
        }
    }
    graphFile<<endl;
}

//Prints all the Similar Node Pairs
void Graph::printSimilarNodes(){
    if(listofSimilars==nullptr) return;
    graphFile<<"Similar node pairs: ";
    listOfObjects<OrderedPair*> *curr;
    curr=listofSimilars;
    while(curr!=nullptr){
        //Printing the result in specified format
        graphFile<<"("<<curr->object->value1<<","<<curr->object->value2<<") ";
        curr=curr->next;
    }
    graphFile<<endl;
}

//Constructs all the similar nodes possible
void Graph::constructSimilar(){
    //Checking for every possible pair i j
    for(int i=1;i<=numNodes;i++){
        for(int j=1;j<=numNodes;j++){
            checkSimilar(i,j);
        }
    }
}

//Checks and updates if n1 is similar to n2
//Returns true if it is and false otherwise
bool Graph::checkSimilar(int n1,int n2){
    //If they are already similar return true
    if(nodes[n1-1].isSimilar(nodes[n2-1])){
        return true;
    }
    //If n1 is source
    if(nodes[n1-1].isSource) return false;
    //Condition 3 of prob stat
    if(nodes[n1-1].inadjnodes->object->value==n2 && nodes[n1-1].inadjnodes->next==nullptr){
        //Adding n1 and n2 as similar
        addSimilar(n1,n2);
        return true;
    }

    //Checking condition 2 of problem statement
    if(nodes[n2-1].isSource) return false;
    listOfObjects<Node*> *curr1;
    listOfObjects<Node*> *curr2;
    curr1=nodes[n1-1].inadjnodes;
    while(curr1!=nullptr){
        curr2=nodes[n2-1].inadjnodes;
        while(curr2!=nullptr){
            if(curr1->object->isSimilar(*curr2->object)){
                break;
            }
            curr2=curr2->next;
        }
        if(curr2==nullptr){
            return false;
        }
        curr1=curr1->next;
    }
    curr1=nodes[n2-1].inadjnodes;
    while(curr1!=nullptr){
        curr2=nodes[n1-1].inadjnodes;
        while(curr2!=nullptr){
            if(curr1->object->isSimilar(*curr2->object)){
                break;
            }
            curr2=curr2->next;
        }
        if(curr2==nullptr){
            return false;
        }
        curr1=curr1->next;
    }
    //Adding both as similar 
    addSimilar(n1,n2);
    addSimilar(n2,n1);
    return true;
}

//Collapses the Graph and prints the collapsed graphs numNodes, NodeList and Edges
void Graph::CollapseGraph(){
    //Iterating through each similar pair
    //And adding it's outneighbours to the higher node
    listOfObjects<OrderedPair*> *curr;
    curr=listofSimilars;
    while(curr!=nullptr){
        int n1= curr->object->value1;
        int n2= curr->object->value2;
        if(n1==n2){
            curr=curr->next;
            continue;
        }
        n2=findFinalCollapse(n2);
        n1=findFinalCollapse(n1);
        int max= getmax(n1,n2);
        int min= getmin(n1,n2);
        listOfObjects<Node*> *clist;
        clist=mergelist(nodes[min-1].outadjnodes,nodes[max-1].outadjnodes);
        nodes[max-1].outadjnodes=clist;
        nodes[min-1].collapsedTo=max;
        curr=curr->next;
    }
    //Calculating the number of Uncollapsed nodes
    for(int i=1; i<=numNodes; i++){
        if(nodes[i-1].collapsedTo==i){
            nUnCollapsedNodes++;
        }
    }
    //Printing
    graphFile<<"Collapsed graph:"<<endl;
    graphFile<<nUnCollapsedNodes<<": ";
    //Adding every uncollapsed node to the collapsedNodes linked list and printing it to the file
    for(int i=1; i<=numNodes; i++){
        if(nodes[i-1].collapsedTo==i){
            if (collapsedNodes==nullptr){
                collapsedNodes=new listOfObjects<int>(i);
                graphFile<<i<<" ";
                continue;
            }
            listOfObjects<int> *curr;
            curr=collapsedNodes;
            while(curr->next!=nullptr){
                curr=curr->next;
            }
            curr->next=new listOfObjects<int>(i);
            graphFile<<i<<" ";
        }
    }
    graphFile<<endl;
    listOfObjects<int> *cur;
    //For every uncollapsed node
    //Truncating the outadjacency list such that it contains only uncollapsed distinct neighbours
    cur=collapsedNodes;
    while(cur!=nullptr){
        int n=cur->object;
        listOfObjects<Node*> *truncatedList=nullptr;
        listOfObjects<Node*> *out;
        out=nodes[n-1].outadjnodes;
        while(out!=nullptr){
            //Finding final collapse of the edge
            int k=findFinalCollapse(out->object->value);
            //If it same as the source node not adding the edge
            if(k==n){
                out=out->next;
                continue;
            }
            //Otherwise updating the truncatedList
            if(truncatedList==nullptr){
                truncatedList=new listOfObjects<Node*>(&nodes[k-1]);
            }
            listOfObjects<Node *> *kurr;
            kurr=truncatedList;
            if (!find(truncatedList,&nodes[k-1]))
            {
                while(kurr->next!=nullptr){
                    kurr=kurr->next;
                }
                kurr->next=new listOfObjects<Node*>(&nodes[k-1]);
            }
            out=out->next;
        }
        //Updating outadjacency list to truncatedList
        nodes[n-1].outadjnodes=truncatedList;
        cur=cur->next;
    }
    //Printing all Edges to the graph file
    cur=collapsedNodes;
    while(cur!=nullptr){
        int n=cur->object;
        listOfObjects<Node*> *adj;
        adj=nodes[n-1].outadjnodes;
        while(adj!=nullptr){
            graphFile<<n<<" "<<adj->object->value<<endl;
            adj=adj->next;
        }
        cur=cur->next;
    }
}

//Finds the node value that the node valued n will finally collapse to
int Graph::findFinalCollapse(int n){
    //Iterating till the node does not have a higher node
    while(nodes[n-1].collapsedTo!=n){
        n=nodes[n-1].collapsedTo;
    }
    return n;
}


#endif