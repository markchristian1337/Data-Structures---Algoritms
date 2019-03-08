#include <iostream>
#include <cassert>
using namespace std;

template <class elemType>
class arrayListType
{
    public:
        //Overloads the assignment operator
        const arrayListType<elemType>& operator=(const arrayListType<elemType>&);

        bool isEmpty() const;
        //function to determine whether the list is empty
        //Postcondition: Returns true if the list is empty;
        //  otherwise, returns false.

        bool isFull() const;
        //Function to determine whether the list is full.
        //Postcondition: Returns true if the list is full;
        //  otherwise, returns false.

        int listSize() const;
        //function to determine the number of elements in the list
        //Postcondition: Returns the value of length.

        int maxListSize() const;
        //Function to determine the size of the list.
        //Postcondition: Returns the value of maxSize.

        void print() const;
        //Function to output the elements of the list
        //Postcondition: Elements of the list are output on the
        // standard output device.

        bool isItemAtEqual(int location, const elemType& item) const;
        //Function to determine whether the item is the same
        //as the item in the list at the position specified by
        //Postcondition: Returns true if list[location]
        // is the same as the item; otherwise,
        // returns false.

        void insertAt(int location, const elemType& insertItem);
        //Function to insert an item in the list at the
        //position specified by location. The item to be inserted
        //is passed as a parameter to the function.
        //Postcondition: Starting at location, the elements of the
        // list are shifted down, list[location] = insertItem;,
        // and length++;. If the list is full or location is
        // out of range, an appropriate message is displayed.

        void insertEnd(const elemType& insertItem);
        //Function to insert an item at the end of the list.
        //The parameter insertItem specifies the item to be inserted.
        //Postcondition: list[length] = insertItem; and length++;
        // If the list is full, an appropriate message is
        // displayed.

        void removeAt(int location);
        //Function to remove the item from the list at the
        //position specified by location
        //Postcondition: The list element at list[location] is removed
        // and length is decremented by 1. If location is out of
        // range, an appropriate message is displayed.

        void retrieveAt(int location, elemType& retItem) const;
        //Function to retrieve the element from the list at the
        //position specified by location.
        //Postcondition: retItem = list[location]
        // If location is out of range, an appropriate message is
        // displayed.

        void replaceAt(int location, const elemType& repItem);
        //Function to replace the elements in the list at the
        //position specified by location. The item to be replaced
        //is specified by the parameter repItem.
        //Postcondition: list[location] = repItem
        // If location is out of range, an appropriate message is
        // displayed.

        void clearList();
        //Function to remove all the elements from the list.
        //After this operation, the size of the list is zero.
        //Postcondition: length = 0;

        int seqSearch(const elemType& item) const;
        //Function to search the list for a given item.
        //Postcondition: If the item is found, returns the location
        // in the array where the item is found; otherwise,
        // returns -1.

        void insert(const elemType& insertItem);
        //Function to insert the item specified by the parameter
        //insertItem at the end of the list. However, first the
        //list is searched to see whether the item to be inserted
        //is already in the list.
        //Postcondition: list[length] = insertItem and length++
        // If the item is already in the list or the list
        // is full, an appropriate message is displayed.

        void insertordered(elemType& obj);
        //inserts items into the array in an ordered fashion

        void remove(const elemType& removeItem);
        //Function to remove an item from the list. The parameter
        //removeItem specifies the item to be removed.
        //Postcondition: If removeItem is found in the list,
        // it is removed from the list and length is
        // decremented by one.

        arrayListType(int size = 100);
        //constructor
        //Creates an array of the size specified by the
        //parameter size. The default array size is 100.
        //Postcondition: The list points to the array, length = 0,
        // and maxSize = size
        arrayListType(const arrayListType<elemType>& otherList);
        //copy constructor
        ~arrayListType();

        elemType getValue(int index){
            return list[index];
        }
        //destructor
        //Deallocates the memory occupied by the array.
        protected:
        elemType *list; //array to hold the list elements
        int length; //to store the length of the list
        int maxSize; //to store the maximum size of the list
};


