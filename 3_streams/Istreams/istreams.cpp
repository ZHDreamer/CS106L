
#include <fstream>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// read numbers from a file
void readNumbers() {
    // Create our ifstream and make it open the file
    std::ifstream in("res/numbers.txt");

    // Something to store values we get from the stream
    int number;
    while (true) {
        // Extract next number from input
        in >> number;

        // If input is in a fail state, either a value couldn't
        // be converted, or we are at the end of the file.
        if (in.fail()) break;

        // print whatever we read
        cout << "Read number: " << number << endl;
    }
}

// read a single word at a time from a file
void readHaikuWord() {
    // Create our ifstream and make it open the file
    std::ifstream in("res/haiku.txt");
    // Something to store values we get from the stream
    string word;
    while (true) {
        // Extract next word from input
        in >> word;
        // If input is in a fail state, either a value couldn't
        // be converted, or we are at the end of the file.
        if (in.fail()) break;
        // print whatever we read
        cout << "Read word:" << word << endl;
    }
}

void readHaikuLine() {
    // Create our ifstream and make it open the file
    std::ifstream in("res/haiku.txt");
    // Something to store values we get from the stream
    string line;
    while (true) {
        // Extract next word from input
        std::getline(in, line);
        // If input is in a fail state, either a value couldn't
        // be converted, or we are at the end of the file.
        if (in.fail()) break;
        // print whatever we read
        cout << "Read word:" << line << endl;
    }
}

// function for us to play around with cin
void playground() {
    string        line;
    std::ifstream in("res/haiku.txt");
    while (std::getline(in, line)) {
        if (in.eof()) {
            cout << "eof" << endl;
            // break;
        } else if (in.fail()) {
            cout << "fail" << endl;
            // break;
        } else
            cout << line << endl;
        cout << in.eof() << in.fail() << endl;
    }
    cout << in.eof() << in.fail() << endl;
}

int main() {
    readNumbers();
    readHaikuWord();
    readHaikuLine();
    playground();

    return 0;
}
