#include <iostream>
#include "planner.cpp"

using namespace std;


// function to handle queries, inorder to declutter main()

bool queryHandler(Query q, Planner &p){

		// deals with EXIT command
		if(q.q_vec.at(0) == "EXIT"){
			return 0;
		}
		

		//deals with ADD command
		else if (q.q_vec.at(0) == "ADD"){
			p.newJourney(q.q_vec.at(1), stoi(q.q_vec.at(2)), q.q_vec.at(3), stoi(q.q_vec.at(4)));
			return 1;
			cout << "Added";
		}


		// deals with QUERY_STATION command
		else if (q.q_vec.at(0) == "QUERY_STATION"){
			vector<Journey> v = p.queryStation(q.q_vec.at(1), stoi(q.q_vec.at(2)));
			if (v.size() == 0){
				cout << "There are no such trains available." << endl;
			} else {
				for (auto i = v.begin(); i != v.end(); ++i)
				{
					cout << (*i).ts << " " << (*i).stat_start << endl;
				}
			}
			return 1;
		}

		// deals with QUERY_JOURNEY command
		else if (q.q_vec.at(0) == "QUERY_JOURNEY"){
			vector<Journey> v = p.queryJourney(q.q_vec.at(1), stoi(q.q_vec.at(2)), q.q_vec.at(3));
			if (v.size() == 0){
				cout << "There are no such trains available" << endl;
			} else if (v.size() == 1){
				cout << v[0].ts << endl;
			} else if (v.size() == 2){
				cout << v[0].ts << " " << v[0].stat_end << " " << v[1].ts << endl;
			}
			return 1;
		}
		else return 0;
}


int main(){

	Planner planner;
	bool active = 1;		// flag for the 'while' loop
	while(active){

		cout << "Enter your command : " << endl;
		Query inp;
		string x;

		getline(cin, x);	// get command from CLI
		

		// converts line into separate words, pushes into Query
		
		string word = "";
		for( char c : x){
			if(c == ' '){
				inp.q_vec.push_back(word);
				word = "";
			} else {
				word += c;
			}
		}
		inp.q_vec.push_back(word);


		// queryHandler called, and returns value of flag
		active =  queryHandler(inp, planner);
	}
}
