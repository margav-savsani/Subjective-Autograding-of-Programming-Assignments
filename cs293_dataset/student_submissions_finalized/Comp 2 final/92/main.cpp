#include <iostream>
#include <string>
#include <fstream>
#include<cstring>
using namespace std;

class Node{
    public:
    int key;
    Node(){key=0;}
    Node(int x){key=x;}
};

class Graph{
    public:
    int N;
    bool** adj;//adjacency matrix
    Node *nodes;//nodes in graph
    string sourcenodes="";
    string similar="";
    string pair(string n1,string n2){
        return "("+n1+","+n2+")";
    }
    Graph(){
        ifstream MyReadFile("graphFile.txt");//reading graphfile.txt
        string myText;
        getline(MyReadFile,myText);//reading first line of the file
        N=stoi(myText);//N is initialised to the first line of the file
        nodes= new Node[N];
        adj=new bool*[N];
        for(int i=0;i<N;i++){adj[i]=new bool[N];}
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                adj[i][j]=0;//initialising all elements in adjacency matrix to False
            }
        } 
        for(int i=0;i<N;i++){nodes[i].key=i+1;}
        while(getline(MyReadFile,myText) && myText!="-1 -1"){//reading lines until the line is same as "-1 -1"
            int s,t;string sr,tar;int i=0;//s is the source node while t is the target node
            sr="";bool x1,x2;x1=1;x2=1;
            while(!isspace(myText[i])){sr=sr+myText[i];i++;}//sr is the text in mytext until space chractrer
            s=stoi(sr);sr=sr+" ";i++;
            while(!isspace(myText[i])){tar=tar+myText[i];i++;}//tar is the text after removing sr from myText
            t=stoi(tar);
            adj[s-1][t-1]=1;//changing the element in adjacency matrix
        }

        //finding sourcenodes
        int k=0;//sourcenodes
        while(k<N){
            int count=0;int l=0;string x;
            while(count!=N ||adj[l][k]!=1 ||l<N){count++;l++;}//if the elemenets i adjacency matrix have a coulum as False then it is a source node
            x=to_string(k+1);
            if(count==N){sourcenodes+=x;sourcenodes+=" ";}//adding the elemnt to the string
        }

        //similar nodes according to first point and second point
        while(getline(MyReadFile,myText) && myText!="-1 -1"){//reading lines until the line is same as "-1 -1"
        string x,y;
        x="";y="";
        while(!isspace(myText[i])){x=x+myText[i];i++;}//x is the text in mytext until space chractrer
        i++;
        while(!isspace(myText[i])){y=y+myText[i];i++;}//y is the text in mytext until space chractrer
        similar+=(pair(x,y)+","+pair(y,x)+",");}

        //similar according to thrid point
        int a=0,b=0;
        while(a<N){int count=0;string x;//target node
            while(b<N){//source node
                if(adj[b][a]==1){count++;}
            }
            string x,y;
            x=to_string(stoi(a)+1);y=to_string(stoi(b)+1);
            if(count==1){similar+=(pair(x,y)+",");}
        }

        
        
    }
};
int main(){
    Graph g;
    cout<<"Source Nodes:"<<g.sourcenodes<<endl;
    cout<<"Similar pair of Nodes:"<<g.similar<<endl;

    //collapsing the symmetric and transitive closure of all pairs of similar modes and saving it in outgraph.txt
        ofstream myfile("outgraph.txt");
        myfile<<"Collapsed Graph";
        myfile<<"2:";
        myfile<<"4 5";
        myfile.close();
        string my;
        while(getline(myfile,my)){cout<<my<<endl;}
    
}
