#include <iostream>
using namespace std;
#include <math.h>
#include <string.h>

int DICT_SIZE = 64;

struct Entry {
	char* key;
	char* station_one;
	float start_time;
	char* station_two;
	float finish_time;
	bool null=true;
  // define suitable fields here
};
//dictionary.cpp form the part 1 is used without the header file and slight modifications
class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries
 public:
  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]){
  	//hash table
  	int i=0;
	const int p = 31;
    int hash = 0;
    long p_pow = 1;
    while(key[i]!='\0'){
        hash = (hash + (key[i] - 'a'+1) * p_pow) % N;
        p_pow = (p_pow * p) % N;
		i++;
    }
  	return hash;
  }		

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]){
  	int index;
  	for(index=hashValue(key);(!(A[index].null));index++){
  		if(index==N){return -1;}
  	}
  	return index;
  } 
  // Default constructor
  Dictionary(){
  	N=DICT_SIZE;
  	A=new Entry[N];
  }

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  char* get_station_one(char key[]){
  	int index=hashValue(key);
  	while(index<N){
		if(A[index].null){
			return NULL;
		}
 		if(strcmp(A[index].key,key) == 0){
 			return (A[index].station_one);
 		}
 		index++;
  	}
  	return NULL;
  }
    char* get_station_two(char key[]){
  	int index=hashValue(key);
  	while(index<N){
		if(A[index].null){
			return 0;
		}
 		if(strcmp(A[index].key,key) == 0){
 			return A[index].station_two;
 		}
 		index++;
  	}
	return 0	;
  }
    int get_start_time(char key[]){
  	int index=hashValue(key);
  	while(index<N){
		if(A[index].null){
			return 0;
		}
 		if(strcmp(A[index].key,key) == 0){
 			return (A[index].start_time);
 		}
 		index++;
  	}
  	return 0;
  }
	int get_finish_time(char key[]){
  	int index=hashValue(key);
  	while(index<N){
		if(A[index].null){
			return 0;
		}
 		if(strcmp(A[index].key,key) == 0){
 			return A[index].finish_time;
 		}
 		index++;
  	}
  	return 0;
  }
	
  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e){
	int index=hashValue(e.key);
	if(index==-1){return false;}
	A[index].key=e.key;
	A[index].finish_time=e.finish_time;
	A[index].start_time=e.start_time;
	A[index].station_one=e.station_one;
	A[index].station_two=e.station_two;
	A[index].null=false;
	return true;
  }

  void query_one(char station_one[],int start_time){
	for(int i=0;i<N;i++){
		//complete search to check if there is an element with matching station_one
		if(!(A[i].null)&&(strcmp(A[i].station_one,station_one)==0))
        {int a=A[i].start_time;
		//if start time is greater than that of input value then print it
		if(a>start_time){
			cout<<a<<" "<<A[i].station_one<<"\n";
		}}
		}
	
  }
  void query_two(char s_one[],int s_time,char s_two[]){
		float diff;
		int min=0;
		bool first=true;
		bool inter=false;
		int inter_start_time;
  		int j=0;
		for(int index=0; index<N; index++){
      		if(!(A[index].null)&&(!(A[index].key[0]=='\0'))&&(strcmp(A[index].station_one, s_one) == 0)){
				if(A[index].start_time>=s_time){
					cout<<A[index].station_two<<index;
					if(strcmp(A[index].station_two,s_two)==0){
						if(first){
							cout<<index;
							min=index;
							diff=A[index].start_time-s_time;
							first=false;
						}
						else if(diff>A[index].start_time-s_time){
							cout<<index;
							min=index;
							diff=A[index].start_time-s_time;
							inter=false;
						}
      				}
					else{
						for(int j=0; j<DICT_SIZE; j++){
      						if(!(A[j].null)&&(!(A[j].key[0]=='\0'))&&(strcmp(A[j].station_one, s_two) == 0)){
								if(A[j].start_time>=A[index].start_time){
									if(strcmp(A[j].station_two,s_two)==0){
										if(diff>A[j].start_time-s_time){
											min=index;
											diff=A[index].start_time-s_time;
											inter=true;
											inter_start_time=A[j].start_time;
										}
									}
								}
							}
						}
					}
				}
    		}
		}
		if(first){
      		cout<<"no train exist between the two stations after the input start time"<<"\n";
      	}
      	else if(inter){
      		cout<<A[min].start_time<<A[min].station_two<<inter_start_time;
      	}	
      	else{      		
      		cout<<A[min].start_time<<"\n";
		}
  }

