//
// Module 9 - Streams and Files
// Implementation File: Soccer.cpp
// ------------------------------------------------------------
// This file contains the function definitions for the Soccer class.
// It demonstrates how to use different file stream types in C++:
//
//   1. ifstream  → read data from a file
//   2. ofstream  → append new data to a file
//   3. fstream   → read and update a file at the same time
//
// Each function in this file connects directly to concepts
// you’ve seen in class: opening files, checking for errors,
// reading line-by-line, and rewriting data.
// ------------------------------------------------------------

#include "Soccer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>  // for std::pair
using namespace std;

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
// The constructor saves the filename in 'filename_' and makes sure
// the file exists before any other function tries to open it.
//
// The 'explicit' keyword in the header prevents accidental conversions
// like: Soccer league = "file.csv";
// ------------------------------------------------------------
Soccer::Soccer(const string& filename) : filename_(filename) {
    ensureFileExists();
}

// ------------------------------------------------------------
// Function: displayPlayers
// Stream used: ifstream  (input file stream)
// ------------------------------------------------------------
// Purpose:
//   Reads each line from the file and displays it in a
//   readable format.
//
//   This demonstrates opening a file for **reading only**.
//
// Notes:
//   - Always check if the file opened successfully.
//   - Each line is expected to be in "Name,Goals" format.
// ------------------------------------------------------------
void Soccer::displayPlayers() {
    ifstream in(filename_); // Open for reading

    if (!in) {
        cerr << "Error: Could not open " << filename_ << " for reading.\n";
        return;
    }

    cout << "\nCurrent Soccer Stats:\n";
    cout << "----------------------------\n";

    string line;
    while (getline(in, line)) {          // Read each line from the file
        if (line.empty()) continue;      // Skip blank lines

        // 'ss' lets us treat the string like a stream (just like cin).
        // getline() reads up to the comma (storing "Messi" into name),
        // and then 'ss >> goals' reads the remaining number (12) into goals.


        stringstream ss(line);           // Convert the line into a stream
        string name;
        int goals;

        getline(ss, name, ',');  // Read characters up to the comma into 'name'
        ss >> goals;                        // Read the number after the comma into 'goals'

        cout << "Player: " << name << " | Goals: " << goals << endl;
    }

    // File closes automatically here when 'in' goes out of scope.
}

// ------------------------------------------------------------
// Function: addPlayer
// Stream used: ofstream (output file stream)
// ------------------------------------------------------------
// Purpose:
//   Adds a new player's record to the end of the file.
//   Demonstrates the use of ios::app (append mode).
//
// Notes:
//   - ios::app ensures existing data is not erased.
//   - Each new record is added as "Name,Goals" on a new line.
// ------------------------------------------------------------

// 'name' is passed by const reference to avoid copying a large string.
// 'goals' is passed by value because ints are small and cheap to copy.
void Soccer::addPlayer(const string& name, int goals) {
    ofstream out(filename_, ios::app); // Open for writing in append mode

    if (!out) {
        cerr << "Error: Could not open " << filename_ << " for writing.\n";
        return;
    }

    out << name << "," << goals << "\n"; // Write to the file
    cout << "Added " << name << " with " << goals << " goals.\n";

    // No need to call out.close(); it closes automatically.
}

// ------------------------------------------------------------
// Function: updatePlayer
// Stream used: fstream (read/write file stream)
// ------------------------------------------------------------
// Purpose:
//   Updates an existing player's goals, or adds them if they
//   don’t already exist.
//
//   Demonstrates the use of ios::in | ios::out for both reading
//   and writing in the same file.
//
// Steps:
//   1. Read all lines into a vector (memory).
//   2. Modify or add the target player.
//   3. Clear and seek to the start of the file.
//   4. Rewrite the entire file with updated data.
//
// Notes:
//   - file.clear() removes EOF flags after reading.
//   - file.seekp(0) moves the write pointer to the beginning.
// ------------------------------------------------------------
void Soccer::updatePlayer(const string& name, int newGoals) {
    fstream file(filename_, ios::in | ios::out);

    if (!file) {
        cerr << "Error: Could not open " << filename_ << " for updating.\n";
        return;
    }


    // 'vector' = dynamic list
    // 'pair<string, int>' = one player's data (name + goals)
    // Together: a list of player records read from the file
    vector<pair<string, int>> players;
    string line;

    // Step 1: Read all players into memory
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string player;
        int goals;
        getline(ss, player, ',');
        ss >> goals;
        players.push_back({player, goals});
    }

    // Step 2: Modify or add the player
    bool found = false;                         // Flag to track whether the player was found in the list

    // Range-based for loop to go through each player in the vector.
    // 'auto' automatically figures out the correct type (pair<string, int>)
    // '&' means we’re working with a reference to the actual element
    // so we can modify it (not just a copy).
    for (auto& p : players) {
        // Each 'p' represents one record in the vector
        // p.first  = player's name
        // p.second = player's goal count

        if (p.first == name) {      // Check if this player's name matches
            p.second = newGoals;    // Update their goals
            found = true;           // Mark that we found them
        }
    }

    if (!found) {
        cout << name << " not found — adding as a new player.\n";
        players.push_back({name, newGoals});
    } else {
        cout << "Updated " << name << "'s goals to " << newGoals << ".\n";
    }

    // Step 3: Clear EOF/fail flags so we can write again
    file.clear();

    // Step 4: Move the write pointer back to the start
    file.seekp(0, ios::beg);

    // Step 5: Rewrite the updated data
    for (auto& p : players) {
        file << p.first << "," << p.second << "\n";
    }

    // File closes automatically here (RAII)
}

// ------------------------------------------------------------
// Helper Function: ensureFileExists
// Stream used: ifstream / ofstream
// ------------------------------------------------------------
// Purpose:
//   Makes sure the file exists before trying to open it.
//   If it doesn’t, creates one with sample data.
//
//   Demonstrates creating a file using ofstream if it’s missing.
// ------------------------------------------------------------
void Soccer::ensureFileExists() {
    // Check if the data file exists by trying to open it for reading.

    ifstream check(filename_);   // Try opening the file for reading


    // If the file doesn't exist or couldn't be opened...
    if (!check.good()) {

        // Create a new file using ofstream (output mode).
        // Opening with ofstream automatically creates the file if missing.
        ofstream create(filename_);   // Create a new file


        if (create) {
            // Add a few starter records for demonstration
            create << "Messi,12\n";
            create << "Rapinoe,9\n";
            create << "Ronaldo,10\n";
            cout << "(Created new file: " << filename_ << ")\n";
        }
    }
}
