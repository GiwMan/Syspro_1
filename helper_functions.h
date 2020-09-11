#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

#include <iostream>
#include <string>
#include "Patient.h"
#include "AVL.h"
#include "Hashing.h"
using namespace std;

/* this is an avl node for id's only */
struct avl_node{
            avl_node *left, *right;
            int height;
            string key;

            avl_node();// : left(NULL), right(NULL), height(0), key(" "){}
            avl_node(string id);// : left(NULL), right(NULL), height(1), key(id) { }
           ~avl_node();// { }

            int getHeight();// { return height;}
            string getKey();// { return key; }
            avl_node* getLeft();// { return left; }
            avl_node* getRight();// { return right; }
        };

/* this is the class of helper avl with a pointer to avl_node */
class avl{  
    private:

        avl_node *root; 
    public:
        avl();// : root(NULL) {}
        ~avl();// { deleteTree(root); }

        void deleteTree(avl_node* proot);
        /*{
            if(proot)
            {
                deleteTree(proot->left);
                deleteTree(proot->right);

                delete proot;
            }

        }*/

        void deleteHelp();// { deleteTree(root); }

        int getHeight(avl_node *node);
        /*{
            if(node) return node->height;
            else
                return 0;
        }*/

        int getBalanceFactor(avl_node *node);
        /*{
            if(node)
                return getHeight(node->left) - getHeight(node->right);
            else 
                return 0;
        }*/

        //int max(int a, int b);// { return (a > b) ? a : b; }

        void fixHeight(avl_node *node);
        /*
        {
            node->height = 1 + max(getHeight(node->left),getHeight(node->right));
        } */

        // Rotations

        avl_node* LL(avl_node *node);
        /*{
            avl_node *Lchild = node->left;
            node->left = Lchild->right;

            Lchild->right = node;

            fixHeight(node);

            return Lchild;
        }*/
        avl_node* LR(avl_node *node);
        /*
        {
            avl_node *Lchild = node->left;

            node->left = RR(Lchild);
    
            return LL(node);
        }
        */
        avl_node* RR(avl_node *node);
        /*{
            avl_node *Rchild = node->right;
            node->right = Rchild->left;
        
            Rchild->left = node;

            fixHeight(node);

            return Rchild;
        } */

        avl_node* RL(avl_node *node);
        /*{
            avl_node *Rchild = node->right;

            node->right = LL(Rchild);

            return RR(node);
        }
        */
        avl_node* self_balance(avl_node* node);
        /*{
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
        }*/

        avl_node* insertNode(avl_node* proot, string key);
        /*{
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
            */
        bool insert(string id);// { root = insertNode(root,id); if(root) return true; else return false; }

        bool search_id(avl_node* proot, string id);
        /*{
            if(proot == NULL || proot->key == id)
                return proot;
            if(proot->key > id)
                return search_id(proot->left,id);
            else
                return search_id(proot->right,id);
        }*/

        bool id_found(string id);// { return search_id(root,id); }
      
};



struct Item{
    char *name;
    int key;

    Item();
    Item(string,int);
    Item(const Item&);
    Item(const char*, int);
    ~Item();

    void print();
    void setName(const char*);
    void setNum(int);
};
/**
 *  this is a struct representing a heap node of heap 
 *  with Item structure as a key
 * */
struct heap_node
{
    heap_node *left, *right, *parent;
    Item *item;

    heap_node();
    heap_node(string,int);
    heap_node(Item*);
    heap_node(const char*, int);
    heap_node(const heap_node&);
    heap_node& operator=(const heap_node&);
    ~heap_node();

    void print();
};
/**
 * a generic linked list node
 **/
template <typename T>
struct list_node{
    T data;
    list_node *next;

    list_node();
    list_node(T*);
    //list_node(heap_node*);
    list_node(T);
    list_node(string);
    
    ~list_node();

    void print();
};
/**
 * a generic linked list
 **/ 
template <typename T>
class List{
    private:
        list_node<T> *head, *tail;
    public:
        List();
        ~List();

        bool isEmpty();
        T front();
        void pop();
        void push_back(T);
        void display();

        void insertString(string str);
        //template <char*> void insertString(string str);
        
