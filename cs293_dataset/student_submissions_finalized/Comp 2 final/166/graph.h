#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <bits/stdc++.h>
using namespace std;
#endif



template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  listOfObjects() {}
  
  // Destructor
  ~listOfObjects() {;}
};
//defining list of objects class

class Node{
        public:
        int value; //value stored in the node

        Node(){};
        Node(int a){value=a;}
        listOfObjects<int> *sim; //list of indices similar to the node
        listOfObjects<Node *> *tolist; //list of nodes to which edges are present
        listOfObjects<Node *> *frolist; //list of objects from which edges are present
        };

class simedge{
        public:

        Node *n1;
        Node *n2;

        simedge(){};
        simedge(Node *c1, Node *c2){n1=c1;n2=c2;};
        void getedge(ofstream &f){
                f<<"("<<n1->value<<", "<<n2->value<<")";
        }
}; //class which defines an set of similar nodes 

class graph{
        int numnodes; //number of nodes
        fstream graphFile;
        Node *nodes;
        listOfObjects<simedge *> *ray; //similar nodes set
        listOfObjects<int> *snodes; //source nodes
        listOfObjects<int> *nsnodes; //non-source nodes
        

        public:
        graph(){
                int n;
                int a,b;
                cin >> n;
                numnodes=n;
                nodes=new Node[n];
                while(true){
                        cin >> a >> b;
                        if(a==-1 && b==-1) break;
                        nodes[a-1].value=a;nodes[b-1].value=b;
                        createedge(&nodes[a-1],&nodes[b-1]);
                }
        } //constructor



        void createedge(Node *n1,Node *n2){
                Node *t1;
                t1=n1;

                listOfObjects<Node *> *tempo;
                tempo = new listOfObjects<Node *>(new Node(-1));
                tempo->object=n1;
                tempo->next=nullptr;
                tempo->prev=nullptr;

                listOfObjects<Node *> *tempu;
                tempu = new listOfObjects<Node *>(new Node(-1));
                tempu->object=n2;
                tempu->next=nullptr;
                tempu->prev=nullptr;

                Node *t2;
                t2=n2;
                
                listOfObjects<Node *> *uwu;
                uwu=n1->tolist;
                listOfObjects<Node *> *owo;
                owo=n2->frolist;
                if(n1->tolist==nullptr){
                        n1->tolist=tempu;
                }
                else{
                        listOfObjects<Node *> *tut;
                        tut = t1->tolist;
                        while(tut->next!=nullptr){
                                tut=tut->next;
                        }
                        listOfObjects<Node *> *tempu;
                        tempu = new listOfObjects<Node *>(new Node(-1));
                        tempu->object=n2;
                        tempu->next=nullptr;
                        tut->next=tempu;
                        tempu->prev=tut;  
                }
                if(n2->frolist==nullptr){
                        n2->frolist=tempo;
                }
                else{
                       listOfObjects<Node *> *tat;
                        tat = t2->frolist;
                        while(tat->next!=nullptr){
                                tat=tat->next;
                        }
                        listOfObjects<Node *> *tempo;
                        tempo = new listOfObjects<Node *>(new Node(-1));
                        tempo->object=n1;
                        tempo->prev=nullptr;
                        tat->next=tempo;
                        tempo->prev=tat; 
                }
                return;
        } //function which creates an edge between two nodes upon calling
        void printsources(ofstream &f){
                f<<"Source nodes:";
                for (int i = 0;i<numnodes;i++){
                        if(nodes[i].frolist==nullptr){ //if the from-list is empty, the node is the source
                                f<<" "<<i+1;
                                if(snodes==nullptr){
                                        snodes = new listOfObjects<int>(i+1);
                                }
                                else{
                                        listOfObjects<int> *tyt;
                                        tyt=snodes;
                                        while(tyt->next!=nullptr){
                                                tyt=tyt->next;
                                        }
                                        tyt->next= new listOfObjects<int>(i+1);
                                        tyt->next->prev=tyt;
                                } //storing the source nodes 
                        }
                        else{
                                if(nsnodes==nullptr){
                                        nsnodes = new listOfObjects<int>(i+1);
                                }
                                else{
                                        
                                        listOfObjects<int> *tyt;
                                        tyt=nsnodes;
                                        while(tyt->next!=nullptr){
                                                tyt=tyt->next;
                                        }
                                        tyt->next= new listOfObjects<int>(i+1);
                                        tyt->next->prev=tyt;
                                } //storing the non-source nodes 
                        }
                }
                f<<" "<<endl;
                return;
        };

