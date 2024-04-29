//RYAN SONTUPE // 4/28/24 // program to track grocery information

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

class GroceryRecord { //class defines all access to the Grocery information
private:
    unordered_map<string, int> record; //map containing data of items and times purchased
    string inputFile;
    string backupFile;

public:
    GroceryRecord(const string& inputFile, const string& backupFile) //requires the file names to construct
        : inputFile(inputFile), backupFile(backupFile) {
        readInputFile();
    }
    void readInputFile() { //reads files to generate map
        ifstream file(inputFile);
        string line;
        while (getline(file, line)) {
            string word;
            stringstream ss(line);
            while (ss >> word) {
                record[word]++;
            }
        }
        file.close();
    }
    void createBackupFile() const { //populates the backup file on exit
        ofstream file(backupFile);
        for (const auto& pair : record) {
            file << pair.first << " " << pair.second << endl;
        }
        file.close();
    }
    void printMap() const { //prints all records
        for (const auto& pair : record) {
            cout << pair.first << " " << pair.second << endl;
        }
    }
    void printHistogram() { //prints records in a histogram
        for (const auto& pair : record) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
    int getItemRecord(const string& item) const { //prints information for one specified record
        return record.count(item) ? record.at(item) : 0;
    }
};

int main() {
    string inputFileName = "CS210_Project_Three_Input_File.txt";
    string backupFileName = "frequency.dat";

    GroceryRecord groceryRecord(inputFileName, backupFileName); //creates class object

    int choice; //controls choices
    do {
        cout << "\nMenu Options:\n" << "1. Find frequency of a specific item\n"
            << "2. Print frequency of all items\n"
            << "3. Print histogram\n"
            << "4. Exit\n"
            << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            string itemToFind;
            cout << "Enter the item you wish to look for: ";
            cin >> itemToFind;
            cout << "Frequency of " << itemToFind << ": " << groceryRecord.getItemRecord(itemToFind) << endl;
            break;
        }
        case 2:
            groceryRecord.printMap();
            break;
        case 3:
            groceryRecord.printHistogram();
            break;
        case 4:
            groceryRecord.createBackupFile();
            cout << "Backup file 'frequency.dat' created successfully.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 4);

	return 0;
}