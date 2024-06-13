# minitalk (with-malloc)

## Overview

This project is part of the 42 school curriculum, where the objective is to implement a messaging system using signals. The unique aspect of this implementation is the use of `malloc` for dynamic memory allocation, ensuring efficient memory management without directly writing to `stdout`.

## Key Features

- **Memory Allocation**: Utilizes `malloc` to handle memory dynamically, with only a single allocation.
- **Efficient Messaging**: Sends the length of the message first, allocates memory, and then receives the message, eliminating the need for reallocation.
- **Signal Handling**: Implements communication between a client and server using UNIX signals.
- **Formatted Output**: Manages message formatting internally before output.

## Getting Started

Clone the repository and follow the instructions in the `Makefile` to compile and run the project.

```bash
git clone https://github.com/n-andr/minitalk-with-malloc.git
cd minitalk-with-malloc
make

## Usage

To use the program, run the server and client with the appropriate arguments.

```bash
./server
./client <server_pid> <message>
