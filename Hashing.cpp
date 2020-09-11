#include <iostream>
#include <string>
#include "Hashing.h"
#include <cstring>

using namespace std;
/* Record functions */
Record::Record()
:   recordString(new char[strlen(" ")+1]),
    tree(NULL)
{
    strcpy(recordString," ");
}

Record::Record(string s)
:   recordString(new char[s.length() + 1])
    //tree(new AVL())
{
    strcpy(recordString,s.c_str());
}

Record::Record(string str, AVL *avl)
:   recordString(new char[str.length() + 1])
    //tree(new AVL())
{
    strcpy(recordString,str.c_str());
    tree = avl;
}

Record::Record(AVL *avl)
:   recordString(new char[strlen(" ")+1])
    //tree(new AVL())
{
    strcpy(recordString," ");
    tree = avl;
}

Record::~Record()
{
    delete [] recordString;
    if(tree)
        delete tree;
    
    tree = NULL;
}

const char* Record::getString() { return recordString; }

void Record::setString(const char* str )
{
    if(strcmp(recordString," ") == 0)
    {
        int length = strlen(str);

        delete []recordString;

        recordString = new char[length + 1];
        strcpy(recordString,str);
    } 
}

void Record::setTreeNode(node* ptr)
{   /* if avl has not been created yet */
    if(tree == NULL)
    {   /*create one */
        tree = new AVL();
    }/* insert in avl */
    tree->insert(ptr); 
}

void Record::print() 
{ 
    if(strcmp(recordString," ")) cout << recordString << endl; 

    if(tree) tree->print_preorder();
}

/*
Record& Record::operator=(const Record& r)
{
    if(&r == this)
        return *this;
    
    delete [] recordString;
    //delete tree;

    this->recordString = new char[strlen(r.recordString) + 1];
    strcpy(this->recordString,r.recordString);

    return *this;
}
*/

/* Bucket functions */
Bucket::Bucket()
:   bucketSize(0),
    recordsNum(0),
    numOfBuckets(0),
    records(new Record*[bucketSize / (sizeof(Record) + sizeof(nextBucket))]),
    nextBucket(NULL)//, lastOverflowBucket(NULL)
{
    for(int i = 0; i < (bucketSize / (sizeof(Record) + sizeof(nextBucket))); i++)
        records[i] = new Record;
}

Bucket::Bucket(int size)
:   bucketSize(size),
    recordsNum(0),
    numOfBuckets(1),
    records(new Record*[bucketSize / (sizeof(Record) + sizeof(nextBucket))]),
    nextBucket(NULL)//, lastOverflowBucket(NULL)
{
    for(int i = 0; i < (bucketSize / (sizeof(Record) + sizeof(nextBucket))); i++)
    {
        records[i] = new Record;
    }
}

Bucket::Bucket(int size, int totalBuckets)
:   bucketSize(size),
    recordsNum(0),
    numOfBuckets(totalBuckets),
    records(new Record*[bucketSize / (sizeof(Record) + sizeof(nextBucket))]),
    nextBucket(NULL)//, lastOverflowBucket(NULL)
{
    for(int i = 0; i < (bucketSize / (sizeof(Record) + sizeof(nextBucket))); i++)
        records[i] = new Record;
}

Bucket::Bucket(const Bucket &oldBucket)
:   bucketSize(oldBucket.bucketSize),
    recordsNum(oldBucket.recordsNum),
    numOfBuckets(oldBucket.numOfBuckets),
    records(new Record*[bucketSize / (sizeof(Record) + sizeof(nextBucket))]),
    nextBucket(new Bucket)//, lastOverflowBucket(new Bucket)
{
    for(int i = 0; i < (bucketSize / (sizeof(Record) + sizeof(nextBucket))); i++ )
        *records[i] = *oldBucket.records[i];

    *nextBucket = *oldBucket.nextBucket;
    //*lastOverflowBucket = *oldBucket.lastOverflowBucket;
}    

Bucket::~Bucket()
{
    for(int i = 0; i < (bucketSize / (sizeof(Record) + sizeof(nextBucket))); i++ )
        delete records[i];

    delete []records;

}

void Bucket::clear_list(Bucket *head)
{
    Bucket* current = head;
    while(current != NULL)
    {
        Bucket* next = current->nextBucket;
        delete current;
        current = next;
    }
    head = NULL;
}

