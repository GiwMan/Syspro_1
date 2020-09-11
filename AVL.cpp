#include <iostream>
#include "AVL.h"

using namespace std;
/* treeNode functions */
treeNode::treeNode()
:   left(NULL), right(NULL),parent(NULL),
    countDates(0),
    height(0),ptr_to_lnode(NULL),
    //patientList(new list()),
    key(new date())
{

}

treeNode::treeNode(const treeNode& node)
:   left(NULL), right(NULL), parent(NULL),
    countDates(node.countDates),height(node.height),
    //ptr_to_lnode(new node())
    key(new date(*node.key))
{

}

treeNode::treeNode(Patient *p)
:   left(NULL), right(NULL), parent(NULL),
    countDates(1)  ,height(1),
    ptr_to_lnode(NULL),
    key(new date(*p->getEntryDate()))
{   // create a list with 1 patient at first

}
treeNode::treeNode(node *node_ptr)
:   left(NULL), right(NULL), parent(NULL),
    countDates(1),height(1),
    ptr_to_lnode(node_ptr),
    key(new date(*node_ptr->patientData->getEntryDate()))
{   // create a list with 1 patient at first

}

treeNode::~treeNode(){ delete key; }

void treeNode::printNode()
{
    node *current = ptr_to_lnode;

    //cout << "=================================\n";
    //cout << "leaf "; key->print(); cout << " pointing to: \n";

    while(current)
    {
        current->patientData->print();
        if(current->next)
        {
            if(current->next->patientData->getEntryDate()->compare(ptr_to_lnode->patientData->getEntryDate()) == 0)
                current = current->next;
            else
                break;
        }else
            break;
    }   
    //cout << "#dates = " << countDates << endl;
    //cout << "=================================\n";
}

node* treeNode::get_node() { return ptr_to_lnode;}
/* avl functions */
AVL::AVL()
:   root(NULL)
{

}

AVL::AVL(const AVL& avl)
:   root(NULL)
{
    if(avl.root)
        root = copyTree(avl.root);
}



AVL::~AVL()
{
    delete_helper();
    root = NULL;
}

treeNode* AVL::copyTree(treeNode *node)
{   // Recursive copy function for a BST
    if(node)
    {
        treeNode *temp = new treeNode(*node);
        temp->left = copyTree(node->left);
        temp->right = copyTree(node->right);

        return temp;
    }
    return NULL;
}

void AVL::delete_helper() { deleteTree(root); }

void AVL::deleteTree(treeNode *&node)
{   // Recursive delete function for a BST
    if(node)
    {   // first delete leaf nodes and then parent
        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }
}

treeNode* AVL::getRoot() { return root; }

int AVL::getHeight(treeNode *node)
{
    if(node) return node->height;
    else
        return 0;
}
/* get balance factor of given node */
int AVL::getBalanceFactor(treeNode *node)
{
    if(node)
        return getHeight(node->left) - getHeight(node->right);
    else 
        return 0;
}
/* get total nodes in tree */
int AVL::get_total_nodes(treeNode *proot)
{
    int count = 1;
    if(proot == NULL) return 0;
    else
    {
        count = proot->countDates;

        count +=  get_total_nodes(proot->left);
        count += get_total_nodes(proot->right);
        
        return count;
    }
}
/* count nodes of bst in a range recursively */
int AVL::get_nodes_inRange(treeNode* proot, date* date1, date* date2, int& count)
{ /*base  case of recursion */
    if(proot == NULL)
        return 0;
    if((proot->key->compare(date1) == 0) && (proot->key->compare(date2) == 0))
    {   /* counDates holds the duplicate dates */
        int c = 1;
        node *current = proot->ptr_to_lnode;
        node *prev = proot->ptr_to_lnode;
        
        while(current)
        {
            current = current->next;
            if(current)
                if(current->patientData->getEntryDate()->compare(proot->ptr_to_lnode->patientData->getEntryDate()) == 0)
                {
                    prev = current;
                    c++;
                }
                else
                    break;
        }
        return c;
    }
    if((proot->key->compare(date1) >= 0) && (proot->key->compare(date2) <= 0))
    {   /* counDates holds the duplicate dates */
        int k = 1;
        node *current = proot->ptr_to_lnode;
        node *prev = proot->ptr_to_lnode;

        while(current)
        {
            current = current->next;
            if(current)
                if(current->patientData->getEntryDate()->compare(proot->ptr_to_lnode->patientData->getEntryDate()) == 0 )
                {
                    prev = current;
                    k++;
                }
                else
                    break;
        }
        return k + get_nodes_inRange(proot->left,date1,date2,count) + get_nodes_inRange(proot->right,date1,date2,count);
    }
    /* inorder check */
    else if(proot->key->compare(date1) < 0) return get_nodes_inRange(proot->right,date1,date2,count);
    else
        return get_nodes_inRange(proot->left,date1,date2,count);
    //get_nodes_inRange(proot->left,date1,date2,count);
    //get_nodes_inRange(proot->right,date1,date1,count);
}

