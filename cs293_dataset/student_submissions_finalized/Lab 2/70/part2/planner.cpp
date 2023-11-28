#include <iostream>
#include "planner.h"

using namespace std;

int hashValue1(char key[]){	//generate hash value for a station
	const int p = 31, m=64;
	int i=0;
	double A = 0.61;
	long int pow = 1;
	int hash=0;
	while(key[i] != '\0' && key[i] != '\n'){
	hash = (hash+ (key[i]-'a'+97)*pow)%m;
	 pow = (p*pow)%m;
	 i++;
	}
	double h = hash*A - int(hash*A);

	int r = m*h; 
	return r;
}

int Planner::findFreeIndex1(char key[]){
	int i=hashValue1(key);
	int j=i;
	int r;
	bool k=false;
	while(true){ 
		if(strcmp(d.A[j].key, key)==0 || d.A[j].key[0]=='\0'){
			return j;
		}
		j = (j+1)%(d.N);
	}
	return -1;
}

void Planner::Add(Journey p){
	int i = findFreeIndex1(p.s1.name);
	strcpy(d.A[i].key, p.s1.name);
	d.A[i].j.QInsert(p);
}

int Planner::bin_srch(DynamicQueue &b, int time, int low, int high){
	if(b.size()==0){
		return -1;
	}
	if(low > high )
		return -2;
	int mid = (low+high)/2;
	if(b.tail>b.head ){
		if(mid==b.head && time<=b.A[mid].start){
			return mid;
		}
		else if(time > b.A[mid].start){
			return bin_srch(b, time, mid+1, high);
		}
		else if(time<=b.A[mid].start && time>b.A[mid-1].start){
			return mid;
		}
		else {
			return bin_srch(b, time, low, mid-1);
		}
	}
	else {
		int t;
		t = mid-b.N;
		if(time<=b.A[t].start && time>b.A[t-1].start)
			return mid;
		else if(time > b.A[t].start)
			return bin_srch(b, time, mid+1, high);
		else 
			return bin_srch(b, time, low, mid-1);
	}
	return 1;

}
void Planner::query_station(station_query q1){
	int i = findFreeIndex1(q1.s.name);
	int r1=d.A[i].j.head;
	int r2 = d.A[i].j.tail; 
	int l = d.A[i].j.N;
	int res=0;

	if(r2>r1){
		res = bin_srch(d.A[i].j, q1.start_time, r1, r2) ;
	}
	else if(r2<=r1)
		res = bin_srch(d.A[i].j, q1.start_time, r1, r2+l);
	if(res==-1){
		cout << "Invalid station name"<< endl;//If no such station
		return;
	}
	if(res==-2){
		cout << "No train available" << endl;//If no such train
		return;
	}

	while( res != r2){
		cout << (d.A[i].j.A[res].start) << " " << (d.A[i].j.A[res].s2.name) << endl;
		res = (res+1)%l; //print all the Journey's with start time greater than that of start_time of given query
	}

} 

void Planner::query_journey(journey_query q2){
	int i = findFreeIndex1(q2.s1.name);
	int r1=d.A[i].j.head;
	int r2 = d.A[i].j.tail; 
	int l = d.A[i].j.N;
	int res=0, res1=0;
	bool k=false; 
	if(r2>r1){
		res = bin_srch(d.A[i].j, q2.start_time, r1, r2) ;
	}
	else if(r2<=r1)
		res = bin_srch(d.A[i].j, q2.start_time, r1, r2+l);
	int p1=res;
	if(res==-1){//If no such station
		cout << "Invalid station name"<< endl;
		return;
	}
	else if(res==-2){//If no such train
		cout << "No train available" << endl;
		return;
	}
	while( p1 != r2){
		if(strcmp(d.A[i].j.A[p1].s2.name, q2.s2.name)==0){
			cout << (d.A[i].j.A[p1].start) <<endl;
			k=true;
			return;
		}
		else {
			int I1 = findFreeIndex1(d.A[i].j.A[p1].s2.name);
			int R1=d.A[I1].j.head;
			int R2 = d.A[I1].j.tail;
			int l1 = d.A[I1].j.N;
			bool k=false;
			if(r2>r1){
				res1 = bin_srch(d.A[I1].j, d.A[i].j.A[p1].finish, R1, R2) ;
			}
			else if(r2<=r1){
				res1 = bin_srch(d.A[i].j, d.A[i].j.A[p1].finish, R1, R2+l);
			}
			if(res1 !=-1 && res1!=-2){ //if no Journey's available
				while(res1 != R2){
					if(strcmp(q2.s2.name, d.A[I1].j.A[res1].s2.name)==0){
						cout << (d.A[i].j.A[p1].start) <<  " " << d.A[I1].j.A[R1].s1.name << " " << (d.A[I1].j.A[res1].start) << endl;
						k=true; //search all Journeys from intermediate destination to final destination after first journeys finish time
						return; 
					}
					res1 = (res1+1)%l;
				}
			}
		}
		p1 = (p1+1)%l;
	}
	if(res1==-2)
		cout << "No train available" << endl;
	return;
}