void Bucket::setNext(Bucket *temp) { nextBucket = temp;}
int Bucket::getNumOfRecords() { return recordsNum; }
const char* Bucket::getRecordString(int i) { return records[i]->getString(); }

void Bucket::setRecord(node *ptr, string str) 
{   /* if there is a disease/country with same name then add tree node only */
    for(int i = 0; i < recordsNum; i++)
        if(strcmp(records[i]->getString(),str.c_str()) == 0)
        {   /* found same disease/country */ 
            records[i]->setTreeNode(ptr);
            return ;
        }
        /* set values */
    records[recordsNum]->setString(str.c_str());
    records[recordsNum++]->setTreeNode(ptr);
}

bool Bucket::maxRecords() 
{
    return recordsNum >= ( bucketSize / (sizeof(Record) + sizeof(nextBucket)) ); 
}
void Bucket::initNewBucket(node *ptr, string str) { 
    nextBucket = new Bucket(bucketSize,++numOfBuckets);

    nextBucket->setRecord(ptr,str);
}

Bucket* Bucket::getNextBucket() { return nextBucket; }

void Bucket::printDiseaseStats(string str, int i)
{
    if(strcmp(str.c_str(),getRecordString(i)) == 0)
    {
        AVL *tree = getTree(i);
        
        tree->print_preorder();
        //cout << tree->get_total_nodes(tree->getRoot()) << endl;

    } else 
        cout << "error\n";

}
/* check if a string exists in current bucket */
int Bucket::stringExist(string str)
{  
    int pos = -1;
    for(int i = 0; i < getNumOfRecords(); i++)
    {
        if(strcmp(str.c_str(),records[i]->getString()) == 0)
        {
            pos = i;
            return pos;
        }       
    }
    return pos;
}

void Bucket::printRecords()
{  // print records
    for(int i = 0; i < recordsNum; i++)
        if(records[i])
            records[i]->print();  
}

AVL* Bucket::getTree(int i)
{
    if(records[i])
        if(records[i]->treeExists())
            return records[i]->getTree();
    return NULL;
}
/*
Bucket& Bucket::operator=(const Bucket& B)
{
    if(&B == this)
        return *this;
    
    this->bucketSize = B.bucketSize;
    this->recordsNum = B.recordsNum;
    this->numOfBuckets = B.numOfBuckets;

    int i;

    for(i = 0; i < bucketSize / (sizeof(Record) + sizeof(nextBucket)); i++)
        delete this->records[i];
    delete [] records;

    delete nextBucket;
    delete lastOverflowBucket;

    this->records = new Record*[bucketSize / (sizeof(Record) + sizeof(nextBucket))];
    for(i = 0; i < bucketSize / (sizeof(Record) + sizeof(nextBucket)); i++)
        this->records[i] = B.records[i];

    this->nextBucket = new Bucket;
    this->lastOverflowBucket = new Bucket;

    this->nextBucket = B.nextBucket;
    this->lastOverflowBucket = B.lastOverflowBucket;

    return *this;
}
*/

/* Hash functions */
Hash::Hash(int size)
:   hashSize(size),
    hashTable(new Bucket*[hashSize])
{
    int i;

    for(i = 0; i < hashSize; i++) hashTable[i] = NULL;
}


Hash::~Hash()
{   

    for(int i = 0; i < hashSize; i++)
    {   /* delete bucket list at first */
        hashTable[i]->clear_list(hashTable[i]);
    }
    delete [] hashTable;
}

