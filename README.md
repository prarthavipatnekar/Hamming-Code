# Hamming Code Implementation
 Hamming code is used for error detection and correction in data transmission. This project demonstrates an implementation of Hamming code using C++ includes generating parity bits, encoding a message, simulating errors, correcting the errors and using the Armadillo library for matrix operations.

## Features
- User Input for Data Bits: Get the number of data bits from the user.
- Matrix Operations: Utilize the Armadillo library for efficient matrix operations.
- Error Detection and Correction: Detect and correct a single-bit error in the transmitted message.
- Customizable Parity and Data Bit Generation: Generate matrices and vectors based on the user's input.

## Requirements
- C++ compiler (supporting C++11 or later)
- Armadillo library


## Installation
1. Install Armadillo
   Ensure the Armadillo library is installed on your system. You can install it using your package manager (e.g., sudo apt-get install libarmadillo-dev on Ubuntu).

2. Clone the Repository: Clone the project repository to your local machine.
``` bash
git clone https://github.com/prarthavipatnekar/Hamming-Code.git
cd Hamming
```
3. Build the Project:
``` bash
g++ -o hamming Hamming.cpp -larmadillo
```

## Usage
1. Run the Program:

``` bash
./hamming
```
2. Input Data Bits: The program will prompt you to enter the number of data bits. Enter an integer value.

3. View Results: The program will display the generated message, the send vector, the received vector (with possible errors), and the decoded message.

## Code Structure
Hamming.cpp: The main file containing the implementation of Hamming code. It includes functions for:
- Getting user input for the number of data bits.
- Generating matrices for encoding and decoding.
- Creating a message and introducing errors.
- Correcting errors in the received message.
