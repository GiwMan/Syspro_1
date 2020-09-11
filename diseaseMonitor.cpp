#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "Hashing.h"
#include "Date.h"
#include "AVL.h"
#include "helper_functions.h"

using namespace std; 
/**
 * this is an avl created to hold the id of a patient 
 * in order to check fast if an id exists in current tree or not. 
**/

/*
class avl{  
    private:

         struct avl_node{
            avl_node *left, *right;
            int height;
            string key;

            avl_node() : left(NULL), right(NULL), height(0), key(" "){}
            avl_node(string id) : left(NULL), right(NULL), height(1), key(id) { }
           ~avl_node() { }

            int getHeight() { return height;}
            string getKey() { return key; }
            avl_node* getLeft() { return left; }
            avl_node* getRight() { return right; }
        };

        avl_node *root; 
    public:
        avl() : root(NULL) {}
        ~avl() { deleteTree(root); }

        void deleteTree(avl_node* proot)
        {
            if(proot)
            {
                deleteTree(proot->left);
                deleteTree(proot->right);

                delete proot;
            }

        }

        void deleteHelp() { deleteTree(root); }

        int getHeight(avl_node *node)
        {
            if(node) return node->height;
            else
                return 0;
        }

        int getBalanceFactor(avl_node *node)
        {
            if(node)
                return getHeight(node->left) - getHeight(node->right);
            else 
                return 0;
        }

        int max(int a, int b) { return (a > b) ? a : b; }

        void fixHeight(avl_node *node)
        {
            node->height = 1 + max(getHeight(node->left),getHeight(node->right));
        }

        // Rotations

        avl_node* LL(avl_node *node)
        {
            avl_node *Lchild = node->left;
            node->left = Lchild->right;

            Lchild->right = node;

            fixHeight(node);

            return Lchild;
        }
        avl_node* LR(avl_node *node)
        {
            avl_node *Lchild = node->left;

            node->left = RR(Lchild);
    
            return LL(node);
        }

        avl_node* RR(avl_node *node)
        {
            avl_node *Rchild = node->right;
            node->right = Rchild->left;
        
            Rchild->left = node;

            fixHeight(node);

            return Rchild;
        }

        avl_node* RL(avl_node *node)
        {
            avl_node *Rchild = node->right;

            node->right = LL(Rchild);

            return RR(node);
        }

        avl_node* self_balance(avl_node* node)
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

        avl_node* insertNode(avl_node* proot, string key)
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

        bool insert(string id) { root = insertNode(root,id); if(root) return true; else return false; }

        bool search_id(avl_node* proot, string id)
        {
            if(proot == NULL || proot->key == id)
                return proot;
            if(proot->key > id)
                return search_id(proot->left,id);
            else
                return search_id(proot->right,id);
        }

        bool id_found(string id) { return search_id(root,id); }
      
};
*/
/* print a list of char* when if needed */
void printList(List<char*> *l)
{
    list_node<char*> *current = l->getHead();

    while(current)
    {
        cout << current->data << endl;
        current = current->next;
    }
}

int main(int argc, char* argv[])
{
    /* check for correct input */
    if(argc < 9)
    {
        cout << " wrong input.try again!\n";

        return -1;
    }
    /* save some values */
    int diseaseHashtableNumOfEntries = atoi(argv[4]);
    int countryHashtableNumOfEntries = atoi(argv[6]);
    int bucketSize = atoi(argv[8]);
    string text_file = argv[2];
    /* read from file */
    string line;
    ifstream file(text_file.c_str());
    /*  list of patients */
    list *patient_list = new list;
    /* disease hash table */
    Hash *diseaseHashTable = new Hash(diseaseHashtableNumOfEntries);
    /* country hash table */
    Hash *countryHashTable = new Hash(countryHashtableNumOfEntries);
    /** 
     * AVL tree that inserts Patients in the list in descending order 
     * according to their dates, and ensures that no duplicate recordId
     * exists. If there is a double Id, then exits.
     **/
    helping_hash<Item*> *countries_diseases_stats = new helping_hash<Item*>(1024);
    helping_hash<Item*> *diseases_and_countries = new helping_hash<Item*>(1024);

    List<char*> *countriesList = new List<char*>;
    List<char*> *diseasesList = new List<char*>;

    AVL *record_tree = new AVL;//, *treeOfCountries;
    avl *id_tree = new avl;
    //treeOfDiseases = new AVL; treeOfCountries = new AVL;

    /* start reading from file and creating the structures */
    node *last_inserted_node = NULL;
    if(file.is_open())
    { 
        while(getline(file,line))
        {   /* create Patient */
            Patient *patient = createPatient(line);
            /* insert him in tree of records and in the list */
            if(patient) 
            { /* create a tree by record id */
                if(id_tree->insert(patient->getPatientId()))
                    record_tree->insert(patient,patient_list,last_inserted_node);
                else  
                    return exit_id(patient_list,patient);
             
                /* continue adding him in the hash table */
                bool isDisease = true;
                diseaseHashTable->addRecord(last_inserted_node,
                                bucketSize,isDisease);
                
                /* country hash */
                countryHashTable->addRecord(last_inserted_node,
                                    bucketSize,!isDisease);
                /* create a list of total countries/diseases */
                countriesList->insertString(patient->getPatientCountry());
                diseasesList->insertString(patient->getPatientDisease());
                /* create hash table of country having diseases */
                countries_diseases_stats->add_record(patient,!isDisease,bucketSize);
                /* create hash table of disease , happened in countries */
                diseases_and_countries->add_record(patient,isDisease,bucketSize);
            }
        }
        // close file
        file.close();
    }else
    {
        cout << "Unable to open file.\n";
        return -1;
    }


    return  user_input(id_tree,patient_list,record_tree,diseaseHashTable,
                    countryHashTable,bucketSize, countries_diseases_stats, 
                    diseases_and_countries,countriesList, diseasesList);
}

