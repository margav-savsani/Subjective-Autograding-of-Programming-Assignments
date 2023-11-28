#include "planner.cpp"

void create() {  // creates a planner object and do the required operations.
    planner p;
for(int i=0;i>=0;i++) {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){  // exits the loop if user types EXIT
      break;
    }

    if(strcmp(input,"ADD") == 0){ // adds a data of a train to the existing array of trains

      string s1,s2;
      float t1,t2;
      cin >> s1;
      cin >> t1;   // taking input from the user
      cin >> s2;
      cin >> t2;

      train data;
      data.stat1=s1;
      data.stat2=s2;  // passing the values to the data 
      data.time1=t1;
      data.time2=t2;

      int hash = p.hashValue(s1); // calling the hash function
      int index = p.findFreeIndex(hash);
      p.insert(data);  // calling insert() to add this train to the existing data
    }
    if(strcmp(input,"QUERY_STATION") ==0 ) { // prints the list of all trains starting from that station and >= given time

        string s1;
        float t1;
        cin >> s1;
        cin >> t1;

        p.query1(s1,t1);  // calling query1() to execute the process.
    }
    if(strcmp(input,"QUERY_JOURNEY")==0) { // prints the train which starts at the station at least possible time/soonest train.

        string s1,s2;
        float t1;

        cin >> s1;
        cin >> t1;
        cin >> s2;

        p.query2(s1,t1,s2); // calling query2() to execute the process.
    }

}
}


int main() {
  cout<<"Welcome to rail planner!!"<<endl;
  create();
}