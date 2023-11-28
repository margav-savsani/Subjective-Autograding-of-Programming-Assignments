#include "graph.cpp"
using namespace std;

int main(int argc, char** argv){
    string line;
    int numnodes;
    graph* g;

    if(getline(cin,line)){          //reading line
        numnodes=stoi(line);
        g=new graph(numnodes);      //creating graph
    }

    while(getline(cin, line)){
        if(line=="-1 -1"){
            break;
        }
        istringstream ss(line);
        string l2;
        int a,b;
        if(ss >> l2) a=stoi(l2);
        if(ss >> l2) b=stoi(l2);
        g->insert_edge(a-1,b-1);        //inserting edge between a and b
    }

    while(getline(cin,line)){
        if(line=="-1 -1"){
            break;
        }
        istringstream ss(line);
        string l3;
        int a,b;
        if(ss >> l3) a=stoi(l3);
        if(ss >> l3) b=stoi(l3);
        if(g->nodes[a-1].sources==1 && g->nodes[b-1].sources==1){       //1st similar condition
            g->similar[(a-1)*numnodes+(b-1)]=1;
        }
    }

    ofstream myfile("outgraph.txt");            //writing into output file
    myfile<<"Source nodes: ";
    for(int i=0; i<numnodes; i++){
        if(g->nodes[i].sources==1){
            myfile<<i+1<<" ";
        }
    }
    myfile<<endl;

    for(int i=0; i<numnodes; i++){
        node2* x;
        x=g->nodes[i].incom;
        if(x!=NULL && x->next==NULL){
            g->similar[(i*numnodes)+(x->index)]=1;      //3rd similar condition 
        }
    }

    for(int i=0; i<numnodes; i++){
        for(int j=0; j<numnodes; j++){
            g->similar_edge(i,j);                       //2nd sinilar condition
        }
    }

    myfile<<endl;
    myfile<<"Similar node pairs: ";

    for(int i=0; i<numnodes*numnodes; i++){
        if(g->similar[i]==1){
            myfile<<"("<<(i/numnodes)+1<<", "<<i%numnodes+1<<") ";      //writing similar nodes into output file
            node2* cc=g->nodes[i/numnodes].coladj;
            if(cc==NULL){
                g->nodes[i/numnodes].coladj=new node2(i%numnodes);      //inserting into coladj
            }
            else{
                while(cc->next!=NULL){
                    cc=cc->next;
                }
                cc->next=new node2(i%numnodes);
            }
            node2* cc1=g->nodes[i%numnodes].coladj;
            if(cc1==NULL){
                g->nodes[i%numnodes].coladj=new node2(i/numnodes);      //inserting into coladj
            }
            else{
                while(cc1->next!=NULL){
                    cc1=cc1->next;
                }
                cc1->next=new node2(i/numnodes);
            } 
        }
    }
    myfile<<endl;

    node2* ans1;
    ans1=new node2(-5);                 //new nodes list
    int replace[numnodes];
    int count=0;
    for(int i=0; i<numnodes; i++){
        if(g->nodes[i].visited==0){
            node2* qwe;                 //dfs traversal of a connected component
            qwe=new node2(-2);
            g->DFS(i, qwe);
            node2* p=qwe->next;
            int max=p->index;
            while(p!=NULL){
                if(p->index > max){
                    max=p->index;
                }
                p=p->next;
            }
            qwe=qwe->next;
            while(qwe!=NULL){
                replace[qwe->index-1]=max;      
                qwe=qwe->next;
            }
            node2* as=ans1;
            while(as->next!=NULL){
                as=as->next;
            }
            as->next=new node2(max);        //inserting max value
            count++;
        }     
    }

    point* r;
    r=g->edges;
    while(r!=NULL){
        r->a=replace[r->a];                 //collapsing
        r->b=replace[r->b];
        r=r->next;
    }

    int collapsed[numnodes*numnodes];       
    for(int i=0; i<numnodes*numnodes; i++){
        collapsed[i]=0;
    }
    point* r1;
    r1=g->edges;
    while(r1!=NULL){
        collapsed[numnodes*(r1->a-1)+r1->b-1]=1;        //updating collapsed array
        r1=r1->next;
    }
    myfile<<endl;
    myfile<<"Collapsed graph: "<<endl;
    myfile<<endl;
    myfile<<count<<": ";                                //no. of nodes
    ans1=ans1->next;
    while(ans1!=NULL){
        myfile<<ans1->index<<" ";                       //identifiers
        ans1=ans1->next;
    }
    myfile<<endl;
    for(int i=0; i<numnodes*numnodes; i++){
        if(collapsed[i]==1){
            if(i/numnodes!=i%numnodes){
                myfile<<i/numnodes+1<<" "<<i%numnodes+1<<endl;
            }
        }
    }
}
