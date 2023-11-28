#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>
using namespace std;

// int ActualArrTime(TrainInfoPerStation *t)
// {
// 	int a = t->arrTime;
// 	int day = 0;

// 	for (int i=0; i<7; i++)
// }


void print_vector(vector<int> v){
	for(int i=0; i<v.size(); i++){
		cout << v[i] << ", ";
	}
	cout << endl;
}


// void foo(int k, vector<int> *plist , int list_no , vector<vector<vector<int>>> &jlist){
vector<vector<int>>  foo(int k, vector<int> *plist , int list_no , vector<vector<int>> jlist){

	// cout << "k: " << k << endl;
	// cout << "Current list: ";
	// print_vector(jlist[list_no]);

	vector<int> currlist = jlist[list_no];
	if (k == -1){
		return jlist;
	}

	// for(int i=0; i<plist[k].size(); i++){
	// 	jlist[list_no + i] = jlist[list_no];
	// }

	for(int i=0; i<plist[k].size(); i++){
		// cout << "***164" << endl;
		int t = plist[k][i];

		if (i != 0){
			vector<int> v = currlist;
			v.push_back(t);
			jlist.insert(jlist.begin() + i, v );
			// jlist[list_no + i].push_back(t);
		}
		else{
			jlist[list_no].push_back(t);
		}

		jlist = foo(t, plist, list_no + i, jlist);
	}	

	return jlist;
}




vector<vector<pair<int,int>>> hoo(int stindex,  vector<vector<pair<int,int>>> q , vector<pair<int,vector<int>>> t ){

    // if( stindex >= t.size() - 1){
    if( stindex >= t.size()){

        return q;
    }

    if( stindex == 0 ){
        vector<pair<int,int>> a;
        q.push_back(a);
    }

    auto currlist = q.back();

    for(int i=0; i<t[stindex].second.size(); i++){
        
        if( i!= 0 ){
            q.push_back(currlist);
        }

        q[q.size()-1].push_back(make_pair(t[stindex].first, t[stindex].second[i]));

        q = hoo(stindex + 1, q, t);

    }

    return q;

}


void print5( vector<vector<pair<int,int>>> q ){
    for(int i=0; i<q.size(); i++){
        cout << "(" << i+1 << ")   ";

        for(int j=0; j<q[i].size() - 1; j++){
            cout << "("<<q[i][j].first << ", "<< q[i][j].second << ") -> ";
        }
        cout << "("<<q[i][q[i].size()-1].first << ", "<< q[i][q[i].size()-1].second << ")\n";
    }
}

void print6( vector<pair<int,vector<int>>> q ){
    for(int i=0; i<q.size(); i++){
        cout << "(" << i+1 << ")   ";

        cout << GREEN << q[i].first << RESET << ": ";
		for(int j=0; j<q[i].second.size()-1; j++){
			cout << q[i].second[j] << " -- ";
		}
		cout << q[i].second[q[i].second.size()-1] << "\n";
    }
}

void print7( vector<vector<int>> jlist){
	for(int i=0; i<jlist.size(); i++){
		cout << "(" << i+1 << ")   ";

		for(int j=0; j<jlist[i].size()-1; j++){
			cout << jlist[i][j] << " <-- ";
		}

		cout << jlist[i][jlist[i].size() -1] << "\n";
	}
}

void printDays( bool yy[7] ){
	string day[7];
	day[1] = "Mon";
	day[2] = "Tue";
	day[3] = "Wed";
	day[4] = "Thurs";
	day[5] = "Fri";
	day[6] = "Sat";
	day[0] = "Sun";

	for(int i=0; i<6; i++){
		if(yy[i]){
			cout << day[i] << ", ";
		}
	}
	if(yy[6]){
		cout << day[6] << "\n";
	}

}




