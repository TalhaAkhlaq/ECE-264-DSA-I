# Program 1

## Description

This C++ program reads a sequence of mysterious creatures called foobars from an input file, assigns them a position in a line, calculates their strength based on their type and position, and outputs the names and strengths of the foobars to an output file.

## Program Details

- **Foobar**: The base class with basic attributes and default strength calculation.
- **Foo**: A derived class where strength is calculated as position × 3.
- **Bar**: A derived class where strength is calculated as position + 15.

The input file must contain lines with the type and name of each foobar. The program will process the file in a single pass, calculate strengths based on positions, and write results to the output file.

## Usage

1. **Compile**: Compile the program using a C++ compiler.
2. **Run**: Execute the program.
3. **Input File**: Enter the name of the text file containing foobars.
4. **Output File**: Enter the name of the file where results will be saved.

## Code Structure

- `Foobar` (Base Class): Handles basic attributes and strength calculation.
- `Foo` (Derived Class): Calculates strength as position × 3.
- `Bar` (Derived Class): Calculates strength as position + 15.
- `readInputFile()`: Reads the input file and populates the `vector<Foobar *>`.
- `updatePositions()`: Updates the position of each foobar in the vector.
- `writeOutputFile()`: Writes the names and strengths of foobars to the output file.
