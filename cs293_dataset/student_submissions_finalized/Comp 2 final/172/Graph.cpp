
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <vector>
#include <stack>
#include "Graph.h"

using namespace std;

void Graph:: DFS(int starting_vertex){
    visited[starting_vertex] = true;
    if(nodes[starting_vertex].incoming==nullptr){
        if(sourceNodes==nullptr){ 
            sourceNodes=new listOfObjects<Node*>(new Node(starting_vertex+1));
        }
        else{
            listOfObjects<Node*>* a=sourceNodes;
            while(sourceNodes->next!=nullptr){
                sourceNodes=sourceNodes->next;
            }
            sourceNodes->next=new listOfObjects<Node*>(new Node(starting_vertex+1));
            sourceNodes=a;
        }
    }
    listOfObjects<Node*>* a=nodes[starting_vertex].outgoing;
    while(a!=nullptr){
        if(!visited[a->object->value-1])DFS(a->object->value-1);
        a=a->next;
    }
}

void Graph::callDFS(){
    for(int i=0; i<numNodes; i++){
        if(!visited[i]){
            DFS(i);
        }
    }
}

void Graph:: PrintSourceNodes(string filename){
    ofstream myfile;
    myfile.open (filename);
    if(sourceNodes==nullptr){
        myfile<<"There are no source nodes.\n";
    }
    else{
        myfile<<"Source nodes:";
        while(sourceNodes!=nullptr){
            myfile<<" "<<sourceNodes->object->value;
            sourceNodes=sourceNodes->next;
        }
        myfile<<"\n"<<"\n";
    }
    myfile.close();
}

void Graph::makeEdge(int n1,int n2){
    for(int i=0; i<numNodes; i++){
        if(nodes[i].value==n1){
            listOfObjects<Node*>* a=nodes[i].outgoing;
            if(a==nullptr){
                nodes[i].outgoing=new listOfObjects<Node*>(new Node(n2));
            }
            else{
                while(a->next!=nullptr){
                    a=a->next;
                }
                a->next=new listOfObjects<Node*>(new Node(n2));
            }  
        }
        if(nodes[i].value==n2){
            listOfObjects<Node*>* a=nodes[i].incoming;
            if(a==nullptr){
                nodes[i].incoming=new listOfObjects<Node*>(new Node(n1));
            }
            else{
                while(a->next!=nullptr){
                    a=a->next;
                }
                a->next=new listOfObjects<Node*>(new Node(n1));
            }
        }
    }
}

void Graph::similar_type3(){
    for(int i=0;i<numNodes; i++){
        listOfObjects<Node*>* a=nodes[i].incoming;
        for(int j=0;j<numNodes; j++){
            if(a!=nullptr){
                if(a->object->value==j+1 && a->next==nullptr){
                    if(similarnodes==nullptr){
                        similarnodes=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(i+1,j+1));
                    }
                    else{
                        listOfObjects<Similar_Nodes*>* b=similarnodes;
                        while(similarnodes->next!=nullptr){
                            similarnodes=similarnodes->next;
                        }
                        similarnodes->next=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(i+1,j+1));
                        similarnodes=b;
                    }
                }
            }
        }
    }
}

void Graph::similar_type2(){
    for(int i=0; i<numNodes; i++){
        for(int j=0; j<numNodes; j++){
            if(i!=j)check_similar(i+1,j+1);
        }
    }    
}

bool Graph::check_similar(int n1, int n2){
    listOfObjects<Similar_Nodes*>* c=similarnodes;
    while(similarnodes!=nullptr){
        if(similarnodes->object->node_1->value==n1 && similarnodes->object->node_2->value==n2){
            similarnodes=c;
            return true;
        }
        similarnodes=similarnodes->next;
    }
    similarnodes=c;
    bool similar1=true;
    listOfObjects<Node*>* a=nodes[n1-1].incoming;
    listOfObjects<Node*>* b=nodes[n2-1].incoming;
    if(a==nullptr && b==nullptr)return false;
    if(a==nullptr && b!=nullptr)return false;
    while(a!=nullptr){
        bool similar=false;
        while(b!=nullptr){
            if(check_similar(a->object->value,b->object->value))similar=true;
            b=b->next;
        }
        b=nodes[n2-1].incoming;
        if(!similar){
            similar1=false;
            return false;
        }
        a=a->next;
    }
    if(similar1 && n1<n2){
        if(check_similar(n2,n1)){
            if(similarnodes==nullptr){
                similarnodes=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(n1,n2));
                similarnodes->next=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(n2,n1));
            }
            else{
                listOfObjects<Similar_Nodes*>* a=similarnodes;
                while(similarnodes->next!=nullptr){
                    similarnodes=similarnodes->next;
                }
                similarnodes->next=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(n1,n2));
                similarnodes=similarnodes->next;
                similarnodes->next=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(n2,n1));
                similarnodes=a;
            }
        }
    }
    return true;
}

