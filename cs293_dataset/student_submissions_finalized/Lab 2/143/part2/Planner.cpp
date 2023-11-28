#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;



struct Entry{   //struct entry stores the start station,start time end station,end time
    string key1;
    float value1;
    string key2;
    float value2;
};
class Planner{
    struct Entry *ele;
    int *A;
    public:
        Planner(){   //initialises the arrays ele,A
            ele = new Entry[64]; 
            A= new int[64];
            for(int i =0;i<63;i++){
                A[i] = 0;
            }  
        }
        int hashValue(string key){ //returns the hashvalue of the key
            int x = 33;
            long long unsigned int y = 0;
            int num = 0;
            for(int i = 0;key[i]!= '\0';i++){
                num++;
            }
            for(int i = num - 1 ;i>=0;i--){
                y = y*x + key[i];
            }
            int hash;
            double c = y*((sqrt(5) - 1)/2.0); 
            int d = 64*(c - int(c));
            hash = d%64;
            return hash;
            }
        int findFreeIndex(string key){ //will find the free index to insert the key
            int count = 1;
            int a = hashValue(key);
            while(count<=64){
            if(A[a]==0){
                return a;
            }
            a = (a+1)%64;
            count++;
        }
        return -1;
        }

        void ADD(string tat1,float time1,string tat2,float time2){ //will add elements to the array ele and set A[i] to 1
            int free = findFreeIndex(tat1);
            ele[free].key1=tat1;
            ele[free].value1=time1;
            ele[free].key2=tat2;
            ele[free].value2=time2;
            A[free]=1;
            cout<<"train is scheduled from "<<tat1<<" "<<time1<<" to "<<tat2<<" "<<time2<<endl;
            }
        void QUERY_STATION(string stat1,float ttime1){//will print all the trains starting from first station and above the start time
            int d = hashValue(stat1);
            int check = 0;
            while(A[d]!=0){
                if(ele[d].key1==stat1 && ele[d].value1>=ttime1 ){
                    cout<<ele[d].value1<<" "<<ele[d].key1<<endl;
                    check++;
                }
            d = (d+1)%64;
            }
            if(check==0){
                cout<<"there are no such trains"<<endl;
            }
        }
        bool QUERY_JOURNEY(string station1,float starttime,string station2){//will print the path of the train to reach from 1st station to the next with atmost 1 intermediate station
            int d3 = hashValue(station1);
            int count = 0;
            int *inter;
            inter = new int[64];
            while(A[d3]!=0){
                if(ele[d3].key1==station1&& ele[d3].value1>=starttime ){
                    inter[count]=d3;
                    count++;
                }
                d3 = (d3+1)%64;
            }
            for(int i = 1;i<count;i++){
                 while(ele[i].value1<ele[i-1].value1){
                    int x = inter[i - 1];
                    inter[i - 1] = inter[i];
                    inter[i] = x;
                }
            }   
    
            for(int i = 0;i<count;i++){
                if(ele[inter[i]].key2==station2){
                    cout<<ele[inter[i]].value1<<endl;
                    return true;
                 }
                else{
                    int d4 = hashValue(ele[inter[i]].key2);
                    int count1=0;
                    int*inter1;
                    inter1=new int[64];
                    while(A[d4]!=0){
                        if(ele[d4].key1==ele[inter[i]].key2 && ele[d4].value1>=ele[inter[i]].value2){
                        inter1[count1]=d4;
                        count1++;
                    }
                    d4 = (d4+1)%64;
                    }
                    for(int i1 = 1;i1<count1;i1++){
                        while(ele[i1].value1<ele[i1-1].value1){
                            int x = inter1[i1 - 1];
                            inter1[i1 - 1] = inter1[i1];
                            inter1[i1] = x;
                    }
                    }
                    for(int i1 = 0;i1<count1;i1++){
                        if(ele[inter1[i1]].key2==station2){
                            cout<<ele[inter[i]].value1<<" "<<ele[inter1[i1]].key1<<" "<<ele[inter1[i1]].value1<<endl;
                            return true;
                        }   
                     }
            


                    }
            }
            return false;
        }

};
void PlannerHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"QUIT") == 0){
      break;
    }

    
    if(strcmp(input,"ADD") == 0){
      string inputstation1;
      cin >> inputstation1;
      
      float inputtime1;
      cin >> inputtime1;
     
      string inputstation2;
      cin >> inputstation2;
     
      float inputtime2;
      cin >> inputtime2;
      planner.ADD(inputstation1,inputtime1,inputstation2,inputtime2);
     
    }
    if(strcmp(input,"QUERY_STATION")==0){
        char inputstation1[32];
        cin >> inputstation1;
        float inputtime1;
        cin >> inputtime1;
        planner.QUERY_STATION(inputstation1,inputtime1);
    }
    if(strcmp(input,"QUERY_JOURNEY")==0){
        char inputstation1[32];
        cin >> inputstation1;
        float inputtime1;
        cin >> inputtime1;
        char inputstation2[32];
        cin >> inputstation2;
        if(!planner.QUERY_JOURNEY(inputstation1,inputtime1,inputstation2)){
            cout<<"there is no such train"<<endl;
        }

    }
    
  }
}


void interactive()
{
  cout<<"hi"<<endl;
  Planner planner;
  PlannerHandler(planner);
}


int main()
{
   
  cout<<"Enter 1 for interactive testing"<<endl;
  int which;
  cin>>which;
  
  if(which == 1){
    interactive();
  }
  
  return 0;
}