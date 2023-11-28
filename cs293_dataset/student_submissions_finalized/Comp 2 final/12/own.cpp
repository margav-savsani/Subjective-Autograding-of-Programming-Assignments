#include "own.h"
using namespace std;

Own::Own()
{
	nodes=0;
}
void Own :: setNodes(int x)
{
	nodes = x;
}
int Own::getNodes() {
	return nodes;
}

void Own::setEdges(vector<pair<int, int> > e) {
	edges = e;
}

vector<pair<int, int> > Own::getEdges() {
	return edges;
}
void Own ::displayEdges() {
	for(int i = 0; i<edges.size();i++) {
		cout << edges[i].first<<" , "<<edges[i].second<<endl;
	}
}
int Own::contains (vector<int> sources, int x) {
	if (count(sources.begin(), sources.end(), x)) {
        	return 1;
   	}
   	else {
   		return 0;
   	}
}
void Own::setsourcesdest() {
	for(int i = 0; i<edges.size();i++) {
		int x = edges[i].first;
		int y = edges[i].second;	
		if (!contains(sources,x) ) {
        	 sources.push_back(x);
        	//allsources.push_back(x);
   		 }
   		
   		if (!contains(dest,y)) {
        	dest.push_back(y);
   		 }
	}
	for(int i = 0; i<edges.size();i++){
		int x = edges[i].first;
		if (!contains(sources,x) && !contains(dest,x)){
			allsources.push_back(x);
		}
	}
	
}
vector<int> Own::displaysources() {

	return allsources;
	
}

void Own::setsources() {
	for(int i = 1;i<=nodes;i++) {
		if(!contains(allsources,i)) {
			if(count(dest.begin(), dest.end(), i)==0) {
				allsources.push_back(i);
				collapse_node.push_back(i);
			}
		}
	}
}

vector<int> Own :: directEdge(int n1) {
	vector<int> s;
	for(int i=0;i<edges.size();i++) {
		if(edges[i].second==n1) {
			s.push_back(edges[i].first);
		}
	}
	return s;
}
void add(vector<pair <int, int> > &s, int n1, int n2) {
	int flag=0;
	for(int i = 0 ;i<s.size(); i++) {
		if(s[i].first==n1 && s[i].second==n2) {
			flag=1;
			break;
		}
	}
	if(flag==0) {
		s.push_back(make_pair(n1,n2));
	}
 }
void Own::setsimedges() {
	int n1, n2;
	for(n1=1;n1<=nodes;n1++) {
		for(n2 = 1; n2<=nodes;n2++) {
			if(n1!=n2) {
				if(contains(sources,n1) && contains(sources,n2)) {
					//cout<<n1<<"and "<<n2<<"added from if"<<endl;
					add(simedges,n1,n2);
				}
				else if(contains(dest,n1) && contains(dest,n2)) {
					vector<int> source_of_n1 = directEdge(n1);
					vector<int> source_of_n2 = directEdge(n2);
					if(source_of_n1.size()==1 && source_of_n2.size()==1) {
						if(source_of_n1[0]!= source_of_n2[0]) {
						//	cout<<n1<<"and "<<n2<<"added from 2nd if"<<endl;
							add(simedges,n1,n2);
						}
						else {
							for(int m = 0; m<source_of_n1.size(); m++) {
								for(int n=0; n<source_of_n1.size();n++) {
									if(source_of_n1[m]!= source_of_n2[n]) {
								
										add(simedges,source_of_n1[m],source_of_n2[n]);
									}
								}
							}
						}
					}	
				}
				
				if(directEdge(n1).size()==1){
						add(simedges,directEdge(n1)[0],n1);				
				}
			}
		}
	}
}
vector<pair<int, int> > Own::dispsimedges() {
	
	return simedges;
}
int Own::checksimiliar(int x, int y) {
	for(int i=0;i<simedges.size();i++) {
		if((simedges[i].first==x && simedges[i].second==y) || (simedges[i].first==y && simedges[i].second==x))
			return  1;
	}
	
		return 0;
}
vector<int> Own::getcollapsenode() {
	vector<int> maxedges ;
	for(int i =0;i<edges.size(); i++) {
		maxedges.push_back( max(edges[i].first,edges[i].second));
	}
	for(int i=0; i<maxedges.size()-1;i++) {
		if( checksimiliar (maxedges[i],maxedges[i+1])) {
			
			collapse_node.push_back(max(maxedges[i],maxedges[i+1]));
			i++;
		}
	}
	return collapse_node;
}
