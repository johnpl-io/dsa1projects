// CPP program to find infix for
// a given postfix.
#include <iostream>
#include <sstream> 
#include <fstream>

using namespace std;

template <typename T> 
class SimpleList {
private:
class Node {
    public:
    T data;
    Node *next;
    Node(T data) {
        this->data = data;
        next = nullptr;
    }
    Node(T data, Node *next) {
        this->data = data;
        this->next = next;
    }
};
//change to protected later
public:
    void insertatEnd(T value) {
        if(isEmpty()) {
            Node* newNode = new Node(value);
            theSize++;
            head = tail = newNode;

        } else {
            Node* newNode = new Node(value);
            tail->next = newNode;
            tail = newNode;
        }


    }
    void insertatStart(T value);
    T removefromStart() ;
public:
    SimpleList() {
        theSize = 0;
        head = nullptr;
        tail = nullptr;
    }
    bool isEmpty() {
      return theSize == 0;
    }
    //virtual T pop() = 0;
    //virtual void push(T value) = 0;
    //change to private later
public:
    int theSize;
    Node *head;
    Node *tail;
};

void parseinput() {
         cout << "what is your input file?" << "\n";
     string inputfile2;
     cin >> inputfile2;
     string line;
  ifstream inputfile (inputfile2);
 if (inputfile.is_open()) {
    
     while ( getline (inputfile, line)) {
         cout << line << "\n";
     }
     inputfile.close();
 }
}


// Driver code
int main()
{
SimpleList<string> test;
test.insertatEnd("test");
test.insertatEnd("test2");
cout  << (test.head)->data << endl;
}