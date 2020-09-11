 //h->printDiseaseStats(Lpatients);#include <iostream>
#include <string>
#include <sstream>
#include "Patient.h"

using namespace std;

Patient::Patient()
{
    //cout << "A Patient just created!\n";
}

Patient::Patient(string id, 
    string nam, string last,
    string disease, string country,
    date* entry, date* exit) 
:   patientId(id),
    FName(nam),LName(last),
    Disease(disease),Country(country),
    entryDate(new date(*entry)),exitDate(new date(*exit))
{
    //cout << "A Patient just created!\n";
}

Patient::Patient(string id,
    string nam, string last,
    string disease, string country,
    string entry, string exit)
:   patientId(id),
    FName(nam),LName(last),
    Disease(disease),Country(country),
    entryDate(new date(entry)),
    exitDate(new date(exit))
{

}

Patient::~Patient()
{
    //cout << "A Patient has been destroyed!\n";
    delete entryDate;
    delete exitDate;
}

//getters
string Patient::getPatientId(){ return patientId; }
string Patient::getPatientFirstName() { return FName; }
string Patient::getPatientLastName() { return LName; }
string Patient::getPatientDisease() { return Disease; }
string Patient::getPatientCountry() { return Country; }
date* Patient::getEntryDate() { return entryDate; }
date* Patient::getExitDate() { return exitDate; }
bool Patient::still_inHospital()
{
    int dd, mm, yy;

    exitDate->get(dd,mm,yy);

    if(dd == '-')
        return true;
    else
        return false;
}
//setters
void Patient::setExitDate(string exit)
{
    stringstream ss(exit);
    string s1;
    int day, month, year;
        
    getline(ss,s1,'-');
    day = atoi(s1.c_str());
    getline(ss,s1,'-');
    month = atoi(s1.c_str());
    getline(ss,s1,'-');
    year = atoi(s1.c_str());

    exitDate->set(day,month,year);
}


void Patient::print()
{
    cout << "* " << patientId << " *" << endl;
    cout <<"    FName:" << FName << endl;
    cout <<"    LName:" << LName << endl;
    cout <<"    Disease:" << Disease << endl;
    cout <<"    Country:" << Country << endl;
    cout <<"    Entry: "; entryDate->print();//<< Entry << endl;
    cout <<"    Exit: "; exitDate->print(); 
}

node::node(Patient* patient)
:   patientData(patient),
    next(NULL), prev(NULL)
{ }

node::~node()
{
    delete patientData; 
}

list::list() { head = NULL; tail = NULL; }


list::~list()
{
    delete_list(head);

}

node* list::get_head(){ return head; }

void list::delete_list(node *&phead)
{
    node *prev_node = head;

    while(head)
    {
        head = head->next;
        delete prev_node;
        prev_node = head;
    }
}
/* insert at tail position in list */
node* list::insert_after(node* prev_node, Patient *p)
{   // insert node after given node
    node *to_insert = new node(p);

    if(prev_node == tail)
    {   // if previous is the tail node
        tail->next = to_insert;
        // set previous of new node to tail
        to_insert->prev = tail;
        // change previous
        tail = to_insert;
    }
    else
    {   // set next of to_insert node
        to_insert->next = prev_node->next;
        // now previous node is linked to new node
        prev_node->next = to_insert;
        // make previous of new node point to prev_node
        to_insert->prev = prev_node;
        // create a link between old nodes
        to_insert->next->prev = to_insert;
    }

    return to_insert;
}
/* insert at start of list */
node* list::insert_start(Patient* p)
{   
    node *to_insert = new node(p);
    // make next as head
    to_insert->next = head;
    // if empty list
    if(head == NULL)
    {
        head = to_insert;
        tail = to_insert;    
    }else{
        head->prev = to_insert;
        head = to_insert;
    }

    return to_insert;
}
/* insert before given node in list */
node* list::insert_before(node* given_node, Patient* p)
{
    node *to_insert = new node(p);

    if(given_node == head)
    {
        to_insert->next = head;
        to_insert->prev = NULL;

        head->prev = to_insert;
        head = to_insert;

        return head;
    }

    to_insert->next = given_node;
    to_insert->prev = given_node->prev;

    given_node->prev = to_insert;

    if(to_insert->prev)
        to_insert->prev->next = to_insert;
    else
        head = to_insert;

    return to_insert;
}
/* update exit date of given id */
void list::insert_exitDate(string id, string exit)
{
    node *current = head;

    int d, m, y;

    while(current != NULL)
    {
        if(current->patientData->getPatientId() == id)
        {   
            current->patientData->getExitDate()->get(d,m,y);
            if(d == '-')
            {
                current->patientData->setExitDate(exit);
                return;
            }else
            {   current->patientData->setExitDate(exit);
                return;
            }

        }
        current = current->next;
    }
    //cout << "Patient with id = " << id << " doesn't exist.\n";

}
/* return number of patients that are still in hospital with given disease */
int list::getNumCurrentPatients(string disease)
{
    node *current = head;
    int numCurrentPatients = 0;

    while(current)
    {
        if(current->patientData->getPatientDisease() == disease)
        {
            if(current->patientData->still_inHospital())
            {
                numCurrentPatients++;
            }
        }
        current = current->next;
    }
    return numCurrentPatients;
}

node* list::get_last_node() { return tail; }

Patient* list::get_last() 
{ 
    if(tail)
        return tail->patientData;
    return NULL;
}

void list::display()
{
    node* temp = head;

    while(temp != NULL)
    {
        temp->patientData->print();
        temp = temp->next;
    }
}
