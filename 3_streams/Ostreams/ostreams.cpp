// What do we need to include?
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

// No using namespace std;!!!!
using std::cout;
using std::endl;
using std::string;

// function to write num to any ostream
void write_to_ostream(std::ostream& out, int num) {
    out << "Write to stream: " << num << endl;
}

int main() {
    // Write an int to the user's console.
    int myNum = 42;
    cout << "The answer is: " << myNum << endl;

    // Write an int to a file.
    std::ofstream out_stream("out.txt");

    out_stream << "The answer is: " << myNum << endl;

    // Write method to take any ostream
    write_to_ostream(cout, myNum);
    std::ofstream fout("out.txt");
    write_to_ostream(fout, myNum * 2);

    return 0;
}
