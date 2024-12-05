#include "HashTable.h"

HashTable::HashTable(){
    BUCKET_SIZE = 10;
    MAX_LOAD_FACTOR = 0.8;

    for(int i = 0; i < BUCKET_SIZE; i++){
        vec.push_back("");
    }
}

//VVVVVVVVVVVV Accessor functions for testing the hash table w/o testing the whole project VVVVVVVVVV
int HashTable::getBucketSize(){
    return BUCKET_SIZE;
}

float HashTable::getMaxLF(){
    return MAX_LOAD_FACTOR;
}

unordered_map<int, string> HashTable::getTable(){
    return table;
}

vector<string> HashTable::getVec(){
    return vec;
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//basic exponential function to calculate base^exp
int power(int base, int exp){
    if(exp == 0){
        return 1;
    }

    return base * power(base, exp - 1);
}

//returns an int key corresponding to the given word
//key = sum of powers of 26 = letter * base^i (base = 26)
//  i = 0, 1, 2, etc. (increments up by 1 for each successive letter in the string)
//  letter = alphabetic rank of each letter: a->1, b->2, c->3, etc.
//computeKey("abc") = 1*26^0 + 2*26^1 + 3*26^2
int HashTable::computeKey(string s){
    int key = 0;
    const int BASE = 26;

    for(int i = 0; i < s.length(); i++){
        int letter = tolower(s.at(i));
        int alphaIndex = letter - 96;
        key += alphaIndex * power(BASE, i);
    }

    if(key < 0){
        return -1 * key;
    }

    return key;
}

//simple hash function returning key mod bucket_size: O(1)
int HashTable::hashFunc(int k){
    return k % BUCKET_SIZE;
}

//uses quadratic probing to resolve collisions
//if the given index is already filled, the probe looks at (index + 1) % bucketsize,
//  (index + 4) % bucketsize, (index + 9) % bucketsize, etc. until empty bucket is found
int HashTable::collisionReduction(int index){
    //quadratic probing
    //index = hashFunc(k)

    int i = 1;
    int newIndex = index;

    while(vec[newIndex] != ""){
        int step = i * i;
        newIndex = (index + step) % BUCKET_SIZE;
        if(newIndex < 0){
            newIndex *= -1;
        }
        i++;
    }

    return newIndex;
}

//doubles the size of the vector of words and doubles the BUCKET_SIZE attribute to match the new
//  vector size
//called when the current load factor exceeds the maximum
void HashTable::resizeVector(){
    for(int i = BUCKET_SIZE; i < BUCKET_SIZE * 2; i++){
        vec.push_back("");
    }
    BUCKET_SIZE *= 2;
}

//recalculates the vector index of each word using the new bucket size
//called after resizeVector when load factor exceeds the maximum
void HashTable::rehashWords(){
    for(int i = 0; i < BUCKET_SIZE; i++){
        vec[i] = "";
    }

    for(auto it = table.begin(); it != table.end(); it++){
        int index = hashFunc(it->first);

        if(vec[index] == ""){
            vec[index] = it->second;
        }

        else{
            index = collisionReduction(index);
            vec[index] = it->second;
        }
    }
}

//inserts a given word into the hash table map and vector
//assigns word to the map key and vector index using computeKey and hashFunc
//calls collisionReduction if necessary to resolve collisions
//calls resizeVector and rehashWords as necessary
void HashTable::insertWord(string word){
    int key = computeKey(word);
    table[key] = word;

    int index = hashFunc(key);

    if(vec[index] == ""){
        vec[index] = word;
    }

    else{
        index = collisionReduction(index);
        vec[index] = word;
    }

    float loadFactor = (float)table.size() / (float)BUCKET_SIZE;
    if(loadFactor >= MAX_LOAD_FACTOR){
        resizeVector();
        rehashWords();
    }

}

//inserts every word from a given text file into the map
void HashTable::insertAll(string filename){
    ifstream file;
    file.open(filename);

    string word;
    while(getline(file, word)){
        insertWord(word);
    }

    file.close();
}

//searches for the given input string in the map using unordered_map::find(key)
bool HashTable::searchWord(string input){
    int key = computeKey(input);
    if(table.find(key) != table.end()){
        return true;
    }

    return false;
}
