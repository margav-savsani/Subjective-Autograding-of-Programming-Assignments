#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
// Add code as appropriate for your implementation
bool find_obj(listOfObjects<Edge> *edgelist, Edge e)
{
  listOfObjects<Edge> *ptr = edgelist;
  while (ptr != nullptr)
  {
    if (ptr->object.isEqual(e))
    {
      return true;
    }
    ptr = ptr->next;
  }
  return false;
}
void update_obj(listOfObjects<Edge> *edgelist, Node j, Node new_j)
{
  listOfObjects<Edge> *ptr = edgelist;
  while (ptr != nullptr)
  {
    if (ptr->object.n1.value == j.value)
    {
      ptr->object.n1 = new_j;
    }
    else if (ptr->object.n2.value == j.value)
    {
      ptr->object.n2 = new_j;
    }
    ptr = ptr->next;
  }
}

void Graph::printSourceNodes()
{
  gFile << "Source Nodes: ";
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].inadjNodes == nullptr)
    {
      isSourceNode[i] = 1;
    }
    else
    {
      isSourceNode[i] = 0;
    }
  }
  for (int i = 0; i < numNodes; i++)
  {
    if (isSourceNode[i])
    {
      gFile << i + 1 << " ";
    }
  }
  gFile << endl;
}
bool Graph::checkSimilarity(Node node1, Node node2)
{
  Edge e = Edge(node1, node2);
  if (find_obj(similarNodes, e))
  {
    return false;
  }
  else if (node1.inadjNodes == nullptr || node2.inadjNodes == nullptr)
  {
    return false;
  }
  else
  {
    bool isSimilar = true;
    listOfObjects<Node> *ptr1 = node1.inadjNodes;
    while (ptr1 != nullptr && isSimilar)
    {
      listOfObjects<Node> *ptr2 = node2.inadjNodes;
      while (ptr2 != nullptr)
      {
        Edge e = Edge(ptr1->object, ptr2->object);
        if (find_obj(similarNodes, e))
        {
          isSimilar = true;
          break;
        }
        else
          isSimilar = false;
        ptr2 = ptr2->next;
      }
      ptr1 = ptr1->next;
    }
    return isSimilar;
  }
}
void Graph::updateSimilarity()
{
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].inadjNodes != nullptr)
    {
      if (nodes[i].inadjNodes->next == nullptr)
      {
        Edge e = Edge(nodes[i], nodes[nodes[i].inadjNodes->object.value - 1]);
        if (similarNodes != nullptr)
          similarNodes->insert(e);
        else
          similarNodes = new listOfObjects<Edge>(e);
      }
    }
  }
  listOfObjects<Edge> *ptr = similarNodes;
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      if (i != j)
      {
        if (checkSimilarity(nodes[i], nodes[j]) && checkSimilarity(nodes[j], nodes[i]))
        {
          Edge e = Edge(nodes[i], nodes[j]);
          Edge e1 = Edge(nodes[j], nodes[i]);
          if (similarNodes != nullptr)
          {
            similarNodes->insert(e);
            similarNodes->insert(e1);
          }
        }
      }
    }
  }
}
void Graph::printSimilarNodes()
{
  gFile << "Similar Nodes: ";
  listOfObjects<Edge> *ptr = similarNodes;
  if (ptr == nullptr)
    return;
  while (ptr->next != nullptr)
  {
    ptr->object.printEdge(gFile);
    gFile << " ";
    ptr = ptr->next;
  }
  ptr->object.printEdge(gFile);
  gFile << endl;
}
void Graph::printCollapsedGraph()
{
  Node *simNodes = new Node[numNodes];
  int *identifiers = new int[numNodes];
  listOfObjects<Edge> *updatedSimNodes = similarNodes;
  listOfObjects<Edge> *updatedEdges = nullptr;
  int count = 0;
  for (int i = 0; i < numNodes; i++)
  {
    simNodes[i].inadjNodes = nullptr;
    simNodes[i].outadjNodes = nullptr;
    simNodes[i].value = i + 1;
    identifiers[i] = 0;
  }
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      Edge e = Edge(simNodes[j], nodes[i]);
      Edge e1 = Edge(nodes[i], simNodes[j]);
      if (find_obj(updatedSimNodes, e) || find_obj(updatedSimNodes, e1))
      {
        if (simNodes[j].value < i + 1)
          simNodes[j].value = i + 1;
        update_obj(updatedSimNodes, nodes[j], simNodes[j]);
      }
    }
  }
  gFile << "Collapsed Graph: " << endl;
  for (int i = 0; i < numNodes; i++)
  {
    identifiers[simNodes[i].value - 1] = 1;
  }
  for (int i = 0; i < numNodes; i++)
  {
    if (identifiers[i])
    {
      count++;
    }
  }
  gFile << count << ": ";
  for (int i = 0; i < numNodes; i++)
  {
    if (identifiers[i])
    {
      gFile << i + 1 << " ";
    }
  }
  gFile << endl;
  listOfObjects<Edge> *temp = edgeList;
  while (temp != nullptr)
  {
    Node node1 = temp->object.n1;
    Node node2 = temp->object.n2;
    Edge e2 = Edge(simNodes[node1.value - 1], simNodes[node2.value - 1]);
    if ((e2.n1.value != e2.n2.value) && (!find_obj(updatedEdges, e2)))
    {
      if (updatedEdges == nullptr)
      {
        updatedEdges = new listOfObjects<Edge>(e2);
      }
      else
      {
        listOfObjects<Edge> *temps = updatedEdges;
        while (temps->next != nullptr)
        {
          temps = temps->next;
        }
        temps->next = new listOfObjects<Edge>(e2);
      }
    }
    temp = temp->next;
  }
  listOfObjects<Edge> *temp1 = updatedEdges;
  while (temp1 != nullptr)
  {
    Edge e3 = temp1->object;
    if ((e3.n1.value != e3.n2.value) || (!find_obj(updatedEdges, e3)))
    {
      gFile << temp1->object.n1.value << " " << temp1->object.n2.value << endl;
    }
    temp1 = temp1->next;
  }
}
#endif
