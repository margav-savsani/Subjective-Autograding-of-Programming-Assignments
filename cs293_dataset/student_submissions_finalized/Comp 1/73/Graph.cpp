#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::DFS(int v1,BST *t,int v,bool *back,listOfObjects<int> *stc)
{
  if (nodes[v1].visited == 2) //retrun
    return;
  if (nodes[v1].visited == 1)
  {//it is in cycle if it is already visited
    listOfObjects<int> *s=stc;
    while(s != nullptr)
    {
      if (s->object==v1)
      {
        numcycle++;
        break;
      }
      s=s->next;
    }
  }
  nodes[v1].visited++;//incr the visit num
  listOfObjects<int> *sample=nodes[v1].adj;
  t->insert(nodes[v1].value);
  while(sample != nullptr)
  {
    if ( sample->object != v && back[sample->object]== false)
    {//checking for all except the parent and backededge
      listOfObjects<int> *s=stc;
      while (s->next != nullptr)
      {
        s=s->next;
      }
      s->next=new listOfObjects<int>(sample->object);
      s->next->prev=s;
      DFS(sample->object,t,v1,back,stc);
      back[sample->object]=true;
      s->next=nullptr;
    }
    sample=sample->next;
  }
}
void Graph::modifiedDFS() {
  bool backtraced[numNodes]={false};
  listOfObjects<int> *stack;
  for (int i=0;i<numNodes;i++)
  {
    if (nodes[i].visited==0)//new connected graph
    {
      numconnected++;
      if (trees == nullptr)//if nullptr
      {
        nodes[i].visited++;
        trees=new listOfObjects<BST> (new TreeNode(nodes[i].value));
        listOfObjects<int> *sample=nodes[i].adj;
        stack=new listOfObjects<int> (i);//dfs
        if (nodes[i].adj->next != nullptr)
        {
          stack->next=new listOfObjects<int> (i);
          stack->next->prev=stack;
        }
        while(sample != nullptr)
        {
          if ( nodes[sample->object].visited < 2 )
          {
            stack->next=new listOfObjects<int> (sample->object);
            stack->next->prev=stack;
            DFS(sample->object,&trees->object,i,backtraced,stack->next);
            backtraced[sample->object]=true;
            stack->next=nullptr;
          }
          //backtraced[i]=true;
          sample=sample->next;
        }
        stack->next=nullptr;
      }
      else
      {
        nodes[i].visited++;
        listOfObjects<BST> *sample1=trees;
        while (sample1->next != nullptr)
        {
          sample1=sample1->next;
        }
        sample1->next=new listOfObjects<BST> (new TreeNode(nodes[i].value));
        sample1->next->prev=sample1;
        listOfObjects<int> *sample=nodes[i].adj;
        stack=new listOfObjects<int> (i);
        if (nodes[i].adj->next != nullptr)
        {
          stack->next=new listOfObjects<int> (i);
          stack->next->prev=stack;
        }
        while(sample != nullptr)
        {
          if ( nodes[sample->object].visited < 2 )
          {
            stack->next=new listOfObjects<int> (sample->object);
            stack->next->prev=stack;
            DFS(sample->object,&sample1->object,i,backtraced,stack->next);
            backtraced[sample->object]=true;
            stack->next=nullptr;
          }
          //backtraced[i]=true;
          sample=sample->next;
        }
        stack->next=nullptr;
      }
    } 
  }
  return;
}

void Graph::printResults() 
{
  //num of connected comp
  cout<<"No. of connected components: "<<numconnected<<endl;
  for (int i=0;i<numNodes;i++)
  {
    if(nodes[i].visited == 1)
      num1++;//visited once
    if(nodes[i].visited == 2)
      num2++;//twice
  }
  if (num1<0)
    num1=0;
  if (num2<0)
    num2=0;
  cout<<"No. of nodes visited once: "<<num1<<endl;
  cout<<"No. of nodes visited twice: "<<num2<<endl;
  if (numcycle<0)
    numcycle=0;
  cout<<"No. of nodes that are present in a cycle: "<<numcycle<<endl;
  listOfObjects<BST> *sample=trees;
  while (sample != nullptr)
  {//printing all bsts
    sample->object.printBST(" ");
    sample=sample->next;
  }
  
  return;
}

#endif
//by saran 210050036