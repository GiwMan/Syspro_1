#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include "helper_functions.h"
#include "Patient.h"

class queue{
    private:
        int front, rear;
        int size;
        heap_node **arr;
    public:
        queue(int qsize)
        {
            front = rear = -1;
            size = qsize;
            
            arr = new heap_node*[size];

            for(int i = 0; i < size; i++)
                arr[i] = NULL;
        }
        ~queue() 
        { 
            delete [] arr;
        }

        bool isEmpty() { return front == -1;}
        bool isFull() { return rear == size - 1; }
        void push_back(heap_node *node)
        {
            if(isFull())
            {
                return ;
            }

            arr[++rear] = node;

            if(isEmpty())
                ++front;
        }

        heap_node *pop()
        {
            if(isEmpty())
                return NULL;
            
            heap_node *temp = arr[front];

            if(rear == front)
                front = rear = -1;
            else
                front++;

            return temp;
        }

        heap_node *getFront()
        {
            return arr[front]; 
        }
};

template <>
void List<char*>::insertString(string str)
{

    if(head == NULL)
    {
        list_node<char*> *new_node = new list_node<char*>;
        new_node->data = new char[str.length() + 1];
        strcpy(new_node->data,str.c_str());

        head = new_node;
        tail = new_node;
    }else
    {
 
        if(strcmp(tail->data,str.c_str()) == 0)
            return;
        else if(strcmp(head->data,str.c_str()) == 0)
            return;
        
        list_node<char*> *current = head;

        while(current)
        {
            if(strcmp(current->data,str.c_str()) == 0)
                return;
            current = current->next;
        }
        
        list_node<char*> *new_node = new list_node<char*>;
        new_node->data = new char[str.length() + 1];
        strcpy(new_node->data,str.c_str());

        tail->next = new_node;
        tail = new_node;
    }
}

int max(int a, int b) { return (a > b) ? a : b; }

int compare_dates(string entry, string exit)
{
    int d1, m1, y1;
    int d2, m2, y2;

    stringstream ss1(entry);
    stringstream ss2(exit);
    string s1, s2;
    // entry date
    getline(ss1,s1,'-');
    d1 = atoi(s1.c_str());
    getline(ss1,s1,'-');
    m1 = atoi(s1.c_str());
    getline(ss1,s1,'-');
    y1 = atoi(s1.c_str());
    // exit date
    getline(ss2,s2,'-');
    d2 = atoi(s2.c_str());
    getline(ss2,s2,'-');
    m2 = atoi(s2.c_str());
    getline(ss2,s2,'-');
    y2 = atoi(s2.c_str());

    if(y1 != y2)
        return y1 - y2;
    else if(m1 != m2)
        return m1 - m2;
    else
        return d1 - d2;
}

bool validDate(string entry, string exit)
{
    bool correct_type = validDate(entry);

    if(correct_type)
    {
        if(exit == "-")
            return true;
        
        if(validDate(exit))
        {
            if(compare_dates(entry,exit) <= 0)
                return true;
        }
    }
    return false;
}

bool validDate(string date)
{   // function that checks if string date follows style DD-MM-YY
    // with DD, MM, YY in specific limits
    int dd,mm,yy;

    int countDashSymbol = 0;
    for(int i = 0; i < date.length(); i++)
    {
        if(date[i] == '-')
        {   
            countDashSymbol++;
        }
    }

    if(countDashSymbol == 2)
    {   // DD-MM-YY
        // now check if numbers are valid
        stringstream ss(date);
        string s1;

        getline(ss,s1,'-');
        dd = atoi(s1.c_str());
        getline(ss,s1,'-');
        mm = atoi(s1.c_str());
        getline(ss,s1,'-');
        yy = atoi(s1.c_str());

        //cout << dd << " " << mm << " " << yy << endl;

        if(dd > 0 && dd <= 31)
        {
            if(mm > 0 && mm <= 12)
            {
                if(yy > 0 && (yy >= 2000 && yy <= 2020))
                    return true;
            }
        }
    }
    return false;
}
/*
void tokenize(string str,string* id,
            string* fname, string* lname,
            string* disease, string* country,
            string* entry, string* exit)
{   // function that splits string 
    stringstream ss(str);

    string s1;

    string firstInput;

    getline(ss,s1,' ');
    firstInput = s1;

    if(firstInput == "/insertPatientRecord")
    {
        int count = 0;

        while(getline(ss,s1,' '))
        {
            if(count == 0)
                *id = s1;
            else if(count == 1)
                *fname = s1;
            else if(count == 2)
                *lname = s1;
            else if(count == 3)
                *disease = s1;
            else if(count == 4)
                *country = 5;
            else if(count == 5)
                *entry = s1;
            else 
                *exit = s1;

            count++;
        }
    }
}*/

int wordsInString(string str)
{   // word counter
    int countWords = 0;
    int i;
    bool foundSpace = false;


    for(i = 0; i < str.length();i++) {

        if(str[i] == ' ' )
        {
            if((isalpha(str[i+1]) || isdigit(str[i+1]))
                && i > 0)
                foundSpace = true;
            else if(str[i+1] == ' ' || str[i+1] == '\t')
                return -1;
        }
        else if(foundSpace)
        {
            foundSpace = false;
            countWords++;
        }
    }

    return ++countWords;
}