        void createNode(string);
        list_node<T> *getHead();
};
/**
 * this class represents our bucket entry
 * that holds a string and a pointer to list.
 **/
template <typename T>
class bucketEntry{
    private:
        char* record_name;
        List<T> *list_of_data;
    public:
        bucketEntry();
        bucketEntry(string,int);
        //bucketEntry(T );
        ~bucketEntry();

        const char* get_string();
        //int get_number();

        void set_string(const char*);
        void set_list(string);
        void set_number(int);

        bool listExists();
        List<T> *getList();

        void print();
};
/**
 * this is the bucket of the hash table
 */ 
template <typename T>
class bucket{
    private:
        int bucketSize;
        int n_records;

        bucketEntry<T> **records;
        bucket *next_bucket;
    public:
        bucket(int);
        bucket();
        ~bucket();

        void clear_list(bucket*);
        int get_Records();
        bucket* get_nextBucket();
        const char* get_recString(int);
        //int get_recNum(int);

        void set_record(string,string);
        int stringExist(string);
        bool maxRecords();
        void initBucket(string,string);

        List<T> *getList(int);

        void print_recs();
};
/**
 * this is a helping hash table for the needs
 * of topK, holding some specific infos for
 * countries and diseases
 **/ 
template <typename T>
class helping_hash{
    private:
        unsigned int size;
        bucket<T> **hash_table;
    public:
        helping_hash(unsigned int);
        ~helping_hash();

        //int get_recNum(int);
        const char* get_recString(int);

        void display();
        //void set_record(Patient*,string)
        void add_record(Patient*, bool, int);

        unsigned long int hashing(const char*);

        void top_k(string, int);
        void top_k(string, int, date*, date*);
};
/* forward declaration of a queue */
class queue;
/**
 * this is a max heap that has a pointer to heap node
 * which is our root node. The below implementantion is tree-based.
 **/ 
template <typename T>
class max_heap
{
    private:
        heap_node *root;
    public:
        max_heap();
        ~max_heap();

        //void insert_HPnode(heap_node**,List<heap_node*>*, list_node<T> *);
        //void insert(List<heap_node*>*,list_node<T>*);
        void insert_HPnode(heap_node**,queue*, list_node<T> *);
        void insert(queue*,list_node<T>*);
        void inOrder(heap_node*);
        void print_inOrder();  
        void heapify(heap_node*);
        void heapifyDown(heap_node*);
        //void heapify(heap_node*, heap_node*);
        //void heapify(heap_node*)
        heap_node* pop();
        heap_node *pop(date*,date*);
        void remove(heap_node*);

        int getHeight(heap_node*);
        void findDeepestNode(heap_node*&);
        void right_mostNode(heap_node*,int,heap_node*&);
        void removeNode(heap_node *&);
        void remove();
        bool isLeftChild(heap_node*);
        bool emptyHeap();

        bool hasBothChilden(heap_node*);
        void deleteHeap(heap_node*);
        //heap_node 
};
/* return the max betwwen two integers */
int max(int a, int b);
/* comparing two dates by given strings */
int compare_dates(string entry,string exit);

bool validDate(string date);

bool validDate(string entry,string exit);

//void tokenize(string ,string*,string*,string*,string*,string*,string*,string*);

/* functions that returns a Patient or NULL */
Patient* createPatient(string line);
/* counting wordns in given string */
int wordsInString(string str); 
/* if id exists in tree then exit programm */
int exit_id(list*,Patient*);
/* deallocate any dynamically allocate memory */
//template <>
void deallocate_mem(list*&,AVL*&,Hash*&,Hash*&, helping_hash<Item*>*&, helping_hash<Item*>*&,
                List<char*> *&, List<char*>*&);
/* printing menu of options */
void print_menu();
/* user giving input for the second part of the project */
int user_input(avl*&,list *&, AVL*& , Hash*&, Hash*&, int, helping_hash<Item*>*&, helping_hash<Item*>*&,
        List<char*>*, List<char*>*);
//void add_record(node*,AVL*& , AVL*&, int , bool);
void topK(List<Item*> *, int);
/* print given list */
void printList(List<Item*> *);
/* swap pointer values of 2 heap nodes */
void swap(heap_node*, heap_node*);

#endif