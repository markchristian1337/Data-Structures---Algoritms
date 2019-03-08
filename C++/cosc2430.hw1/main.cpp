#include "ArgumentManager.h"
#include <fstream>
#include <iterator>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;


//	Declare in simpleLinkedList.cpp a structure 'node' which defines a single
//	node of linkedList containing integers only. Your structure should have at
//	least one variable for data section and a pointer for the next node.

struct Node
{
    Node* link;
    string name;
    double data;
};


class simpleLinkedList
{
public:

    simpleLinkedList();
    ~simpleLinkedList();
	void sortedInsert(const string&, double&);
    void printFile(ofstream&);
    int length();
    double getTotal();
    double getMax();
	void remove(double); // delete a node containing specific item


private:
    int count;      //variable to store the number of list elements
    Node* first;    //pointer to the first node of the list
    Node* last;     //pointer to the last node of the list
};

simpleLinkedList::simpleLinkedList(){
    count = 0;
    first = NULL;
    last = NULL;
}

simpleLinkedList::~simpleLinkedList(){
    Node *temp; //pointer to deallocate the memory
                //occupied by the node
    while (first != NULL) //while there are nodes in the list
    {
        temp = first; //set temp to the current node
        first = first->link; //advance first to the next node
        delete temp; //deallocate the memory occupied by temp
    }
    last = NULL; //initialize last to NULL; first has already
    //been set to NULL by the while loop

    count = 0;
}


double simpleLinkedList::getTotal(){
    double total = 0.0;
    Node* current = first; //pointer to traverse the list
	while(current!=NULL) {
        total+=current->data;
        current = current->link;
	}
    return total;
}

double simpleLinkedList::getMax(){
    double max_price = 0.0;
    Node* current = first; //pointer to traverse the list
	while(current!=NULL) {
        if(current->data >= max_price){
            max_price = current->data;
        }
        current = current->link;
    }
    return max_price;
}

int simpleLinkedList::length(){
    return count;
}
/*
void simpleLinkedList::insertNode(const string& s, double& d)
{
    Node* node = new Node();
    node->name = s;
    node->data = d;
    node->link = NULL;

    if(first == NULL){
        first = node;
        last = node;
        count++;
    }
    else{
        last->link = node;
        last = node;
        count++;
    }
}
*/

void simpleLinkedList::sortedInsert(const string& name, double& data){
    Node* node = new Node();
    node->name = name;
    node->data = data;
    node->link = NULL;


    if(first==NULL || first->name >= name){
        node->link = first;
        first = node;
        count++;
    }
    else{
        Node* current = first;

        while (current->link!=NULL &&
               current->link->name < node->name)
        {
            current = current->link;
        }
        node->link = current->link;
        current->link = node;
        count++;
    }

}


void simpleLinkedList::printFile(ofstream &outFile)
{
    outFile.precision(2);
    outFile.setf(ios::fixed,ios::floatfield);
    Node* current = first; //pointer to traverse the list
	while(current!=NULL) {
		outFile<< current->name << ", " <<current->data<<endl;
		current = current->link;
	}
	outFile<<endl<<"Number of items: "<<length()<<endl;
	outFile<<"Cost: "<<getTotal();
}



// delete a node containing specific item
void simpleLinkedList::remove(double max_price){
    Node *current; //pointer to traverse the list
    Node *trailCurrent; //pointer just before current
    bool found;
    if (this->first == NULL)    //Case 1; the list is empty.
        cout << "Cannot delete from an empty list." << endl;
    else
    {
        if (this->first->data == max_price) //Case 2
        {

            current = this->first;
            this->first = this->first->link;
            this->count--;

            if (this->first == NULL) //the list has only one node
                this->last = NULL;

            delete current;
        }
        else //search the list for the node with the given info
            //set trailCurrent to point
            //to the first node
            //set current to point to
            //the second node
        {
            found = false;
            trailCurrent = this->first;
            current = this->first->link;

            while (current != NULL && !found)
            {
                if (current->data != max_price)
                {
                    trailCurrent = current;
                    current = current-> link;
                }
                else{ found = true;
                }
            }//end while

            if (found) //Case 3; if found, delete the node
            {
                trailCurrent->link = current->link;
                this->count--;
                if (this->last == current) //node to be deleted was the //last node
                    this->last = trailCurrent;//update the value of last delete current; //delete the node from the list
            delete current;
            }
            else
                cout << "The item to be deleted is not in the list." << endl;

        }//end else
    }//end else

}

bool checkList(string& item, double& price) //function to read alpha numeric
{

    if(item.empty()) return false;
 /*   while(item[i])
    {
        if(!isalnum(item[i]) && item[i] != ' ' && item[i] != '(' && item[i] != ')') //check each char in each//string for punctuation
        {
            return false;
        }
        i++;
    }*/
    if(price<0.0 || price=='\0')return false;
    else{
        return true;
    }
}




int main(int argc, char* argv[]){

    simpleLinkedList gList;

    cout.precision(2);
    cout.setf(ios::fixed,ios::floatfield);

    if (argc < 2) {
        cout << "Usage: main \"A=<file>;C=<file>\"" << endl;
        return -1;
    }

    // get input and output file names from arguments
    ArgumentManager am(argc, argv);
    string infilename = am.get("A");
    string outfilename = am.get("C");

    ifstream ifs(infilename);

    if(ifs.fail()){ //error message
        ofstream ofs(outfilename);
        ofs.close();
        exit(1);
    }

    double budget;
    string s_budget;
    string item;
    string s_price;
    double price;
    char check[1];

    ifs.read(check,1);
    if(!isdigit(*check)){
        ofstream ofs(outfilename);
        ofs.close();
        exit(1);
    }
    ifs.putback(*check);

    getline(ifs,s_budget);

    budget = atof(s_budget.c_str());
    //budget = stod(s_budget);
    if(ifs.eof()){
        ofstream ofs(outfilename);
        ofs.close();
        exit(1);
    }
    while(ifs.good()){

        getline(ifs,item,',');
        getline(ifs,s_price,'\n');
      /*  stringstream ss(item);
        ss>>item;
        stringstream ss1(s_price);
        ss1>>s_price;           */
        price = atof(s_price.c_str());
        //price = stod(s_price);
//        if(item)
        if(checkList(item,price) == true)
        {
            gList.sortedInsert(item,price);
        }
    }
    ifs.close();

    while(gList.getTotal()>budget){
        gList.remove(gList.getMax());
    }

    ofstream ofs(outfilename);
    gList.printFile(ofs);

    ofs.close();

    return 0;
}