int exit_id(list* l, Patient *p)
{
    cout << "Double record Id found, while inserting :\n"; 
    p->print();

    cout << "\nList of Patients untill now :\n ===================\n";
    l->display();
    cout << "=====================\n";

    cout << "*End of Program*\n";
    return -1;
}
//template <typename T>
void deallocate_mem(avl *&id_tree,list *&l, AVL*& t1, Hash *& h1, Hash *& h2, 
                helping_hash<Item*> *& H1, helping_hash<Item*> *& H2,
                List<char*> *&l1, List<char*> *&l2 )
{
    
    delete id_tree;
    delete l;
    delete t1;
    delete h1;
    delete h2;
    delete H1;
    delete H2;
    delete l1; 
    delete l2;
}

Patient* createPatient(string line)
{
    string temp = line;
    stringstream ss(temp);

    string s1, id, name, last_name, 
        disease, country, entry, exit;

    int count = 0;


    while(getline(ss,s1,' '))
    {   
        if(s1 == "/insertPatientRecord")
            continue;
        if(count == 0)
            id = s1;
        else if(count == 1)
            name = s1;
        else if(count == 2)
            last_name = s1;
        else if(count == 3)
            disease = s1;
        else if(count == 4)
            country = s1;
        else if(count == 5)
            entry = s1;
        else 
            exit = s1;

        count++;
    }
    
    if(validDate(entry,exit))
    {
        return new Patient(id,name,last_name,disease,country,entry,exit);
    }
    return NULL;
}

void print_menu()
{
    cout << "\n****** Menu Options ******\n\n";

    cout << "--->" << " /globalDiseaseStats [date1 date2]" << endl;
    cout << "--->" << " /diseaseFrequency virusName date1 date2 [country]" << endl;
    cout << "--->" << " /topk-Diseases k country [date1 date2]" << endl;
    cout << "--->" << " /topk-Countries k disease [date1 date2]" << endl;
    cout << "--->" << " /insertPatientRecord recordID patientFirstName patientLastName diseaseID countryId entryDate [exitDate]\n";
    cout << "--->" << " /recordPatientExit recordID exitDate" << endl;
    cout << "--->" << " /numCurrentPatients [disease]" << endl;
    cout << "--->" << " /exit" << endl;
}



