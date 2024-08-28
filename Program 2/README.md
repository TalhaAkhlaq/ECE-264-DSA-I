# Program 2

## Description

This C++ program processes commands from an input file to manage and log operations on stacks and queues of integers, doubles, and strings. It supports `create`, `push`, and `pop` commands, logging each action and any errors to a specified output file.

## Program Details

- **Create**: Initializes new stacks or queues for integers, doubles, or strings.
- **Push**: Adds elements to the top of a stack or the end of a queue.
- **Pop**: Removes and retrieves elements from the top of a stack or the front of a queue.
- **Error Handling**: Logs errors for invalid operations and data types.

## Instructions

1. **Input File**: Create a text file with commands in the following format:
- `<name>`: Identifier for the stack or queue.
- `<type>`: Either `stack` or `queue`.
- `<value>`: Value to push (for `push` command).

2. **Execution**: Run the program and provide the names of the input and output files when prompted.

3. **Output File**: The program will log all actions and errors to the specified output file.

## Command Format

- **Create**: `create <name> <type>`
  - `<name>`: A unique identifier for the stack or queue. Must start with 'i', 'd', or 's' followed by alphanumeric characters.
  - `<type>`: Either `stack` or `queue`.
  
- **Push**: `push <name> <value>`
  - `<name>`: Identifier of the stack or queue.
  - `<value>`: Value to be pushed. Should match the type of the stack or queue.

- **Pop**: `pop <name>`
  - `<name>`: Identifier of the stack or queue.
