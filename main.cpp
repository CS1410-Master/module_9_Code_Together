//
// Module 9 - Streams and Files
// Example: Soccer Stats Tracker
// ---------------------------------------------
// This program demonstrates how to use:
//   - ifstream: to read data from a file
//   - ofstream: to write (append) data to a file
//   - fstream : to read and then update data in the same file
//
// The file "soccer.csv" stores player names and goals scored.
// Each line looks like this:
//
//    Messi,12
//    Ronaldo,10
//    Rapinoe,9
//
// Students can view, add, or update records.
// ---------------------------------------------

#include <iostream>
#include <limits>   // for numeric_limits (used when clearing input buffer)
#include "Soccer.h" // our custom class that handles file operations
using namespace std;

// Define menu options for readability
enum MenuOptions { VIEW = 1, ADD, UPDATE, QUIT };

// Function prototype for displaying the menu
int menu();

int main() {

    // Create an instance of Soccer. This class automatically ensures
    // the file "soccer.csv" exists or creates one if not found.
    Soccer league;

    int choice = 0;  // will hold the user’s menu choice

    // Keep running until the user chooses to quit
    do {
        // Display menu and get user choice
        choice = menu();

        switch (choice) {

            // -------------------------------
            // Option 1: View Players
            // -------------------------------
            case VIEW:
                // This function reads from "soccer.csv" using ifstream
                // and displays each player's name and goal count.
                league.displayPlayers();
                break;

            // -------------------------------
            // Option 2: Add New Player
            // -------------------------------
            case ADD: {
                // Variables to store user input
                string name;
                int goals;

                // Always clear the input buffer before getline
                // (Prevents skipping input if user pressed Enter earlier)
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\nEnter the player's name: ";
                getline(cin, name);

                cout << "Enter number of goals: ";
                cin >> goals;

                // Adds a new player using ofstream in append mode (ios::app)
                // This means the new player is added to the *end* of the file.
                league.addPlayer(name, goals);
                break;
            }

            // -------------------------------
            // Option 3: Update Existing Player
            // -------------------------------
            case UPDATE: {
                string name;
                int goals;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\nEnter the player's name to update: ";
                getline(cin, name);

                cout << "Enter the new goal count: ";
                cin >> goals;

                // Uses fstream (ios::in | ios::out) to both read and rewrite
                // the same file. Demonstrates seekp() and clear() internally.
                league.updatePlayer(name, goals);
                break;
            }

            // -------------------------------
            // Option 4: Quit
            // -------------------------------
            case QUIT:
                cout << "\nExiting Soccer Stats Tracker. Goodbye!\n";
                break;

            // -------------------------------
            // Invalid Choice Handling
            // -------------------------------
            default:
                cout << "\nInvalid choice. Please select 1–4.\n";
                break;
        }

    } while (choice != QUIT);

    return 0;
}

// ------------------------------------------------------------
// Function: menu()
// Purpose : Display menu options and return user’s choice.
// ------------------------------------------------------------
int menu() {
    int choice;
    cout << "\n=========================================\n";
    cout << "         ⚽️  SOCCER STATS TRACKER ⚽️\n";
    cout << "=========================================\n";
    cout << "1. View All Players\n";
    cout << "2. Add New Player\n";
    cout << "3. Update Player Score\n";
    cout << "4. Quit\n";
    cout << "-----------------------------------------\n";
    cout << "Choose an option: ";

    cin >> choice;

    // NOTE: We intentionally don't call cin.ignore() here because
    // some menu options (like VIEW) don’t immediately read text input.
    // We handle it in each specific case where getline() is used.
    return choice;
}
