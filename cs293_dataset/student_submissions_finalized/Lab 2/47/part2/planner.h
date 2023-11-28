#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include<string.h>
#include<vector>
#include<cmath>

using namespace std;

struct node{

	float start;
	float end;
	char s2[32];
};
	

struct station{

	char s1[32];
	vector<node> q;
	bool filled = false;
};	
	
class stations{

	private:
	
	int N;
	station* s;
	
	public:
	
	stations(){
		
		N = 64;
		s = new station[N];
	}
	int hashValue(char key[]){

	
		int x=33;
		int p= 0;
		int i=0;
		while( key[i] != '\0'){
	
			int b = key[i];
			p = (p*x+b)%127;
			i++;
		}	
	
		double a = 0.618;
		double b = 1;
		double c = (a*p+b);
		p = c;
		p = p%64;
		return p;
	}
	
	int findFreeIndex(char key[]){
		int index = hashValue(key);
		int indexfinal = -1;
		for( int i = index; i< 64; i++){
	
			if((s[i].filled == true && strcmp(s[i].s1,key)==0)){

				indexfinal = i;
				break;
			}
			else if( s[i].filled == false){

				indexfinal = i;
				break;
			}	
			
		}
		return indexfinal;
	}
	bool put(struct station e){

			int index = findFreeIndex(e.s1);
		
			if( index != -1){
			strcpy(s[index].s1, e.s1);
			(s[index].q).push_back((e.q)[0]);
			s[index].filled = true;
			}
	
		return false;
	}
	
	int found(char s2[]){
	
		for( int i=0; i<64; i++){
		
			if( strcmp(s[i].s1, s2) == 0){
			
				return i;
			}
		}
		return -1;
	}
	
	void querystation(float st, int index){
	
		bool found = false;
		for(int i=0; i<(s[index].q).size();i++){

			if((s[index].q)[i].start >=  st){
					
				cout<<(s[index].q)[i].start<<" "<<(s[index].q)[i].s2<<endl;
				found = true;
			}
		}
		
		if( !found){
		
			cout<<"ERROR\n";
		}
	}
	
	void queryjourney(float a, int index, char f[]){
		
		float min1;
		float min2;
		int final1;
		int final2;
		int minin;
		int jmin;
		bool found1 = false;
		bool found2 = false;
		for(int i=0; i<(s[index].q).size();i++){
		
			if((s[index].q)[i].start >=  a && strcmp((s[index].q)[i].s2, f) == 0 ){
				
				if( !found1 ){
				
					min1 = (s[index].q)[i].start;
					final1 = i; 
					found1 = true;
				}
				else{
				
					int x = min( min1, (s[index].q)[i].start);
					if ( x != min1 ){
					
						min1 = x;
						final1 = i;
					}
				}
			}
			else if ( (s[index].q)[i].start >=  a && strcmp((s[index].q)[i].s2, f) != 0){
			
				int intermediate = found((s[index].q)[i].s2);
				
				if( intermediate!=-1){
					
					for(int j=0; j<(s[intermediate].q).size();j++){
				
					if((s[index].q)[i].end <= (s[intermediate].q)[j].start){
					
						
		
							if(strcmp((s[intermediate].q)[j].s2, f) == 0){
					
									
								if( !found2 ){
				
									min2 = (s[index].q)[i].start;
									final2= i; 
									minin=intermediate;
									jmin = j;
									found2 = true;
								}
								else{
				
									int x = min( min2, (s[index].q)[i].start);
									if ( x != min2 ){
					
										min2 = x;
										final2 = i;
										minin = intermediate;
										jmin = j;
									}
								}
							}
						}
					}
				}
			}
		}
		
		
			if( !found1){
			
				if(!found2){
				
					cout<<"ERROR\n";
				}
				else{
				
					cout<<(s[index].q[final2]).start<<" "<<(s[index].q[final2]).s2<<" "<<(s[minin].q[jmin]).start<<"\n";
				}
			}
			else{
			
				if( found2 ){
			
				if ( min1<=min2){
				
					cout<<min1<<"\n";
				}
				
				else{

					cout<<(s[index].q[final2]).start<<" "<<(s[index].q[final2]).s2<<" "<<(s[minin].q[jmin]).start<<"\n";
				
				}
				}
				else{
				
				
					cout<<min1<<"\n";
				}
			}
																		
				
		}		
		
};


#endif