int AVL::get_nodes_inRange(treeNode* proot, date* date1, date* date2,string country, int& count)
{ /*base  case of recursion */
    if(proot == NULL)
        return 0;
    if((proot->key->compare(date1) == 0) && (proot->key->compare(date2) == 0))
    {   /* counDates holds the duplicate dates */
        int c = 0;
        node *current = proot->ptr_to_lnode;
        node *prev = proot->ptr_to_lnode;

        if(proot->ptr_to_lnode->patientData->getPatientCountry() == country) c++;
        
        while(current)
        {
            current = current->next;
            if(current)
                if(current->patientData->getEntryDate()->compare(proot->ptr_to_lnode->patientData->getEntryDate()) == 0)
                {
                    prev = current;
                    if(current->patientData->getPatientCountry() == country)
                        c++;
                }
                else
                    break;
        }
        return c;
    }
    if((proot->key->compare(date1) >= 0) && (proot->key->compare(date2) <= 0) )
    {   /* counDates holds the duplicate dates */
        //return 1 + get_nodes_inRange(proot->left,date1,date2,count) + get_nodes_inRange(proot->right,date1,date2,count);
        int k = 0;
        node *current = proot->ptr_to_lnode;
        node *prev = proot->ptr_to_lnode;

        if(proot->ptr_to_lnode->patientData->getPatientCountry() == country) k++;
        
        while(current)
        {
            current = current->next;
            if(current)
                if(current->patientData->getEntryDate()->compare(proot->ptr_to_lnode->patientData->getEntryDate()) == 0 )
                {
                    prev = current;
                    if(current->patientData->getPatientCountry() == country )
                        k++;
                }
                else
                    break;
        }

        return k + get_nodes_inRange(proot->left,date1,date2,country,count) + get_nodes_inRange(proot->right,date1,date2,country,count);
    }
    /* inorder check */
    else if(proot->key->compare(date1) < 0) return get_nodes_inRange(proot->right,date1,date2,country,count);
    else
        return get_nodes_inRange(proot->left,date1,date2,country,count);
    //get_nodes_inRange(proot->left,date1,date2,count);
    //get_nodes_inRange(proot->right,date1,date1,count);
}


void AVL::fixHeight(treeNode *node)
{
    node->height = 1 + max(getHeight(node->left),getHeight(node->right));
}

// Rotations

treeNode* AVL::LL(treeNode *node)
{
    treeNode *Lchild = node->left;
    node->left = Lchild->right;
    if(Lchild->right)
        Lchild->right->parent = node;

    Lchild->right = node;

    Lchild->parent = node->parent;
    node->parent = Lchild;

    fixHeight(node);

    return Lchild;
}
treeNode* AVL::LR(treeNode *node)
{
    treeNode *Lchild = node->left;

    node->left = RR(Lchild);
    
    return LL(node);
}

treeNode* AVL::RR(treeNode *node)
{
    treeNode *Rchild = node->right;
    node->right = Rchild->left;
    if(Rchild->left)
        Rchild->left->parent = node;

    Rchild->left = node;

    Rchild->parent = node->parent;
    node->parent = Rchild;

    fixHeight(node);

    return Rchild;
}

treeNode* AVL::RL(treeNode *node)
{
    treeNode *Rchild = node->right;

    node->right = LL(Rchild);

    return RR(node);
}

treeNode* AVL::self_balance(treeNode* node)
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



bool AVL::id_found(treeNode *current,Patient *p)
{
    if(current == NULL) return false;

    if(current->get_node()->patientData->getPatientId() == p->getPatientId())
        return true;
    // node with id found
    if(id_found(current->left,p)) return true;
    // if not found yet keep searching
    if(id_found(current->right,p)) return true;
    else return false;
}

bool AVL::search_id(Patient *p) { return id_found(root,p); }



