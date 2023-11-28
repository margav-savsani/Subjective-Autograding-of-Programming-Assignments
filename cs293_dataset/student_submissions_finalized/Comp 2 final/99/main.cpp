#include "graph.cpp"

int main(int argc, char** argv)
{
   DirectedGraph * myGraph;
   myGraph = new DirectedGraph();
   if (myGraph == nullptr)
   {
      cerr << "Memory allocation failure\n";
      exit(-1);
   }
   myGraph->printSourceNodes();
   myGraph->getSimilarNodes();
   myGraph->printSimilar();
   myGraph->collapseSimilarNodes();
   myGraph->getCollapsedGraph();
   delete myGraph;
}