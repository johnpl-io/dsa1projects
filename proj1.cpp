// CPP program to find infix for
// a given postfix.
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
    T pop() {
        return this->removefromStart();
    }
};



bool check_exists(string name, map<string, SimpleList<int> *> mapsSLi,  map<string, SimpleList<double> *> mapsSLd, map<string, SimpleList<string> *> mapsSLs) {
    return (mapsSLi.find(name)!=mapsSLi.end() || mapsSLd.find(name)!=mapsSLd.end() || mapsSLs.find(name)!=mapsSLs.end());
}
 
void parseinput(const string &inputname, const string &outputname) {
    auto start = chrono::high_resolution_clock::now();
    ifstream inputfile (inputname);
    ofstream outputfile;
    string line;
    map<string, SimpleList<int> *> mapsSLi;
    map<string, SimpleList<double> *> mapsSLd;
    map<string, SimpleList<string> *> mapsSLs;
    string arg[3];
    char dtype;
    int count; 

    outputfile.open(outputname);
 if (inputfile.is_open()) {
    
     while ( getline (inputfile, line)) {
         outputfile << "PROCESSING COMMAND: " << line << "\n";
         stringstream s(line);
         count = 0;
         while (s >> line) {
             arg[count] = line;
             count++;
         }
         if (arg[0] == "pop") {
             arg[2] = "";
         }
            dtype = arg[1].at(0);
            if(arg[0] == "create") {
                if( check_exists(arg[1],mapsSLi,mapsSLd,mapsSLs) ) {
                  outputfile << "ERROR: This name already exists!" << "\n";
              }
              else {
                if(arg[2] == "stack") {
                   if(dtype == 'i') 
                         mapsSLi.insert(pair<string, SimpleList<int> *>(arg[1], new Stack<int>()));
                   
                   if(dtype == 'd') 
                      mapsSLd.insert(pair<string, SimpleList<double> *>(arg[1], new Stack<double>())); 
                    
                    if (dtype == 's')
                     mapsSLs.insert(pair<string, SimpleList<string> *>(arg[1], new Stack<string>()));
                }

                 if(arg[2] == "queue") {
                   if(dtype == 'i') 
                         mapsSLi.insert(pair<string, SimpleList<int> *>(arg[1], new Queue<int>()));
                   
                   if(dtype == 'd') 
                      mapsSLd.insert(pair<string, SimpleList<double> *>(arg[1], new Queue<double>())); 
                    
                    if (dtype == 's')
                     mapsSLs.insert(pair<string, SimpleList<string> *>(arg[1], new Queue<string>()));
                }
                        
              }
                  }
  
        if(arg[0] == "pop") {
        if(!check_exists(arg[1],mapsSLi,mapsSLd,mapsSLs)) {
            outputfile << "ERROR: This name does not exist!" << "\n";
                }
        else {
            if(dtype == 'i') {
                if(mapsSLi[arg[1]]->getlength() == 0) {
                outputfile << "ERROR: This list is empty!" << "\n";
                }
                else {
                 outputfile << "Value popped: " << mapsSLi[arg[1]]->pop() << "\n";
                }
            }
              if(dtype == 'd') {
                if(mapsSLd[arg[1]]->getlength() == 0) {
                outputfile << "ERROR: This list is empty!" << "\n";
                }
                else {
                 outputfile << "Value popped: " << mapsSLd[arg[1]]->pop() << "\n";
                }
            }
                 if(dtype == 's') {
                if(mapsSLs[arg[1]]->getlength() == 0) {
                outputfile << "ERROR: This list is empty!" << "\n";
                }
                else {
                 outputfile << "Value popped: " << mapsSLs[arg[1]]->pop() << "\n";
                }
            }

        }
            
        }
          if(arg[0] == "push") {
                if(!check_exists(arg[1],mapsSLi,mapsSLd,mapsSLs)) {
                    outputfile << "ERROR: This name does not exist!" << "\n";
                }
                else {
                    if (dtype == 'i') 
                    mapsSLi[arg[1]]-> push(stoi(arg[2]));
                    if (dtype == 'd') 
                    mapsSLd[arg[1]]-> push(stod(arg[2]));
                    if (dtype == 's') 
                    mapsSLs[arg[1]]-> push(arg[2]);


                    
                }
           

            }        
            
     }
     inputfile.close();
 }
 outputfile.close();
 for (auto i : mapsSLi) {
     delete i.second;
 }
  for (auto i : mapsSLd) {
     delete i.second;
 }
   for (auto i : mapsSLs) {
     delete i.second;
 }
 auto stop = chrono::high_resolution_clock::now();
 auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
cout << duration.count() << endl;
}


// Driver code
int main()
{
string inputname;
string outputname;
cout << "input" << "\n";
cin >> inputname;
cout << "output" << "\n";
cin >> outputname;
parseinput(inputname, outputname);


}