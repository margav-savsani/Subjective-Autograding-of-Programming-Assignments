#include "planner.h"
#include<iostream>
#include "dictionary.cpp"
#include<string>
using namespace std;
#include<sstream>
#include<cstring>

Planner::Planner(){}


void Planner::take_query(string query){ //it is fed with the input taken from user
	
	Query q;//where all the seperate components of the input is stored 
	stringstream iss{query};		//stringstream to process the input taken from user
	string word;
	int i=0;
	while(iss>>word){
		q.query[i]=word;
		i++;//processing and storing the user input
	}
	
	if(q.query[0]=="ADD" && i==5){	//the class implementing the part where we have to add journeys
		char k[32];
		strcpy(k, q.query[1].c_str());
		Station *s=station.get(k);
		if(s==NULL){
			Station sq;
			strcpy(sq.key, q.query[1].c_str());
			add_start_station(sq);
		}
		
		strcpy(k, q.query[1].c_str());
		s=station.get(k);
		strcpy(k, q.query[3].c_str());
		Journey j;
		strcpy(j.stop, k);
		j.t1 = stof(q.query[2]);
		j.t2 = stof(q.query[4]);
		s->j.add(j);
	}
	
	else if(q.query[0]=="QUERY_STATION" && i==3){ //the part where the Query station command is processed 
		char k[32];
		strcpy(k, q.query[1].c_str());
		float time = stof(q.query[2]);
		query_station(k ,time);
	}
	
	else if(q.query[0] == "QUERY_JOURNEY" && i==4){// the part where the Query_Journey command is processes 
		char start[32];
		strcpy(start, q.query[1].c_str());
		float time = stof(q.query[2]);
		char stop[32];
		strcpy(stop, q.query[3].c_str());
		query_journey(start, time, stop);
	}
	
}

void Planner::add_start_station(Station s){
	if(!station.put(s))	//If new station cannot add because of filled dictionary, show this message
		cout<<"Sorry no space left in the dictionary of 64 items "<<endl;
}


void Planner::query_station(char k[], float time){
	Station *s=station.get(k); // gets the pointer to the dictionary object
	if(s!=NULL){	//confirming that the station is added in the dictionary or the command is apt otherwise it shows error message
		int index = s->j.find(time);
		if(index < s->j.size){
			for(int i=index ; i<s->j.size ; i++){
				cout<<s->j[i].t1<<" "<<s->j[i].stop<<endl;
			}
		}
		else{
			cout<<"Error"<<endl;	//If no journey is there beyond the given time show error message
		}
	}
	
	else{
		cout<<"Error"<<endl;
	}
}

void Planner::query_journey(char start[], float time, char stop[]){//responsible for finding the earliest start time journey possible from station start to station stop after time *time*

	Station *s = station.get(start);
	if(s!=NULL){//checks whether the start station is valid (or added in the planner dictionary). If not displays the error message
		int index1 = via_0_stop(start, time, stop);	//calles a member method responsible for finding journey via 0 stop 
		int index2 = via_1_stop(start, time, stop);//calls a member method repsonsible for finding journey via 1 stop 
		if(index1 == -1 && index2 == -1){
			cout<<"Error"<<endl;		//If can't find any journey show the error message
		}
		
		else if(index1== -1 && index2!= -1){
			Station *s1 = station.get(s->j[index2].stop);
			int index3 = via_0_stop(s->j[index2].stop, s->j[index2].t1, stop);
			cout<<s->j[index2].t1<<" "<<s->j[index2].stop<<" " << s1->j[index3].t1<<endl;//Print statement required to show to the user
			return;
		}
		
		else if(index1 != -1 && index2 == -1){
			cout<< s->j[index1].t1 <<endl;// Print statement requred to show to the user
			return;
		}
		
		else if(index1 != -1 && index2 != -1){
			if(s->j[index1].t1>= s->j[index2].t1){
				Station *s1 = station.get(s->j[index2].stop);
				int index3 = via_0_stop(s->j[index2].stop, s->j[index2].t1, stop);
				cout<<s->j[index2].t1<<" "<<s->j[index2].stop<<" " << s1->j[index3].t1<<endl;//Print statement required to show to the user
				return;
			}
			
			else{
				return;
			}
		}
		
	}
	else{
		cout<<"Error"<<endl;
	}
}


