#ifndef OWN_H
#define OWN_H
#include<iostream>
#include<vector>
#include<utility>
#include <algorithm>
using namespace std;
class Own
{
	private :
		int nodes;
		vector<pair<int, int> > edges;
		vector<int> sources;
		vector<int> allsources;
		vector<int> dest;
		vector<int> totalnodes;
		int contains (vector<int> sources, int x);
		vector<pair <int, int> > simedges;
		vector<int> collapse_node;
		
	public: 
		Own();
		void setNodes(int x);
		int getNodes();
		void setEdges(vector<pair<int, int> > x);
		vector<pair <int,int> > getEdges();
		
		void displayEdges();
		void settotalnodes();
		void setsourcesdest();
		vector<int> displaysources();
		void setsources();
		void setsimedges();
		vector<pair<int,int> > dispsimedges();
		vector<int> directEdge(int n2);
		vector<int> getcollapsenode();
		int checksimiliar(int x, int y);
	protected:
};

#endif
