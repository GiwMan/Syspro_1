#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

class Patient{
private:
    string patientId;
    string FName, LName;
    string Disease, Country;
    //string Entry, Exit;
    date *entryDate, *exitDate;
public:
    Patient();
    Patient(string,string,string,string,string,date*,date*);//string,string);//string,string);
    Patient(string,string,string,string,string,string,string);
    ~Patient();

    //getters
    string getPatientId();
    string getPatientFirstName();
    string getPatientLastName();
    string getPatientDisease();
    string getPatientCountry();
    date* getEntryDate();
    date* getExitDate();
    bool still_inHospital();
    // setters
    void setExitDate(string);

    void print();
};

    // Patient List
struct node
{
    Patient *patientData;
    node *next, *prev;

    node(Patient*);
    ~node();
};

class list{
private:
    node *head, *tail;
public:
    list();
    //list(Patient*);
    //list(const list&);
    ~list();

    // functions of list

    void display();


    Patient* get_last();
    node *get_last_node();
    void insert_exitDate(string,string);
    int getNumCurrentPatients(string);
    //void printDiseaseStats(list*);
    void delete_list(node*&);
    node *get_head();

    node* insert_after(node*,Patient*);
    node* insert_start(Patient*);
    node* insert_before(node*,Patient*);
};


#endif