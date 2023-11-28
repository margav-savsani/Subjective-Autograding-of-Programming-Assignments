#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;

void Graph::DFS(int i){ 
   
   v[i]=1;
   listOfObjects<int>* edge = nodes[i].outedge;
   while(edge->next!=NULL){
       if (v[edge->next->object]==0) 
            DFS(edge->next->object); 
       
       edge=edge->next;
     }  
}           

void Graph::modifiedDFS() {
  for(int i=0; i<numNodes; i++)
     {
        cl[i]=0;
        v[i]=0;
        source[i]=0;
      }  
  while(true){
    int a = 0;
    int i;
    for(i=0; i<numNodes; i++)   
       if(v[i]==0) {a=1;break;}
    if(a==0) break;
    source[i]=1;
    DFS(i); 
   }  
  return;
}

void Graph::add(int i, int j,int &x){
  // adds j to the similarity list of i
      listOfObjects<int>* s = nodes[i].Similar;
      int a=0;
      while(s!=NULL){
	 if(s->object==j)
	  {
	    a = 1; 
	    break;
	   }   
	 if(s->next==NULL) break;  
	   s=s->next;
	}
        if(a!=1)
        {
         x++;  
        s->next = new listOfObjects<int> (j);
        }
}  

void Graph::Similarity(int &x){
        // checks similarity pairs and adds them into respective similarity lists 
   for(int i=0; i<numNodes; i++)
    for(int j=i+1; j<numNodes; j++)
      {
            int c=0,d=0;
             listOfObjects<int>* edgei = nodes[i].inedge;
             while(edgei->next!=NULL)
              {
                 if(edgei->next->object==j) c=1;
                 else {c=0;break;}
                 edgei=edgei->next;
               }
             if(c==1) add(i,j,x);
             
            listOfObjects<int>* edgej = nodes[j].inedge; 
	  while(edgej->next!=NULL)
	   {
	      if(edgej->next->object==i) d=1;
	       else {d=0;break;}
	       edgej=edgej->next;
	     }          
            if(d==1) add(j,i,x);
                       
       if(source[i]!=1 && source[j]!=1)    
          if(c==0)
           {
             int b=0;
             listOfObjects<int>* ei = nodes[i].inedge;
             while(ei->next!=NULL)
              {
                int a=0;
                listOfObjects<int>* ej = nodes[j].inedge;
                while(ej->next!=NULL)
                 {
                       listOfObjects<int>* s = nodes[ei->next->object].Similar;
                       while(s->next!=NULL)
                        {
                          if(s->next->object == ej->next->object) {a=1; break;}
                          s=s->next;
                         } 
                     if(a==1) break;
                     ej=ej->next;
                    } 
                   if(a==0) {b=1;break;}
                    ei=ei->next;
                  }
     
            listOfObjects<int>* ej = nodes[j].inedge;   
            while(ej->next!=NULL)
             {
                int a=0;
                listOfObjects<int>* ei = nodes[i].inedge;
                while(ei->next!=NULL)
                 {
                       listOfObjects<int>* s = nodes[ej->next->object].Similar;
                       while(s->next!=NULL)
                        {
                          if(s->next->object == ei->next->object) {a=1; break;}
                          s=s->next;
                         }
                     if(a==1) break;
                     ei=ei->next;
                    } 
                   if(a==0) {b=1;break;}
                    ej=ej->next;
                  }                   
              if(b==0)
               {
                 add(i,j,x);
                 add(j,i,x);    
                } 
            }        
    }
}  

void Graph::Class(int i, int j){

     // adds elements into equivalance classes
   if(cl[i]==1) return;

     listOfObjects<eq *>* EQ = classes;
     while(EQ->next!=NULL)
        {
          if(EQ->next->object->l[i]==1) break;
          EQ=EQ->next;
          }
     listOfObjects<int>* s = nodes[i].Similar;
     while(s->next!=NULL)
       {
         EQ->next->object->l[s->next->object]=1;
         if(j!=s->next->object)
           {
             Class(s->next->object,i);
             cl[s->next->object]=1;
            } 
          s=s->next;	
        }                        
}            


