#include <iostream>
#include <sstream> 
#include <fstream>
#include <unordered_map>
#include <map>
#include <chrono>
using namespace std;
//Abstract base class SimpleList
template <typename T> 
class SimpleList {
private:
//private member class Node 
class Node {
//public member variables are used in Node constructor
    public:
    T data;
    Node *next;

//member Inititlization List for Default constructor of Node
    Node(T data): data{data}, next{nullptr} { }
};
//initilization of protected member functions to only be used in derived classes of Stack and Queue
protected:
    void insertatEnd(T value);
    void insertatStart(T value);
    T removefromStart();
public:
//Member Initilization list for Default constructor of Simple List
    SimpleList() : theSize{0}, head{nullptr}, tail{nullptr} { }
inline int getlength() {
      return theSize;
    }

//virtual SimpleList destructor as it used to delete a derived stack and queues using a pointer of SimpleList
//destructor allows for freeing of all nodes once a SimpleList pointer is deleted
 virtual ~SimpleList() {
    Node* curr = head;
    Node* next;
    while(curr != nullptr) {
        next = curr->next;
        delete curr;
        curr = next;
    }
}
//pure virtual function that are used in derive classes of Stack and Queue
virtual T pop() = 0;
virtual void push(T value) = 0;
//private member variables
private:
    int theSize;
    Node *head;
    Node *tail;
};
//function decleration for insert an element at the end of a list
template <typename T>
void SimpleList<T>::insertatEnd(T value) {
//if the list has a length 0 the head and tail become the new node that is inserted
    if(getlength() == 0) {
        Node* newNode = new Node(value);
        theSize++;
        head = tail = newNode;
//otherwise the element is inserted next to the tail, becoming the new tail
   } else {
        Node* newNode = new Node(value);
        tail->next = newNode;
        tail = newNode;
              theSize++;
        }
    }
//function declaration for inserting elements at the start of the list
template <typename T>
   void SimpleList<T>::insertatStart(T value) {
    //same procedure as insert at end of the list has a size 0
        if(getlength() == 0) {
            Node* newNode = new Node(value);
            theSize++;
            head = tail = newNode;
        }
    //otherwise insert the node at the front of the list and make it the new head
        else {
            Node* newNode = new Node(value);
            newNode->next = head;
               theSize++;
            head = newNode;
        }
    }
//function declaration for removing an element from start of list
template <typename T>
  T SimpleList<T>::removefromStart() {
//if the length of the list is zero 0 is returned as this condition should not be possible
        if(getlength() == 0) {
            return 0;
        }
//a temp variable is used to store the data of the head so it can be returned after the temp pointer storing its contents are deleted
//the value next to the head becomes the new head
        else {
       Node *temp = head;
       T tempval = head->data;
       head = head->next;
       delete (temp);
       theSize--;
       return tempval;
        }
       
    } 

//Derived class stack 
template <typename T>
class Stack : public SimpleList<T> {
    public:
//This allows for SimpleList constructors to be inherited
    using SimpleList<T>::SimpleList;
//function declaration push allowing for insertatStart to be defined as push only for Stacks
    void push(T value) { 
        this->insertatStart(value);
    }
//function delcaration pop allowing for pop to remove from start
    T pop() {
        return this->removefromStart();
    }

};
//class definition for derived class Queue
template <typename T>
class Queue : public SimpleList<T> {
    public: 
    using SimpleList<T>::SimpleList;
//function declaration for push that is insertatEnd for Queue
    void push(T value) { 
        this->insertatEnd(value);
    }
//function decleration for pop for Queue which calls removefromStart
    T pop() {
        return this->removefromStart();
    }
};