int  user_input(avl*& id_tree,list *&pat_list, AVL *&rec_tree, Hash *&dis_hash, Hash *&country_hash, int bSize,
                        helping_hash<Item*> *&country_has_disease, helping_hash<Item*> *&disease_has_country,
                        List<char*> *countries, List<char*> *diseases)
{
    bool exit = false;
    string userInput;

    while(!exit)
    {   
        getline(cin,userInput);
        /* counter to check validity of input */
        int count = wordsInString(userInput);
        
        stringstream ss(userInput);
        string s1;
        string firstInput;

        getline(ss,s1,' ');
        firstInput = s1;

        if(firstInput == "/globalDiseaseStats" && (count >= 1 && count <= 3))
        {
            //cout << "\n * Print Disease Stats *" << endl;
            if(count == 1)
                dis_hash->printDiseaseStats();
            else if(count == 3)
            {   /* hold date1 and date2 */
                getline(ss,s1,' ');
                string entry_date = s1;
                getline(ss,s1,' ');
                string exit_date = s1;
                if(validDate(entry_date) )
                {   
                    if(exit_date != "-")
                    {/* create dates */
                        date *date1 = new date(entry_date);
                        date *date2 = new date(exit_date);
                        /* print */
                        dis_hash->printDiseaseStats(date1,date2);

                        delete date1; delete date2;
                    }else
                    {
                        cout << "error";
                    }
                    
                }else
                {
                    cout << "error";

                }
                
            }else
            {
                ;
            }
            
        }else if(firstInput == "/diseaseFrequency" && (count == 4 || count == 5) )
        {   /* hold virus name, date1, date2 */
            getline(ss,s1,' '); string virusName = s1;
            getline(ss,s1,' '); string entryD = s1;
            getline(ss,s1,' '); string exitD = s1;

            if(exitD != "-" && exitD != " " )
            {
                if(validDate(entryD,exitD))
                {
                    date *date1 = new date(entryD);
                    date *date2 = new date(exitD);

                    if(count == 4)
                        dis_hash->diseaseFrequency(virusName,date1,date2);
                    else
                    {    
                        string country; getline(ss,s1,' '); country = s1;
                        if(country_hash->stringExist(country))
                        {
                            cout << virusName << " ";
                            cout << dis_hash->diseaseFrequency(virusName,date1,date2,country) << endl;
                        }
                        else 
                            cout << "error\n";
                    }
                    
                    delete date1; delete date2;
                }else
                {
                    cout <<"error\n";
                }
                
            }else
            {
                cout << "erro\n";
            }

        }else if(firstInput == "/topk-Diseases" && (count <= 5))
        {
            getline(ss,s1,' '); int k = atoi(s1.c_str());
            getline(ss,s1,' '); string country = s1;
            string entryD, exitD;
            if(count == 3)
            {   /* print top-k cases of disease not in range */
                
                country_has_disease->top_k(country,k);

            }
            else if(count == 4)
            {
                cout << "error\n";

            } else
            {
                getline(ss,s1,' '); string entryD = s1;
                getline(ss,s1,' '); string exitD = s1;
                /* if exit date has some value */
                if(exitD != "-" && exitD != " " )
                {   /* if dates are valid */
                    if(validDate(entryD,exitD))
                    {
                        date *date1 = new date(entryD);
                        date *date2 = new date(exitD);

                        //country_has_disease->top_k(country,k,date1,date2);
                        list_node <char*> *curr = diseases->getHead();
                        List<Item*> *Litems = new List<Item*>;
                        while(curr)
                        {   /* conver char* to string */
                            string dis(curr->data);
                            /* call diseaseFrequency for disease at given range */
                            int numOfCases = dis_hash->diseaseFrequency(dis,date1,date2,country);
                            if(numOfCases != -1)
                            {   
                                Litems->push_back(new Item(dis,numOfCases));
                            }
                            /* move to next diseases */
                            curr = curr->next;
                        }
                        if(!Litems->isEmpty())
                            topK(Litems,k);

                        delete date1; delete date2;
                        delete Litems;
                    }else
                        cout << "error" << endl;
                }else
                {
                    cout << "error\n";
                }   
            }
        
        }else if(firstInput == "/topk-Countries" && count <= 5)
        {
            getline(ss,s1,' '); int k = atoi(s1.c_str());
            getline(ss,s1,' '); string disease = s1;
            string entryD, exitD;
            if(count == 3)
            {
                disease_has_country->top_k(disease,k);
                
            }else if(count == 4)
            {
                cout << "error\n";

            } else
            {
                getline(ss,s1,' '); string entryD = s1;
                getline(ss,s1,' '); string exitD = s1;
                /* if exit date has some value */
                if(exitD != "-" && exitD != " " )
                {   /* if dates are valid */
                    if(validDate(entryD,exitD))
                    {
                        date *date1 = new date(entryD);
                        date *date2 = new date(exitD);

                        //country_has_disease->top_k(country,k,date1,date2);
                        list_node <char*> *curr = countries->getHead();
                        List<Item*> *Litems = new List<Item*>;
                        while(curr)
                        {   /* conver char* to string */
                            string country(curr->data);
                            /* call diseaseFrequency for disease at given range */
                            int numOfCases = dis_hash->diseaseFrequency(disease,date1,date2,country);
                    
                            if(numOfCases != -1)
                            {   
                                Litems->push_back(new Item(country,numOfCases));
                            }
                            /* move to next diseases */
                            curr = curr->next;
                        }
                        if(!Litems->isEmpty())
                            topK(Litems,k);

                        delete date1; delete date2;
                        delete Litems;
                    }else
                        cout << "error\n" << endl;
                }else
                {
                    cout << "error\n";
                }   
            }

        }
        else if(firstInput == "/insertPatientRecord" &&
                    (count == 7 || count == 8) )
        {
            /* same staff */
            Patient *patient = createPatient(userInput);
            /* insert him in tree of records and in the list */
            if(patient) 
            {
                node *last_inserted_node = NULL;

                if(id_tree->insert(patient->getPatientId()))//!rec_tree->search_id(patient))    
                    rec_tree->insert(patient,pat_list,last_inserted_node);
                else  
                    return exit_id(pat_list,patient);
             
                /* continue adding him in the hash table */
                bool isDisease = true;
                dis_hash->addRecord(last_inserted_node,bSize,isDisease);
                /* country hash */
                country_hash->addRecord(last_inserted_node,bSize,!isDisease);
                /* add country in the list of countries if needed */
                countries->insertString(patient->getPatientCountry());
                /* add disease in the list of diseases */
                diseases->insertString(patient->getPatientDisease());
                /* add him in the helping hash tables */
                disease_has_country->add_record(patient,isDisease,bSize);
                country_has_disease->add_record(patient,!isDisease,bSize);

                cout << "Record added\n";
            }else
                {
                    cout << "error\n";
                }
            
        }else if(firstInput == "/recordPatientExit" && count == 3)
        {
            bool skipId = false;
            bool stop = false;
            string id, exit_date;
            int error = -1;

            while(!stop)
            {
                if(!skipId)
                {   /* do not skip id at first */
                    getline(ss,s1,' ');
                    id = s1;
                    getline(ss,s1,' ');
                    exit_date = s1;
                }
                /* check date validity */
                if(validDate(exit_date))
                {   /* insert in the list of Patients */
                    if(rec_tree->search_id(id,exit_date,error))
                    {
                        cout << "Record updated\n";
                        pat_list->insert_exitDate(id,exit_date);
                    }
                    else
                    {
                        if(error == -1)
                        {
                            cout << "Not found\n"; 
                        }
                    }
                    /* stop loop */
                    stop = true;
                }else
                    cout << "\nerror\n";
            }
        }else if(firstInput == "/numCurrentPatients" && count <= 2 )
        {
            if(count == 1)
                dis_hash->printNumCurrentPatients(pat_list);
            else if(count == 2)
            {   
                getline(ss,s1,' '); string disease = s1;
                dis_hash->printNumCurrentPatients(pat_list,disease);
            }else
                cout << "\nerror\n";

        }
        else if(firstInput == "/exit")
        {
            deallocate_mem(id_tree,pat_list,rec_tree,dis_hash,country_hash,
                country_has_disease,disease_has_country,diseases,
                countries);

            cout << "\nexiting";
            exit = true;
        }else
        {
            cout << "\nerror\n";
        }
    }
    return 0;

}
/*
data_node::data_node() 
:   name(new char[strlen(" ") + 1]), num(0), next(NULL) {}
data_node::data_node(string s)
:   name(new char[s.length() + 1]), num(1), next(NULL)
{
    strcpy(name,s.c_str());
}

data_node::~data_node() 
{ 
    if(name) 
        delete []name; 
    name = NULL;
}

data_list::data_list(): head(NULL), tail(NULL)
{

}
data_list::~data_list() 
{
    data_node* current = head;

    while(current)
    {
        data_node* next = current->next;
        delete current;
        current = next;
    }
}
*/
/* avl_node functions */
avl_node::avl_node() : left(NULL), right(NULL), height(0), key(" "){}
avl_node::avl_node(string id) : left(NULL), right(NULL), height(1), key(id) { }
avl_node::~avl_node() { }

