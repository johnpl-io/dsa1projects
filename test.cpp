# include <iostream> 
#include <string>
#include <iostream>
#include <sstream> 
#include <fstream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int data) {
        this->data = data;
        next = nullptr;
    }
        Node(int data, Node *next) {
        this->data = data;
        this->next=next;
    }
};
void traverse(Node* head)
{
    if (head == NULL)
       return;
     
    // If head is not NULL, print current node
    // and recur for remaining list  
    cout << head->data << " ";
 
    traverse(head->next);
}
void parseinput() {
         cout << "what is your input file?" << "\n";
     string inputfile2;
     cin >> inputfile2;
     string line;
     ofstream output;
     int size = 0;
     output.open("test.txt");
    output << "hello" << "\n";

  ifstream inputfile (inputfile2);
 if (inputfile.is_open()) {
    
     while ( getline (inputfile, line)) {
         cout << line << "\n";
        
         size++;
     }
     inputfile.close();
 }
 output << size << endl;
   output.close();
}
int main() {
parseinput();
}
