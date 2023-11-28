    #include "dictionary.h"
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    int Dictionary :: hashValue(char key[]){
        int i = 0;
        int factor = 39;
        int sum = 0;
        for(int i = 0; key[i] != '\0'; i++){
            sum = sum*factor + int(key[i]);
        }
        int m = N;
        return sum%m;
    };    
    
    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int Dictionary :: findFreeIndex(char key[]){
        int location = hashValue(key);
        int start = location;
        while(true){
            if(A[location].key[0] == '\0'){
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
            if(A[place].key[0] == '\0') return NULL;
            else if(A[place].location == place)return &A[place];
            else if(start = place)return NULL;
            else place = (place+1)%N;
        }
    };

    // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
    bool Dictionary :: put(struct Entry e){
        e.location = findFreeIndex(e.key);
        int place = e.location;
        while(true){
            if(A[place].key[0] = '\0'){
                A[place] = e;
                e.location = place;
                break;
            }
            else{
                place = (place+1)%DICT_SIZE;
                if(e.location == place) return false;
            }
        }
        return true;
    };   
    
    // Remove the given key; return true if success, false if failure (given key not present)
    bool Dictionary :: remove(char key[]){
        Entry* ele_rem = get(key);
        if (ele_rem == NULL) return false;
        ele_rem->location = N+1;
        std::string a = "tomb";
        ele_rem->key = &a[0];
        return true;
    };