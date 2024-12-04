#include "HashTable.h"

HashTable::HashTable(){
    BUCKET_SIZE = 10;
    MAX_LOAD_FACTOR = 0.8;

    for(int i = 0; i < BUCKET_SIZE; i++){
        vec.push_back("");
    }
}

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

int power(int base, int exp){
    if(exp == 0){
        return 1;
    }

    return base * power(base, exp - 1);
}

int HashTable::computeKey(string s){
    int key = 0;
    int BASE = 26;

    for(int i = 0; i < s.length(); i++){
        int letter = tolower(s.at(i));
        int alphaIndex = letter - 96;
        key += alphaIndex * power(BASE, i);
    }

    while(table.count(key) == 1){
        key += 1;
    }

    if(key < 0){
        return -1 * key;
    }

    return key;
}

int HashTable::hashFunc(int k){
    return k % BUCKET_SIZE;
}

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

void HashTable::insertAll(){
    ifstream file;
    file.open("../englishWords.txt");

    string word;
    while(getline(file, word)){
        insertWord(word);
    }

    file.close();
}

void HashTable::resizeVector(){
    for(int i = BUCKET_SIZE; i < BUCKET_SIZE * 2; i++){
        vec.push_back("");
    }
    BUCKET_SIZE *= 2;
}

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

bool HashTable::searchWord(string input){
    if(table.count(computeKey(input)) == 1){
        return true;
    }

    return false;
}