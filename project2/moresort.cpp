// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
	   << pData->firstName << " " 
	   << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
Data * result[1'001'000];
inline bool comparedata(const Data* a, const Data* b) {
  if(a->lastName != b->lastName) 
    return a->lastName < b->lastName;
  if(a -> firstName != b->firstName) {
    return a->firstName < b->firstName;
  }
  return a->ssn < b->ssn;

  }

inline bool comparesus(const Data* a, const Data* b) {
  if (a->lastName < b->lastName) 
  return true;
  if (a->lastName == b->lastName) {
  if (a->firstName < b->firstName)
  return true;
  if(a->firstName == b->firstName && a->ssn < b->ssn)
  return true;
  }
 return false;
}
 
inline bool comparedata3(const Data* a, const Data* b) {
    if (a->lastName > b->lastName)
        return false;
    if (a->lastName < b->lastName)
        return true;
    if (a->firstName > b->firstName)
        return false;
    if (a->firstName < b->firstName)
        return true;
  return a->ssn < b->ssn;

  }
  inline bool comparedata4(const Data* a, const Data* b) {
  return a->ssn < b->ssn;

  }
inline bool comparedata2(const Data* a, const Data* b) {
 if (a->lastName > b-> lastName || a->firstName > b->firstName)
 return false;
  if (a->lastName < b-> lastName || a->firstName < b->firstName)
 return true;
 return a->ssn < b->ssn;

  }
void sortDataList(list<Data *> &l) {
  int k = 0;
 
for (auto const &c : l) {
   result[k] = c;
   k++;
}

sort(result, result + l.size(), comparedata3);
k =0;
for (auto &c : l) {
  c = result[k];
   k++;
}
/*int i = 0;
int j = 0;
int z = 0;
Data* tmp [100];
string keylast = "";
string keyfirst = "";
while(i < l.size()) {
  keylast = result[i]->lastName;
   keyfirst = result[i]->firstName;
   j = i;
   while(result[j]->firstName==keyfirst && result[j]->lastName==keylast ) {
     z = 0;
      tmp[z] = result[j];
      j++;
      z++;
   }
   cout << tmp[0]->lastName + " " + tmp[0]->firstName << endl;
i++;
}
  */

}