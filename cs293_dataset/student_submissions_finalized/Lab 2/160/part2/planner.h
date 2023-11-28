#ifndef PLANNER_H
#define PLANNER_H
#include <climits>
#include "dictionary.cpp"
//the station has a dictionary of the details of the train
struct Station {
	// define suitable fields here
	char s[32];
	Dictionary d;
};
//It stores journey of train
struct Journey {
	// define suitable fields here
	char st1[32];
	char st2[32];
	int tm1;
	int tm2;

};

struct Query{
	char operation[32];
	char station1[32];
	char station2[32];
	int time1;
	int time2;
};

class Planner {
	// define suitable fields here
	Station startstations[32];Station endstations[32];Journey j[64];int n=0;
//the above line basically means that each station has two dictionaries of the one that come to the station and the ones that leave the station
	public:
	void addjourney(Entry e1,Entry e2){
		string q=e1.key;bool f=0;
		for(int i=0;i<32;i++){
			string p=startstations[i].s;
			if(p==q) {startstations[i].d.put(e2);f=1;}
		}
		if(!f){for(int i=0;i<32;i++){
			string p;p=startstations[i].s;
			if(p=="") {startstations[i].d.put(e2);strcpy(startstations[i].s,e1.key);break;}
		}
		}
		f=0;q=e2.key;
		for(int i=0;i<32;i++){
			string p=endstations[i].s;
			if(p==q) {endstations[i].d.put(e1);f=1;}
		}
		if(!f){for(int i=0;i<32;i++){
			string p=endstations[i].s;
			if(p=="") {endstations[i].d.put(e1);strcpy(endstations[i].s,e2.key);break;}
		}

		}
		strcpy(j[n].st1,e1.key);strcpy(j[n].st2,e2.key);j[n].tm1=e2.value;j[n].tm2=e1.value;n++;
		cout<<"Successfully added"<<endl;
		return;
	}
	void listall(char s1[],int t){
		string q=s1;bool f=0;Entry* e;
		for(int i=0;i<32;i++){
			string p=startstations[i].s;
			if(p==q){
				/*for(int j=0;j<32;j++){
				  if((startstations[i].d.get(endstations[j].s))!=NULL&&(startstations[i].d.get(endstations[j].s)->value>=t)){ cout<<((startstations[i].d.get(endstations[j].s))->key)<<" "<<((startstations[i].d.get(endstations[j].s))->value)<<endl;}
				  }*/
				for(int j=0;j<32;j++){string a;a=endstations[j].s;
					if(a!=""){
						e=startstations[i].d.get(endstations[j].s);
						if(e!=NULL){
							if(e->value>=t) {cout<<e->value<<" "<<e->key<<endl;f=1;}
						}
					}
				}
				if(!f) cout<<"No trains after the given time"<<endl;return;
				break;
			}
		}

		if(!f) {

			cout<<"No such station exists"<<endl;
		}
	}

	void route(char s1[],int t,char s2[]){
		string p,q,r,s,u,v;p=s1;q=s2;bool f=0;int time[20];int a=0;
		for(int i=0;i<n;i++){
			r=j[i].st1;s=j[i].st2;
			if((p==r)&&(q==s)&&(j[i].tm1>=t)){
				f=1;time[a]=i;a++;
			}
		}
		for(int i=0;i<n;i++){
			r=j[i].st1;s=j[i].st2;
			if(p==r){
				for(int x=0;x<n;x++){
					u=r=j[x].st1;v=j[x].st2;
					if((s==u)&&(v==q)&&(j[x].tm1>j[i].tm2)&&(j[i].tm1>=t)){
						time[a]=i;a++;f=1;
					}
				}

			}
		}


		if(!f) cout<<"No path is there"<<endl;
		int min = INT_MAX;
		int index = -1;
		for(int i=0; i < a; i++)
		{
			if(j[time[i]].tm1 < min)
			{    
				min = j[time[i]].tm1;
				index = time[i];
			}
		}

		s=j[index].st2;
		if(s==q) cout<<j[index].tm1<<endl;
		else{
			for(int i=0;i<n;i++){
				string c,d;c=j[i].st1;d=j[i].st2;
				if((c==s)&&(d==q)){
					cout<<j[index].tm1<<" "<<c<<" "<<j[i].tm1<<endl;break;
				}
			}
		}

	}

};

#endif