int avl_node::getHeight() { return height;}
string avl_node::getKey() { return key; }
avl_node* avl_node::getLeft() { return left; }
avl_node* avl_node::getRight() { return right; }

/* avl functions */
avl::avl() : root(NULL) {}
avl::~avl() { deleteTree(root); }

void avl::deleteTree(avl_node* proot)
{
    if(proot)
    {
        deleteTree(proot->left);
        deleteTree(proot->right);

        delete proot;
    }

}

void avl::deleteHelp() { deleteTree(root); }

int avl::getHeight(avl_node *node)
{
    if(node) return node->height;
    else
        return 0;
}

int avl::getBalanceFactor(avl_node *node)
{
    if(node)
        return getHeight(node->left) - getHeight(node->right);
    else 
        return 0;
}

//int max(int a, int b) { return (a > b) ? a : b; }

void avl::fixHeight(avl_node *node)
{
    node->height = 1 + max(getHeight(node->left),getHeight(node->right));
}

        // Rotations

avl_node* avl::LL(avl_node *node)
{
    avl_node *Lchild = node->left;
    node->left = Lchild->right;

    Lchild->right = node;

    fixHeight(node);

    return Lchild;
}
avl_node* avl::LR(avl_node *node)
{
    avl_node *Lchild = node->left;

    node->left = RR(Lchild);
    
    return LL(node);
}

avl_node* avl::RR(avl_node *node)
{
    avl_node *Rchild = node->right;
    node->right = Rchild->left;
        
    Rchild->left = node;

    fixHeight(node);

    return Rchild;
}

avl_node* avl::RL(avl_node *node)
{
    avl_node *Rchild = node->right;

    node->right = LL(Rchild);

    return RR(node);
}

avl_node* avl::self_balance(avl_node* node)
{
    int balance = getBalanceFactor(node);

    if(balance > 1)
    {   // Left-Left case
        if(getHeight(node->left->left) >= getHeight(node->left->right))
        {
            //cout << "performing a LL-rotation!\n";
            node = LL(node);
        }else
        {   // Left - Right case
            //cout << "performing a LR-rotation!\n";
            node = LR(node);
                    fixHeight(node);
        }
    }else if(balance < -1)
    {   // Right - Right case
        if(getHeight(node->right->right) >= getHeight(node->right->left))
        {
            //cout << "performing a RR-rotation!\n";
            node = RR(node);
        }else
        {   // Right - Left case
            //cout << "performing a RL-rotation!\n";
             node = RL(node);
            fixHeight(node);
        }
        
    }

    return node;
}

avl_node* avl::insertNode(avl_node* proot, string key)
{
    if(proot == NULL)
        return new avl_node(key);
            
    if(proot->key > key)
        proot->left = insertNode(proot->left,key);
    else if(proot->key < key)
        proot->right = insertNode(proot->right,key);
    else
        return NULL;
            
    fixHeight(proot);

    proot = self_balance(proot);

    return proot;
}

bool avl::insert(string id) { root = insertNode(root,id); if(root) return true; else return false; }

bool avl::search_id(avl_node* proot, string id)
{
    if(proot == NULL || proot->key == id)
        return proot;
    if(proot->key > id)
        return search_id(proot->left,id);
    else
        return search_id(proot->right,id);
}

bool avl::id_found(string id) { return search_id(root,id); }
            

/* Item Constructors / Destroctor */
Item::Item()
:   name(new char[strlen(" ") + 1 ]), key(0)
{
    strcpy(name," ");
}

Item::Item(string s, int n)
:   name(new char[s.length() + 1]), key(n)
{
    strcpy(name,s.c_str());
}

Item::Item(const char* s, int n)
:   name(new char[strlen(s) + 1]), key(n)
{
    strcpy(name,s);
}

Item::Item(const Item& it)
:   name(new char[strlen(it.name) + 1]),
    key(it.key)
{
    strcpy(name,it.name);
}

Item::~Item()
{
    if(name)
        delete [] name;
    name = NULL;
}
/* list_node Constructors / Destructor */
template <typename T>
list_node<T>::list_node()
:   data(NULL), next(NULL)
{

}
template <typename T>
list_node<T>::list_node(T *t)
:   data(new T(*t)), next(NULL)
{

}
template <typename T>
list_node<T>::list_node(T t)
:   data(t), next(NULL)
{

}
template <typename T>
list_node<T>::list_node(string s)
:   data(new Item(s,1)), next(NULL)
{

}
template <typename T>
list_node<T>::~list_node() 
{
    if(data)
        delete data;
    data = NULL;
}

