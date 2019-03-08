#include <iostream>
#include <cstdlib>

using namespace std;


struct Node
{
    Node* link;
    string name;
    double price;
};



class simpleLinkedList
{
public:

    simpleLinkedList();
    ~simpleLinkedList();
    void add(string,double);
    void print();
    int length();
//    int itemAt(int location);   //returns the item at location
    void insertAt(int insertItem, int location); // insert a node at a specific position in the list
	void remove(int removeItem); // delete a node containing specific item
	void insertSorted(int insertItem);
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

void simpleLinkedList::print(){
    Node* temp = first;
    while(temp != NULL){
        cout << temp->name << ", "<<temp->price;
        temp = temp->link;
    }
}

int simpleLinkedList::length(){
    return count;
}


//Function to insert newItem at the end of the list.
//Postcondition: first points to the new list, newItem is
// inserted at the end of the list, last points to the
// last node, and count is incremented by 1.
void simpleLinkedList::add(string s,double d){
    Node* node = new Node();
    node->name = s;
    node->price = d;
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


// insert a node at a specific position in the list
void simpleLinkedList::insertAt(string s, int location){
    node->name = s;
    node->link = NULL;


    if(location==0){ // insert in the first position
            node->link = this->first;
            first = node;
            if (last == NULL) //if the list was empty, newNode is also //the last node in the list
                last = node;
            count++;
        }
    else if(location<=count){
            int localCount = 0;
            Node *current = first;
            while(localCount<(location-1) ){
                current = current->link;
                localCount++;
            }
            node->link = current->link;
            current->link = node;

            count++;
    }
    else
        cout <<"Can not insert at location = "<<location << "! List length is " << count  << endl;


}


/*
int simpleLinkedList::itemAt(int location){
    Node* node = new Node();


    if(location==0){ // insert in the first position
            return first->data;
        }
    else if(location<count){
            int localCount = 0;
            Node *current = first;
            while(localCount<(location) ){
                current = current->link;
                localCount++;
            }
            return current->data;
    }
    else{
        cout <<"Can not find item at location = "<<location << "! List length is " << count  << endl;
        throw;
    }

}
*/



void simpleLinkedList::remove(int deleteItem){
    Node *current; //pointer to traverse the list
    Node *trailCurrent; //pointer just before current
    bool found;
    if (this->first == NULL)    //Case 1; the list is empty.
        cout << "Cannot delete from an empty list." << endl;
    else
    {
        if (this->first->name == deleteItem) //Case 2
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
                if (current->name != deleteItem)
                {
                    trailCurrent = current;
                    current = current-> link;
                }
                else found = true;
            }//end while

            if (found) //Case 3; if found, delete the node
            {
                trailCurrent->link = current->link;
                this->count--;
                if (this->last == current) //node to be deleted was the //last node
                    this->last = trailCurrent; //update the value of last delete current; //delete the node from the list
            }
            else
                cout << "The item to be deleted is not in the list." << endl;

        }//end else
    }//end else

}


void simpleLinkedList::insertSorted(string n){
    Node* node = new Node();
    node->name = n;
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

/*

void sortedInsert(struct Node** first_ref, struct Node* new_node)
{
    struct Node* current;
    // Special case for the first end
    if (*first_ref == NULL || (*first_ref)->data >= new_node->data)
    {
        new_node->next = *first_ref;
        *first_ref = new_node;
    }
    else
    {
        // Locate the node before the point of insertion
        current = *first_ref;
        while (current->next!=NULL &&
               current->next->data < new_node->data)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

*/

