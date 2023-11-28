#include<iostream>
using namespace std;
#include "planner.h"

int main(){
	Query q;Planner p;
	for(int i=0;i>=0;i++)
	{
		cout << ">>> " ;
		cin>>q.operation;
		if(strcmp(q.operation,"EXIT") == 0){
			break;
		}

		// INS <key> <value>
		if(strcmp(q.operation,"ADD") == 0){


			cin >> q.station1;
			cin >> q.time1;
			cin >> q.station2;
			cin >> q.time2;      
			Entry data1,data2;
			strcpy(data1.key,q.station2);
			data1.value  = q.time1;
			strcpy(data2.key,q.station1);
			data2.value  = q.time2;      
			p.addjourney(data2,data1);
		}

		// DEL <key>
		else if(strcmp(q.operation, "QUERY_STATION") == 0){
			cin >> q.station1;
			cin >> q.time1;
			p.listall(q.station1,q.time1);
		}

		// FIND <key>
		else if(strcmp(q.operation,"QUERY_JOURNEY") == 0){
			cin >> q.station1;
			cin >> q.time1;
			cin >> q.station2;
			p.route(q.station1,q.time1,q.station2);
		}
	}
}