template <typename T>
List<T>::List()
:   head(NULL), tail(NULL)
{

}
template <typename T>
List<T>::~List() 
{
    list_node<T> *current = head;

    while(current)
    {
        list_node<T> *next = current->next;
        delete current;
        current = next;
    }
}
/* bucketEntry Constructors / Destructor */
template <typename T>
bucketEntry<T>::bucketEntry() 
:   record_name(new char[strlen(" ")+1]),  
    list_of_data(NULL) 
{
    strcpy(record_name," ");
}
template <typename T>
bucketEntry<T>::bucketEntry(string str, int i) 
:   record_name(new char[str.length()+1]),  
    list_of_data(new List<T>) 
{

}

template <typename T>
bucketEntry<T>::~bucketEntry() 
{ 
    if(record_name) delete [] record_name;
    record_name = NULL; 

    if(list_of_data)
        delete list_of_data;
    list_of_data = NULL;
}
/* bucket Constructors / Destructor */
template <typename T>
bucket<T>::bucket() 
:   bucketSize(0),
    n_records(0),
    records(new bucketEntry<T>*[0]),
    next_bucket(NULL) 
{

}
template <typename T>
bucket<T>::bucket(int size) 
:   bucketSize(size),
    n_records(0),
    records(new bucketEntry<T>*[bucketSize / (sizeof(bucketEntry<T>) + sizeof(next_bucket))]),
    next_bucket(NULL) 
{ 
    for(int i = 0; i < (bucketSize / (sizeof(bucketEntry<T>) + sizeof(next_bucket))); i++)
        records[i] = new bucketEntry<T>;
}
template <typename T>
bucket<T>::~bucket() 
{
    for(int i = 0; i < (bucketSize / (sizeof(bucketEntry<T>) + sizeof(next_bucket))); i++) 
        delete records[i];
    delete [] records;
}
/*helping hash  Constructors / Destructor */
template <typename T>
helping_hash<T>::helping_hash(unsigned int hashSize)
:   size(hashSize), hash_table(new bucket<T>*[size])
{ 
    for(int i = 0; i < size; i++)
        hash_table[i] = NULL;
}
template <typename T>
helping_hash<T>::~helping_hash( )
{
    for(int i = 0; i < size; i++)
        hash_table[i]->clear_list(hash_table[i]);
    delete [] hash_table;
}
/* heap_node Constructors / Destructor */
heap_node::heap_node() 
:   left(NULL), right(NULL), parent(NULL),
    item(new Item)
{

}

heap_node::heap_node(const heap_node& h)
:   left(h.left) , right(h.right),
    parent(h.parent), item( new Item(*h.item))
{


    
}

heap_node& heap_node::operator=(const heap_node& rhs)
{
    if(&rhs == this)
        return *this;
    
    if(left) delete left;
    if(right) delete right;
    if(parent) delete parent;
    if(item) delete item;

    item = new Item(*rhs.item);
    left = new heap_node(*rhs.left);
    right = new heap_node(*rhs.right);
    parent = new heap_node(*rhs.parent);
    //left = rhs.left; right = rhs.right;
    //parent = rhs.parent;

    return *this;
    //left = new heap_node()
}

heap_node::heap_node(const char* s, int n)
:   left(NULL), right(NULL), parent(NULL),
    item(new Item(s,n))
{

}

heap_node::heap_node(Item *it)
:   left(NULL), right(NULL), parent(NULL),
    item(new Item(*it))
{

}

heap_node::heap_node(string s, int val)
:   left(NULL), right(NULL), parent(NULL),
    item(new Item(s,val))
{

}

heap_node::~heap_node() 
{
    if(item)
        delete item;
    item = NULL;
}
/* max heap  Constructor / Destructor */
template <typename T>
max_heap<T>::max_heap() : root(NULL) { }
template <typename T>
max_heap<T>::~max_heap() 
{
    deleteHeap(root);
    root = NULL;
    //delete root;
}
/********************* Functions****************************/
/**
 * Item functions
**/
void Item::print()
{
    if(name)
        cout << name << " " << key << endl;
}

void Item::setName(const char* s)
{
    if(name)
    {
        delete [] name;

        name = new char[strlen(s) + 1];
        strcpy(name,s);
    }
}

