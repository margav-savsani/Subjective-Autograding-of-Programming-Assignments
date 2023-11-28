#include "planner.h"
bool Planner::addjourney(Entry a){
	return d.put(a);
}
void Planner::querystation(Query b)
	{
		if (d.get(b.A) == NULL) // if no trains depart from that station 
		{
			cout << "ERROR" << endl;
		}
		else
		{
			Entry *x = d.get(b.A);    
			int count = 0;
			for (int i = 0; x[i].value1 >= 0; i++)  // if we reach the station at X time , then we have to print the trains from station which depart after x 
			{
				if (x[i].value1 >= b.t2)
				{
					cout << x[i].value1 << " " << x[i].key2 << endl;
					count++;
				}
			}

			if (count == 0) // if no trains left to depart 
			{
				cout << "ERROR" << endl;
				return;
			}
		}
		}
	
bool Planner ::journey_exists(Query &b)  // function to find if journey between 2 cities exists or not after a given time 
	{
		if (d.get(b.A) == NULL) // if no trains start from the starting station 
		{
			return false;
		}
		float min = 1000000;
		int count = 0;

		Entry *x = d.get(b.A);

		for (int i = 0; x[i].value1 >= 0; i++) // 
		{
			if (x[i].value1 >= b.t2 && strcmp(x[i].key2, b.B) == 0)
			{
				if (x[i].value1 < min)
					min = x[i].value1;
				count++;
			}
		}
		b.t2 = min; // for our output we need the leaving time from intermediate station 
		return count != 0;
	}
void Planner:: queryjourney(Query c) // 3rd function query_journey 
	{
		if ((d.get(c.A) == NULL))
		{
			cout << "ERROR" << endl; // error if no trains are departing from station A 
		}
		else
		{
			Entry *x = d.get(c.A); 
			float min1 = 1000000; // keeping them large initially so that if some journey exists , we replace it with MINIMUM WHILE COMPARING  
			float min2 = 1000000;
			float t3 = 0;
			char A2[32]; // it will contain the intermediate station 
			A2[0] = 0;

			for (int i = 0; x[i].value1 >= 0; i++)
			{
				if (x[i].value1 < min1 && strcmp(x[i].key2, c.B) == 0 && x[i].value1 >= c.t2) // finding minimum value for a direct train 
				{
					min1 = x[i].value1;
				}
			}
			// cout<<min1<<endl; just for debugging 
			for (int i = 0; x[i].value1 >= 0; i++)// finding minimum time with one intermediate station 
			{

				if (x[i].value1 < min2 && strcmp(x[i].key2, c.B) != 0 && x[i].value1 >= c.t2)
				{
					Query k;
					strcpy(k.A, x[i].key2);
					k.t2 = x[i].value2;
					strcpy(k.B, c.B);
					if (journey_exists(k))
					{
						min2 = x[i].value1;
						strcpy(A2, x[i].key2);
						t3 = k.t2;
					}
				}
			}
			// cout<<min2<<endl;
			if (min1 == 1000000 && min2 == 1000000) // if they are not replaced , it means minimum journey does not exist 
			{
				cout << "ERROR" << endl;
			}
			else if (min1 <= min2)  // simple comparision to print whether a direct journey or an intermediate journey 
			{
				cout << min1 << endl;
			}
			else if (min2 < min1)
			{
				cout << min2 << " " << A2 << " " << t3;
			}
		}
	}
	
