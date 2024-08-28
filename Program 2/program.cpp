/*
Name: Talha Akhlaq
Description:
This program processes commands from an input file to manage and log operations on stacks and queues of integers, doubles,
and strings, executing create, push, and pop commands, and recording each action and any errors in a specified output file.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdexcept>

using namespace std;

// Declaration of SimpleList class for reference
template <typename T>
class SimpleList;

// Node class for SimpleList
template <typename T>
class Node
{
public:
  T data;        // Data stored in the node
  Node<T> *next; // Pointer to the next node
  Node(T value);
};

// Constructor definition for Node class
template <typename T>
Node<T>::Node(T value) : data(value), next(nullptr) {}

// SimpleList abstract base class
template <typename T>
class SimpleList
{
protected:
  Node<T> *head; // Pointer to the first node in the list
  Node<T> *tail; // Pointer to the last node in the list
  string name;   // Name of the list

public:
  // Constructor: Initializes head and tail pointers to nullptr, and sets the name of the list
  SimpleList(string listName);

  // Destructor: Deletes all nodes in the list to prevent memory leaks
  virtual ~SimpleList();

  // Getter method for retrieving the name of the list
  string getName() const;

  // Abstract method to push a new value onto the list
  virtual void push(T value) = 0;

  // Abstract method to pop and retrieve the last value from the list
  virtual T pop() = 0;

  // Method to check if the list is empty
  bool isEmpty() const;
};

// Constructor definition for SimpleList class
template <typename T>
SimpleList<T>::SimpleList(string listName) : head(nullptr), tail(nullptr), name(listName) {}

// Destructor definition for SimpleList class
template <typename T>
SimpleList<T>::~SimpleList()
{
  while (head != nullptr)
  {
    Node<T> *temp = head;
    head = head->next;
    delete temp;
  }
}

// Getter method definition for SimpleList class
template <typename T>
string SimpleList<T>::getName() const
{
  return name;
}

// Method definition to check if the list is empty for SimpleList class
template <typename T>
bool SimpleList<T>::isEmpty() const
{
  return head == nullptr;
}

// Stack derived from SimpleList
template <typename T>
class Stack : public SimpleList<T>
{
public:
  Stack(string listName) : SimpleList<T>(listName) {} // Constructor: Initializes the stack with the given name using the base class constructor
  void push(T value) override;                        // Push method: Adds a new node containing the given value to the top of the stack
  T pop() override;                                   // Pop method: Removes and returns the value from the top of the stack
};

// Push method definition for Stack class
template <typename T>
void Stack<T>::push(T value)
{
  Node<T> *newNode = new Node<T>(value);
  if (this->head == nullptr)
  {
    this->head = this->tail = newNode; // If the stack is empty, set both head and tail to the new node
  }
  else
  {
    newNode->next = this->head; // If the stack is not empty, add the new node to the top of the stack
    this->head = newNode;
  }
}

// Pop method definition for Stack class
template <typename T>
T Stack<T>::pop()
{
  if (this->head == nullptr)
  {
    throw logic_error("\nERROR: This list is empty!"); // If the stack is empty, throw a logic_error
  }
  Node<T> *temp = this->head;
  T value = temp->data;
  this->head = this->head->next;
  delete temp;
  if (this->head == nullptr)
  {
    this->tail = nullptr; // If the stack becomes empty after popping, update the tail pointer to nullptr
  }
  return value;
}

// Queue class derived from SimpleList
template <typename T>
class Queue : public SimpleList<T>
{
public:
  Queue(string listName) : SimpleList<T>(listName) {} // Constructor: Initializes the queue with the given name using the base class constructor
  void push(T value) override;                        // Push method: Adds a new node containing the given value to the end of the queue
  T pop() override;                                   // Pop method: Removes and returns the value from the front of the queue
};

// Push method definition for Queue class
template <typename T>
void Queue<T>::push(T value)
{
  Node<T> *newNode = new Node<T>(value);
  if (this->head == nullptr)
  {
    this->head = this->tail = newNode; // If the queue is empty, set both head and tail to the new node
  }
  else
  {
    this->tail->next = newNode; // If the queue is not empty, add the new node to the end of the queue
    this->tail = newNode;
  }
}

// Pop method definition for Queue class
template <typename T>
T Queue<T>::pop()
{
  if (this->head == nullptr)
  {
    throw logic_error("\nERROR: This list is empty!"); // If the queue is empty, throw a logic_error
  }
  Node<T> *temp = this->head;
  T value = temp->data;
  this->head = this->head->next;
  delete temp;
  if (this->head == nullptr)
  {
    this->tail = nullptr; // If the queue becomes empty after popping, update the tail pointer to nullptr
  }
  return value;
}

// Function to find SimpleList by name
template <typename T>
SimpleList<T> *findList(const string &name, list<SimpleList<T> *> &lists)
{
  for (SimpleList<T> *list : lists) // Iterate through the list of SimpleLists
  {
    if (list->getName() == name) // Check if the name of the current list matches the provided name
    {
      return list; // Return a pointer to the found list
    }
  }
  return nullptr;
}

// Main function to execute the program
int main()
{
  string inputFileName, outputFileName;
  cout << "Enter name of input file: ";
  cin >> inputFileName;
  cout << "Enter name of output file: ";
  cin >> outputFileName;

  ifstream inputFile(inputFileName);   // Open input file stream
  ofstream outputFile(outputFileName); // Open output file stream

  list<SimpleList<int> *> intLists;
  list<SimpleList<double> *> doubleLists;
  list<SimpleList<string> *> stringLists;

  string command, name, type, value; // Variables to store input command and parameters

  // Loop to process commands from input file
  while (inputFile >> command)
  {
    if (command == "create")
    {
      inputFile >> name >> type;
      outputFile << "PROCESSING COMMAND: " << command + " " + name + " " + type;
      if (type == "stack")
      {
        if (findList(name, intLists) || findList(name, doubleLists) || findList(name, stringLists))
        {
          outputFile << "\nERROR: This name already exists!\n";
        }
        else
        {
          if (name[0] == 'i')
          {
            intLists.push_front(new Stack<int>(name));
          }
          else if (name[0] == 'd')
          {
            doubleLists.push_front(new Stack<double>(name));
          }
          else if (name[0] == 's')
          {
            stringLists.push_front(new Stack<string>(name));
          }
          outputFile << endl;
        }
      }
      else if (type == "queue")
      {
        if (findList(name, intLists) || findList(name, doubleLists) || findList(name, stringLists))
        {
          outputFile << "\nERROR: This name already exists!\n";
        }
        else
        {
          if (name[0] == 'i')
          {
            intLists.push_front(new Queue<int>(name));
          }
          else if (name[0] == 'd')
          {
            doubleLists.push_front(new Queue<double>(name));
          }
          else if (name[0] == 's')
          {
            stringLists.push_front(new Queue<string>(name));
          }
          outputFile << endl;
        }
      }
    }
    else if (command == "push")
    {
      inputFile >> name >> value; // Read name and value from input
      outputFile << "PROCESSING COMMAND: " << command + " " + name + " " + value << endl;
      if (name[0] == 'i')
      {
        SimpleList<int> *list = findList(name, intLists);
        if (list)
        {
          try
          {
            list->push(stoi(value));
          }
          catch (const invalid_argument &e)
          {
            outputFile << "ERROR: Invalid value for type int!\n";
          }
        }
        else
        {
          outputFile << "ERROR: This name does not exist!\n";
        }
      }
      else if (name[0] == 'd')
      {
        SimpleList<double> *list = findList(name, doubleLists);
        if (list)
        {
          try
          {
            list->push(stod(value));
          }
          catch (const invalid_argument &e)
          {
            outputFile << "ERROR: Invalid value for type double!\n";
          }
        }
        else
        {
          outputFile << "ERROR: This name does not exist!\n";
        }
      }
      else if (name[0] == 's')
      {
        SimpleList<string> *list = findList(name, stringLists);
        if (list)
        {
          list->push(value);
        }
        else
        {
          outputFile << "ERROR: This name does not exist!\n";
        }
      }
    }
    else if (command == "pop")
    {
      inputFile >> name;
      outputFile << "PROCESSING COMMAND: " << command + " " + name;
      if (name[0] == 'i')
      {
        SimpleList<int> *list = findList(name, intLists);
        if (list)
        {
          try
          {
            int poppedValue = list->pop();
            outputFile << "\nValue popped: " << poppedValue << endl;
          }
          catch (const logic_error &e)
          {
            outputFile << e.what() << endl;
          }
        }
        else
        {
          outputFile << "\nERROR: This name does not exist!\n";
        }
      }
      else if (name[0] == 'd')
      {
        SimpleList<double> *list = findList(name, doubleLists);
        if (list)
        {
          try
          {
            double poppedValue = list->pop();
            outputFile << "\nValue popped: " << poppedValue << endl;
          }
          catch (const logic_error &e)
          {
            outputFile << e.what() << endl;
          }
        }
        else
        {
          outputFile << "\nERROR: This name does not exist!\n";
        }
      }
      else if (name[0] == 's')
      {
        SimpleList<string> *list = findList(name, stringLists);
        if (list)
        {
          try
          {
            string poppedValue = list->pop();
            outputFile << "\nValue popped: " << poppedValue << endl;
          }
          catch (const logic_error &e)
          {
            outputFile << e.what() << endl;
          }
        }
        else
        {
          outputFile << "\nERROR: This name does not exist!\n";
        }
      }
    }
  }

  // Cleanup: delete dynamically allocated lists
  for (SimpleList<int> *list : intLists)
  {
    delete list;
  }
  for (SimpleList<double> *list : doubleLists) // Delete double lists
  {
    delete list;
  }
  for (SimpleList<string> *list : stringLists) // Delete string lists
  {
    delete list;
  }

  inputFile.close();  // Close input file stream
  outputFile.close(); // Close output file stream

  return 0;
}