void Item::setNum(int i ) { key = i;}
/**
 * list_node functions
**/
template <typename T>
void list_node<T>::print()
{
    data->print();
}
/**
 * List functions
**/
template <typename T>
bool List<T>::isEmpty() { return head == NULL; }
template <typename T>
T List<T>::front()
{
    if(!isEmpty())
    {
        return head->data;
    }
    return NULL;
}
template <typename T>
void List<T>::pop()
{
    if(!isEmpty())
    {
        list_node<T> *current = head;
        head = head->next;

        //delete current;
    }
}
template<typename T>
list_node<T>* List<T>::getHead() { return head;}
template<typename T>
void List<T>::push_back(T t)
{
    list_node<T> *new_node = new list_node<T>(t);

    if(head == NULL)
    {
        head = new_node;
        tail = new_node;
    }else
    {
        tail->next = new_node;
        tail = new_node;
    }
}
template<>
void List<Item*>::createNode(string s)
{
    list_node<Item*> *new_node = new list_node<Item*>(s);

    if(head == NULL)
    {
        head = new_node;
        tail = new_node;
        new_node = NULL;
    }else
    {
        list_node<Item*> *current = head;

        while(current)
        {
            if(strcmp(current->data->name,s.c_str()) == 0)
            {
                current->data->key++;
                delete new_node;
                return;
            }
            current = current->next;
        }
        tail->next = new_node;
        tail = new_node;
    }
    
}
/*
template <>
void List<char*>::insertString(string str)
{

    if(head == NULL)
    {
        list_node<char*> *new_node = new list_node<char*>;
        new_node->data = new char[str.length() + 1];
        strcpy(new_node->data,str.c_str());

        head = new_node;
        tail = new_node;
    }else
    {
 
        if(strcmp(tail->data,str.c_str()) == 0)
            return;
        else if(strcmp(head->data,str.c_str()) == 0)
            return;
        
        list_node<char*> *current = head;

        while(current)
        {
            if(strcmp(current->data,str.c_str()) == 0)
                return;
            current = current->next;
        }
        
        list_node<char*> *new_node = new list_node<char*>;
        new_node->data = new char[str.length() + 1];
        strcpy(new_node->data,str.c_str());

        tail->next = new_node;
        tail = new_node;
    }
}
*/
template <typename T>
void List<T>::display()
{
    list_node<T> *current = head;

    while(current)
    {
        //current->print();
        current = current->next;
    }
}

/**
 * bucketEntry functions
**/
template <typename T>
const char* bucketEntry<T>::get_string() { return record_name; }
template <typename T>
List<T>* bucketEntry<T>::getList() { return list_of_data; }
template <typename T>
void bucketEntry<T>::set_string(const char* str)
{
    if(strcmp(record_name," ") == 0)
    {
        int length = strlen(str);

        delete []record_name;

        record_name = new char[length + 1];
        strcpy(record_name,str);
    } 
}
template <typename T>
void bucketEntry<T>::print() 
{
    if(strcmp(record_name," ") != 0) 
    {   cout <<endl<< record_name << "----> ";
        
        if(list_of_data) 
            list_of_data->display();
    }
}
template <typename T>
void bucketEntry<T>::set_list(string str)
{
    if(list_of_data == NULL)
    {
        list_of_data = new List<T>;
    }
    list_of_data->createNode(str);
}
template <typename T>
bool bucketEntry<T>::listExists() { return list_of_data == NULL; }
/**
 * bucket functions
**/
template <typename T>
int bucket<T>::get_Records() { return n_records; }
template <typename T>
bucket<T>* bucket<T>::get_nextBucket() { return next_bucket; }
template <typename T>
const char* bucket<T>::get_recString(int i) 
{
    if(records[i])
        records[i]->get_string();
}
template <typename T>
List<T>* bucket<T>::getList(int i) 
{
    if(records[i])
        return records[i]->getList();
}
template <typename T>
void bucket<T>::clear_list(bucket<T> *head_buck)
{
    bucket<T>* current = head_buck;

    while(current != NULL)
    {
        bucket<T>* next = current->next_bucket;
        delete current;
        current = next;
    }
    head_buck = NULL;
}
template <typename T>
void bucket<T>::print_recs()
{
    for(int i = 0; i < n_records; i++)
        if(records[i])
            records[i]->print();
}
template <typename T>
void bucket<T>::set_record(string hash_key, string str)
{
    for(int i = 0; i < n_records; i++)
        if(strcmp(records[i]->get_string(),hash_key.c_str()) == 0)
        {
            records[i]->set_list(str);
            return;
        }
    records[n_records]->set_string(hash_key.c_str());
    records[n_records++]->set_list(str);
}
template <typename T>
int bucket<T>::stringExist(string str)
{
    for(int i = 0; i < n_records; i++)
        if(strcmp(str.c_str(),get_recString(i)) == 0)
            return i;

    return -1;
}
template <typename T>
bool bucket<T>::maxRecords() { return n_records >= (bucketSize / (sizeof(records) + sizeof(next_bucket)) ); }
template <typename T>
void bucket<T>::initBucket(string hash_key, string str)
{
    next_bucket = new bucket<T>(bucketSize);

    next_bucket->set_record(hash_key,str);
}
/**
 * helping_hash functions
**/
template <typename T>
const char* helping_hash<T>::get_recString(int i){ return hash_table[i]->get_recString(i); }
template <typename T>
void helping_hash<T>::display()
{
    for(int index = 0; index < size; index ++)
    {
        bucket<T> *current = hash_table[index];

        while(current)
        {
            current->print_recs();

            current = current->get_nextBucket();
            cout << endl;
        }
    }
}
template <typename T>
unsigned long int helping_hash<T>::hashing(const char* str)
{ // A hash function that i found 
    unsigned long int hash = 5381;
    int c; 

    while (c = *str++)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}