const char* Hash::getRecordString(int i) { return hashTable[i]->getRecordString(i); }
/* hash function for strings */
unsigned int Hash::hashing(const char* str)
{   // A hash function that i found 
    unsigned int hash = 5381;
    int c; 

    while (c = *str++)
    {
        hash = ((hash << 5) + hash) + c;
             
        hash = hash % hashSize;
    }
    return hash;
}
/* function that adds record in hash table and creates a/inserts in avl */
void Hash::addRecord(node *ptr , int bucketSize, bool isDisease)
{
    int index;
    string str;
    /* recognise if it is a disease or country */
    if(isDisease)
        str = ptr->patientData->getPatientDisease();
    else
        str = ptr->patientData->getPatientCountry();

    index = hashing(str.c_str());
    if(hashTable[index] == NULL)
    {
        hashTable[index] = new Bucket(bucketSize);
        hashTable[index]->setRecord(ptr,str);
    }else
    {   /*  * We will traverse every bucket and if there is no space
            * then we will initNewBucket
        */
        Bucket* currentBucket = hashTable[index];
        bool stop = false;
        
        /* if there is no string like this then add the new one */
        while(!stop && currentBucket)
        {   
            if(currentBucket->stringExist(str) != -1)
            {
                currentBucket->setRecord(ptr,str);
                stop = true;
            }
            /* There is some space in current Bucket */
            else if(!currentBucket->maxRecords())
            {
                currentBucket->setRecord(ptr,str);
                stop = true;
            }
            else 
            {  /* get next Bucket and save current bucket to temp */
                Bucket* temp = currentBucket;

                currentBucket = currentBucket->getNextBucket();
                /* check if it is the last bucket */
                if(currentBucket == NULL)
                {  // Make space for a new Bucket and set the first record
                    temp->initNewBucket(ptr,str);
                    stop = true;
                }
            }
        }      
    }
    
}
/* print hash table if needed */
void Hash::display()
{
    int index;

    for(index = 0; index < hashSize; index++)
    {   // Get current Bucket and traverse al buckets of current index
        Bucket *currentB = hashTable[index];
        //cout << "----------------------\n";
        //cout << "index = " << index << endl;

        while(currentB)
        {
            currentB->printRecords();
            //cout << "#records = " << currentB->getNumOfRecords() << endl;
            //cout << "---------------------\n";
            // move to next bucket
            currentB = currentB->getNextBucket();
        }
    }
    //cout << "**************************\n";
    
}
bool Record::treeExists() { return tree->getRoot() != NULL; }
AVL* Record::getTree() { return tree; }