void Graph::printResults() {

  // printing Source nodes
   cout<<"Source nodes:";
   for(int i=0; i<numNodes; i++)
     if(source[i]==1) cout<<" "<<i+1;
     cout<<endl; 
  

   
   int n=0;
  // adding similar source nodes to the corresponding Similar lists
  for(int i=0; i<numNodes; i++)
    {
      if(source[i]==1)
        {
              listOfObjects<int>* s1 = nodes[i].Similar;
              listOfObjects<int>* s = nodes[i].sim;
  	    while(s->next!=NULL){
        	        if(source[s->next->object]==1)
                       add(i,s->next->object,n);
        	      s=s->next;
        	    } 
      }  	     
  } 
    
   while(true)
   {
     int m=n;
     Similarity(n);
     if(m==n) break;
    } 
     
   // printing Similar node pairs     
   cout<<"Similar node pairs:";
   for(int i=0; i<numNodes; i++)
     {
       listOfObjects<int>* s = nodes[i].Similar;
       while(s->next!=NULL)
         {
           cout<<" ("<<i+1<<", "<<s->next->object+1<<")";
           s=s->next;
          } 
      }  
  cout<<endl;
  
  while(true)
   {
     int m=n;
     Similarity(n);
     if(m==n) break;
    } 
    
     // seperating elements into equivalance classes
     while(true){
    int a = 0;
    int i;
    for(i=0; i<numNodes; i++)   
       if(cl[i]==0) {a=1;break;}
    if(a==0) break;
    
   listOfObjects<eq *>* EQ = classes;
   while(EQ->next!=NULL)
    EQ=EQ->next; 
   eq* C = new eq(numNodes);
   
   C->l[i]=1; 
   listOfObjects<eq *>* EQ2 = classes;
   int l=0;
   for(int i=0;i<numNodes;i++)
     {
       if(EQ->object->l[i]==1)
       while(EQ2->next!=NULL){
         if(EQ2->next==EQ) break;
         if(EQ2->next->object->l[i]==1) 
            { 
               l=1;
               break;
               
               } 
          EQ2=EQ2->next;  
        }
       if(l==1) break; 
      }  
     if(l==1){ 
      for(int i=0;i<numNodes;i++)
         if(EQ->object->l[i]==1) EQ2->next->object->l[i]=1;
       EQ->object=C;   
        }                 
   else      
     EQ->next=new listOfObjects<eq *>(C);
   Class(i,-10);
   cl[i]=1;          
   }  
   
  // if the last equivalance class have same elements as the elements of previous class we add 
  //elements of last class into this previous class   
   listOfObjects<eq *>* EQ5 = classes;
   while(EQ5->next!=NULL)
     EQ5=EQ5->next; 
   listOfObjects<eq *>* EQ6 = classes;
   int e=0;
   for(int i=0;i<numNodes;i++)
     {
       if(EQ5->object->l[i]==1)
       while(EQ6->next!=NULL){
         if(EQ6->next==EQ5) break;
         if(EQ6->next->object->l[i]==1) 
            { 
               e=1;
               break;
               
               } 
          EQ6=EQ6->next;  
        }
       if(e==1) break; 
      }  
     if(e==1){ 
       for(int i=0;i<numNodes;i++)
         if(EQ5->object->l[i]==1) EQ6->next->object->l[i]=1;
         eq* C = new eq(1);
         C->l[0]=0;
         EQ5->object=C;  
        }    
   
   // printing Collapsed graph and the edges 
   
   cout<<"Collapsed graph:"<<endl;  
   int p=0;
   listOfObjects<eq *>* EQ = classes;
   while(EQ->next!=NULL){
      for(int i=0;i<numNodes;i++)
        if(EQ->next->object->l[i]==1)
           if(i>EQ->next->object->max) EQ->next->object->max=i;
        if(EQ->next->object->max!=-1) p++;    
       EQ=EQ->next;
     }
   cout<<p<<":";
   listOfObjects<eq *>* EQ1 = classes;
   while(EQ1->next!=NULL){
        if(EQ1->next->object->max!=-1)
          cout<<" "<<EQ1->next->object->max+1;
       EQ1=EQ1->next;
     }     
   cout<<endl;
   
  listOfObjects<eq *>* EQ3 = classes;
  while(EQ3->next!=NULL)
     {
         if(EQ3->next->object->max==-1) {EQ3=EQ3->next;continue;}
         listOfObjects<eq *>* EQ4 = classes;
         while(EQ4->next!=NULL)
          {
            if(EQ4->next->object->max==-1) {EQ4=EQ4->next;continue;}
            if(EQ4->next == EQ3->next) {EQ4=EQ4->next;continue;}
            int q=0;
            for(int i=0;i<numNodes;i++)
              {
                for(int j=0;j<numNodes;j++)
                  if(EQ4->next->object->l[i]==1 && EQ3->next->object->l[j]==1){
                  listOfObjects<int>* edge = nodes[j].outedge;
                  while(edge->next!=NULL)
                   {
                     if(edge->next->object==i) 
                      {
                        q=1;
                        cout<<EQ3->next->object->max+1<<" "<<EQ4->next->object->max+1<<endl;
                        break;
                       }
                      edge=edge->next; 
                     }
                    if(q==1) break;
                    }
                  if(q==1) break;
                 }
                EQ4=EQ4->next;
               }
             EQ3=EQ3->next;           
        }   
}

#endif