template <class elemType>
bool arrayListType<elemType>::isEmpty() const
    {
    return (length == 0);
    }

template <class elemType>
bool arrayListType<elemType>::isFull() const
    {
    return (length == maxSize);
    }

template <class elemType>
int arrayListType<elemType>::listSize() const
    {
    return length;
    }

template <class elemType>
int arrayListType<elemType>::maxListSize() const
    {
    return maxSize;
    }

template <class elemType>
void arrayListType<elemType>::print() const
{
    for (int i = 0; i < length; i++)
        cout << list[i];
    cout << endl;
}

template <class elemType>
bool arrayListType<elemType>::isItemAtEqual
    (int location, const elemType& item) const {

        return(list[location] == item);
    }

template <class elemType>
void arrayListType<elemType>::insertAt(int location, const elemType& insertItem) {
    if (location < 0 || location >= maxSize) {
            cerr << "The position of the item to be inserted is out of range" << endl;
    }else {

        if (length >= maxSize) { //list is full
                cerr << "Cannot insert in a full list" << endl;
        }else if(location ==0 && list[0].getID()==""){
            list[0] = insertItem;cout<<insertItem;
        }else{
            cout <<"test3"<<endl;
        for (int i = length; i > location; i--){
            cout <<"test4"<<endl;
            list[i] = list[i - 1]; //move the elements down
            list[location] = insertItem; //insert the item at the
            //specified position
            length++; //increment the length
            cout<<"Inserted: "<<insertItem<<" at pos: "<<location<<endl;
        }
        }
    }
} //end insertAt

template <class elemType>
void arrayListType<elemType>::insertordered(elemType& obj){

            if (length >= maxSize){ //list is full
                cerr << "Cannot insert in a full list" << endl;
            }else {
                for (int i = 0; i < length+1; i++){
                    if(!(obj > list[i]) || list[i].getID() == ""){
                        //insertAt(i,obj);

                        for(int j =length-1;j>=i;j--){
                            if(list[j].getID() !=""){
                                list[j+1] = list[j]; //move the elements down
                            }

                        }
                        list[i] = obj; //insert the item at the
                                        //specified position
                        length++; //increment the length
                        break;

                    }
                }
            }

}


template <class elemType>
void arrayListType<elemType>::insertEnd(const elemType& insertItem)
{
    if (length >= maxSize) { //the list is full
        cerr << "Cannot insert in a full list" << endl;
    }
    else
    {
        list[length] = insertItem; //insert the item at the end
        length++; //increment the length
    }
} //end insertEnd

template <class elemType>
void arrayListType<elemType>::removeAt(int location){
    if (location < 0 || location >= length){
    cerr << "The location of the item to be removed is out of range" << endl;
    }
    else {

    for(int i = location; i < length - 1; i++) {
        list[i] = list[i+1];
        length--;
    }
    }

} //end removeAt

template <class elemType>
void arrayListType<elemType>::retrieveAt(int location, elemType& retItem) const {
    if (location < 0 || location >= length){
        cerr << "The location of the item to be retrieved is out of range." << endl;
    }else{
        retItem = list[location];
    }

} //end retrieveAt

template <class elemType>
void arrayListType<elemType>::replaceAt(int location, const elemType& repItem){
    if (location < 0 || location >= length) {
    cerr << "The location of the item to be replaced is out of range." << endl;
    }
    else
    {
        list[location] = repItem;
    }

} //end replaceAt



template <class elemType>
void arrayListType<elemType>::clearList()
{
    length = 0;

} //end clearList



template <class elemType>
arrayListType<elemType>::arrayListType(int size)
{
    if (size < 0)
    {
        cerr << "The array size must be positive. Creating "
        << "an array of size 100. " << endl;
        maxSize = 100;
    }
    else    {
        maxSize = size;
        length = 0;
        list = new elemType[maxSize];
        assert(list != NULL);
    }

}

template <class elemType>
arrayListType<elemType>::~arrayListType()
{
    delete [] list;
}
