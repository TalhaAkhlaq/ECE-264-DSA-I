# Program 3

## Description

This program sorts nodes in a linked list where each node contains a data object with a last name, first name, and social security number (SSN). It reads data from an input file, creates a linked list, sorts the list by last name, first name, and SSN, and writes the sorted list to an output file.

## Program Details

- **Input File**: The file should contain a number indicating the number of data objects followed by rows of data objects, each with a last name, first name, and SSN.
- **Output File**: The file will contain the sorted data in the same format as the input file.
- **Sorting Criteria**: 
  1. Last name
  2. First name (if last names are identical)
  3. SSN (if both last and first names are identical)

## Usage

1. Compile the program using `g++ program_name.cpp -o program_name`.
2. Run the program with `./program_name input_file output_file`.
3. Ensure `input_file` follows the specified format, and `output_file` will be created with the sorted data.

## Code Structure

- **Data Class**: Defines the structure of the data object containing last name, first name, and SSN.
- **File Operations**: Functions `loadDataList` and `writeDataList` handle loading data from the input file and saving sorted data to the output file.
- **Sorting Function**: `sortDataList` determines the appropriate sorting algorithm based on data characteristics and dataset size. It uses:
  - **Optimized Quicksort**: For large datasets (T1 and T2) leveraging indirect sorting with a global array.
  - **Insertion Sort**: For nearly sorted data (T3).
  - **Radix Sort**: For datasets with identical names (T4) using integer SSN keys.
- **Main Function**: Manages program execution, including reading input, invoking sorting, and writing output. It also times the sorting process.


