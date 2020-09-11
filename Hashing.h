#ifndef HASHING_H_
#define HASHING_H_

#include <iostream>
#include <string>
#include "Patient.h"
#include "AVL.h"

using namespace std;

class Record {
private:
    char* recordString;
    AVL *tree;
    // pointer to record
public:
    Record();
    Record(AVL*);
    Record(string);
    Record(string,AVL*);
    ~Record();
   // Record& operator=(const Record&);

    const char* getString();
    void setString(const char*);
   
    //void setTreeNode(Patient*);
    void setTreeNode(node*);
    void print();

    bool treeExists();
    AVL* getTree();
};

class Bucket{
private:    
    int bucketSize;
    int recordsNum;
    int numOfBuckets;

    Record **records;
    Bucket *nextBucket;
    //Bucket *lastOverflowBucket;
    
public:
    Bucket();
    Bucket(int);
    Bucket(int,int);
    ~Bucket();
    Bucket(const Bucket&);
    //Bucket& operator=(const Bucket&);

    //void setRecord(Patient*,string);
    void setRecord(node*,string);
    void printRecords();
    bool maxRecords();
    void initNewBucket(node*,string);
    Bucket* getNextBucket();
    void setNext(Bucket*);
    int getNumOfRecords();
    AVL* getTree(int);
    const char* getRecordString(int);
    int stringExist(string);
    void clear_list(Bucket*);
    void printDiseaseStats(string,int);
    };

class Hash {
private:
    int hashSize;
    //int countryHashSize;
    Bucket **hashTable;
    //Bucket **countryHashTable;
public:
    Hash(int);
    ~Hash();
    unsigned int hashing(const char*);
    //void addRecord(Record*,Record*,int,Patient*);
    //void addRecord(Patient*,AVL*,int,bool);
    void addRecord(node*,int,bool);
    void display();

    void printNumCurrentPatients(list*);
    void printNumCurrentPatients(list*,string);

    const char* getDiseaseString(int);
    const char* getCountryString(int);
    const char* getRecordString(int);
    AVL* getTree(int);

    void printDiseaseStats();
    void printDiseaseStats(date*,date*);

    bool stringExist(string);
    
    void diseaseFrequency(string,date*,date*);
    int diseaseFrequency(string,date*,date*,string);

    //void top_kDiseases(int,string);
};



#endif