void Graph::PrintSimilarNodes(string filename){
    std::ofstream myfile;
    myfile.open(filename, std::ios_base::app);
    listOfObjects<Similar_Nodes*>* a=similarnodes;
    if(similarnodes==nullptr){
        myfile<<"There are no similar nodes.\n";
    }
    else{
        myfile<<"Similar node pairs:";
        while(similarnodes!=nullptr){
            myfile<<" ("<<similarnodes->object->node_1->value<<","<<similarnodes->object->node_2->value<<")";
            similarnodes=similarnodes->next;
        }
        similarnodes=a;
    }
    myfile<<"\n"<<"\n";
    myfile.close();
}

 bool Graph::isTransitive(int n1, int n2,listOfObjects<int>* intlist){
    listOfObjects<Similar_Nodes*>* a=similarnodes;
    while(a!=nullptr){
        if((a->object->node_1->value==n1 && a->object->node_2->value==n2) || (a->object->node_1->value==n2 && a->object->node_2->value==n1)){
            return true;
        }
        a=a->next;
    }
    a=similarnodes;
    if(intlist==nullptr){
        intlist=new listOfObjects<int>(n1);
        intlist->next=new listOfObjects<int>(n2);
    }
    listOfObjects<Similar_Nodes*>* c=nullptr;
    while(a!=nullptr){
        if(a->object->node_1->value==n1 && a->object->node_2->value!=n1){
            if(c==nullptr)c=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(n1,a->object->node_2->value));
            else{
                listOfObjects<Similar_Nodes*>* d=c;
                while(d->next!=nullptr){d=d->next;}
                d->next=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(n1,a->object->node_2->value));
            }
        }
        else if(a->object->node_1->value!=n1 && a->object->node_2->value==n1){
            if(c==nullptr)c=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(n1,a->object->node_1->value));
            else{
                listOfObjects<Similar_Nodes*>* d=c;
                while(d->next!=nullptr){d=d->next;}
                d->next=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(n1,a->object->node_1->value));
            }
        }
        a=a->next;
    }
    a=similarnodes;
    listOfObjects<int>* dummylist=intlist;
    while(c!=nullptr){
        bool found=false;
        while(dummylist!=nullptr){
            if(dummylist->object==c->object->node_2->value)found=true;
            dummylist=dummylist->next;
        }
        dummylist=intlist;
        if(!found){
            while(dummylist->next!=nullptr){
                dummylist=dummylist->next;
            }
            dummylist->next=new listOfObjects<int>(c->object->node_2->value);
            dummylist=intlist;
            if(isTransitive(c->object->node_2->value,n2,intlist))return true;
        }
        c=c->next;
    }
    return false;
 }

 bool Graph:: ispresent(int n1, int n2){
    listOfObjects<Similar_Nodes*>* a=final_list;
    while(a!=nullptr){
        if(a->object->node_1->value==n1 && a->object->node_2->value==n2 || a->object->node_1->value==n2 && a->object->node_2->value==n1){
            return true;
        }
        a=a->next;
    }
    return false;
 }

 listOfObjects<listOfObjects<int>*>* Graph::collapsing_nodes(){
    final_list=similarnodes;
    listOfObjects<Similar_Nodes*>* b=final_list;
    for(int i=0; i<numNodes; i++){
        for(int j=0; j<numNodes; j++){
            listOfObjects<int>* a=nullptr;
            if(j!=i){
                if(isTransitive(i+1,j+1,a)){
                    bool found=false;
                    while(b->next!=nullptr){
                        if(b->object->node_1->value==i+1 && b->object->node_2->value==j+1 || b->object->node_1->value==j+1 && b->object->node_2->value==i+1)found=true;
                        b=b->next;
                    }
                    if(b->object->node_1->value==i+1 && b->object->node_2->value==j+1 || b->object->node_1->value==j+1 && b->object->node_2->value==i+1)found=true;
                    if(!found)b->next=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(i+1,j+1));
                    b=final_list;
                }
            }
        }
    }

    listOfObjects<listOfObjects<int>*>* partition=nullptr;
    for(int i=0; i<numNodes; i++){
        if(i==0)partition=new listOfObjects<listOfObjects<int>*>(new listOfObjects<int>(1));
        else{
            bool found=false;
            listOfObjects<listOfObjects<int>*>* dummy=partition;
            while(dummy!=nullptr){
                listOfObjects<int>* list=dummy->object;
                if(ispresent(list->object,i+1)){
                    found=true;
                    while(list->next!=nullptr){
                        list=list->next;
                    }
                    list->next=new listOfObjects<int>(i+1);
                }
                dummy=dummy->next;
            }
            dummy=partition;
            if(!found){
                while(dummy->next!=nullptr){
                    dummy=dummy->next;
                }
                dummy->next=new listOfObjects<listOfObjects<int>*>(new listOfObjects<int>(i+1));
                dummy=partition;
            }
        }
    }
    listOfObjects<listOfObjects<int>*>* dummy=partition;
    while(dummy!=nullptr){
        listOfObjects<int>* a=dummy->object;
        int maximum=a->object;
        while(a!=nullptr){
            if(a->object>maximum)maximum=a->object;
            a=a->next;
        }
        if(collapsed_nodes==nullptr)collapsed_nodes=new listOfObjects<int>(maximum);
        else{
            listOfObjects<int>* a=collapsed_nodes;
            while(a->next!=nullptr){
                a=a->next;
            }
            a->next=new listOfObjects<int>(maximum);
        }
        dummy=dummy->next;
    }
    return partition;
}

