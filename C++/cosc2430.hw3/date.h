#ifndef H_DATE
#define H_DATE
#include <string.h>
#include <iostream>

using namespace std;

class Date
{
    private:
        int day;
        int month;
        int year;
    public:
        Date(){     //default constructor
            day = 0;
            month = 0;
            year = 0;
        }

       /* Date(Date &a){
            day = a.day;
            month = a.month;
            year = a.year;
        }
        */

        Date(int yearOB, int monthOB, int dayOB)
        {
            day = dayOB;
            month = monthOB;
            year = yearOB;
        }

        Date(string a){
            string delimiter = "-";
            size_t pos = 0;
            string token;
            a+="-";

                pos = a.find(delimiter);
                token = a.substr(0, pos);

                year = stoi(token);//gets year

                a.erase(0, pos + delimiter.length());

                pos = a.find(delimiter);
                token = a.substr(0, pos);

                month = stoi(token);//gets month

                a.erase(0, pos + delimiter.length());

                pos = a.find(delimiter);
                token = a.substr(0, pos);

                day = stoi(token);//gets day

                a.erase(0, pos + delimiter.length());



        }

        int getYear()
        {
            return year;
        }

        int getMonth(){
            return month;
        }

        int getDay(){
            return day;
        }

        string toString()
        {
            string DOB = "";
            DOB += to_string(year) + to_string(month) + to_string(day);
            return DOB;
        }

        void printDate(){
            cout << year <<"-" << month<< "-" << day<< endl;
        }

        string printDatestr(){
            string str="";
            str += to_string(year) + "-" + to_string(month) + "-" + to_string(day);
            return str;
        }

        bool operator==(const Date& d) const {
            return (day == d.day && month == d.month && year == d.year);
        }
        void operator= (const Date& d){
            day = d.day;
            month = d.month;
            year = d.year;
        }
        bool operator> (const Date& d) const{
            if (this->year > d.year)
            return true;
            if (this->year < d.year)
            return false;
            if (this->month > d.month)
            return true;
            if (this->month < d.month)
            return false;
            if (this->day > d.day)
            return true;
            if (this->day < d.day)
            return false;
        }
        friend ostream& operator<< (ostream& osObject, const Date& d);
};

ostream& operator<< (ostream& osObject, const Date& d) {
        osObject << d.year << "-" << d.month << "-" << d.day;
        return osObject;
    }


#endif
