#include "planner.h"

planner::planner() {
    N = Max_size;
    A = new train[N]; // creating an dynamic array of size Max_size.
}

int planner :: get_size() {
    return size;  // returns the number of trains in the data
}

void planner :: insert(train t) {
    if(size >= N)  {
        cout << "error!!There is no enough space for this train:("<<endl; // error if there is no space in the array.
        return;
    }
    int index = findFreeIndex(hashValue(t.stat1));
		if(index == -1) {
			cout << "error!!No place to insert"<<endl; // there is no free place to insert.
            return;
		}
		A[index] = t;
		A[index].is_empty = false; // changing the status of is_empty
        size++;                    // incrementing size
		cout << "succesfully added!"<<endl;
}

void planner :: print_data(train t) { // a function to print the data of a particular train
    cout << "first_station "<<t.stat1;
    cout << "second_station "<<t.stat2;
    cout << "start_time "<<t.time1;
    cout << "end_time "<<t.time2;
}

vector<train> planner :: query1(string s, float t) { // it is simply query_station
    bool ch=false;
    vector<train> t1;
    for(int i=hashValue(s); i<N; i++) {
        if(s==A[i].stat1) { // checking for the required train in the array
            if(A[i].time1>=t) { // A[].start_time should be greater than start_time
                cout << A[i].time1 << " "<<A[i].stat2 << endl; // printing the required values
                ch=true;
                t1.push_back(A[i]); // pushing it into vector for further use 
                                    // but, I haven't implemented that further part ;(
            }
        }
    }
    if(!ch) {
        cout << "No train statisfies the required conditions :(" << endl;
    }
    return t1;
}

int planner :: hashValue(string s) {
        int a=0,x=37; // for decreasing the number of collisions.
		for(int j=s.length()-1;j>=0;j--) {
			a = (int(s[j])+x*a); // computing the integer
		}
		double b = a*(0.618);
		double intpart,fracpart;
		fracpart = modf(b,&intpart); // to obtain the fractional part
		return int(48*fracpart); //returning value should be (<= size) and (>=0)
}

int planner :: findFreeIndex(int hash) { // finding the free index
		for(int i=hash; i<N; i++) {
			if(A[i].is_empty==true) {
				return i;
			}
		}
		return -1; // if there is no free index to insert
}

pair<int,int> planner :: direct(string s1,float t,string s2) {
    int hash=hashValue(s1);  // computing the hashvalue
        vector<pair<int,int>> v1;
        for(int i=hash; i<N; i++) {
            if((A[i].time1 >= t)&&(A[i].stat2==s2)&&(A[i].stat1==s1)) {
                v1.push_back(make_pair(i,A[i].time1)); // when I found the correct train, I push it into the vector
            }
        }
        int a=v1[0].second,x=0,m=0;
        for(int i=0;i<v1.size();i++) { // to find the soonest train.
             m = v1[i].second;
             if(m<=a) {
                a=m;
                x=v1[i].first;
             }
        }
        cout << A[x].time1 <<" "<<s2<<endl; // printing the required data
        if(a==0) {
            cout <<"doesn't exist"<<endl;   // error message
        }
        return make_pair(x,m);
}
void planner :: query2(string s1,float t,string s2) {
        // direct travel
        pair<int,int> p = direct(s1,t,s2);
        // x contains i, a contains least time
        // pair<a,b> => a=index, b=start_time

        // exactly one station in between
}