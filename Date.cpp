#include <iostream>
#include <sstream>
#include "Date.h"

using namespace std;

date::date()
:   year(0), month(0), day(0)
{
    
}

date::date( int d, int m, int y) 
:   month(m), day(d), year(y)
{ 

}

date::date(string str)
{
    if(str != "-")
    {
        stringstream ss(str);
        string s1;
        
        getline(ss,s1,'-');
        day = atoi(s1.c_str());
        getline(ss,s1,'-');
        month = atoi(s1.c_str());
        getline(ss,s1,'-');
        year = atoi(s1.c_str());
    }
    else
    {
        day = '-'; month = '-'; year = '-';
    }
}
date::~date(){ }//cout << "Destroying a date!" << endl; }
void date::set(int i, int j, int k)
{ day = i; month = j; year = k;}
void date::get(int& i, int& j, int& k) const
{ i = day; j = month ; k = year; }
void date::print()
{
    if(day == '-')
        cout << "-"<<endl;
    else
    {
        cout << day << "-"<<month<<"-"<<year<<endl;
    }
}

int date::compare(date* d)
{
    int dd,mm,yy;

    d->get(dd,mm,yy);

    if(year != yy)
        return year - yy;
    else if(month != mm)
        return month - mm;
    else
        return day - dd; 
}