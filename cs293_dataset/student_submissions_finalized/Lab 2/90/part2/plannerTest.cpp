#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;

/*

In interactive mode you can give commands:
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>
  EXIT
  HELP
*/

void QueryHandler(Planner &planner){
	for(int i=0;i>=0;i++){
		char input[32];
		cout << ">>> " ;
		cin >> input;
		
		//HELP
		if(strcmp(input,"HELP") == 0){
			cout << "1. ADD <station_one> <start_time> <station_two> <finish_time>\n"
  				<< "2. QUERY_STATION <station_one> <start_time>\n" 
  				<< "3. QUERY_JOURNEY <station_one> <start_time> <station_two>\n"
  				<< "4. EXIT\n";
		}	


		//EXIT
		if(strcmp(input,"EXIT") == 0){
			break;
		}	

		// ADD <station_one> <start_time> <station_two> <finish_time>
		if(strcmp(input,"ADD") == 0){

			char stn1name[32], stn2name[32];
			float stime, ftime;
			cin >> stn1name >> stime >> stn2name >> ftime;
			Journey jrny;
			jrny.set_jrny_details(stime, stn2name, ftime);
			if(planner.get(stn1name)==NULL){
				Station stn;
				strcpy(stn.name,stn1name);
				if(!planner.put(stn)){
					cout << "ERROR! No. of trains overloaded" << endl;
					continue;
				}
			}
			Station* stn1 = planner.get(stn1name);
			stn1->add_jrny(jrny);
		}


		// QUERY_STATION <station_one> <start_time>
		else if(strcmp(input,"QUERY_STATION") == 0){
			char stn1name[32];
			float stime;
			cin >> stn1name >> stime;
			Station *stn = planner.get(stn1name);
			if(stn == NULL){
				cout << "ERROR! Station Doesn't Exists" << endl;
				continue;
			}
			bool travel_exists = false;
			int index = (int)(stime/100);
			if(stn->jrnies[index].stime>=stime){
				cout << stn->jrnies[index].stime << " " << stn->jrnies[index].stn2 << endl;
				travel_exists=true;
			}
			for(int i=index+1; i!=index; i=(i+1)%24){
				if(stn->jrnies[i].stime>=stime){
					cout << stn->jrnies[i].stime << " " << stn->jrnies[i].stn2 << endl;
					travel_exists=true;
				}
			}
			if(!travel_exists) cout << "ERROR! Not Available" << endl;
		}
		

		//QUERY_JOURNEY <station_one> <start_time> <station_two>
		else if(strcmp(input,"QUERY_JOURNEY") == 0){
			char stn1name[32], stn2name[32];
			float stime;
			cin >> stn1name >> stime >> stn2name;
			Station *stn = planner.get(stn1name);
			if(stn == NULL){
				cout << "ERROR! Station Doesn't Exists" << endl;
				continue;
			}
			bool direct = false;
			int i = (int)(stime/100);
			int best_stime = 2400;
			int best_ftime = 2400; //shall be used Part 3
			int best_index = -1;
			do{
				if(stn->jrnies[i].stime>=stime && stn->jrnies[i].stime<best_stime){
					if(strcmp(stn->jrnies[i].stn2,stn2name)==0){
						best_stime = stn->jrnies[i].stime;
						best_index = i;
						direct = true;

					}
					else{
						Station *stn2 = planner.get(stn->jrnies[i].stn2);
						if(stn2!=NULL){
							int stime2 = stn2->check_train_availability(stn->jrnies[i].ftime, stn2name);
							if(stime2!=2400){
								best_stime = stn->jrnies[i].stime;
								best_index = i;
								best_ftime = stime2;
								direct = false;
							}
						}
					}
				}		
				i=(i+1)%24;
			}
			while(i!=(int)(stime/100));
			if(best_index==-1) cout << "ERROR! No trains available\n";
			else{
				if(direct) cout << best_stime << endl;
				else cout << best_stime << " " << stn->jrnies[best_index].stn2 << " " <<  best_ftime << endl;
			}		
		}
		
		
		
	}
}	

int main(){
	cout<<"Welcome to Railway Planning Panel!\n";
	cout << "For any help related to commands, please type 'HELP'\n";
	Planner planner;
	QueryHandler(planner);
}

