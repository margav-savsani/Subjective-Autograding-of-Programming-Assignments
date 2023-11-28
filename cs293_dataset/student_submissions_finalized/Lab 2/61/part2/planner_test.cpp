#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<cmath>
#include"planner.cpp"
#include"planner.h"

//Note for TA: I have not explicitly used the dictionary created in the inlab. Instead, I have implemented the dictionary within the planner class itself.

int main(){
    planner p;
    
 for(int i=0;i>=0;i++)
  {
    string input;
    cout << ">>> " ;
    cin>>input;
    if(input=="EXIT"){
      break;
    }

    // INS <key> <value>
    if(input=="ADD"){
         
     
      string s1,s2;
      int t1,t2;
      cin >>s1;
      cin>> t1;
      cin >> s2;
      cin>>t2;
      struct train entry;
      entry.stn1=s1;
      entry.stn2=s2;
      entry.st_time=t1;
      entry.end_time=t2;
      bool done=p.findlocation_insert(entry);
      if(done){
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }

    }

    // DEL <key>
    else if(input=="QUERY_STATION"){
      string s1;
      int t1;
      cin>>s1;
      cin>>t1;
      vector<struct train> v=p.query1(s1,t1);
      if(v.size()==0){
        cout<<"ERROR\n";
        continue;
      }
      for(auto t:v){
        cout<<t.st_time<<" ";
        cout<<t.stn2<<endl;
      }
     
    }

    // FIND <key>
    else if(input=="QUERY_JOURNEY"){
      string s1;
      int t1;
      string s2;
      cin>>s1;
      cin>>t1;
      cin>>s2;
      p.query2(s1,t1,s2);
    
    }
    else{
      continue;
    }
  }
}
 
