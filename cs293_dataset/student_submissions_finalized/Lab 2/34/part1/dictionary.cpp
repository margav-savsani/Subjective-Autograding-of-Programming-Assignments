    #include "dictionary.h"
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    int Dictionary :: hashValue(char key[]){
        int i = 0;
        int factor = 39;
        int sum = 0;
        for(int i = 0; key[i] != '\0'; i++){
            sum = (sum*factor + int(key[i]))%(1000000);
        }
        double fibonacci_factor = (sqrt(5)-1)/2;
        double fractional = sum*fibonacci_factor - int(sum*fibonacci_factor);
        int m = N;
        return int(fractional*m);
    };    
    
    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int Dictionary :: findFreeIndex(char key[]){
        int location = hashValue(key);
        int start = location;
        while(true){
            if(A[location].key == NULL or A[location].tomb){
                A[location].tomb = false;
                return location;
            }
            location = (location+1)%N;
            if(location == start) return -1;
        }
    };

    // Default constructor
    Dictionary :: Dictionary(){
        N = DICT_SIZE;
        A = new Entry[N];
    };  

    // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
    struct Entry* Dictionary :: get(char key[]){
        int place = hashValue(key);
        int start = place;
        while(true){
            if(A[place].key == NULL) {
                std::cout << "yes\n";
                return NULL;
                std::cout << "Not executed\n";}
            else if(A[place].key == key && !A[place].tomb){
                std::cout << key << std::endl;
                return &A[place];
            }
            else{
                place = (place+1)%N;
                if(start == place)
                    return NULL; 
            }
        }
    };

    // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
    bool Dictionary :: put(struct Entry e){
        int place = findFreeIndex(e.key);
        int start = place;
        while(true){
            if(A[place].key == NULL){
                A[place] = e;
                break;
            }
            else{
                place = (place+1)%DICT_SIZE;
                if(start == place) return false;
            }
        }
        return true;
    };   
    
    // Remove the given key; return true if success, false if failure (given key not present)
    bool Dictionary :: remove(char key[]){
        Entry* ele_rem = get(key);
        if (ele_rem == NULL) return false;
        // ele_rem->location = N+1;
        ele_rem->tomb = true;
        return true;
    };