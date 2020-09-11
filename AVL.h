#ifndef AVL_H_
#define AVL_H_

#include <iostream>
#include "Patient.h"


using namespace std;

/**
 * this struct represents a tree node in our bbst 
**/
struct treeNode{
    treeNode *left, *right, *parent;
    int countDates; //  times a date presents in treeNode
    int height; //  height of tree
    node *ptr_to_lnode; // list node where treeNode points at
    date *key;  // key

    treeNode();
    ~treeNode();
    treeNode(Patient*);
    treeNode(node*);
    treeNode(const treeNode&);

    void printNode();
    /* get the list node where treeNode points at */
    node* get_node();

};
/* class of an avl tree */
class AVL{
private:
    treeNode *root;
public:
    AVL();
    AVL(const AVL&);
    ~AVL();

    treeNode* getRoot();
    
    treeNode* copyTree(treeNode*);
    /* delete tree reccursively */
    void delete_helper();
    void deleteTree(treeNode*&);
    /* get node of a tree recursively */
    int get_total_nodes(treeNode*);
    /* in  given range */
    int get_nodes_inRange(treeNode*,date*,date*,int&);
    int get_nodes_inRange(treeNode*,date*,date*,string,int&);
    

    void insert(node*);
    void insert(Patient*,list*&,node*&);
    /* recursive search functions */
    bool id_found(treeNode*,Patient*);
    bool id_found(treeNode*,string,string,int&);
    bool search_id(Patient*); 
    bool search_id(string,string,int&);
    //void insert(list*);
    /* recursive insert functions */
    treeNode* insertNode(Patient*,treeNode*,list*&,node*&);
    treeNode* insertNode(treeNode*,node*);

    /* height functions */
    int getHeight(treeNode*);
    int getBalanceFactor(treeNode*);
    void fixHeight(treeNode*);
    /* print preorder */
    void preorder(treeNode*);
    void print_preorder();


    bool update_exitDate(treeNode*,string);  
    /*rotations*/
    treeNode* LL(treeNode*);
    treeNode* LR(treeNode*);
    treeNode* RR(treeNode*);
    treeNode* RL(treeNode*);
    /*rebalance*/
    treeNode* self_balance(treeNode*);
};

#endif