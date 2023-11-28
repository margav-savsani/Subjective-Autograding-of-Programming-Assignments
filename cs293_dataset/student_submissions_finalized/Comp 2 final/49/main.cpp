#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// checks similarity between n1, n2 which are not sources 
bool similarity(int nodes,int n1, int n2,int*adj,int*sim){
    if(*(sim+n1*nodes+n2)==-1)return false;
    if(*(sim+n1*nodes+n2)==1)return true;
    // takes parents of n1 and compares with n2
    for(int i=0;i<nodes;i++){
        if(*(adj+n1*nodes+i)==-1){
            bool s = false;
            for(int j=0;j<nodes;j++){
                if(*(adj+n2*nodes+j)==-1){
                    if(*(sim+i*nodes+j)==1)s=true;
                    else if(*(sim+i*nodes+j)==0)s=similarity(nodes,i,j,adj,sim);                   
                }
            }
            if(s==false){
                *(sim+n1*nodes+n2)=-1;
                *(sim+n2*nodes+n1)=-1;
                return false;
            }
        }
    }
    // takes parents of n2 and compares with n1
    for(int i=0;i<nodes;i++){
        if(*(adj+n2*nodes+i)==-1){
            bool s = false;
            for(int j=0;j<nodes;j++){
                if(*(adj+n1*nodes+j)==-1){
                    if(*(sim+i*nodes+j)==1)s=true;
                    else if(*(sim+i*nodes+j)==0)s=similarity(nodes,i,j,adj,sim);                   
                }
            }
            if(s==false){
                *(sim+n1*nodes+n2)=-1;
                *(sim+n2*nodes+n1)=-1;
                return false;
            }
        }
    }
    *(sim+n1*nodes+n2)=1;
    *(sim+n2*nodes+n1)=1;
    return true;
}
int main(int argc, char **argv){

    ofstream file("outgraph.txt");    
    int nodes;
    cin>>nodes;
    int source[nodes];    
    int *adj = new int[nodes*nodes];
    int *sim = new int[nodes*nodes];
    int group[nodes][nodes];
    int coll[nodes];
    for(int i=0;i<nodes;i++){
        source[i] = 0;
        coll[i] = -1;
        for(int j=0;j<nodes;j++){
            if(i==j)group[i][j]=1;
            else group[i][j]=0;
            *(adj+i*nodes+j) = 0;
            *(sim +i*nodes+j) = 0;
        }
    }
    // input of edges
    while(true){
        int a,b;
        cin>>a>>b;
        if(a==-1||b==-1)break;
        *(adj+(a-1)*nodes+b-1)= 1;
        *(adj+(b-1)*nodes+a-1) = -1;
    }
    // input of similar source nodes
    while(true){
        int a,b;
        cin>>a>>b;
        if(a==-1||b==-1)break;
        *(sim +(a-1)*nodes+b-1)= 1;        
    }
    // printing source nodes
    file<<"Sourcenodes: ";
    for(int i=0;i<nodes;i++){
        bool s = true;
        for(int j=0;j<nodes;j++){
            if(*(adj+i*nodes+j)==-1){
                s = false;
            }            
        }
        if(s){
            file<<i+1<<" ";
            source[i]=1;
        }    
    }
    file<<endl;
    file<<endl;
    file<<"Similar node pairs: ";
    for(int i=0;i<nodes;i++){
        // if source checks its similarity using case1
        if(source[i]==1){
            for(int j=0;j<nodes;j++){
                if(*(sim+i*nodes+j)!=1)*(sim+i*nodes+j)=-1;
            }
        }
        // if not source checks its similarity using case2, case3
        else{
            int n=0;
            int similar = i;
            for(int j=0;j<nodes;j++){
                if(*(adj+i*nodes+j)==-1){
                    n++;
                    similar = j;
                }
            }
            if(n==1){
                for(int j=0;j<nodes;j++){
                    if(source[j]==1){
                        *(sim+i*nodes+j)=-1;                        
                    }
                    else{
                        bool s = similarity(nodes,i,j,adj,sim);
                    }                    
                }
                *(sim+i*nodes+similar)=1;
                if(source[similar]==1)*(sim+similar*nodes+i)=-1;
            }
            else{
                for(int j=0;j<nodes;j++){
                    if(source[j]==1){
                        *(sim+i*nodes+j)=-1;                        
                    }
                    if(*(sim+i*nodes+j)==0){
                        similarity(nodes,i,j,adj,sim);
                    }
                }
            }

        }
    }
    // uses sim array and writes into file
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){            
            if(*(sim+i*nodes+j)==1)file<<"("<<i+1<<", "<<j+1<<") ";
        }
    }
    file<<endl;
    file<<endl;
    file<<"Collapsed graph: "<<endl;    
    for(int i=0;i<nodes;i++){        
        for(int j=0;j<nodes;j++){
            if(*(sim+i*nodes+j)==1||*(sim+j*nodes+i)==1)group[i][j]=1;
        }        
    }
    int l=0;
    //collapsing nodes and grouping them
    while(l<nodes){   
        int n=0;     
        for(int j=0;j<nodes;j++){
            if(l!=j&&group[l][j]==1){
                for(int k=0;k<nodes;k++){
                    if(group[j][k]==1){
                        group[l][k]=1;
                        group[j][k]=0;
                        n++;
                    }
                }
            }
        }  
        if(n==0)l++;      
    }
    int num = 0;
    int max[nodes];    
    for(int i=0;i<nodes;i++){
        if(group[i][i]==1){
            for(int j=0;j<nodes;j++){
                if(group[i][j]==1){
                    if(coll[i]<j)coll[i]=j;                   
                }                
            }
            num++;
        }        
    }
    file<<num<<": ";
    for(int i=0;i<nodes;i++){
        if(coll[i]>0){
            file<<coll[i]+1<<" ";
            for(int j=0;j<nodes;j++){
                if(group[i][j]==1){
                    max[j] = coll[i];
                }
            }
        }        
    }
    file<<endl;
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
           if(*(adj+max[i]*nodes+max[j])!=1)*(adj+max[i]*nodes+max[j])=*(adj+i*nodes+j);
           if(*(adj+max[j]*nodes+max[i])!=1)*(adj+max[j]*nodes+max[i])=*(adj+j*nodes+i);                      
        }
    } 
    //matrix for new graph   
    int node[num];
    l=0;
    for(int i=0;i<nodes;i++){
        if(coll[i]>0){
            node[l]=coll[i];
            l++;
        }
    }
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
                if(*(adj+node[i]*nodes+node[j])==1&&i!=j)file<<node[i]+1<<" "<<node[j]+1<<endl;  
        }
    }
}  