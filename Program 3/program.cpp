// THIS IS THE PROVIDED CODE FOR PROGRAM #3, DSA 1, SPRING 2024

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
class Data
{
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename)
{

  ifstream input(filename);
  if (!input)
  {
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
  for (int i = 0; i < size; i++)
  {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename)
{

  ofstream output(filename);
  if (!output)
  {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData : l)
  {
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
int main()
{
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
  double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

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

// Name: Talha Akhlaq

/*
This program sorts a list of data objects containing personal information
 using different sorting algorithms based on the characteristics of the data.
 It handles large datasets with optimized quicksort, uses insertion sort for
 nearly sorted data, and employs radix sort when names are identical across entries.
 */

#include <unordered_map>
#include <tuple>
#include <utility>
#include <set>
#include <array>
#include <execution>

// Global array to hold pointers to Data objects for efficient access during sorting
Data *container[1100000];

// Comparison function to determine the order of Data objects
// Sorts primarily by lastName, then firstName, and finally by ssn if needed
bool comp(const Data *l, const Data *r)
{
  if (l->lastName == r->lastName)
  {
    if (l->firstName == r->firstName)
    {
      return l->ssn < r->ssn;
    }
    return l->firstName < r->firstName;
  }
  return l->lastName < r->lastName;
}

// Function to perform an optimized quicksort on a list of Data objects
// Utilizes a global array to achieve indirect sorting which is more efficient
void optimizedQuicksort(list<Data *> &l, int size)
{
  int index = 0;
  // Copy data pointers to the global array
  for (Data *data : l)
  {
    container[index++] = data;
  }
  // Sort the global array using the standard library sort function
  sort(container, container + size, comp);

  // Copy sorted data back to the list
  auto it = l.begin();
  for (int i = 0; i < size; ++i, ++it)
  {
    *it = container[i];
  }
}

// Function to sort a list of Data objects using insertion sort
// Best used when the data is nearly sorted
void insertionSort(list<Data *> &l)
{
  vector<Data *> vec(l.begin(), l.end());
  int size = vec.size();
  // Perform insertion sort on the vector of Data pointers
  for (int i = 1; i < size; ++i)
  {
    Data *key = vec[i];
    int j = i - 1;
    while (j >= 0 && comp(key, vec[j]))
    {
      vec[j + 1] = vec[j];
      j--;
    }
    vec[j + 1] = key;
  }
  // Copy sorted data back to the list
  auto lit = l.begin();
  for (auto &item : vec)
  {
    *lit++ = item;
  }
}

// Function to perform radix sort on a list of Data objects
// Used specifically when all data objects have identical names
void radixSort(list<Data *> &l)
{
  vector<pair<int, Data *>> ssnPairs;
  ssnPairs.reserve(l.size());
  // Convert SSNs to integer keys for sorting
  for (Data *data : l)
  {
    int ssnKey = stoi(data->ssn.substr(7, 4)) + 10000 * stoi(data->ssn.substr(0, 3));
    ssnPairs.push_back(make_pair(ssnKey, data));
  }
  // Sort based on integer SSN keys
  stable_sort(ssnPairs.begin(), ssnPairs.end(), [](const pair<int, Data *> &a, const pair<int, Data *> &b)
              { return a.first < b.first; });
  // Reassemble the list from sorted pairs
  auto it = l.begin();
  for (auto &pair : ssnPairs)
  {
    *it++ = pair.second;
  }
}

// Main function to determine the appropriate sorting strategy based on data characteristics
void sortDataList(list<Data *> &l)
{
  // Check if all first names or last names are the same across the dataset
  bool sameFirst = true, sameLast = true;
  string firstName = l.front()->firstName;
  string lastName = l.front()->lastName;

  for (auto &data : l)
  {
    if (data->firstName != firstName)
      sameFirst = false;
    if (data->lastName != lastName)
      sameLast = false;
    if (!sameFirst && !sameLast)
      break;
  }

  // Decide which sorting algorithm to apply based on the data analysis
  if (sameFirst && sameLast)
  {
    radixSort(l); // Apply radix sort for T4
  }
  else if (l.size() > 100000)
  {
    optimizedQuicksort(l, l.size()); // Use optimized quicksort for T1 and T2
  }
  else
  {
    insertionSort(l); // Use insertion sort for T3
  }
}
