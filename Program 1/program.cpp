/* Name: Talha Akhlaq
Description: This program reads a sequence of foobars (mysterious creatures) from an input file,
assigns them a position based on their order, calculates their strength based on their position,
and outputs each foobar's name and calculated strength to an output file. */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Represents an "ordinary foobar" with basic attributes and behaviors.
class Foobar
{
private:
  string name;  // Name of the foobar
  int position; // Position in the line, affects strength calculation

protected:
  // Allows derived classes to access the foobar's position for strength calculation
  int getPosition() const { return position; }

public:
  // Constructor initializes name and position (default position is 0)
  Foobar(const string &name, int position = 0) : name(name), position(position) {}

  void setPosition(int pos) { position = pos; }        // Set the foobar's position
  virtual int getStrength() const { return position; } // Default strength calculation
  string getName() const { return name; }              // Returns the foobar's name
};

// Represents a Foo, a specialized type of foobar with a unique strength calculation.
class Foo : public Foobar
{
public:
  // Constructor initializes a foo with a name and position.
  Foo(const string &name, int position = 0) : Foobar(name, position) {}
  int getStrength() const override { return getPosition() * 3; } // Strength calculation for a foo: position * 3.
};

// Represents a Bar, another specialized type of foobar with its own strength calculation
class Bar : public Foobar
{
public:
  Bar(const string &name, int position = 0) : Foobar(name, position) {}
  int getStrength() const override { return getPosition() + 15; } // Strength calculation for a bar: position + 15
};

// Function to read input file and populates the vector of Foobar pointers
void readInputFile(const string &filename, vector<Foobar *> &foobars)
{
  ifstream inFile(filename);
  // Check if input file successfully opened
  if (!inFile)
  {
    cerr << "Error opening input file: " << filename << endl;
    exit(1);
  }
  string line, type, name;

  while (getline(inFile, line))
  {
    stringstream ss(line);
    ss >> type >> name;
    // Checking for foobar type and adding error handling for unknown types
    if (type == "foo")
    {
      foobars.push_back(new Foo(name));
    }
    else if (type == "bar")
    {
      foobars.push_back(new Bar(name));
    }
    else if (type == "foobar")
    {
      foobars.push_back(new Foobar(name));
    }
    else
    {
      cerr << "Unknown foobar type: " << type << endl;
      exit(1);
    }
  }
}

// Function to update positions of foobars in the line
void updatePositions(vector<Foobar *> &foobars)
{
  int position = 1; // Start from the front of the line
  for (auto it = foobars.rbegin(); it != foobars.rend(); ++it, ++position)
  {
    (*it)->setPosition(position);
  }
}

// Function to write output file with the name and strength of each foobar
void writeOutputFile(const string &filename, const vector<Foobar *> &foobars)
{
  ofstream outFile(filename);
  if (!outFile)
  {
    cerr << "Error opening output file: " << filename << endl;
    exit(1);
  }
  for (auto foobar : foobars)
  {
    outFile << foobar->getName() << " " << foobar->getStrength() << endl;
  }
}

int main()
{
  cout << "Enter the name of the input file: ";
  string inputFileName;
  cin >> inputFileName;

  cout << "Enter the name of the output file: ";
  string outputFileName;
  cin >> outputFileName;

  vector<Foobar *> foobars;                 // Store dynamically created foobars
  readInputFile(inputFileName, foobars);    // Read and populate foobars from input file
  updatePositions(foobars);                 // Assign positions based on input order
  writeOutputFile(outputFileName, foobars); // Write foobars' names and strengths to the output file

  // Clean up dynamically allocated foobars to prevent memory leaks
  for (auto &foobar : foobars)
  {
    delete foobar;
  }

  cout << "The proccess has completed.\n";
  return 0;
}