int Planner::via_0_stop(char start[], float time, char stop[]){//Plans the journey without a stop
	Station *s = station.get(start);
	if(s != NULL){
		int index = s->j.find(time);
		for(int i=index; i<s->j.size ; i++){
			if(strcmp(s->j[i].stop,stop) == 0){
				return i;
			}
		}
	}
	return -1;
}

int Planner::via_1_stop(char start[], float time, char stop[]){//Plans a journey with only 1 stop. It takes the help of via_0_Stop member method as well 
	Station *s = station.get(start);
	int index = s->j.find(time);
	for(int i=index; i<s->j.size ; i++){
		int index2 = via_0_stop(s->j[i].stop, s->j[i].t2, stop);
		if(index2 != -1)
			return i;
	}
	return -1;
}

//Implementation of class Planner is done. From here on implementation of class SortedArray is done. This is created so as to store the time in such a data structure such that when we need to find a breakpoint (eg greater then this time ) we can find it rather easily. 
//Hence sorted array is used .








// #################################################################  //
// #################################################################  //


//constructor of SortedArray class 
SortedArray::SortedArray(){
	growth_constant = 10;		//used so as to grow the array when needed. Yes I have created a dynamiccaly growing array so as to accomodate any number of journeys from station A to any other station
	size = 0; // keeps check on the size of the array 
	ptr = new Journey[growth_constant]; //ptr responsible for storing the array of journeys 
	N = growth_constant;	//it is the overall size of the array
}

int SortedArray::find(float element){//perhaps the most important methos of this class. It is responsible for finding the right position, through iterative algorithm of binary sort, where to put the element (whethere or not it is alreadey there ) or find the index of the element  
	int head{0};
	int tail{size-1};
	while(true){
		if(head > tail)
			return head;
		
		int m= (head+tail)/2;
		if(ptr[m].t1 <= element+0.0001 && ptr[m].t1 >= element-0.0001){
			int i=m;
				while(i>0){
					if(ptr[i-1].t1 <= element+0.0001 && ptr[i-1].t1 >= element-0.0001){
						i--;
						continue;
					}
					else
						break;
				}
				return i;
		}
		if(ptr[m].t1>element){
			tail = m-1;
			continue;
		}
		if(ptr[m].t1<element){
			head = m+1;
			continue;
		}
	}
	return -1;
} 

void SortedArray::add(Journey element){	//adds the element, It uses find member method and grow member method
	if(size == N) //if size == N grow the array
		grow();
	int index = find(element.t1);
	
	for(index; index<size+1;){
		if(ptr[index].t1 <= element.t1+0.0001 && ptr[index].t1 >= element.t1-0.0001){
			index++;
			continue;
		}
		else
			break;
	}
	
	for(int i=size-1;i>index-1;i--){//shifts the array to accomdate the new element to be added at its required position to maintain order in the array (SortedArray)
		ptr[i+1].t1=ptr[i].t1;
		ptr[i+1].t2=ptr[i].t2;
		strcpy(ptr[i+1].stop, ptr[i].stop);
	}
	ptr[index]=element;
	size++;
}


Journey& SortedArray::operator[](int a){ //operator overloading of [] operator so that the code writer for anything using Sorted Array feels as home and can use array[index] to refer to the position of the array 
	if(a<size)
		return ptr[a];
	else{
		cout<<"Incorrect index"<<endl;
		return ptr[size-1];
	}	 
}

void SortedArray::grow(){ //dynamically grows the array when needed 
	Journey *ptr2 = new Journey[N+growth_constant];
	N+=growth_constant;
	for (int i=0;i<size;i++){
		ptr2[i].t1=ptr[i].t1;
		ptr2[i].t2=ptr[i].t2;
		strcpy(ptr2[i].stop, ptr[i].stop);
	}
	delete[] ptr;
	ptr = ptr2;
	ptr2 = nullptr;
}


