#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cmath>
using namespace std;


class linked_list{// linked linked_list class to store the edges of graph
    public:
    linked_list* next;
    int adjacentNode;
    linked_list(int node){
        next=NULL;
        adjacentNode=node;
    }
};
class DAG{
    public:
    bool* sourcenode;
    int numNodes;
    int ** simmatrix;// matrix to store similarity for memoisation using recursion
    linked_list** toedges;
    linked_list** fromedges;
    int *rep;
    
    DAG(int n){
        simmatrix=new int*[n]; 
        for(int i=0;i<n;i++)simmatrix[i]=new int[n];
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)simmatrix[i][j]=0;
        }
        sourcenode=new bool[n];
        numNodes=n;
        toedges=new linked_list*[n];
        fromedges=new linked_list*[n];
        for(int i=0;i<n;i++){
            toedges[i]=NULL;
            fromedges[i]=NULL;
        }
        for(int i=0;i<n;i++)sourcenode[i]=1;
        rep=new int[n];
        for(int i=0;i<n;i++)rep[i]=0;
    }

    bool similar(int i,int j){
        if(simmatrix[i-1][j-1]!=0){
            if(simmatrix[i-1][j-1]==1)return true;
            else return false;
        }
        if(!sourcenode[i-1] && !sourcenode[j-1]){// applying to check rule 2
            bool sim=true;
            
            linked_list* m1=fromedges[i-1];
            while(m1 != NULL){
                linked_list* m2=fromedges[j-1];
                bool found=false;
                while(m2 != NULL){
                    bool simi=similar(m1->adjacentNode,m2->adjacentNode);
                    if(simi){
                        found=true;
                        break;
                    }
                    m2=m2->next;
                }
                if(!found){
                    sim=false;
                    break;
                }
                m1=m1->next;
            }


            m1=fromedges[j-1];
            while(m1 != NULL){
                linked_list* m2=fromedges[i-1];
                bool found=false;
                while(m2 != NULL){
                    bool simi=similar(m1->adjacentNode,m2->adjacentNode);
                    if(simi){
                        found=true;
                        break;
                    }
                    m2=m2->next;
                }
                if(!found){
                    sim=false;
                    break;
                }
                m1=m1->next;
            }

            if(sim){
                simmatrix[i-1][j-1]=1;
                simmatrix[j-1][i-1]=1;
                return true;
            }
            else{
                simmatrix[i-1][j-1]=-1;
                return false;
            }

        }
        simmatrix[i-1][j-1]=-1;
        return false;

    }

    int repfind (int i){
        if(rep[i-1]!=0)return rep[i-1];
        int repo=i;
        rep[i-1]=i;
        for(int j=0;j<numNodes;j++){
            if(j+1==i)continue;
            if(simmatrix[i-1][j]==1 || simmatrix[j][i-1]==1){
                repo=max(repo,repfind(j+1));
            }
        }
        rep[i-1]=0;
        return repo;
    }
};



int main(){
    ofstream outdata;
    outdata.open("outgraph.txt");
    int num;
    cin>>num;
    DAG graph(num);
    int n1,n2;




    while(true){// reading in the nodes 
        cin>>n1>>n2;
        if(n1==-1 && n2==-1 )break;
        graph.sourcenode[n2-1]=false;
        linked_list* to=new linked_list(n2);
        to->next=graph.toedges[n1-1];
        graph.toedges[n1-1]=to;
        linked_list* from=new linked_list(n1);
        from->next=graph.fromedges[n2-1];
        graph.fromedges[n2-1]=from;
    }


    
    while(true){ // changing status of nodes to similar wherever rule 1 is applicable
        cin>>n1>>n2;
        if(n1==-1 && n2==-1 )break;
        graph.simmatrix[n1-1][n2-1]=1;
    }
    

    for(int i=0;i<num;i++){ // changing status of nodes to similar wherever rule 3 is applicable
        if(graph.fromedges[i]!=NULL){
            if(graph.fromedges[i]->next==NULL){
                graph.simmatrix[i][graph.fromedges[i]->adjacentNode-1]=1;
            }
        }
    }


    for(int i=0;i<num;i++){// changing status of nodes to similar wherever rule 1 is applicable
        for(int j=0;j<num;j++)graph.similar(i+1,j+1);
    }
    for(int i=num-1;i>=0;i--){
        graph.rep[i]=graph.repfind(i+1);
    }

    



    outdata<<"Source nodes: ";
    for (int i=0;i<num;i++)if(graph.sourcenode[i])outdata<<i+1<<" ";
    outdata<<endl;
    outdata<<"Similar nodes: ";
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++)if(graph.simmatrix[i][j]==1)outdata<<"("<<i+1<<","<<j+1<<") ";
    }
    outdata<<endl;
    outdata<<"Collapsed graph:"<<endl;
    int colnodes=0;
    for(int i=1;i<=num;i++)if(graph.rep[i-1]==i)colnodes++;
    outdata<<colnodes<<": ";
    for(int i=1;i<=num;i++)if(graph.rep[i-1]==i)outdata<<i<<" ";
    outdata<<endl;   
    for(int i=1;i<=num;i++){
        if(graph.rep[i-1]!=i)continue;
        linked_list* start=NULL;
        for(int j=0;j<num;j++){
            if(graph.rep[j]==i){
                linked_list*adj=graph.toedges[j];
                while(adj!=NULL){
                    int x=graph.rep[adj->adjacentNode-1];
                    linked_list*temp=start;
                    bool found=false;
                    while(temp!=NULL){
                        if(temp->adjacentNode==x)found=true;
                        temp=temp->next;
                    }
                    if(i==x)found=true;
                    if(!found){
                        linked_list* head=new linked_list(x);
                        head->next=start;
                        start=head;
                    }
                    
                    adj=adj->next;
                }
            }
        }
        while(start!=NULL){
            outdata<<i<<" "<<start->adjacentNode<<endl;
            start=start->next;
        }

    }
}