#include <iostream>
#include "student.h"
#include "arrayList.h"
#include "AVLtree.h"
#include "ArgumentManager.h"
#include <string.h>
#include <fstream>

using namespace std;

arrayListType<Student> gatherinfo(string inputfile);


int binarySearch(arrayListType<Student> *arr, int l, int r, string x){

	if(r<l()){
		return -1;/* REMOVE */
	}
	int mid = (l + r) / 2;
	Student v = arr->getValue(mid);
	if(x == v){
		return mid;/* REMOVE */
	}
	else if(x < v){
		return binarySearch(arr, l, mid-1, x);/* REMOVE */
	}
	return binarySearch(arr, mid+1, r, x);/* REMOVE */
}




int main(int argc, char*argv[]){

    ArgumentManager am(argc, argv);
    string infilename1 = am.get("A");
    string infilename2 = am.get("B");
    string outfilename = am.get("C");
    cout << "inputfilename1 is " <<infilename1 << "\ninfilename2 is " << infilename2 << "\nOutputfilename is " << outfilename << endl;

    arrayListType<Student> arr = gatherinfo(infilename1);
    arr.print();
    //fstream ofs;
    ofstream ofs;
    ofs.open(outfilename);
    ofs.close();


    /*
    Date DOB("1990-4-29");
    Student Mark("123456", "Mark", "Gingoyon", "CS", stof("3.00"), DOB);

	Mark.print();
    */
    AVLtree<string> fnTree;
    AVLtree<string> lnTree;
    AVLtree<Date> dateTree;
    AVLtree<string> majorTree;
    AVLtree<float> gpaTree;
    //cout<<arr.listSize();
    for(int i=0;i<arr.listSize();i++){
        //AVLNode<int> node(arr[i],i);
        fnTree.insert(arr.getValue(i).getFName(),i);
        lnTree.insert(arr.getValue(i).getLName(),i);
        dateTree.insert(arr.getValue(i).getDOB(),i);
        //arr.getValue(i).getDOB().printDate();
        majorTree.insert(arr.getValue(i).getMajor(),i);
        gpaTree.insert(arr.getValue(i).getGPA(),i);

        //cout << "root is " << root->key;
        cout << " inorder: " ;
        fnTree.inorder();
        lnTree.inorder();
        dateTree.inorder();
        majorTree.inorder();
        gpaTree.inorder();
        cout << endl;
        cout << endl;





    }

return 0;
};

arrayListType<Student> gatherinfo(string inputfile){
    fstream infile;
    infile.open(inputfile,ios::in);

    string a;
    Student *temp;

    arrayListType<Student> arr(100);

    while(!infile.eof()){//loop readin info
        getline(infile,a);
        if(a == "\n"){break;}

        string id=""; string firstName =""; string lastName=""; string dob=""; string major="";
        float gpa=0;
        //read
         string delimiter = ",";
            size_t pos = 0;
            string token;
            a+=",";

                pos = a.find(delimiter);
                token = a.substr(0, pos);

                id = token;//gets year

                a.erase(0, pos + delimiter.length());

                pos = a.find(delimiter);
                token = a.substr(0, pos);

                firstName = token;//gets firstname

                a.erase(0, pos + delimiter.length());

                pos = a.find(delimiter);
                token = a.substr(0, pos);

                lastName = token;//gets lastname

                a.erase(0, pos + delimiter.length());

                pos = a.find(delimiter);
                token = a.substr(0, pos);

                dob = token;//gets dob

                a.erase(0, pos + delimiter.length());

                pos = a.find(delimiter);
                token = a.substr(0, pos);

                major = token;//gets major

                a.erase(0, pos + delimiter.length());

                pos = a.find(delimiter);
                token = a.substr(0, pos);

                gpa = stof(token);//gets gpa

                a.erase(0, pos + delimiter.length());

                Date obj(dob);
                temp = new Student(id,firstName,lastName,major,gpa,obj);

                //put into array
                arr.insertordered(*temp);
                //temp ->print();
    }

    infile.close();
    return arr;
}