AVL* Hash::getTree(int i)
{
    int index;

    for(index = 0; index < hashSize; index++)
    {
        if(hashTable[index])
        {
            return hashTable[index]->getTree(i);
        }
    }
    return NULL;
}
/* string exist in hash table */
bool Hash::stringExist(string str)
{   /* hash the string value */
    int index = hashing(str.c_str());
    /* get the bucket where virusName may exist */
    Bucket *currentB = hashTable[index];

    while(currentB)
    {
        for(int i = 0; i < currentB->getNumOfRecords(); i++)
        {
            if(strcmp(str.c_str(),currentB->getRecordString(i)) == 0)
            {
                return true;
            }
        }
        currentB = currentB->getNextBucket();
    }
    return false;
}
/* function that prints num of patients that still are in hospital */
void Hash::printNumCurrentPatients(list *patients)
{
    int index, numOfCurrentPatients = 0;
    Bucket *currentB;

    for(index = 0; index < hashSize; index++)
    {
        currentB = hashTable[index];
        
        while(currentB)
        {
            for(int i = 0; i < currentB->getNumOfRecords(); i++)
            {
                string disease = currentB->getRecordString(i);

                numOfCurrentPatients = patients->getNumCurrentPatients(disease);

                cout << disease << " " << numOfCurrentPatients << endl;
                //return;
            }
            currentB = currentB->getNextBucket();
        }
    }
}
/* function that prints num of patients that still are in hospital because of disease given */
void Hash::printNumCurrentPatients(list *patients, string disease)
{
    int index, numOfCurrentPatients = 0;
    
    Bucket *currentB;

    index = hashing(disease.c_str());
    currentB = hashTable[index];
        
    while(currentB)
    {   /* find where and if disease exists in current bucket */
        int pos = currentB->stringExist(disease);
        if(pos != -1)
        {
            numOfCurrentPatients = patients->getNumCurrentPatients(disease);

            cout << disease << " " << numOfCurrentPatients << endl; 
            return;
        }
        /* traverse the list of buckets */
        currentB = currentB->getNextBucket();
    }  
    cout << disease << " 0" << endl;  
}
/* funtion that prints stats for every disease */
void Hash::printDiseaseStats()
{
    Bucket *currentB;
    int index;
    string disease;
    //cout << "\n=======================================\n";
    /* for bucket hashTable[index] */
    for(index = 0; index < hashSize; index++)
    {
        currentB = hashTable[index];

        int countBuckets = 0;
        /* traverse list of buckets */
        while(currentB)
        {   /* for every record */
            for(int i = 0; i < currentB->getNumOfRecords(); i++)
            {
                //cout << "#CASES of '" << currentB->getRecordString(i) << "' are : ";
                cout << currentB->getRecordString(i) << " ";
                //cout << currentB->getTree(i)->get_total_nodes(currentB->getTree(i)->getRoot()) << endl;
                AVL* tree = currentB->getTree(i);
                /* counts total nodes in range */
                cout << tree->get_total_nodes(tree->getRoot()) << endl;
            }
            ///cout << "*End of Bucket #" << countBuckets + 1 << " with records "<< currentB->getNumOfRecords()<< endl;
            currentB = currentB->getNextBucket();
            //cout << "*End of Bucket #" << countBuckets + 1 << endl;
            countBuckets++;
        }
        //break;
    }

}
/* funtion that prints stats for every disease in given range*/
void Hash::printDiseaseStats(date *date1, date *date2)
{
    Bucket *currentB;
    int index;
    string disease;

   // cout <<"=======================\n";
    for(index = 0; index < hashSize; index++)
    {
        currentB = hashTable[index];
        int countBuckets = 0;
        int count = 0;
        while(currentB)
        {
            for(int i = 0; i < currentB->getNumOfRecords(); i++)
            {   /* get total nodes in a range */
                cout << currentB->getRecordString(i) << " ";
                
                AVL* tree = currentB->getTree(i);
                /* counts total nodes in a tree in range */
                cout << tree->get_nodes_inRange(tree->getRoot(),date1,date2,count) << endl; 

            }
            //cout << "*End of Bucket #" << countBuckets + 1 << " with records "<< currentB->getNumOfRecords()<< endl;

            currentB = currentB->getNextBucket();
            countBuckets++;
            /* reset count to 0 for next disease */
            count = 0;
        }

    }
}
/* disease frequency of virus in given range */
void Hash::diseaseFrequency(string virus,date* d1,date* d2)
{   /* hash the string value */
    int index = hashing(virus.c_str());
    /* get the bucket where virusName may exist */
    Bucket *currentB = hashTable[index];

    /* if not NULL */
    if(currentB)
    {   /* check for records */
        for(int i = 0; i < currentB->getNumOfRecords(); i++)
        {
            string disease = currentB->getRecordString(i);

            if(disease == virus)
            {
                int count = 0;
                cout << virus << " ";
                //printDiseaseStats(d1,d2);
                AVL* tree = currentB->getTree(i);
                
                cout << tree->get_nodes_inRange(tree->getRoot(),d1,d2,count) << endl; 

                return ;
            }
        }
        currentB = currentB->getNextBucket();
    }

}
/* disease frequency of virus in given range for given country */
int Hash::diseaseFrequency(string virus,date* d1,date* d2, string country)
{   /* hash the string value */
    int index = hashing(virus.c_str());
    /* get the bucket where virusName may exist */
    Bucket *currentB = hashTable[index];
    //cout <<"=======================\n";
    /* if not NULL */
    while(currentB)
    {   /* check for records */
        for(int i = 0; i < currentB->getNumOfRecords(); i++)
        {
            string disease = currentB->getRecordString(i);

            if(disease == virus)
            {
                int count = 0;
                //cout << "Disease Frequency of virus '" << virus << "' in country '" << country <<"' are : ";cout << virus << " ";
                //cout << virus << " ";
                //printDiseaseStats(d1,d2);
                AVL* tree = currentB->getTree(i);
                return tree->get_nodes_inRange(tree->getRoot(),d1,d2,country,count);

                //tree->print_preorder(); 
            }
        }
        currentB = currentB->getNextBucket();
    }
    return -1;
    //cout <<"=======================\n";
}
/* print topk diseases of country */
/*
void Hash::top_kDiseases(int k, string country) 
{
    int index = hashing(country.c_str());

    Bucket *currentB = hashTable[index];

    cout << "\nPrint all Diseases in country '" << country <<"'\n";
    int pos = 0;

    while(currentB)
    {
        pos = currentB->stringExist(country);
        if( pos != -1)
            currentB->printDiseaseStats(country,pos);

        currentB = currentB->getNextBucket();
    }
}*/