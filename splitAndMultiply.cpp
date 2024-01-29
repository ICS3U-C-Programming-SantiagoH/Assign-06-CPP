// Copyright (c) 2023 Santiago Hewett All rights reserved.
// Created by: Santiago Hewett
// Date: Dec 11, 2023
// This program allows users to input a list of numbers,
// specify a multiplier, multiply each element by the multiplier,
// and view the resulting split list, with the option to repeat the process

#include <cctype>
#include <iostream>
#include <limits>

// Function to multiply each element in the input list by the multiplier
// and store the result in two halves
void splitAndMultiply(int inputList[], int size, float multiplier,
int firstHalf[], int secondHalf[]) {
    // Multiply each element in the input list by the multiplier
    for (int inputIndex = 0; inputIndex < size; ++inputIndex) {
        inputList[inputIndex] = static_cast<int>(inputList[inputIndex]
        * multiplier);
    }

    // Find the midpoint of the input list
    int mid = size / 2;

    // Copy the first half of the input list to the firstHalf array
    int firstHalfIndex = 0;
    while (firstHalfIndex < mid) {
        firstHalf[firstHalfIndex] = inputList[firstHalfIndex];
        ++firstHalfIndex;
    }

    // Copy the second half of the input list to the secondHalf array
    int secondHalfIndex = mid;
    while (secondHalfIndex < size) {
        secondHalf[secondHalfIndex - mid] = inputList[secondHalfIndex];
        ++secondHalfIndex;
    }
}

int main() {
    // Constants for the maximum size of the input list
    const int MAXSIZE = 100;

    // Arrays to store the input list and the halves of the multiplied list
    int inputList[MAXSIZE];
    float multiplier;
    int size = 0;

    // Main loop for user interaction
    while (true) {
        // Take user input for a list of numbers separated by commas
        std::cout << "Enter a list of numbers separated by commas: ";
        std::string userInput;
        std::cin >> userInput;

        // Variables for parsing user input
        size = 0;
        int currentNumber = 0;
        bool isNegative = false;
        bool hasDecimal = false;

        try {
            // Parse user input and convert to an array of integers
            for (char ch : userInput) {
                if (std::isdigit(ch)) {
                    currentNumber = currentNumber * 10 + (ch - '0');
                } else if (ch == '-') {
                    isNegative = true;
                } else if (ch == '.' && !hasDecimal) {
                    hasDecimal = true;
                } else if (ch == ',') {
                    inputList[size++] = isNegative ? -currentNumber
                    : currentNumber;
                    currentNumber = 0;
                    isNegative = false;
                    hasDecimal = false;
                } else {
                    std::cout << "Invalid character in input";
                }
            }

            // Check if the input is empty
            if (size == 0) {
                std::cout << "Empty input\n";
            }
        } catch (const char* errorMessage) {
            // Print error message and continue the loop if an error occurs
            std::cout << "Error: " << errorMessage << std::endl;
            continue;
        }

        // Take user input for the multiplier, handling the
        // possibility of a string input
        std::cout << "Enter a multiplier: ";
        try {
            std::cin >> multiplier;

            // Check if the multiplier input is not a valid number
            if (std::cin.fail()) {
                std::cout << "Invalid number for the multiplier";
            }
        } catch (const char* errorMessage) {
            // Print error message, clear input stream, and continue
            // the loop if an error occurs
            std::cout << "Error: " << errorMessage << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Call the splitAndMultiply function with user inputs
        const int mid = size / 2;
        int firstHalf[mid];
        int secondHalf[mid];
        splitAndMultiply(inputList, size, multiplier, firstHalf, secondHalf);

        // Print the results
        std::cout << "The first half of the multiplied list is: [";
        int printIndex = 0;
        while (printIndex < mid) {
            std::cout << firstHalf[printIndex];
            if (printIndex < mid - 1) {
                std::cout << ", ";
            }
            ++printIndex;
        }
        std::cout << "]\n";

        std::cout << "The second half of the multiplied list is: [";
        printIndex = 0;
        while (printIndex < mid) {
            std::cout << secondHalf[printIndex];
            if (printIndex < mid - 1) {
                std::cout << ", ";
            }
            ++printIndex;
        }
        std::cout << "]\n";

        // Ask if the user wants to try again
        std::string tryAgain;
        std::cout << "Do you want to try again? (yes/no): ";
        std::cin >> tryAgain;
        if (tryAgain != "yes") {
            break;  // Exit the loop if the user doesn't want to try again
        }
    }
}
