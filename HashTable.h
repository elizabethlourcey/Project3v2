#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

class HashTable{
    int BUCKET_SIZE;
    float MAX_LOAD_FACTOR;
    //load factor = size of map / size of vector (bucket size)

    vector<string> vec;
    unordered_map<int, string> table;

public:
    HashTable();
    int getBucketSize();
    float getMaxLF();
    unordered_map<int, string> getTable();
    vector<string> getVec();
    int computeKey(string s);
    int hashFunc(int k);
    int collisionReduction(int index);
    void resizeVector();
    void rehashWords();
    void insertWord(string word);
    void insertAll(string filename);
    bool searchWord(string input);
};
