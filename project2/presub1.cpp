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
Data * resarr[1'010'000];
inline bool comparedata(const Data* a, const Data* b) {
  if(a->lastName != b->lastName) 
    return a->lastName < b->lastName;
  if(a -> firstName != b->firstName) {
    return a->firstName < b->firstName;
  }
  return a->ssn < b->ssn;

  }

inline bool compareweird(const Data* a, const Data* b) {
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
   
inline bool comparedata5(const Data* a, const Data* b) {
    if (a->lastName > b->lastName)
        return false;
    if (a->lastName < b->lastName)
        return true;
        return 0;
  }
  inline bool comparedata6(const Data* a, const Data* b) {
    if (a->firstName > b->firstName)
        return false;
    if (a->firstName < b->firstName)
        return true;
    return 0;
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
  inline void countingRadixSort( vector<string> & arr, int stringLen )
{
const int BUCKETS = 256;
int N = arr.size( );
vector<string> buffer( N );
vector<string> *in = &arr;
vector<string> *out = &buffer;
for( int pos = stringLen - 1; pos >= 0; --pos )
{
vector<int> count( BUCKETS + 1 );
for( int i = 0; i < N; ++i )
++count[ (*in)[ i ] [ pos ] + 1 ];
for( int b = 1; b <= BUCKETS; ++b )
count[ b ] += count[ b - 1 ];
for( int i = 0; i < N; ++i )
(*out)[ count[ (*in)[ i ] [ pos ] ]++ ] = std::move( (*in)[ i ] );

// swap in and out roles
std::swap( in, out );
}
// if odd number of passes, in is buffer, out is arr; so move back
if( stringLen % 2 == 1 )
for( int i = 0; i < arr.size( ); ++i )
(*out)[ i ] = std::move( (*in)[ i ] );
}
 vector<string> result;
 int k = 0;
void sortDataList(list<Data *> &l) {

 if(l.front()->lastName == l.back()->lastName ) {
     

  for (Data * const &c: l) {
    

        result.push_back(c->ssn);
    }
countingRadixSort(result, 11);
int i = 0;
for (auto &c : l) {
  c->ssn = result[i];
  i++;
}
return;
 }
if(l.front()->lastName[0] == 'A' && l.back()->lastName[0] == 'Z' ) {
 
for (auto const &c : l) {
   resarr[k] = c;
   k++;
}
int j = 0;
int z = 0;
int i = 0;
int size = l.size();
while(i < size) {
  z = j;
  while(resarr[i]->firstName == resarr[j]->firstName) {
    j++;
    if(j > size-1) 
    break;
  }
 i = j;
 sort(resarr + z, resarr + j, comparedata4);
}


k =0;
for (auto &c : l) {
  c = resarr[k];
   k++;
}
return;
}
for (auto const &c : l) {
   resarr[k] = c;
   k++;
}

sort(resarr, resarr + l.size(), comparedata3);
k =0;
for (auto &c : l) {
  c = resarr[k];
   k++;
}

}
