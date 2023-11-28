#include "dictionary.h"
#include <math.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;

const ull MOD = 1000000007ll;
const int HORNER_X = 41;
// int polynomial_coeffs[31] = {48, 16, 78, 7, 17, 62, 24, 75, 57, 92, 90, 70, 47, 45, 70, 16, 99, 71, 5, 64, 91, 4, 51, 58, 78, 51, 69, 86, 12, 25, 17};

// inline ll abs(ll inp){return inp<0?-inp:inp;}

ull polyAccumulation(char*);
ull fibHash(ull);
/**
 * @brief Computes the power modulo MOD given base and exponent 
 * 
 * @param a Base
 * @param b Exponent
 * @return ll (a^b)%MOD
 */
ll modPower(ll a, ll b){
    ll res = 1;

    while(b){
        if(b&1) res = (res*a)%MOD;
        b >>= 1;
        res = (res*res)%MOD;
    }

    return res;
}

/**
 * @brief Construct a new Dictionary:: Dictionary object
 * Initialises the internal dictionary and size to appropriate values. 
 */
Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];

    for(int i=0; i<N; i++){
        strcpy(A[i].key, "");
    }
}

/**
 * @brief Gets the entry corresponding to the given key
 * 
 * @param key - The key corresponding to the entry that is to be obtained 
 * @return struct Entry* - The corresponding entry
 */
struct Entry* Dictionary::get(char key[]){
    int target_loc = this->hashValue(key);

    int locations_checked = 0;
    while(this->A[target_loc].value != VAL_NULL){
        locations_checked++;
        if(locations_checked >= this->N) return nullptr;

        if(!strcmp(this->A[target_loc].key,key)) return this->A + target_loc;

        target_loc++;
        target_loc = target_loc%N;
    }

    return nullptr;
}

/**
 * @brief Attempts to put a new entry (e) in the dictionary. Returns true if it succeeds to do this, otherwise false.
 * 
 * @param e - The entry to be put into the dictionary
 * @return true - If successful
 * @return false - If failed
 */
bool Dictionary::put(struct Entry e){
    int free_loc = this->findFreeIndex(e.key);
    if(free_loc == -1) return false;

    this->A[free_loc].value = e.value;
    // this->A[free_loc].key = e.key;
    strcpy(this->A[free_loc].key, e.key);

    return true;
}

/**
 * @brief - Removes the entry corresponding to the given key 
 * 
 * @param key - The target key
 * @return true - If element present and successfully removed
 * @return false - If element not present in the array
 */
bool Dictionary::remove(char key[]){
    Entry* target = this->get(key);
    if(target==nullptr) return false;

    strcpy(target->key, "");
    target->value = VAL_TOMBSTONE;

    return true;
}

/**
 * @brief - Finds the first free index present in the dictionary's array 
 * 
 * @param key - The key corresponding to which the free index is to be found. 
 * @return int - The respective free index. -1 if no such free index present.
 */
int Dictionary::findFreeIndex(char key[]){
    int target_loc = this->hashValue(key);

    int locations_checked = 0;
    while(this->A[target_loc].value != VAL_NULL && this->A[target_loc].value != VAL_TOMBSTONE){
        locations_checked++;
        if(locations_checked >= this->N) return -1;

        target_loc++;
        target_loc = target_loc%N;
    }

    return target_loc;
}

/**
 * @brief Computes the hash value corresponding to some key
 * 
 * @param key - The key for which the hash value is to be calculated
 * @return int - The hash value for the key
 */
int Dictionary::hashValue(char key[]){
    return (int)fibHash(polyAccumulation(key));
}

/**
 * @brief - Applies polynomial accumulation on the given key 
 * 
 * @param key 
 * @return ll - The result of polynomial accumulation 
 */
ull polyAccumulation(char key[]){
    int i;
    ull res=0ll;
    for(i=0;i<KEY_MAX_LENGTH; i++){
        if(key[i]=='\0') break;

        res += ((int)key[i])*modPower(HORNER_X,i);
        
        res = res % MOD;
    }

    return res;
}
/**
 * @brief - Applies the fibonacci hash function to a given integer 
 * 
 * @param k 
 * @return ll
 */
ull fibHash(ull k){
    double fact1 = FIB_MULT * k;
    fact1 = fact1 - (ull)fact1;

    return (ull)(fact1*DICT_SIZE);
}


void test__polynomialAccumulation(){
    char inp[32];
    ll res;
    while(true){
        cin >> inp;
        res = polyAccumulation(inp);
        cout << "Polynomial accumulation: " << res <<"\n";
        res = fibHash(res);
        cout << "After FibHash: " << res << "\n";
    }
}

void test__dictionary(){
    Dictionary d;
    cout<<"Hash value: "<<d.hashValue("dheerbanker")<<"\n";
    cout<<"Free index: "<<d.findFreeIndex("dheerbanker")<<"\n";
    Entry newEntry;
    strcpy(newEntry.key, "dheerbanker");newEntry.value=43;
    cout<<"Put ('dheerbanker',43) success?: "<< d.put(newEntry) <<"\n";
    cout<< "Returns nothing: "<<(d.get("dheerbanker")==nullptr)<<"\n";
    // cout<<"Get 'dheerbanker': "<<(*(d.get("dheerbanker"))).value<<"\n";
    cout<<"Remove 'dheerbanker': "<<d.remove("dheerbanker")<<"\n";
    cout<<"Get 'dheerbanker': "<<d.get("dheerbanker")<<"\n";
}

void printDictionary(Dictionary& d){
    Entry* a = d.getDictArray();

    cout<<"Key  - \tValue";
    for(int i=0; i<DICT_SIZE; i++){
        cout<<a[i].key<<"  - \t"<<a[i].value<<"\n";
    }
}

// int main(){
//     // cout<<"Testing long and double multiplication"<<"\n";
//     // cout<<5ll*0.5<<"\n";
//     // cout<<"Testing typecasting of double to ll"<<"\n";
//     // cout<<(long long int)5344.664<<"\n";

//     // cout<<(int)'E';

//     // // Testing polynomial accumulation
//     // test__polynomialAccumulation();

//     // Dictionary d;
//     // printDictionary(d);

//     test__dictionary();
// }