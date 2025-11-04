//
// Module 9 - Streams and Files
// Header File: Soccer.h
// ------------------------------------------------------------
// This class manages reading and writing player data
// for the "Soccer Stats Tracker" program.
//
// The file we’re working with is called "soccer.csv"
// and contains data in this format:
//
//     Name,Goals
//     Messi,12
//     Rapinoe,9
//     Ronaldo,10
//
// This class demonstrates three types of file streams:
//
//   1. ifstream  → Reading from an existing file
//   2. ofstream  → Writing new data (append mode)
//   3. fstream   → Reading and updating data in the same file
//
// ------------------------------------------------------------

#pragma once   // Prevents multiple inclusions of this header file
#include <string>   // Needed for std::string

// The Soccer class manages file operations for player statistics
class Soccer {
public:
    // ------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------
    // Accepts a filename (default is "soccer.csv")
    // and ensures the file exists.
    //
    // 'explicit' prevents accidental conversions like: Soccer team = "file.csv";
    // It forces the constructor to be called intentionally: Soccer team("file.csv");
    //
    //
    //
    // Example:
    //    Soccer league;                 // uses soccer.csv
    //    Soccer league("players.csv");  // uses a custom file
    // ------------------------------------------------------------
    explicit Soccer(const std::string& filename = "soccer.csv");

    // ------------------------------------------------------------
    // Function: displayPlayers
    // ------------------------------------------------------------
    // Purpose:
    //   - Demonstrates reading data from a file using ifstream.
    //   - Displays each player’s name and goals.
    //
    // Example Output:
    //   Player: Messi | Goals: 12
    //   Player: Rapinoe | Goals: 9
    // ------------------------------------------------------------
    void displayPlayers();

    // ------------------------------------------------------------
    // Function: addPlayer
    // ------------------------------------------------------------
    // Purpose:
    //   - Demonstrates appending data to a file using ofstream.
    //   - Adds a new line with the player's name and goals.
    //
    // 'const std::string& name' passes the string by reference (not copied)
    // and marks it const so the function can read it but not modify it.
    // This makes the code faster and safer for read-only string parameters.
    //
    // Example:
    //   addPlayer("Alex Morgan", 8);
    //   → Adds "Alex Morgan,8" to the end of soccer.csv
    // ------------------------------------------------------------
    void addPlayer(const std::string& name, int goals);

    // ------------------------------------------------------------
    // Function: updatePlayer
    // ------------------------------------------------------------
    // Purpose:
    //   - Demonstrates reading and writing to the same file
    //     using fstream (ios::in | ios::out).
    //   - Finds the player and updates their goal count.
    //   - If the player doesn’t exist, adds them as new.
    //
    // Example:
    //   updatePlayer("Rapinoe", 11);
    //   → Finds "Rapinoe" and updates their goals to 11.
    // ------------------------------------------------------------
    void updatePlayer(const std::string& name, int newGoals);

private:
    // ------------------------------------------------------------
    // Variable: filename_
    // ------------------------------------------------------------
    // Stores the name of the data file (e.g., "soccer.csv")
    // so we can use it for reading/writing across multiple functions.
    // ------------------------------------------------------------
    // The underscore shows this is a private class member (not a local variable)
    std::string filename_;

    // ------------------------------------------------------------
    // Helper Function: ensureFileExists
    // ------------------------------------------------------------
    // Purpose:
    //   - Checks if the file exists using ifstream.
    //   - If not, creates a new file with sample starter data
    //     using ofstream.
    //
    // This helps avoid errors when trying to open a missing file.
    // ------------------------------------------------------------
    void ensureFileExists();
};
