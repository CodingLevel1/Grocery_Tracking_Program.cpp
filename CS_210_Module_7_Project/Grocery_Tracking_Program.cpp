#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <cctype> 

// Function to capitalize the first letter of a string
void capitalizeFirstLetter(std::string& str) {
    if (!str.empty()) {
        str[0] = std::toupper(str[0]);
    }
}

class ItemTracker {
private:
    std::map<std::string, int> itemFrequency; // Map to store item frequencies

    // Function to read input file and update item frequencies
    void readInputFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        std::string item;
        while (inputFile >> item) {
            itemFrequency[item]++;
        }
        inputFile.close();
    }

    // Function to backup data to a file
    void backupData(const std::string& backupFilename) {
        std::ofstream backupFile(backupFilename);
        for (const auto& pair : itemFrequency) {
            backupFile << pair.first << " " << pair.second << std::endl;
        }
        backupFile.close();
    }

public:
    // Constructor to initialize the object with input file
    ItemTracker(const std::string& filename) {
        readInputFile(filename);
    }

    // Function to prompt user for item and return its frequency
    int getItemFrequency(const std::string& item) {
        return itemFrequency[item];
    }

    // Function to print list of items with frequencies
    void printFrequencyList() {
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }

    // Function to print histogram representation of item frequencies
    void printHistogram() {
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }

    // Public function to trigger backup data operation
    void performBackup(const std::string& backupFilename) {
        backupData(backupFilename); // Call private function
    }
};

int main() {
    ItemTracker tracker("CS210_Project_Three_Input_File.txt"); // Use provided input file
    int choice = 0; // Initialize choice variable
    bool invalidInput = false; // Flag to track invalid input

    do {
        if (invalidInput) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::cout << "Invalid input. Please enter a valid menu option." << std::endl;
            std::cout << "-----------------------------------------------------------------" << std::endl;
            invalidInput = false; // Reset flag
        }

        std::cout << "-----------------------------------------------------------------" << std::endl;
        std::cout << "Menu:\n";
        std::cout << "1. Search for item\n";
        std::cout << "2. Print frequency list\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::string input;
        std::cin >> input;
        std::cout << "-----------------------------------------------------------------" << std::endl;

        if (input == "1" || input == "Search") {
            choice = 1;
        }
        else if (input == "2" || input == "Print") {
            choice = 2;
        }
        else if (input == "3" || input == "Histogram") {
            choice = 3;
        }
        else if (input == "4" || input == "Exit") {
            choice = 4;
        }
        else {
            invalidInput = true; // Set flag for invalid input
            continue; // Skip processing this input
        }

        switch (choice) {
        case 1: {
            std::string item;
            std::cout << "Enter item to search: ";
            std::cin >> item;
            capitalizeFirstLetter(item); // Capitalize first letter of input
            std::cout << "Frequency of " << item << ": " << tracker.getItemFrequency(item) << std::endl;
            break;
        }
        case 2:
            tracker.printFrequencyList();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            tracker.performBackup("frequency.dat");
            std::cout << "Data backed up successfully. Exiting program." << std::endl;
            break;
        default:
            invalidInput = true; // Set flag for invalid input
        }
    } while (choice != 4);

    return 0;
}