template <typename T>
void helping_hash<T>::add_record(Patient *p, bool isDisease, int bucketSize)
{
    unsigned int index;  
    string str, str2;

    if(isDisease)
    {
        str = p->getPatientDisease(); 
        str2 = p->getPatientCountry();
    }
    else 
    {
        str = p->getPatientCountry(); /* holds the key that we will hash */
        str2 = p->getPatientDisease(); /* holds the value that we will set */
    }
    
    index = hashing(str.c_str());

    if(hash_table[index] == NULL)
    {
        hash_table[index] = new bucket<T>(bucketSize);
        hash_table[index]->set_record(str,str2);
    }else
    {   // We will traverse every bucket and if there is no space
        // then we will initNewBucket
        bucket<T>* currentBucket = hash_table[index];
        bool stop = false;
        
        /* if there is no string like this then add the new one */
        while(!stop && currentBucket)
        {   
            if(currentBucket->stringExist(str) != -1)
            {
                currentBucket->set_record(str,str2);
                stop = true;
            }
            // There is some space in current Bucket
            else if(!currentBucket->maxRecords())
            {
                currentBucket->set_record(str,str2);
                stop = true;
            }
            else 
            {  // get next Bucket and save current bucket to temp
                bucket<T>* temp = currentBucket;

                currentBucket = currentBucket->get_nextBucket();
                // check if it is the last bucket
                if(currentBucket == NULL)
                {  // Make space for a new Bucket and set the first record
                    temp->initBucket(str,str2);
                    stop = true;
                }
            }
        }      
    }

}
template <typename T>
void helping_hash<T>::top_k(string str, int k)
{
    unsigned int index;  
    
    index = hashing(str.c_str());

    bucket<T> *current = hash_table[index];

    while(current)
    {
        int pos = current->stringExist(str);
        if(pos != -1)
        {   /* get the list of Items */
            List<T> *temp_list = current->getList(pos);

            if(temp_list)
            {   /* create a max_heap */
                max_heap<T> *maxHeap = new max_heap<T>;

                cout << endl;  
                int size = 0;
                

                /* traverse the list of items */
                list_node<T> *current = temp_list->getHead();
                
                while(current)
                {
                  //  maxHeap->insert(qu,current);
                    /* move to next item */
                    size++;
                    current = current->next;
                }
                /* create a queue with the same size of list */
                queue *qu = new queue(size);
                /* traverse the list and insert in heap */
                current = temp_list->getHead();
                while(current)
                {
                    maxHeap->insert(qu,current);

                    current = current->next;
                }

                //maxHeap->print_inOrder();

                for(int i = 0; i < k; i++)
                {  
                    if(!maxHeap->emptyHeap())
                    {
                        
                        heap_node *to_print = maxHeap->pop();
                        
                        to_print->print();
                        
                        maxHeap->remove();
                        
                    }else
                        break;
                }
                cout << endl;
                /* deallocate memory */
                delete maxHeap;
                delete qu;
                return; 
            }
        }
        current = current->get_nextBucket();
    }
}
template <typename T>
heap_node* max_heap<T>::pop(date *d1, date *d2)
{

}

template <typename T>
void helping_hash<T>::top_k(string str, int k, date *entry, date* exit)
{
    unsigned int index;  
    
    index = hashing(str.c_str());

    bucket<T> *current = hash_table[index];

    while(current)
    {
        int pos = current->stringExist(str);
        if(pos != -1)
        {   /* get the list of Items */
            List<T> *temp_list = current->getList(pos);

            if(temp_list)
            {   /* create a max_heap */
                max_heap<T> *maxHeap = new max_heap<T>;

                cout << endl;  
                int size = 0;
                
                /* traverse the list of items */
                list_node<T> *current = temp_list->getHead();
                
                while(current)
                {
                  //  maxHeap->insert(qu,current);
                    /* move to next item */
                    size++;
                    current = current->next;
                }
                /* create a queue with the same size of list */
                queue *qu = new queue(size);
                /* traverse the list and insert in heap */
                current = temp_list->getHead();
                while(current)
                {
                    maxHeap->insert(qu,current);

                    current = current->next;
                }

                //maxHeap->print_inOrder();

                for(int i = 0; i < k; i++)
                {  
                    if(!maxHeap->emptyHeap())
                    {
                        
                        heap_node *to_print = maxHeap->pop(entry,exit);
                        
                        to_print->print();
                        
                        maxHeap->remove();
                        
                    }else
                        break;
                }
                cout << endl;
                /* deallocate memory */
                delete maxHeap;
                delete qu;
                return; 
            }
        }
        current = current->get_nextBucket();
    }
}

template<typename T>
bool max_heap<T>::hasBothChilden(heap_node *bnode) 
{ 
    return (bnode->left != NULL && bnode->right != NULL); 
}
template <typename T>
void max_heap<T>::findDeepestNode(heap_node*& temp) 
{ 
    right_mostNode(root,getHeight(root),temp);
}


template <typename T>
void max_heap<T>::insert_HPnode(heap_node **proot, queue *qu, list_node<T> *node)
{
    heap_node *to_insert = new heap_node(node->data);

    if((*proot) == NULL)
    {
        (*proot) = to_insert;
        (*proot)->parent =  NULL;
    }
    else
    {
        heap_node *parent_node = qu->getFront();

        if(parent_node->left == NULL)
        {
            parent_node->left = to_insert;
            to_insert->parent = parent_node;
            //temp->left->parent = temp->left;

            heapify(to_insert);
        }
        else if(parent_node->right == NULL)
        {
            parent_node->right = to_insert;
            to_insert->parent = parent_node;
            //temp->right->parent = temp->right;
            //temp->right->parent = temp->right;
            heapify(to_insert);
        }
        

        if(parent_node->left && parent_node->right)
            qu->pop();
      
    }

    qu->push_back(to_insert);
}

