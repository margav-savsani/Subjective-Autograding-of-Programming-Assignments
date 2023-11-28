#include "Graph.h"
void Graph::insert(int a, int b){
    nodes[a].toNode.push_back(b);
    nodes[b].fromNode.push_back(a);
    nodes[b].isSource = false;
}

void Graph::sourceNodes(){
    file << "Source Nodes: " << endl;
    for(int i = 0;i<numNodes;i++){
        if(nodes[i].isSource){
            file << i+1 << " ";
        }
    }
    file << endl;
    return;
}

void Graph::setsimilar(int a, int b){
    if(nodes[a].isSource && nodes[b].isSource){
        leftSim.push_back(a);
        RightSim.push_back(b);
    }
}

void Graph::similarNodes()
{
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].fromNode.size() == 1)
        {
            leftSim.push_back(i);
            RightSim.push_back(nodes[i].fromNode.get(0));
        }
    }
    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            if (!nodes[i].isSource && !nodes[j].isSource)
            {
                vector<bool> c1;
                vector<bool> c2;
                for (int k=0;k<nodes[i].fromNode.size();k++)
                {
                    for (int l=0;l<nodes[j].fromNode.size();l++)
                    {
                        for (int s = 0;s<leftSim.size();s++)
                        {
                            if (leftSim.get(s) == (nodes[i].fromNode).get(k) && RightSim.get(s) == nodes[j].fromNode.get(l))
                            {
                                c1.push_back(true);
                            }
                            else
                            {
                                c1.push_back(false);
                            }
                        }
                    }
                }

                for (int k=0;k<nodes[j].fromNode.size();k++)
                {
                    for (int l=0;l<nodes[i].fromNode.size();l++)
                    {
                        for (int s = 0;s<leftSim.size();s++)
                        {
                            if (leftSim.get(s) == (nodes[i].fromNode).get(k) && RightSim.get(s) == nodes[j].fromNode.get(l))
                            {
                                c2.push_back(true);
                            }
                            else
                            {
                                c2.push_back(false);
                            }
                        }
                    }
                }
                int count1 = 0;
                int count2 = 0;
                for (int k = 0; k < c1.size(); k++)
                {
                    if (c1[k])
                    {
                        count1++;
                    }
                }
                for (int k = 0; k < c2.size(); k++)
                {
                    if (c2[k])
                    {
                        count2++;
                    }
                }
                if (count1 >= nodes[i].fromNode.size() && count2 >= nodes[j].fromNode.size())
                {
                    bool f = false;
                    for(int o=0;o<leftSim.size();o++){
                        if(leftSim.get(o) == nodes[i].value-1 && RightSim.get(o) == nodes[j].value-1){
                            f = true;
                            break;
                        }
                    }
                    if(!f){
                        leftSim.push_back(i);
                        RightSim.push_back(j);
                    }
                }
            }
        }
    }
    file << "Similar Nodes: " << endl;
    for(int i=0;i<leftSim.size();i++){
        file << "(" << leftSim.get(i)+1 << " " << RightSim.get(i)+1 << ") ";
    }
    file << endl;
}

