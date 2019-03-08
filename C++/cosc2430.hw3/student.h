#pragma once
#include <iostream>
//#include "linkedList.h"
#include "date.h"
#include <cstdio>
#include <string>

using namespace std;
class Student {
    private:
            string studentID;
            string firstName;
            string lastName;
            string major;
            float GPA;
            Date *DOB;
    public:
            Student()   {
                studentID = "";
                firstName = "";
                lastName ="";
                major = "";
                GPA = 0.0;
                DOB = new Date();
            }
            Student(string iD, string fName, string lName, string Major, float grade, Date &dateOB){//:   //composition instead of overloading, working better
                //Student(id),fName(fn),lName(ln), Major(mj), grade(gr), DOB(dob)



                studentID = iD;
                firstName = fName;
                lastName = lName;
                major = Major;
                GPA = grade;
                //int y, m, d;
                //sscanf_s(dateOB.c_str(), "%d-%d-%d", &y, &m, &d);
                DOB = new Date(dateOB);
            }

            string getID() {
                return studentID;
            }
            string getFName()   {
                return firstName;
            }
            string getLName()   {
                return lastName;
            }
            string getMajor() {
                return major;
            }
            float getGPA() {
                return GPA;
            }
            Date getDOB()   {
                return *DOB;
            }

        void print()
        {
            cout << studentID <<" "<< firstName << " " << lastName << " " << DOB->printDatestr() << " " << major << " " << GPA << " " << endl;
        }

        string out(){
             string str = studentID + " "+ firstName + " " + lastName + " " + DOB->printDatestr() + " " + major + " " + to_string(GPA) + " \n";
             return str;
        }

        bool operator >(Student a){
            if(studentID > a.studentID){return true;}
            else{return false;}
        }

        friend ostream& operator <<(ostream& abc,Student a);

};

ostream& operator <<(ostream& abc,Student a){
            abc << a.out();
            return abc;
}