        void addedge(listOfObjects<simedge *> *list){
                if(ray==nullptr){
                                ray=list;
                        }
                        else{
                                listOfObjects<simedge *> *x;
                                x=ray;
                                while(x->next!=nullptr){
                                        x=x->next;
                                }
                                x->next=list;
                                list->prev=x;
                        }
                return;
        } //add a list of set to the similar nodes list

        void checker(Node *r1,Node *r2){
                listOfObjects<simedge *> *temp;
                temp=new listOfObjects<simedge * >(new simedge(r1,r2));
                addedge(temp);

                return;
        } //a functiton which creates a list of set and adds to the list of similar nodes sets

        bool present(listOfObjects<int> *su,int sui){
                while(su!=nullptr){
                        if(su->object=sui) return true;
                        su=su->next;
                }
                return false;
        } //checks if an int is present in the list of objects or not

        bool check(int x1,int x2){
                listOfObjects<int> *wee=nodes[x1-1].sim;
                listOfObjects<int> *woo=nodes[x2-1].sim;
                listOfObjects<Node *> *ee=nodes[x1-1].frolist;
                listOfObjects<Node *> *oo=nodes[x2-1].frolist;
                listOfObjects<Node *> *tre = oo;
                if(ee==nullptr || tre==nullptr){
                        return present(nodes[x1-1].sim,x2);
                }
                else{
                        while(ee!=nullptr && tre!=nullptr){
                                if(check(ee->object->value,tre->object->value)){
                                        ee=ee->next;
                                        tre=oo;
                                }
                                else{
                                        tre=tre->next;
                                }
                        }
                }
                if(ee!=nullptr) return false;
                else return true;
        } // function which checks if two non-source nodes are similar or not but checking their from-list using the 2nd condition given 

        int size(listOfObjects<int> *uwu){
                int i=0;
                while(uwu!=nullptr){
                        i++;uwu=uwu->next;
                }
                return i;
        } //size of the list of objects
        
        void similaredges(){
                while(true){
                        int a1,b1;
                        cin>>a1>>b1;
                        if(a1==-1 && b1==-1) break;
                        else{
                        Node *node1;
                        node1=&nodes[a1-1];
                        Node *node2;
                        node2=&nodes[b1-1];
                        if(node1->sim==nullptr){
                                node1->sim = new listOfObjects<int>(b1);
                        }
                        else{
                                listOfObjects<int> *uiy;
                                uiy=node1->sim;
                                while(uiy->next!=nullptr){
                                        uiy=uiy->next;
                                }
                                uiy->next= new listOfObjects<int>(b1);
                                uiy->next->prev=uiy;
                        }
                        checker(node1,node2);
                        }
                        
                }
                for(int i=0;i<numnodes;i++){
                        if(nodes[i].frolist!=nullptr&& nodes[i].frolist->next==nullptr){
                                Node *r1;
                                r1=&nodes[i];
                                Node *r2;
                                r2=nodes[i].frolist->object;
                                if(r1->sim==nullptr){
                                r1->sim = new listOfObjects<int>(r2->value);
                                }
                                else{
                                listOfObjects<int> *uiy;
                                uiy=r1->sim;
                                while(uiy->next!=nullptr){
                                        uiy=uiy->next;
                                }
                                uiy->next= new listOfObjects<int>(r2->value);
                                uiy->next->prev=uiy;
                                }
                                listOfObjects<simedge *> *temp;
                                temp=new listOfObjects<simedge * >(new simedge(r1,r2));
                                addedge(temp);
                        }
                }
                int *arr;
                arr = new int [size(nsnodes)];
                listOfObjects<int> *fuck;
                fuck=nsnodes;
                for (int i=0;i<size(fuck)+1;i++){
                        arr[i]=fuck->object;
                        fuck=fuck->next;
                }

                for(int i=0;i<size(nsnodes);i++){
                        for(int j=i+1;j<size(nsnodes);j++){
                                if(check(arr[i],arr[j])){
                                        listOfObjects<simedge *> *temp;
                                        temp = new listOfObjects<simedge *>(new simedge(&nodes[i],&nodes[j]));
                                        addedge(temp);
                                        temp = new listOfObjects<simedge *>(new simedge(&nodes[j],&nodes[i]));
                                        addedge(temp);
                                }
                                }
                        }
                return;
        } //function which is called to start finding the similar edges
                
        

        void printer(ofstream &f){
                f<<"Similar node pairs: "; 
                listOfObjects<simedge *> *ye;
                ye=ray;
                while(ye!=nullptr){
                        ye->object->getedge(f);
                        ye=ye->next;
                }
                f<<endl;
        } //function which prints the similar

};

#endif