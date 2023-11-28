#include "Graph.h"
using namespace std;

DirectedGraph::DirectedGraph(int v)
{
    nodes=new Node[v];
    isSource=new bool[v]{false};
    similar=new bool*[v];
    for (int i=0;i<v;i++)
        similar[i]=new bool[v]{false};
    visited=new bool[v]{false};
    classes=nullptr;
    num=v;
}
void DirectedGraph::AddEdge(int v,int u)
{
    if (nodes[v].tonodes == nullptr)
    {
        nodes[v].tonodes=new listOfObjects(u);
    }
    else
    {
        listOfObjects<int> *sample=new listOfObjects<int>(u);
        sample->next=nodes[v].tonodes;
        sample->next->prev=sample;
        nodes[v].tonodes=sample;
    }
    if (nodes[u].fromnodes == nullptr)
    {
        //cout<<v+1<<" "<<u+1<<endl;
        nodes[u].fromnodes=new listOfObjects(v);
    }
    else
    {
        //cout<<v+1<<" "<<u+1<<endl;
        listOfObjects<int> *sample=new listOfObjects<int>(v);
        sample->next=nodes[u].fromnodes;
        sample->next->prev=sample;
        nodes[u].fromnodes=sample;
    }
}
void DirectedGraph::printSourcenode()
{
    cout<<"Source node: ";
    for (int i=0;i<num;i++)
    {
        if (nodes[i].fromnodes == nullptr)
        {
            cout<<i+1<<" ";
            isSource[i]=true;
        }
    }
    cout<<endl;
}

void DirectedGraph::SimilarNode()
{
    for (int i=0;i<num;i++)
    {
        if (nodes[i].fromnodes != nullptr)
        {
            if ( nodes[i].fromnodes->next == nullptr)
            {
                //cout<<i+1<<" "<<nodes[i].fromnodes->object+1<<endl;
                if (nodes[i].similar == nullptr)
                {
                    nodes[i].similar=new listOfObjects<int> (nodes[i].fromnodes->object);
                    similar[i][nodes[i].fromnodes->object]=true;
                }
                else
                {
                    listOfObjects<int> *sample=new listOfObjects<int> (nodes[i].fromnodes->object);
                    sample->next=nodes[i].similar;
                    sample->next->prev=sample;
                    nodes[i].similar=sample;
                    similar[i][nodes[i].fromnodes->object]=true;
                }
                if (nodes[i].symsimilar == nullptr)
                    nodes[i].symsimilar=new listOfObjects<int>(nodes[i].fromnodes->object);
                else
                {
                    listOfObjects<int> *sample=new listOfObjects<int> (nodes[i].fromnodes->object);
                    sample->next=nodes[i].symsimilar;
                    sample->next->prev=sample;
                    nodes[i].symsimilar=sample;
                }
                if (nodes[nodes[i].fromnodes->object].symsimilar == nullptr)
                    nodes[nodes[i].fromnodes->object].symsimilar=new listOfObjects<int>(i);
                else
                {
                    listOfObjects<int> *sample=new listOfObjects<int> (i);
                    sample->next=nodes[nodes[i].fromnodes->object].symsimilar;
                    sample->next->prev=sample;
                    nodes[nodes[i].fromnodes->object].symsimilar=sample;
                }
            }
        }
    }
    for (int i=0;i<num;i++)
        for (int j=i+1;j<num;j++ )
        {
            if (isSimilar(i,j) && !similar[i][j] && !similar[j][i] && !(isSource[i] || isSource[j]))
            {
                //cout<<i<<" "<<j<<endl;
                if (nodes[i].similar == nullptr)
                {
                    nodes[i].similar=new listOfObjects<int> (j);
                    similar[i][j]=true;
                }
                else
                {
                    listOfObjects<int> *sample=new listOfObjects<int> (j);
                    sample->next=nodes[i].similar;
                    sample->next->prev=sample;
                    nodes[i].similar=sample;
                    similar[i][j]=true;
                }
                if (nodes[j].similar == nullptr)
                {
                    nodes[j].similar=new listOfObjects<int> (i);
                    similar[j][i]=true;
                }
                else
                {
                    listOfObjects<int> *sample=new listOfObjects<int> (i);
                    sample->next=nodes[j].similar;
                    sample->next->prev=sample;
                    nodes[j].similar=sample;
                    similar[j][i]=true;
                }
                if (nodes[i].symsimilar == nullptr)
                    nodes[i].symsimilar=new listOfObjects<int>(j);
                else
                {
                    listOfObjects<int> *sample=new listOfObjects<int> (j);
                    sample->next=nodes[i].symsimilar;
                    sample->next->prev=sample;
                    nodes[i].symsimilar=sample;
                }
                if (nodes[j].symsimilar == nullptr)
                    nodes[j].symsimilar=new listOfObjects<int>(i);
                else
                {
                    listOfObjects<int> *sample=new listOfObjects<int> (i);
                    sample->next=nodes[j].symsimilar;
                    sample->next->prev=sample;
                    nodes[j].symsimilar=sample;
                }
            }
        }
}