void Graph::printCollapsedNodes(string filename){
    listOfObjects<listOfObjects<int>*>* a=collapsing_nodes();
    listOfObjects<listOfObjects<int>*>* b=a;
    listOfObjects<int>* d=collapsed_nodes;
    int length=0;
    while(a!=nullptr){
        a=a->next;
        length=length+1;
    }
    a=b;
    std::ofstream myfile;
    myfile.open(filename, std::ios_base::app);
    myfile<<"Collapsed Graph:"<<"\n"<<"\n";
    myfile<<length<<":"<<" ";
    while(collapsed_nodes!=nullptr){
        myfile<<collapsed_nodes->object<<" ";
        collapsed_nodes=collapsed_nodes->next;
    }
    myfile<<"\n";
    myfile.close();
    collapsed_nodes=d;
    for(int i=0; i<length;i++){
        for(int j=0; j<length; j++){
            if(i!=j){
                int k=0;
                while(k<i){a=a->next; k++;}
                listOfObjects<int>* list1=a->object;
                k=0;a=b;
                while(k<j){a=a->next; k++;}
                listOfObjects<int>* list2=a->object;
                listOfObjects<int>* dummylist2=list2;
                a=b;
                bool found=false;
                while(list1!=nullptr){
                    int num1=list1->object;
                    listOfObjects<Node*>* outfromnum1=nodes[num1-1].outgoing;
                    while(outfromnum1!=nullptr){
                        int num2=outfromnum1->object->value;
                        while(list2!=nullptr){
                            if(list2->object==num2)found=true;
                            list2=list2->next;
                        }
                        list2=dummylist2;
                        outfromnum1=outfromnum1->next;
                    }
                    list1=list1->next;
                }
                if(found){
                    k=0;
                    while(k<i){collapsed_nodes=collapsed_nodes->next; k++;}
                    int number1=collapsed_nodes->object;
                    k=0;collapsed_nodes=d;
                    while(k<j){collapsed_nodes=collapsed_nodes->next; k++;}
                    int number2=collapsed_nodes->object;
                    collapsed_nodes=d;
                    if(directed_edges==nullptr)directed_edges=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(number1,number2));
                    else{
                        listOfObjects<Similar_Nodes*>* dummy3=directed_edges;
                        while(dummy3->next!=nullptr){
                            dummy3=dummy3->next;
                        }
                        dummy3->next=new listOfObjects<Similar_Nodes*>(new Similar_Nodes(number1,number2));
                    }
                }
            }
        }
    }
    listOfObjects<Similar_Nodes*>* dummy3=directed_edges;
    myfile.open(filename, std::ios_base::app);
    while(dummy3!=nullptr){
        myfile<<dummy3->object->node_1->value<<" "<<dummy3->object->node_2->value<<"\n";
        dummy3=dummy3->next;
    }
    myfile.close();
}