treeNode* AVL::insertNode(Patient *person_ptr, treeNode *proot,
                    list *&l, node *&last_inserted)
{ //  Recursive insertion of BST
    if(proot == NULL)
    {
        proot = new treeNode(person_ptr);

        if(l->get_head() == NULL)
        {
            proot->ptr_to_lnode = l->insert_start(person_ptr);
            last_inserted = proot->ptr_to_lnode;
        }
        
        return proot;
    }
    
    if( proot->key->compare(person_ptr->getEntryDate()) > 0  ){
        // insert in left 
        proot->left = insertNode(person_ptr,proot->left,l,last_inserted);   

        proot->left->parent = proot;

        node *parent_node = proot->left->parent->get_node();
        // insert before parent's node
        if(proot->left->ptr_to_lnode == NULL)
        {
            proot->left->ptr_to_lnode = l->insert_before(parent_node,person_ptr);

            last_inserted = proot->left->ptr_to_lnode;
        }    
    }else if (proot->key->compare(person_ptr->getEntryDate()) < 0)
    {
        proot->right = insertNode(person_ptr,proot->right,l,last_inserted);   


        proot->right->parent = proot;

        node *parent_node = proot->right->parent->get_node();

        if(proot->right->ptr_to_lnode == NULL)
        {
        /**
         * find next node with different date of already_in_list 
         * x---->y--->12-2-2015--->12-2-2015--->z\
         * for example tree node with key value 12-2-2015 points to
         * the first appearance of 12-2-2015 in the list. So i have to find
         * the last appearance of it and insert the new node after the last appearance
         * of it.
         **/
            node *current = parent_node;
            node *prev = parent_node;

            while(current)
            {
                current = current->next;
                if(current)
                    if(current->patientData->getEntryDate()->compare(parent_node->patientData->getEntryDate()) == 0)
                        prev = current;
                    else
                        break;
            }
            proot->right->ptr_to_lnode = l->insert_after(prev,person_ptr);
            last_inserted = proot->right->ptr_to_lnode;
        }
    }else
    {   // there is a duplicate date
    //person_ptr->print();
        // create node to insert
        //node *to_insert = new node(person_ptr);
        // points to the first appearance of the date in the list
        node *already_in_list = proot->get_node();
        // insert it after
        proot->ptr_to_lnode->next = l->insert_after(already_in_list,person_ptr); 
        last_inserted = proot->ptr_to_lnode->next;
    }
    // Update heights
    fixHeight(proot);
    // balance current node if needed
    proot = self_balance(proot);

    return proot;
}

void AVL::insert(Patient* p,list *&l, node *& last_inserted)
{ 
    root = insertNode(p,root,l, last_inserted);
}


treeNode* AVL::insertNode(treeNode *proot, node* ptr_node)
{   
    if(proot == NULL)
    {
        proot = new treeNode(ptr_node);
        
        return proot;
    }
    
    if( proot->key->compare(ptr_node->patientData->getEntryDate()) > 0  ){
        // insert in left 
        proot->left = insertNode(proot->left,ptr_node);   

        proot->left->parent = proot;

        node *parent_node = proot->left->parent->get_node();

    }else if (proot->key->compare(ptr_node->patientData->getEntryDate()) < 0)
    {
        proot->right = insertNode(proot->right,ptr_node);   

        proot->right->parent = proot;

        node *parent_node = proot->right->parent->get_node();

    }else
    {   // there is a duplicate date
        proot->countDates++;
    }
    // Update heights
    fixHeight(proot);
    // balance current node if needed
    proot = self_balance(proot);

    return proot;
}

void AVL::insert(node *ptr)
{
    root = insertNode(root,ptr);
}

/* preorder traversal */
void AVL::preorder(treeNode *proot)
{
    if(proot == NULL) return;

    proot->printNode();
    cout << endl;
    preorder(proot->left);
    preorder(proot->right);
}
/* helper function to print in preorder */
void AVL::print_preorder() { preorder(root); }
/* search by id */
bool AVL::id_found(treeNode *proot, string id, string exitD, int &error)
{
    if(proot == NULL) return false;

    if(proot->get_node()->patientData->getPatientId() == id)
    {
        error = 1; // means that id exists
        return update_exitDate(proot,exitD);
    }
        
    // node with id found
    if(id_found(proot->left,id,exitD,error)) return true;
    // if not found yet keep searching
    if(id_found(proot->right,id,exitD,error)) return true;
    else return false;
}
/* return if id exists */
bool AVL::search_id(string id,string exitD,int& error)
{
    return id_found(root,id,exitD,error);
}
/* helper function of updating exit date of a patient */
bool AVL::update_exitDate(treeNode* proot, string exit_d)
{
    if(proot)
    {
        node *to_update = proot->get_node();

        if(to_update)
        {   
            if(exit_d == "-")
            {
                to_update->patientData->setExitDate(exit_d);
                return true;
            }
            /* create a temporary date object and compare it with
                the entry date we have */
            date *exitDate = new date(exit_d);
            /* update it */
            if(to_update->patientData->getEntryDate()->compare(exitDate) <= 0)
                to_update->patientData->setExitDate(exit_d);
            else
            {
                //cout << " The patient's entry date is "; 
                //to_update->patientData->getEntryDate()->print();
                //cout << " Update cannot be done when exit date is earlier than entry!";
                //cout << " Exit date : '" << exit_d << "'\n";
                delete exitDate;
                return false;
            }
            delete exitDate;
            return true;
        }
    }
    return false;
}