template <typename T>
void max_heap<T>::insert(queue *qu, list_node<T>* data) { insert_HPnode(&root,qu,data); }
/**
 * heap_node functions
**/
void heap_node::print()
{
    if(item)
        item->print();
}
/**
 * max_heap functions
**/
template <typename T>
void max_heap<T>::deleteHeap(heap_node *proot)
{
    if(proot)
    {
        deleteHeap(proot->left);
        deleteHeap(proot->right);

        delete proot;
    }
}
template <typename T>
bool max_heap<T>::emptyHeap() { return root == NULL; }
template <typename T>
void max_heap<T>::heapify(heap_node *child)
{
    if(child->parent == NULL)
    {
        return;
    }
    
    if(child->item->key >= child->parent->item->key)
    {
        swap(child,child->parent);
        heapify(child->parent);
    }else
        return ;   
}
template <typename T>
void max_heap<T>::inOrder(heap_node *proot)
{
    if(proot)
    {
        inOrder(proot->left);
        cout << "   " << proot->item->name << ": " << proot->item->key << endl;
        inOrder(proot->right);
    }
}
template <typename T>
void max_heap<T>::print_inOrder() { inOrder(root); }

void swap(heap_node *n1, heap_node *n2)
{
    Item *temp = n1->item;
    n1->item = n2->item;
    n2->item = temp;
}
template <typename T>
int max_heap<T>::getHeight(heap_node *proot)
{
    if(proot == NULL) return 0;

    return 1 + max( getHeight(proot->left),getHeight(proot->right) ); 
}
template <typename T>
void max_heap<T>::right_mostNode(heap_node *proot, int level, heap_node *& right_most)
{ /*  recursive function to return the deepest node in a binary tree */
    if(proot == NULL) 
        return ;

    if(level == 1)
    {
        //proot->print();
        right_most = proot;
    }else if(level > 1)
    {
        right_mostNode( proot->left, level - 1,right_most );
        right_mostNode( proot->right, level - 1, right_most );
    }
    
}
template <typename T>
bool max_heap<T>::isLeftChild(heap_node *current) 
{

    if(current->parent)
    {
        if(current->parent->left == current)
            return true;
    }
    
    return false;
}
template <typename T>
void max_heap<T>::heapifyDown(heap_node *new_root)
{
    if(new_root == NULL) return ;

    if(new_root->left && new_root->right)
    {
        if(new_root->left->item->key >= new_root->right->item->key)
        {
            heapify(new_root->left);
            heapifyDown(new_root->left);
        }
        else
        {
            heapify(new_root->right);
            heapifyDown(new_root->right);
        }   
    }else
    {
        if(new_root->left)
        {
            heapify(new_root->left);
            heapifyDown(new_root->left);
        }
        else if(new_root->right)
        {
            heapify(new_root->right);
            heapifyDown(new_root->right);
        }
        else ;
    }
    //heapifyDown(new_root);
}
template <typename T>
void max_heap<T>::removeNode(heap_node *&proot)
{
    heap_node *to_remove = NULL;
    right_mostNode(proot,getHeight(proot),to_remove);

    if(to_remove )
    {  /* free the left child of it's parent */
        if(to_remove !=  proot)
        {
            if(isLeftChild(to_remove))
                to_remove->parent->left = NULL;
            else
                to_remove->parent->right = NULL;
            /* swap values */
            swap(to_remove,proot);
            /* delete to_remove */
            delete to_remove;
            to_remove = NULL;

            /* hepify down */
            heapifyDown(proot);
        }else
        {   
            delete proot;
            proot = NULL;
        }
    }
}
template <typename T>
void max_heap<T>::remove() { removeNode(root); }
template <typename T>
heap_node* max_heap<T>::pop() 
{   /* checks for empty heap */
    if(root == NULL)
        return NULL;
    else    
        return root;
}

void topK(List<Item*> *l, int k)
{
    max_heap<Item*> *maxHeap = new max_heap<Item*>;

    cout << endl;  
    int size = 0;
                
                /* traverse the list of items */
    list_node<Item*> *current = l->getHead();
                
    while(current)
    {
        size++;
        current = current->next;
    }
    /* create a queue with the same size of list */
    queue *qu = new queue(size);
    /* traverse the list and insert in heap */
    current = l->getHead();
    while(current)
    {
        maxHeap->insert(qu,current);

        current = current->next;
    }
                //maxHeap->print_inOrder();

    for(int i = 0; i < k; i++)
    {  
        if(!maxHeap->emptyHeap())
        {
                        
            heap_node *to_print = maxHeap->pop();
                        
            to_print->print();
                        
            maxHeap->remove();
                        
        }else
            break;
    }
        cout << endl;
                /* deallocate memory */
        delete maxHeap;
        delete qu;
        return;
}

void printList(List<Item*> *l)
{
    list_node<Item*> *current = l->getHead();

    while(current)
    {
        current->data->print();
        current = current->next;
    }
}

template class helping_hash<Item*>;

template class List<heap_node*>;

template class bucket<Item*>;

template class List<char*>;