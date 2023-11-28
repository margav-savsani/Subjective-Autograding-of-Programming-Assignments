#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <cmath>
#include "main.h"
using namespace std;



bool f:: similar(int n1,int n2){

if (source[n1-1]==1 && source[n2-1]==1){
 pairs* l=Similarity;
  while(l!=nullptr){
   if (l->p1==n1 && l->p2==n2) return true;
   l=l->next;
  }
  return false;
}      // this for case 1 when both are source nodes and if they are present in the similarity linked list then they are similar
if (node[n1-1].prev!=nullptr){
if (node[n1-1].prev->value==n2 && node[n1-1].prev->prev==nullptr){return true;}} 
//this is for case3 where the only incoming edge to n1 is from n2 

if (source[n1-1]==0 && source[n2-1]==0){
    Node* m1=node[n1-1].prev;
    bool check=0;
    while(m1!=nullptr){
        check=0;
        Node* m2=node[n2-1].prev;
        while(m2!=nullptr){
            if (similar(m1->value,m2->value)){check=1;}
            m2=m2->prev;
        }
        if (!check) {return false;}
        m1=m1->prev;
    }
   Node* m2=node[n2-1].prev;
    check=0;
    while(m2!=nullptr){
        check=0;
         Node *m1=node[n1-1].prev;
        while(m1!=nullptr){
            if (similar(m2->value,m1->value)){check=1;}
            m1=m1->prev;
        }
        if (!check) {return false;}
        m2=m2->prev;
    }
   return true; 
}

return false;
};


