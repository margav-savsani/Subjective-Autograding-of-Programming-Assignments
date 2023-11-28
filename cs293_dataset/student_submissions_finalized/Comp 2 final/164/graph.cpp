#include <iostream>
#include <fstream>
using namespace std;

class listOfObjects {
 public:
  int object;
  listOfObjects *next;
  listOfObjects *prev;
  
  // Constructor
  listOfObjects(int initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

class graph
{
    private:
    int *parent_matrix;
    int *adjacency_matrix;
    int *similar_nodes;
    listOfObjects *source_nodes;
    listOfObjects *s_nodes;
    int no_source_nodes;
    int no_nodes;
    ofstream file;
    public:
    graph()
    {
        file.open("outgraph.txt");
        no_source_nodes=0;
        string text;
        cin>>text;
        no_nodes=stoi(text);
        parent_matrix = new int[no_nodes*no_nodes];
        adjacency_matrix = new int[no_nodes*no_nodes];
        similar_nodes = new int[no_nodes*no_nodes];
        source_nodes= new listOfObjects(0);
        s_nodes=source_nodes;
        int source;
        int dest;
        for(int i=0; i<no_nodes*no_nodes; i++)
        {
            parent_matrix[i]=0;
        }
        for(int i=0; i<no_nodes*no_nodes; i++)
        {
            adjacency_matrix[i]=0;
        }
        while (cin>>source)
        {
            if(source==-1)
            {
                cin>>dest;
                break;
            }
            cin>>dest;
            parent_matrix[(dest-1)*no_nodes+source-1]=1;
            adjacency_matrix[(source-1)*no_nodes+dest-1]=1;
        }
        while (cin>>source)
        {
            if(source==-1)
            {
                cin>>dest;
                break;
            }
            cin>>dest;
            similar_nodes[(source-1)*no_nodes+dest-1]=1;
        } 

    }

    bool check_similar(int a ,int b)
    {
        bool check=false;
        for (int i=0; i<no_nodes; i++)
        {
            bool c=false;
            if(parent_matrix[(a)*no_nodes+i]==1)
            {
                for (int j=0; j<no_nodes; j++)
                {
                    if(parent_matrix[b*no_nodes+j]==1)
                    {
                    if(similar_nodes[(i)*no_nodes+j]==1)
                    {
                        c=true;
                        check=true;
                        break;
                    }
                    }
                }
                if(c==false)
                {
                    return false;
                }
            }

        }
        return check;
    }

    void find_sources()
    {
        file<<"Source Nodes: ";
        for(int i=0;i<no_nodes;i++)
        {
            bool b=false;
            for(int j=0;j<no_nodes;j++)
            {
                if(parent_matrix[ i*no_nodes+j]==1)
                {
                    b=true;
                    break;
                }
                
            }
            if(b==false)
                {
                    source_nodes->next=new listOfObjects(i);
                    source_nodes=source_nodes->next;
                    no_source_nodes++;
                    file<<i+1<<" ";
                }
        }
        s_nodes=s_nodes->next;
        file<<endl<<'\n';
    }

    void find_similar()
    {
       for(int i=0;i<no_nodes;i++)
        {
            int no=0;
            int k;
            for(int j=0;j<no_nodes;j++)
            {
                if(parent_matrix[ i*no_nodes+j]==1)
                {
                    no++;
                    k=j;
                    if(no==2)
                    {break;}
                }
                
            }
            if(no==1)
                {
                    similar_nodes[i*no_nodes+k]=1;
                }
        }
        listOfObjects *nodes=s_nodes;
        int length=no_source_nodes;
        while(length!=0)
        {
            int m=0;
            listOfObjects*next_level=new listOfObjects(0);
            listOfObjects*t=next_level;
            for (int i=0; i<length; i++)
            {
                int l=nodes->object;
                for(int j=0;j<no_nodes;j++)
                {
                    if(adjacency_matrix[l*no_nodes+j]==1)
                    {
                        t->next=new listOfObjects(j);
                        t=t->next;
                        m++;
                    }
                    if(check_similar(l,j) && check_similar(j,l))
                    {
                        similar_nodes[l*no_nodes+j]=1;
                        similar_nodes[j*no_nodes+l]=1;
                    }
                }
                nodes=nodes->next;
            }
            length=m;
            nodes=next_level->next;

        }   
    }
    void print_similar()
    {
        file<<"similar_nodes"<<": ";
        for(int i=0; i<no_nodes*no_nodes; i++)
        {
            if(similar_nodes[i]==1)
            {

                file<<"("<<i/no_nodes+1<<", "<<i-(i/no_nodes)*no_nodes+1<<")"<<" ";
            }
        }
        file<<endl<<'\n';
    }

    void collap(int a, int b)
    {if(a!=b){
        int m,n;
        if(a>b)
        {
            m=a;n=b;
        }
        else {n=a;m=b;}
        for(int i=0;i<no_nodes;i++)
        {
            if(adjacency_matrix[n*no_nodes+i]==1)
            {
                adjacency_matrix[m*no_nodes+i]=1;
            }
        }
        for(int i=0;i<no_nodes;i++)
        {
            if(adjacency_matrix[n+no_nodes*i]==1)
            {
                adjacency_matrix[m+no_nodes*i]=1;
            }
        }
        adjacency_matrix[m*no_nodes+m]=0;
        for(int i=0;i<no_nodes;i++)
        {
            adjacency_matrix[n*no_nodes+i]=-1;
        }
        for(int i=0;i<no_nodes;i++)
        {
            adjacency_matrix[n+no_nodes*i]=-1;
        }}
    }
    void update_similar(int a,int b)
    {if(a!=b){
        int m,n;
        if(a>b)
        {
            m=a;n=b;
        }
        else {n=a;m=b;}
        for(int i=0;i<no_nodes;i++)
        {
            if(similar_nodes[n*no_nodes+i]==1)
            {
                similar_nodes[m*no_nodes+i]=1;
            }
        }
        for(int i=0;i<no_nodes;i++)
        {
            if(similar_nodes[n+no_nodes*i]==1)
            {
                similar_nodes[m+no_nodes*i]=1;
            }
        }
        similar_nodes[m*no_nodes+m]=0;
        for(int i=0;i<no_nodes;i++)
        {
            similar_nodes[n*no_nodes+i]=0;
        }
        for(int i=0;i<no_nodes;i++)
        {
            similar_nodes[n+no_nodes*i]=0;
        }}
    }
    void collapse( )
    {
        file<<"Collapsed_graph:"<<endl<<'\n';
        for(int i=0;i<no_nodes;i++)
        {
            for(int j=0;j<no_nodes;j++)
            {
                if(similar_nodes[i*no_nodes+j]==1)
                {
                    update_similar(i,j);
                    collap(i,j);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
                }
            }
        }
        listOfObjects *collapsed_graph=new listOfObjects(0);
        listOfObjects*tmp=collapsed_graph;
        listOfObjects *link=new listOfObjects(0);
        listOfObjects*temp=link;
            int l=0;
        for(int i=0;i<no_nodes;i++)
        {
            bool b=false;
            for(int j=0;j<no_nodes;j++)
            {
                if(adjacency_matrix[i*no_nodes+j]!=-1)
                    {
                        b=true;
                        if(adjacency_matrix[i*no_nodes+j]==1)
                        {
                            temp->next=new listOfObjects(i+1);
                            temp=temp->next;
                            temp->next=new listOfObjects(j+1);
                            temp=temp->next;
                        }
                    }
            }
            if(b){tmp->next=new listOfObjects(i+1);l++;tmp=tmp->next;}
        }
        collapsed_graph=collapsed_graph->next;
        file<<l<<":";
        while(collapsed_graph!=nullptr)
        {
            file<<collapsed_graph->object<<" ";
            collapsed_graph=collapsed_graph->next;
        }
        file<<endl;
        link=link->next;
        while(link!=nullptr)
        {
            file<<link->object<<" "<<link->next->object<<endl;
            link=link->next->next;
        }
    }
};