//this function checks if a map exists by using the member function find for each map true is returned if a stack or queue name 
//exists inside of the map
bool check_exists(const string &name, map<string, SimpleList<int> *> &mapsLi,  map<string, SimpleList<double> *> &mapsLd, map<string, SimpleList<string> *> &mapsLs) {
//each map is only searched if it is in question based off of the data type
    if (name.at(0) == 'i')
     return (mapsLi.find(name)!=mapsLi.end());
      if (name.at(0) == 'd')
     return (mapsLd.find(name)!=mapsLd.end());
        if (name.at(0) == 's')
     return (mapsLs.find(name)!=mapsLs.end());
     //impossible condition so if reached error return of -1
    return -1;
}
//function that handles parsing the inputfile and creating the outputfile
void parseinput(const string &inputname, const string &outputname) {
//streams are used to handle parsing of the inputfile and write to the output file
    ifstream inputfile (inputname);
    ofstream outputfile;
    string line;
//maps that are used to store abstract SimpleList pointers for each data type
    map<string, SimpleList<int> *> mapsLi;
    map<string, SimpleList<double> *> mapsLd;
    map<string, SimpleList<string> *> mapsLs;
//each element of the arg array is an argument from a single line
    string arg[3];
//this char stores the data type of the Stack or Queue that is being manipulated from the input file
    char dtype;
    int count; 
    outputfile.open(outputname);
 if (inputfile.is_open()) {
  //while loop goes through each line of the file  
     while ( getline (inputfile, line)) {
         outputfile << "PROCESSING COMMAND: " << line << "\n";
         stringstream s(line);
         count = 0;
//string stream is used to break up each line into its arguments and place into the arg string array 
         while (s >> line) {
             arg[count] = line;
             count++;
         }
//since pop is only followed by the name arg[2] is cleared from the previous line
         if (arg[0] == "pop") {
             arg[2] = "";
         }
//the data type of each stack or queue is stored
            dtype = arg[1].at(0);
//creates a new Stack or Queue only if it does not exist and based off its data type
//the name of each Stack or Queue (including its data type) is stored as string value of the map
            if(arg[0] == "create") {
                if( check_exists(arg[1],mapsLi,mapsLd,mapsLs) ) {
                  outputfile << "ERROR: This name already exists!" << "\n";
              }
              else {
                if(arg[2] == "stack") {
                   if(dtype == 'i') 
                         mapsLi.insert(pair<string, SimpleList<int> *>(arg[1], new Stack<int>()));
                   
                   if(dtype == 'd') 
                      mapsLd.insert(pair<string, SimpleList<double> *>(arg[1], new Stack<double>())); 
                    
                    if (dtype == 's')
                     mapsLs.insert(pair<string, SimpleList<string> *>(arg[1], new Stack<string>()));
                }

                 if(arg[2] == "queue") {
                   if(dtype == 'i') 
                         mapsLi.insert(pair<string, SimpleList<int> *>(arg[1], new Queue<int>()));
                   
                   if(dtype == 'd') 
                      mapsLd.insert(pair<string, SimpleList<double> *>(arg[1], new Queue<double>())); 
                    
                    if (dtype == 's')
                     mapsLs.insert(pair<string, SimpleList<string> *>(arg[1], new Queue<string>()));
                }
                        
              }
                  }
//pop will only occur if the list exists, and is not empty
        if(arg[0] == "pop") {
        if(!check_exists(arg[1],mapsLi,mapsLd,mapsLs)) {
            outputfile << "ERROR: This name does not exist!" << "\n";
                }
        else {
            if(dtype == 'i') {
                if(mapsLi[arg[1]]->getlength() == 0) {
                outputfile << "ERROR: This list is empty!" << "\n";
                }
                else {
                 outputfile << "Value popped: " << mapsLi[arg[1]]->pop() << "\n";
                }
            }
              if(dtype == 'd') {
                if(mapsLd[arg[1]]->getlength() == 0) {
                outputfile << "ERROR: This list is empty!" << "\n";
                }
                else {
                 outputfile << "Value popped: " << mapsLd[arg[1]]->pop() << "\n";
                }
            }
                 if(dtype == 's') {
                if(mapsLs[arg[1]]->getlength() == 0) {
                outputfile << "ERROR: This list is empty!" << "\n";
                }
                else {
                 outputfile << "Value popped: " << mapsLs[arg[1]]->pop() << "\n";
                }
            }

        }
            
        }
//push will only occur if the data type exists 
//each element being pushed must be converted to its proper data type, based off of the first letter of the list
          if(arg[0] == "push") {
                if(!check_exists(arg[1],mapsLi,mapsLd,mapsLs)) {
                    outputfile << "ERROR: This name does not exist!" << "\n";
                }
                else {
                    if (dtype == 'i') 
                    mapsLi[arg[1]]-> push(stoi(arg[2]));
                    if (dtype == 'd') 
                    mapsLd[arg[1]]-> push(stod(arg[2]));
                    if (dtype == 's') 
                    mapsLs[arg[1]]-> push(arg[2]);


                    
                }
           

            }        
            
     }
     inputfile.close();
 }
 outputfile.close();
 //to prevent memory leaks all pointers created with new are deleted from all the maps
 for (auto i : mapsLi) {
     delete (i.second);
 }
  for (auto i : mapsLd) {
     delete (i.second);
 }
   for (auto i : mapsLs) {
     delete (i.second);
 }
}
int main()
{
//the input file and output file are collected as string and passed to parseinput 
string inputname;
string outputname;
cout << "input file: ";
cin >> inputname;
cout << "output file: ";
cin >> outputname;
parseinput(inputname, outputname);
}