void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

	// insert your code here
	cout <<  GREEN << "\n\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n" << RESET;
	cout  << "\n\nJOURNEYS FROM " << srcStnName << " TO " << destStnName <<  ", MAX TRANSIT TIME: " << maxTransitTime << ", MAX STOP OVERS: " << maxStopOvers << RESET << endl;
	cout << "\n\n\n";



	// ::::::::::::::::::::::: DFS ::::::::::::::::::::::::::::::::::::::::::::::::::::

	int startStn = stnNameToIndex.get(srcStnName)->value;
	int finalStn = stnNameToIndex.get(destStnName)->value;


	// STACK IMPLEMENTATION INSTEAD OF RECURSIVE IMPLEMENTATION OF DFS
	bool discovered[DICT_SIZE];
	bool processed[DICT_SIZE];

	int parent[DICT_SIZE];
	vector<int> plist[DICT_SIZE];

	int entrytime[DICT_SIZE];
	int exittime[DICT_SIZE];
	for (int i=0; i<DICT_SIZE; i++){
		discovered[i] = false;
		processed[i] = false;
		parent[i] = -1;
		entrytime[i] = -1;
		exittime[i] = -1;
	}


	// Using vector for stack implementation
	vector<int> stck;	// stores the station indices
	int v;	// current vertex
	int y;  // successor vertex



	stck.push_back(startStn);
	discovered[v] = true;

	int time = 0;
	while(!stck.empty()){


		// // Printing stack stck
		// cout << time << endl;
		// for(int i=0; i<stck.size(); i++){
		// 	cout << stnNameToIndex.getKeyAtIndex(stck[i]) << " ||| ";
		// }
		// cout << endl;

		v = stck.back();
		stck.pop_back();

		if(processed[v]){
			continue;
		}

		time++;
		entrytime[v] = time;

		processed[v] = true;

		auto outstnlist = adjacency[v].toStations;

		while(outstnlist != nullptr){

			y = outstnlist->object->adjacentStnIndex;

			if( !discovered[y] ){
				stck.push_back(y);
				discovered[y] = true;
				parent[y] = v;
				plist[y].push_back(v);
			}
			else if( discovered[y] && !processed[y] && entrytime[y] == -1 ){
				stck.push_back(y);
				plist[y].push_back(parent[y]);
				parent[y] = v;
				plist[y][0] = v;
			}
			else if( processed[y] ){	// FORWARD OR CROSS EDGE
				plist[y].push_back(v);
			}

			// END
			outstnlist = outstnlist->next;
		}

		time++;
		exittime[v] = time;

	}


	// :::::::::::::::::: END OF DFS :::::::::::::::::::::::::::::::::::::::

	// int k = finalStn;
	// while( k != -1 ){
	// 	cout << stnNameToIndex.getKeyAtIndex(k) << " <-- ";
	// 	k = parent[k];
	// }

	// vector<vector<vector<<int>>> jlist;

	// cout << 130 << endl;

	vector<vector<int>> jlist;
	vector<int> a;
	a.push_back(finalStn);
	jlist.push_back(a);
	// for(int t=0; t<100; t++){
	// 	jlist.push_back(a);
	// }

	jlist = foo(finalStn, plist , 0,  jlist);
	// cout << "aaa" << endl;
	// for(int i=0; i<100; i++){
	// cout << "JLIST\n";
	// print7(jlist);
	// cout << "\n\n";

	vector< vector<pair< int,vector<int> >> > tt;   // I WILL USE RECURSION ON tt
	for(int i=0; i<jlist.size(); i++){
		
		vector<pair<int,vector<int>>> a;

		for(int j=jlist[i].size()-1; j>=0; j--){

			vector<int> b;

			if( j == 0 ){
				b.push_back(-1);
				a.push_back(  make_pair(jlist[i][0], b) );
				break;
			}

			StationConnectionInfo *c;
			auto currnode = adjacency[jlist[i][j]].toStations;
			while(currnode != nullptr){
				if( currnode->object->adjacentStnIndex == jlist[i][j-1] ){
					c = currnode->object;
					// cout << "206\n";
				}

				currnode = currnode->next;
			}


			auto trainnode = c->trains;
			while(trainnode != nullptr){
				
				b.push_back(trainnode->object->journeyCode);
				trainnode = trainnode->next;
			}

			a.push_back( make_pair(jlist[i][j], b) );

		}
		// cout << "a: \n";
		// print6(a);
		tt.push_back(a);
	}

	vector<vector<pair<int,int>>> qq;
	for( int i=0; i<jlist.size(); i++){
		vector<vector<pair<int,int>>> q;
		q = hoo(0, q, tt[i]);
		// cout << "\nq: \n";
		// print5(q);

		qq.insert( qq.end(), q.begin(), q.end() );
	}	


	// cout << "\nqq\n";
	// print5(qq);






	
	// for(int i=0; i<jlist.size(); i++){

	// 	if(jlist[i].size() == 0) continue;


	// 	cout << "\033[1;32mJOURNEY " << i+1 << "\033[0m\n" << endl;

	// 	cout << "------------------------------------\n\n";

	// 	for(int j=jlist[i].size()-1; j>0; j--){
	// 		cout << "\033[1;31m" << stnNameToIndex.getKeyAtIndex(jlist[i][j]) << " --> \033[0m";
	// 	}
	// 	cout <<  "\033[1;31m" << stnNameToIndex.getKeyAtIndex(jlist[i][0]) << "\033[0m"<< "\n\n";


	// 	for(int j=jlist[i].size()-1; j>0; j--){
	// 		cout << "\033[1;34m" <<stnNameToIndex.getKeyAtIndex(jlist[i][j]) << " --> " << stnNameToIndex.getKeyAtIndex(jlist[i][j-1]) << "\033[0m" <<  endl;
	// 		// cout << "\033[1;32m" << "TRAINS\n" << "\033[0m";
			
	// 		StationConnectionInfo *c;
	// 		auto currnode = adjacency[jlist[i][j]].toStations;
	// 		while(currnode != nullptr){
	// 			if( currnode->object->adjacentStnIndex == jlist[i][j-1] ){
	// 				c = currnode->object;
	// 				// cout << "206\n";
	// 			}

	// 			currnode = currnode->next;
	// 		}

	// 		auto trainnode = c->trains;
	// 		while(trainnode != nullptr){
	// 			cout << "TRAIN NO: " << trainnode->object->journeyCode << ",  ARRIVAL TIME: " << trainnode->object->arrTime << ",  DEP TIME: " << trainnode->object->depTime << endl;

	// 			trainnode = trainnode->next;
	// 		}

	// 		cout << "\n\n";

	// 	}
	// 	cout << "-----------------------------------------------------\n\n";
	// }




	// :::::::::::::::  FILTERING JOURNEYS DUE TO CONSTRAINTS :::::::::::::::::::::::::::::::::::
	bool isValid[qq.size()];
	int stopOver[qq.size()];
	int transitTime[qq.size()];
	for(int i=0; i<qq.size(); i++){
		isValid[i] = true;

		// for(int j=0; j<qq[i].size()-1; j++){
		// }

		int stopOvers = 0;
		int mtt = 0;
		for(int j=0; j<qq[i].size()-2; j++){
			

			if (qq[i][j].second != qq[i][j+1].second){
				// CHANGE OF TRAINS
				stopOvers++;

				// TRANSIT TIME
				// Finding the arrival time of train1
				StationConnectionInfo *c;
				auto currnode = adjacency[qq[i][j+1].first].fromStations;
				while(currnode != nullptr){
					if( currnode->object->adjacentStnIndex == qq[i][j].first ){
						c = currnode->object;
					}

					currnode = currnode->next;
				}

				auto trainnode = c->trains;
				while(trainnode != nullptr){

					if( trainnode->object->journeyCode == qq[i][j].second ){
						break;
					}
					trainnode = trainnode->next;
				}

				int at = trainnode->object->arrTime;

				// Finding the departure time of train2
				currnode = adjacency[qq[i][j+1].first].toStations;
				while(currnode != nullptr){
					if( currnode->object->adjacentStnIndex == qq[i][j+2].first ){
						c = currnode->object;
					}

					currnode = currnode->next;
				}

				trainnode = c->trains;
				while(trainnode != nullptr){

					if( trainnode->object->journeyCode == qq[i][j+1].second ){
						break;
					}
					trainnode = trainnode->next;
				}



				int dt = trainnode->object->depTime;

				int trt;
				if (at > dt){
					int h;
					int minu;
					if( at%100 >= dt % 100 ){
						h = at / 100 - dt / 100;
						minu = at % 100 - dt % 100;
					}
					else{
						h = at / 100 - dt / 100 - 1;
						minu = at % 100 - dt % 100 + 60;
					}
					trt = h*(100) +  minu;
				}
				else{
					int h;
					int minu;
					at = at + 24;
					if( at%100 >= dt % 100 ){
						h = at / 100 - dt / 100;
						minu = at % 100 - dt % 100;
					}
					else{
						h = at / 100 - dt / 100 - 1;
						minu = at % 100 - dt % 100 + 60;
					}
					trt = h*(100) +  minu;
				}

				mtt = max(mtt, trt);
				

			}


			// StationConnectionInfo *c;
			// auto currnode = adjacency[qq[i][j].first].toStations;
			// while(currnode != nullptr){
			// 	if( currnode->object->adjacentStnIndex == qq[i][j+1].first ){
			// 		c = currnode->object;
			// 	}

			// 	currnode = currnode->next;
			// }

			// auto trainnode = c->trains;
			// while(trainnode != nullptr){

			// 	if( trainnode->object->journeyCode == qq[i][j].second ){
			// 		break;
			// 	}
			// 	trainnode = trainnode->next;
			// }


		}

		stopOver[i] = stopOvers;
		transitTime[i] = mtt;

		if( stopOvers > maxStopOvers || mtt > maxTransitTime){
			isValid[i] = false;
		}

		
	}













	int index = 0;
	for(int i=0; i<qq.size(); i++){

		if( !isValid[i] ) continue;

 
		cout << "\033[1;32mJOURNEY " << index+1 << ", STOP OVERS: " << stopOver[i] << ", MAX TRANSIT TIME: " << transitTime[i] <<  "\033[0m\n" << endl;

		// cout << "------------------------------------\n\n";

		for(int j=0; j<qq[i].size()-1; j++){
			cout << "\033[1;31m" << stnNameToIndex.getKeyAtIndex(qq[i][j].first) << " --> \033[0m";
		}
		cout <<  "\033[1;31m" << stnNameToIndex.getKeyAtIndex(qq[i][qq[i].size()-1].first) << "\033[0m"<< "\n\n";


		for(int j=0; j<qq[i].size()-1; j++){
			cout << "\033[1;34m" <<stnNameToIndex.getKeyAtIndex(qq[i][j].first) << " --> " << stnNameToIndex.getKeyAtIndex(qq[i][j+1].first) << "\033[0m" <<  endl;
			// cout << "\033[1;32m" << "TRAINS\n" << "\033[0m";
			
			StationConnectionInfo *c;
			auto currnode = adjacency[qq[i][j].first].toStations;
			while(currnode != nullptr){
				if( currnode->object->adjacentStnIndex == qq[i][j+1].first ){
					c = currnode->object;
					// cout << "206\n";
				}

				currnode = currnode->next;
			}

			auto trainnode1 = c->trains;
			while(trainnode1 != nullptr){

				if( trainnode1->object->journeyCode == qq[i][j].second ){
					break;
				}
				trainnode1 = trainnode1->next;
			}

			int dept = trainnode1->object->depTime;

			currnode = adjacency[qq[i][j+1].first].fromStations;
			while(currnode != nullptr){
				if( currnode->object->adjacentStnIndex == qq[i][j].first ){
					c = currnode->object;
					// cout << "206\n";
				}

				currnode = currnode->next;
			}

			auto trainnode2 = c->trains;
			while(trainnode2 != nullptr){

				if( trainnode2->object->journeyCode == qq[i][j].second ){
					break;
				}
				trainnode2 = trainnode2->next;
			}

			int arrt = trainnode2->object->arrTime;



					cout << "TRAIN NO: " << trainnode1->object->journeyCode << ",  DEP TIME: " << dept << ",  ARR TIME: " << arrt << " on ";
					printDays(trainnode1->object->daysOfWeek);
			cout << "\n\n";

		}
		index++;
		cout << "-----------------------------------------------------\n\n";
	}















	// // PRINTING plist
	// cout << "\n\nPLIST\n";
	// for(int i=0; i<DICT_SIZE; i++){
	// 	if ( plist[i].empty() ) continue;
	// 	cout << stnNameToIndex.getKeyAtIndex(i) << "(" << i << ")" <<  "::::::::::::::::::" << endl;
	// 	for(int j=0; j<plist[i].size(); j++){
	// 		cout << stnNameToIndex.getKeyAtIndex(plist[i][j]) << "(" << plist[i][j] << ")" <<  ", ";
	// 	}
	// 	cout << "\n\n";
	// }







	cout <<  GREEN << "\n\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n" << RESET;

	// cout <<GREEN << "\n\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n" << RESET << endl;;
	return;
}





// // void foo(int k, vector<int> *plist , int list_no , vector<vector<vector<int>>> &jlist){
// vector<int> *foo(int k, vector<int> *plist , int list_no , vector<int> jlist[]){

// 	cout << "k: " << k << endl;

// 	for(int i=0; i<plist[k].size(); i++){
// 		cout << "***164" << endl;
// 		int t = plist[k][i];

// 		jlist[list_no + i].push_back(t);
// 		foo(t, plist, list_no + i, jlist);
// 	}	

// 	return jlist
// }




#endif
