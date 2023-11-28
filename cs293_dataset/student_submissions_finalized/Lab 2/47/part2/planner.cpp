#include<iostream>
#include<string.h>
#include"planner.h"

using namespace std;



int main(){

	stations start;
		
	while(true){
		
		char input[32];
		cin>>input;


		if(strcmp(input,"EXIT") == 0){
		
      			break;
   		}
   		
   		else if(strcmp(input,"ADD") == 0){
			
			char s2[32],s3[32];
			float a,b;
			cin>>s2;
			cin>>a;
			cin>>s3;
			
			cin>>b;


			station k;
			k.filled = true;
			strcpy(k.s1,s2);
			node n;
			n.start = a;
			n.end = b;
			strcpy(n.s2,s3);
			(k.q).push_back(n); 
			start.put(k);		
			
		}
		
		else if(strcmp(input,"QUERY_STATION") == 0){
		
			char s2[32];
			float a;
			cin>>s2>>a;
			int index = start.found(s2);
			if( index == -1 ){
			
				cout<<"ERROR\n";
			}
			else{
			
				start.querystation(a,index);
				
				
			}
		}
		
		else if(strcmp(input,"QUERY_JOURNEY") == 0){
		
			char s2[32],s3[32];
			float a;
			cin>>s2>>a>>s3;
			int index = start.found(s2);
			if( index == -1 ){
				cout<<"ERROR\n";
				continue;
			}
			else{
			
				start.queryjourney(a,index,s3);
				
				
			}
			
		}
		
		else{
		
			cout<<"Invalid Command\n";
		}
		
		
	}
}			
		
		
		
		

