#ifndef DATE_H_
#define DATE_H_

#include <iostream>

using namespace std;

   class date {
     private:
        int day, month, year;
     public:
        date( int d , int m , int y);
        date();
        date(string); // convert string to date
        ~date();
        //bool operator==(const date& d1,const date& d2);
        void set(int i, int j, int k);
             //{ day = i; month = j; year = k;}
        void get(int& i, int& j, int& k) const;
             //{ i = day; j = month ; k = year; }
        void print();
        int compare(date *d);
    };

#endif