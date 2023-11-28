//QueryHandler.cpp



#include<iostream>
#include<string.h>
#include<cmath>


#include"dictionary.cpp"

using namespace std;

int main(){

	struct Query Q;
	
	
while(true){	

	
	char command[32];
	cin>>command;
	
	// "ADD" adds an element to the dictionary
	if (strcmp(command,"ADD")==0){
		char s1[64], s2[64];
		int t1, t2;
		
		cin>>s1>>t1>>s2>>t2;
		
		Q.Add(s1, s2, t1, t2);
		
		
	}
	
	// "QUERY_STATION" shows list of all available trains 
	if (strcmp(command,"QUERY_STATION")==0){
		char s1[64]; int t;
		cin>>s1>>t;
		
		Q.ListTrains(s1,t);
	
	}
	
	
	//"QUERY_JOURNEY" shows list of feasible trains from source to dest
	if (strcmp(command,"QUERY_JOURNEY")==0){
		char s1[64], s2[64]; int t;
		cin>>s1>>t>>s2;
		
		Q.D.shortest_path(s1,t,s2);
	
	}
	
	if(strcmp(command,"EXIT")==0) break;
}

}