bool DirectedGraph::isSimilar(int node1,int node2)
{
    if (similar[node1][node2])
        return true;
    if (isSource[node1] || isSource[node2])
        return false;
    listOfObjects<int> *list1=nodes[node1].fromnodes;
    if (list1 == nullptr || nodes[node2].fromnodes == nullptr)
        return false;
    int len1=0,len2=0;
    while(list1 != nullptr)
    {
        len1++;
        len2=0;
        bool ch=false;
        listOfObjects<int> *list2=nodes[node2].fromnodes;
        while(list2 != nullptr)
        {
            //cout<<list1->object<<" "<<endl;
            if (isSimilar(list1->object,list2->object))
            {
                //cout<<list1->object<<" "<<endl;
                ch=true;
            }
            list2=list2->next;
            len2++;
        }
        if (!ch)
            return false;
        list1=list1->next;
    }
    if (len1 != len2)
        return false;
    return true;
}
void DirectedGraph::printsimlarpairs()
{
    cout<<"Similar node pairs: ";
    for(int i=0;i<num;i++)
    {
        listOfObjects<int> *sample=nodes[i].similar;
        if (sample != nullptr)
        {
            while(sample != nullptr)
            {
                cout<<"("<<i+1<<", "<<sample->object+1<<") ";
                sample=sample->next;
            }
        }
    }
    cout<<endl;
}
void DirectedGraph::getclasses()
{
    for (int i=0;i<num;i++)
    {
        if (visited[i] == false)
        {
            visited[i]=true;
            if (classes == nullptr)
            {
                listOfObjects<int> *s=new listOfObjects<int>(i);
                listOfObjects<int> *sample=nodes[i].symsimilar;
                while(sample != nullptr)
                {
                    if (visited[s->object]==false)
                        DFS(sample->object,s);
                    sample=sample->next;
                }
                cout<<endl;
                classes=new listOfObjects< listOfObjects<int>* >(s);
            }
            else
            {
                listOfObjects<int> *sample=new listOfObjects<int> (i);
                listOfObjects<int> *s=nodes[i].symsimilar;
                while(s != nullptr)
                {
                    if (visited[s->object] == false)
                    {
                        DFS(s->object,sample);
                    }
                    s=s->next;
                }
                listOfObjects<listOfObjects<int>* > *samp=new listOfObjects<listOfObjects<int>* >(sample);
                samp->next=classes;
                samp->next->prev=samp;
                classes=samp;
            }
        }
    }
}

void DirectedGraph::DFS(int v,listOfObjects<int> *l)
{
    listOfObjects<int> *sample=nodes[v].symsimilar;
    listOfObjects<int> *s=new listOfObjects<int> (v);
    if (visited[v] == false)
    {
        s->next=l;
        s->next->prev=s;
        l=s;
    }
    visited[v]=true;
    while(sample != nullptr)
    {
        if (visited[sample->object] == false)
        {
            DFS(sample->object,l);
        }
        sample=sample->next;
    }
}

void DirectedGraph::printclasses()
{
    int num=0;
    listOfObjects<listOfObjects<int>* > *sample=classes;
    listOfObjects<int> *names;
    while(sample != nullptr)
    {
        num++;
        listOfObjects<int> *s=sample->object;
        int m= s->object;
        while (s != nullptr)
        {
            if (m < s->object)
                m=s->object;
            //cout<<s->object<<" "<<m<<endl;
            s=s->next;
        }
        if (names == nullptr)
        {
            names=new listOfObjects<int> (m);
        }
        else
        {
            listOfObjects<int> *samp=new listOfObjects<int> (m);
            samp->next=names;
            samp->next->prev=samp;
            names=samp;
        }
        sample=sample->next;
    }
    cout<<"Collapsed graph:"<<endl;
    cout<<num<<": ";
    listOfObjects<int> *l=names;
    cout<<names->next->object<<endl;
    while(l != nullptr)
    {
        cout<< l->object+1<<" ";
        l=l->next;
    }
    cout<<endl;
}

