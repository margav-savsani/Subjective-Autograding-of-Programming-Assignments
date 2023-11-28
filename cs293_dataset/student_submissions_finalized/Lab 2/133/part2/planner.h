#ifndef PLANNER_H
#define PLANNER_H
#include"dictionary.cpp"

const int N = 64; //number of stations

int get_min(float arr[],int n){
	int min =0;
	for(int i=0;i<n;i++){
		if(arr[min]> arr[i]) min = i;
	}
	return min;
}

struct station{
  // define suitable fields here
  char key[32];
  Dictionary d_start;  
};

bool check(Entry* E, char key[],int k){
	for(int i=0;i<k;i++){
		if(strcmp(E[i].key,key) == 0) return true;
	}
	return false;
}

struct Query{
  // define suitable fields here
  struct Entry* E;
  int n;
}; 

class Planner {
  // define suitable fields here
  	private:    
		struct station S[N];	
		int num_stat=0;
  	public:	
		Planner(){ };	

		int index(char entry[]){		
			int i=0;
			while(i<num_stat){
				if(strcmp(S[i].key,entry) == 0) { break;}
				i++;
			}		
			return i;		
		}

		int num_stations(){
			return num_stat;
		}

		void add_journey(char Entry1[],float time1,char Entry2[],float time2){		
			if(index(Entry1) != num_stat){
				struct Entry data1;
				strcpy(data1.key,Entry2);
				data1.start = time1;
				data1.end = time2;
				S[index(Entry1)].d_start.put(data1);							
			}		
			else{
				struct Entry data1;
				strcpy(data1.key,Entry2);
				data1.start = time1;
				data1.end = time2;
				S[num_stat].d_start.put(data1);
				strcpy(S[num_stat].key,Entry1);						
				num_stat++;
			}							
		}	

		struct Query query_station(char key[],float s_time){
			Query Q;
			int n=0;	
			for(int i=0;i<num_stat;i++){
				if( strcmp(S[i].key,key) == 0){							
					Q.E = S[i].d_start.all_entries(s_time, n);				
					break;
				} 
			}	
			Q.n = n;
			return Q;
		}

		void query_journey(char key1[],float s_time,char key2[]){								
			float array1[num_stat];	
			int array2[num_stat];
			int n=0;
			int s_id = index(key1);
			if (s_id == num_stat) {cout<<"station "<< key1<<" does not exist."<<endl; return;}

			Entry* temp;	
			int k;		
			temp = S[s_id].d_start.all_entries(s_time,k);					
			for(int j=0;j<k;j++){
				if(strcmp(temp[j].key,key2) == 0) {				
				array2[n]= s_id; 
				array1[n]=S[s_id].d_start.get(key2)->start;
				n++;
				}						
			}
			
			for(int p=0;p<num_stat;p++){	
				if(check(temp,S[p].key,k)){
					Entry* temp2;
					int k2;
					temp2 = S[p].d_start.all_entries(S[s_id].d_start.get(S[p].key)->end,k2);											
					for(int j=0;j<k2;j++){
						if(strcmp(temp2[j].key, key2) == 0) {
						array2[n]= p; 
						array1[n]=S[s_id].d_start.get(S[p].key)->start;
						n++;
						}
					}
				}
			}							

			if(n == 0) cout<<"It seems like there are no trains to "<< key2<<" during that time."<<endl;
			else{
				int i = get_min(array1,n);
				if(array2[i] == s_id) cout<<array1[i]<<endl;
				else cout<<array1[i]<<" "<<S[array2[i]].key<<" "<<S[array2[i]].d_start.get(key2)->start<<endl;;			
			}
		}
};

#endif