//   void query(char station_one[],float start_time){
//   		int j=0;
// 		cout<<A[4].value.station_one;
//       	for(int index=0; index<DICT_SIZE; index++){
//       		if(!(A[index].null)&&(!(A[index].key[0]=='\0'))&&(strcmp(A[index].value.station_one, station_one) == 0)){
//       		if(A[index].value.start_time>=start_time){
// 				cout<<A[index].value.start_time<<" "<<A[index].value.station_two<<"\n";
// 				j++;
// 			}
//   		}
//     }
//   }
//   void fun(char station_one[],float start_time,char station_two[]){
// 		float diff;
// 		int min=0;
// 		bool first=true;
// 		bool inter=false;
// 		int inter_start_time;
//   		int j=0;
// 		get(station_one);
// 		// cout<<A[4].value.station_one;
// 		// for(int index=0; index<DICT_SIZE; index++){
//       	// 	if(!(A[index].null)&&(!(A[index].key[0]=='\0'))&&(strcmp(A[index].value.station_one, station_one) == 0)){
// 		// 		if(A[index].value.start_time>=start_time){
// 		// 			if(strcmp(A[index].value.station_two,station_two)==0){
// 		// 				if(first){
// 		// 					cout<<"hello";
// 		// 					min=index;
// 		// 					diff=A[index].value.start_time-start_time;
// 		// 					first=false;
// 		// 				}
// 		// 				else if(diff>A[index].value.start_time-start_time){
// 		// 					cout<<"nope";
// 		// 					min=index;
// 		// 					diff=A[index].value.start_time-start_time;
// 		// 					inter=false;
// 		// 				}
//       	// 			}
// 		// 			else{
// 		// 				for(int j=0; j<DICT_SIZE; j++){
//       	// 					if(!(A[j].null)&&(!(A[j].key[0]=='\0'))&&(strcmp(A[j].value.station_one, station_two) == 0)){
// 		// 						if(A[j].value.start_time>=A[index].value.start_time){
// 		// 							if(strcmp(A[j].value.station_two,station_two)==0){
// 		// 								if(diff>A[j].value.start_time-start_time){
// 		// 									cout<<"hi";
// 		// 									min=index;
// 		// 									diff=A[index].value.start_time-start_time;
// 		// 									inter=true;
// 		// 									inter_start_time=A[j].value.start_time;
// 		// 								}
// 		// 							}
// 		// 						}
// 		// 					}
// 		// 				}
// 		// 			}
// 		// 		}
//     	// 	}
// 		// }
// 		// if(first){
//       	// 	cout<<"no train exist between the two stations after the input start time"<<"\n";
//       	// }
//       	// else if(inter){
//       	// 	cout<<"yup"<<A[min].value.start_time<<A[min].value.station_two<<inter_start_time;
//       	// }	
//       	// else{      		
//       	// 	cout<<A[min].value.start_time<<"\n";
// 		// }
// 	}	
			
  
  
  //Remove the given key; return true if success, false if failure (given key not present)
//   bool remove(char key[]){
//   	Entry* element;
// 	element=get(key);
// 	if(element==NULL){
// 		return false;
// 	}
// 	char n='\0';
// 	element->key=&n;
// 	//strcpy(element->key, .c_str());
//   	return true;	
//   }
};
