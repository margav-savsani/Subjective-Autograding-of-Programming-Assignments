template <typename T> class array{
    int INIT_SIZE = 5;
    int GROW_SIZE = 3;
    T* A;
public:
    int size = INIT_SIZE;
    array(){
        A = new T[INIT_SIZE];
    }
    void grow();
    T& operator[](int idx){
        if(idx == size) grow();
        return A[idx];
    }
};