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

    Node(T data): data{data}, next{nullptr} { }
};
//change to protected later
protected:
    void insertatEnd(T value) {
        if(getlength() == 0) {
            Node* newNode = new Node(value);
            theSize++;
            head = tail = newNode;

        } else {
            Node* newNode = new Node(value);
            tail->next = newNode;
            tail = newNode;
              theSize++;
        }


    }
    void insertatStart(T value) {
        if(getlength() == 0) {
            Node* newNode = new Node(value);
            theSize++;
            head = tail = newNode;
        }
        else {
            Node* newNode = new Node(value);
            newNode->next = head;
               theSize++;
            head = newNode;
        }
    }
    T removefromStart() {
        if(getlength() == 0) {
            return -1;
        }
        else {
       Node *temp = head;
       T tempval = head->data;
       head = head->next;
       delete (temp);
       theSize--;
       return tempval;
        }
       
    } 
public:
    SimpleList() : theSize{0}, head{nullptr}, tail{nullptr} { }

    int getlength() {
      return theSize;
    }
virtual T pop() = 0;
virtual void push(T value) = 0;
private:
    int theSize;
    Node *head;
    Node *tail;
};

template <typename T>
class Stack : public SimpleList<T> {
    public:
    using SimpleList<T>::SimpleList;
    void push(T value) { 
        this->insertatStart(value);
    }
    T pop() {
        return this->removefromStart();
    }

};

template <typename T>
class Queue : public SimpleList<T> {
    public: 
    using SimpleList<T>::SimpleList;
    void push(T value) { 
        this->insertatEnd(value);
    }
    T pop() {
        return this->removefromStart();
    }
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
Queue<int> test;
test.push(3);
test.push(4);
cout << test.pop() << endl;
}