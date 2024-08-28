# Program 2

## Description

This C++ program implements a stack and queue manipulation system. It processes commands from an input file to create stacks and queues, push values onto them, and pop values from them. Commands and their results are logged to an output file.

## Program Details

 **Create**: Create a stack or queue with a specific name and data type.
- **Push**: Push a value onto a specified stack or queue.
- **Pop**: Pop a value from a specified stack or queue.
- **Error Handling**: Outputs appropriate error messages for invalid operations.

## Instructions

1. **Input File**: Provide a text file containing commands. Commands must be in the format specified below.
2. **Output File**: Provide a name for the output file where results and errors will be logged.

### Command Format

- **Create**: `create <name> <type>`
  - `<name>`: A unique identifier for the stack or queue. Must start with 'i', 'd', or 's' followed by alphanumeric characters.
  - `<type>`: Either `stack` or `queue`.
  
- **Push**: `push <name> <value>`
  - `<name>`: Identifier of the stack or queue.
  - `<value>`: Value to be pushed. Should match the type of the stack or queue.

- **Pop**: `pop <name>`
  - `<name>`: Identifier of the stack or queue.
