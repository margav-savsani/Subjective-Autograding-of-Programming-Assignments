#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include "sort.cpp"

class Timer  //reference: https://www.learncpp.com/cpp-tutorial/timing-your-code/
{
private:
	// Type aliases to make accessing nested type easier
	using clock_type = std::chrono::steady_clock;
	using second_type = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_type> m_beg { clock_type::now() };

public:
	void reset()
	{
		m_beg = clock_type::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
	}
};

using namespace std;

int main(int argc, char** argv)
{

    Timer t;
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<4); // Valid choice of pivot chooser function
    //choose.cpp has been changed and now contains only three choose functions
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree A(pivot_chooser, num_entries);
    for(int i=0; i<num_entries; i++){
        int JourneyCode, price;
        cin>>JourneyCode>>price;
        Journey *x = new Journey(JourneyCode,price);
        A.array[i] = *x;
    }
    A.QuicksortWithBSTInsert(0,num_entries-1);
    cout << "Time elapsed: " << t.elapsed() << " seconds"<<endl;
    cout<<A.getTree()->getImbalance()<<endl;

}
