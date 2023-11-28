template <typename T> class vector {
public:
	T* arr;
	int capacity ; 
	int current;
	vector(){
		arr = new T[1];
		capacity = 1;
		current = 0;
	}
	void push_back(T data)
	{
		if (current == capacity) { //grow 
			T* temp = new T[2 * capacity];
			for (int i = 0; i < capacity; i++) {
				temp[i] = arr[i];
			}
            delete[] arr;
			capacity *= 2;
			arr = temp;
		}
		arr[current] = data;
		current++;
	}
	int size() { return current; }
    T& operator[](int i ) { return arr[i]; } 
}; 

