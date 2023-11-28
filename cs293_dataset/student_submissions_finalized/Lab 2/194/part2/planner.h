#ifndef PLANNER_H
#define PLANNER_H

struct Journey
{
	// define suitable fields here
	char station_1[32];
	char station_2[32];
	float start_time;
	float end_time;
};

class Planner
{
	// define suitable fields here
public:
	Journey *journey;
	int N;
	Planner()
	{
		N = 64;
		journey = new Journey[N];
		for (int i = 0; i < N; i++)
		{
			strcpy(journey[i].station_1, "");
		}
	}

	int hashValue(char key[]);

	bool put(Journey j);
};

#endif

int Planner::hashValue(char key[])   //same as inlab
{
	int prev_overflow = 1e7 + 19;
	int hash_val = 0;
	int x_pow = 1;
	int x = 37;
	for (int i = 0; key[i] != '\0' && i < 32; i++)
	{
		hash_val = (hash_val + ((key[i] - 'a' + 1) * x_pow)) % prev_overflow;  //polynomial accumulation
		x_pow *= x;
	}
	int comp_val;
	double B = (sqrt(5) - 1) / 2;
	int m = 64;
	double temp = (B * hash_val) - floor(B * hash_val);
	comp_val = (floor((temp)*m));  //compression
	comp_val = comp_val % m;  
	return comp_val;
}

bool Planner::put(Journey j)  //store the journey in planner
{
	int hash_val = hashValue(j.station_1);
	for (int i = hash_val;; i = (i + 1) % 64)
	{
		if (strcmp("", journey[i].station_1) == 0)  //if empty slot then store
		{
			journey[i]=j;
			return true;
		}
		if (i == hash_val - 1)  //all spots checked
		{
			return false;
		}
	}
	return false;
}