int main(int argc, char *argv[]) {
f h; //declaring class f 
string line;
int i=1; //counts the line number
int k=1;
int n1=0;
 int n2=0;
 int started=0;
int pair1;
int pair2;
int** edgematrix; //edgematrix of graph
while(getline(cin, line)){    //reading lines from input text

  if (i==1) {
    h.numNodes=stoi(line);
    h.source=new bool[h.numNodes]; //creating a source array of type bool and size num of nodes which is true if the node is source node
    h.node= new Node[h.numNodes];  //creating array of type node
     edgematrix= new int*[h.numNodes];
     for(int j=0;j<h.numNodes;j++){
        edgematrix[j]=new int[h.numNodes];
     }

    for (int j=0;j<h.numNodes;j++){
        for (int c=0;c<h.numNodes;c++){
            edgematrix[j][c]=0;
        }
    } 

    for (int j=0;j<h.numNodes;j++){
        h.source[j]=1;     //intially all are set to true and if there is an incoming edge to the node then im setting it to false
        h.node[j].value=j+1; //value of nodes are 1 to numnodes
    }
  }   // if it is the first line of the file which has number of nodes
  if (i!=1){ // this is for second line onwards  which also reads words in the line
    istringstream iss(line);
    k=1;
    do {
        string word;
        iss >> word;
        if(word=="-1") {started=1;} //until word is -1 the lines contains edges of graph
        if (started!=1){ //edges
           if (k==1){n1=stoi(word);}
           if (k==2){
                h.source[stoi(word)-1]=0;
                n2=stoi(word);
                edgematrix[n1-1][n2-1]=1;
                Node *x=&h.node[n1-1];
                while(x->next!=nullptr){
                x=x->next;
                }
                Node* y= new Node(n2);
                x->next=y;
                y->prev=x;
                x=&h.node[n2-1];
                while(x->prev!=nullptr){
                x=x->prev;
                }
                Node* z= new Node(n1);
                x->prev=z;
                z->next=x;
            } //forming incoming and outgoing adjanceny lists for nodes
         }
     
   if (started==1 && word!="-1" && word!=""){ //when line is after -1 -1 then it contains the similar node paies
        if (k==1) pair1=stoi(word);
        if (k==2) {
            pair2=stoi(word);            
            pairs* v=new pairs(pair1,pair2); 
            pairs* s= h.Similarity;
            if (s->p1==0){
               s->p1=pair1;
               s->p2=pair2;
            }
            else{
             while (s->next!=nullptr){
              s=s->next;
            }
             s->next=v;
            } 

        }
        }//storing pairs to Similarity linked list
        
        k++;
    } while (iss);
     }
   i=i+1;
} 
ofstream Myfile("outgraph.txt"); 
Myfile<<"Source nodes: ";
for(int x=0;x<h.numNodes;x++){
    if (h.source[x]==1){
        Myfile<<x+1<<" ";
    }
}
Myfile<<endl<<endl;

int a1[50];
int a2[50];
int a3[h.numNodes];
k=0;

Myfile<<"Similar node pairs: ";
for (int x=1;x<h.numNodes+1;x++){
 for (int j=1;j<h.numNodes+1;j++){
  if (h.similar(x,j)){ Myfile<<"("<<x<<", "<<j<<") "; a1[k]=x; a2[k]=j;k++;}
}
}
Myfile<<endl;
int total = 0;
i = 0;
while(i < k)
{
    int j = 0;
    while(j < total)
    {
        if(a1[i] == a3[j]) break;
        j++;
    }
    if(j == total) {a3[total] = a1[i]; total++;}
    i++;
}
i = 0;
while(i < k)
{
    int j = 0;
    while(j < total)
    {
        if(a2[i] == a3[j]) break;
        j++;
    }
    if(j == total) {a3[total] = a2[i]; total++;}
    i++;
}

Myfile<<endl;


int parent[h.numNodes];
for(int p=0; p<h.numNodes; p++)
{
    parent[p] = 0;
}

i = 0;
int j;
while(i != k)
{
  if(a1[i] == a2[i])
  {
    i++;
    continue;
  }
  for(j = 0; j<k; j++)
  {
    if(a2[i] == a1[j])
    {
        int a=a1[i], b=a2[i], c=a2[j];
        int collapse = max(a, b);
        collapse = max(collapse, c);
        if(a != collapse) parent[a - 1] = collapse;
        if(b != collapse) parent[b - 1] = collapse;
        if(c != collapse) parent[c - 1] = collapse;
        for(int p=0; p<k; p++)
        {
            if(a1[p]==a || a1[p]==b || a1[p]==c)
            {
                a1[p] = collapse;
            }
            if(a2[p]==a || a2[p]==b || a2[p]==c)
            {
                a2[p] = collapse;
            }
        }
        break;
    }
  }
  if(j == k) i++;
  else i = 0;
} //replacing with collapsed nodes


for(int p=0; p<h.numNodes; p++)
{
    if(parent[p] != 0){
    while(parent[parent[p]-1] != 0)
    {
        parent[p] = parent[parent[p]-1];
    }
    }
    else{
        parent[p] = p+1;
    }
}

//parent array contains nodes to which they are collapsed

bool isthere[h.numNodes]; //array representing collapsed nodes
for(int p=0; p<h.numNodes; p++)
{
    isthere[p] = true;
}
for(int p=0; p<total; p++)
{
    isthere[a3[p]-1] = false;
}
for(int p=0; p<k; p++)
{
    isthere[a1[p]-1] = true;
}

int count=0;
for(int p=0; p<h.numNodes; p++)
{
    if(isthere[p]) count++;
}

 
Myfile<<"Collapsed graph:"<<endl<<endl;
Myfile<<count<<": ";

int collapsednodes[count]; //contains index at which it is stored in collapsematrix 
int index=0;
for(int p=0; p<h.numNodes; p++)
{
    if(isthere[p])
    {  
        collapsednodes[index]=p+1;
        h.node[p].value=index;  
        index++;
        Myfile<<p+1<<" ";
        
    }
}
Myfile<<endl;
int collapsematrix[count][count];
for(int j=0;j<count;j++){
    for (int c=0;c<count;c++){
      collapsematrix[j][c]=0;  
    }
}


for (int j=0;j<h.numNodes;j++){
    for(int c=0;c<h.numNodes;c++){
        if (edgematrix[j][c]==1 && (parent[j]!=parent[c]) ){
            
                collapsematrix[h.node[parent[j]-1].value][h.node[parent[c]-1].value]=1;
        }
        
    }
}

for(int j=0;j<count;j++){
    for(int c=0;c<count;c++){

        if (collapsematrix[j][c]==1){
            Myfile<<collapsednodes[j]<<" "<<collapsednodes[c]<<endl;
        }
    }
}
 
Myfile.close();
return 0;    
}