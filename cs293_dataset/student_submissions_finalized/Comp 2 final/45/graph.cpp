#include<iostream>
#include<fstream>
#include<string>
using namespace std;
ofstream fout("outgraph.txt");

class list{
    public:
    int value;
    list* prev;
    list* next;
    list(int x){
        value=x;
        prev=NULL;
        next=NULL;
    }
    list(){
        value=0;
        prev=NULL;
        next=NULL;
    }
};

class graph{
    public:
        int numNodes;//no.of nodes
        bool **edge;//2d adjacency matrix
        bool *source;//checks if a node is source node
        bool *sink_arr;
        bool **similar_arr;//2d boolean matrix. checks if 2 nodes are similar
        bool **user_similar;// similar nodes from user input
        bool *visited;// checks if a node is visited during dfs
        bool **temp;
        list *collapsed_nodes;
        int *collapsed_from;
        graph(int n,bool **edge_arr, bool **sim_arr, bool *source_arr){
            numNodes=n;
            edge = edge_arr;
            source = source_arr;
            similar_arr=sim_arr;
            user_similar=sim_arr;
            visited = new bool[n];
            for(int i=0;i<n;i++){
                visited[i]=false;
            }
            temp=sim_arr;
            collapsed_from=new int[n];
        }
    
        bool similar(int n1, int n2)
        {
            if(similar_arr[n1-1][n2-1]){return true;}

            //condition3
            int count1=0;
            int count2=0;
            for(int i=0;i<numNodes;i++){
                if(edge[i][n1-1]){
                    count1++;
                    if(i==n2-1){
                        count2++;
                    }
                }
            }
            if(count1==1 and count2==1){return true;}

            //condition1
            if(source[n1-1] and source[n2-1] and user_similar[n1-1][n2-1]==1){
                return true;
            }

            // //condition2
            if(!source[n1-1] and !source[n2-1]){
                for(int m1=1;m1<=numNodes;m1++){
                    if(edge[m1-1][n1-1]){
                        int count=0;
                        
                        for(int m2=1;m2<=numNodes;m2++){
                            if(edge[m2-1][n2-1]){
                                if(similar_arr[m1-1][m2-1]){count++;break;}
                            }
                        }
                        if(count==0){return false;}

                    }
                }
                //viceversa
                for(int m2=1;m2<=numNodes;m2++){
                    if(edge[m2-1][n2-1]){
                        int count=0;
                        
                        for(int m1=1;m1<=numNodes;m1++){
                            if(edge[m1-1][n1-1]){
                                if(similar_arr[m2-1][m1-1]){count++;break;}
                            }
                        }
                        if(count==0){return false;}

                    }
                }
                similar_arr[n1-1][n2-1]=true;
                similar_arr[n2-1][n1-1]=true;
                return true;
            }

            return false;
        }

        //prints source nodes
        void print_source_nodes()
        {
            fout<<"Source nodes: ";
            for(int i=0;i<numNodes;i++){
                if(source[i]){
                    fout<<i+1<<" ";
                }
            }
            fout<<endl;
        }

        // updates similar nodes 2d boolean matrix
        void update_similar_nodes()
        {
            for(int i=1;i<=numNodes;i++){
                for(int j=1;j<=numNodes;j++){
                    if(similar(i,j)){
                        similar_arr[i-1][j-1]=true;
                    }
                }
            }
        }

        void print_similar_nodes()
        {
            fout<<"Similar node pairs: ";
            for(int i=1;i<=numNodes;i++){
                for(int j=1;j<=numNodes;j++){
                    if(similar_arr[i-1][j-1]){
                        fout<<"("<<i<<", "<<j<<") ";
                    }
                }
            }
            fout<<endl;
 
            // creating a undirected graph adjacencylist with edges shown by similar node pairs
            for(int i=0;i<numNodes;i++){
                for(int j=0;j<numNodes;j++){
                    if(similar_arr[i][j]){
                        temp[i][j]=true;
                        temp[j][i]=true;
                    }
                }
            }
        }


        //find a maximum in a component by DFS
        int DFS(int n, int maximum, bool *array)
        {
            array[n-1]=true;
            visited[n-1]=true;
            for(int i=0;i<numNodes;i++){
                if(temp[n-1][i] and !visited[i]){
                    if(i+1>maximum){maximum=i+1;}
                    maximum = max(maximum, DFS(i+1,maximum,array));
                }
            }
            return maximum;
        }

        //collapse graph function
        void collapse()
        {
            int components=0;
            for(int i=1;i<=numNodes;i++){
                if(!visited[i-1]){
                    bool *temp_visited;
                    temp_visited=new bool[numNodes];
                    for(int i=0;i<numNodes;i++){temp_visited[i]=false;}

                    if(collapsed_nodes==nullptr){
                        collapsed_nodes=new list(DFS(i,i,temp_visited));
                        for(int i=0;i<numNodes;i++){
                            if(temp_visited[i]){
                                collapsed_from[i] = collapsed_nodes->value - 1;
                            }
                        }
                    }
                    else{
                        list* tmp;
                        tmp=new list(DFS(i,i,temp_visited));
                        collapsed_nodes->next = tmp;
                        // collapsed_nodes->next=new list(DFS(i,i,temp_visited));
                        for(int i=0;i<numNodes;i++){
                            if(temp_visited[i]){
                                collapsed_from[i] = collapsed_nodes->next->value - 1;
                            }
                        }
                        collapsed_nodes->next->prev=collapsed_nodes;
                        collapsed_nodes=collapsed_nodes->next;
                    }
                    components++;
                    
                }
            }

            fout<<"Collapsed graph:"<<endl;
            fout<<endl;
            fout<<components<<": ";
            while(collapsed_nodes->prev!=NULL){
                fout<<collapsed_nodes->value<<" ";
                collapsed_nodes = collapsed_nodes->prev;
            }
            fout<<endl;

            // checks if we already wrote a edge of collapsed graph
            bool **written;
            written = new bool*[numNodes];
            for(int i=0;i<numNodes;i++){
                written[i] = new bool[numNodes];
                for(int j=0;j<numNodes;j++){
                    written[i][j]=false;//intially intializing everything to false
                }
            }

            for(int i=0;i<numNodes;i++){
                for(int j=0;j<numNodes;j++){
                    if(edge[i][j]){
                        if(!written[collapsed_from[i]][collapsed_from[j]] and collapsed_from[i]!=collapsed_from[j]){
                            fout<<collapsed_from[i]+1<<" "<<collapsed_from[j]+1<<endl;
                            written[collapsed_from[i]][collapsed_from[j]]=true;
                        }
                    }
                }
            }
        }
    
};