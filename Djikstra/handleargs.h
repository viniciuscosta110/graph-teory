#include <iostream>
#include <string>

using namespace std;

void handle_args(int argc, char *argv[], string& input_file, string& output_file, int& s, bool& print_tree_flag) {
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-f") {
            if (i + 1 < argc) {
                input_file = string(argv[i+1]);
                i++;
            } else {
                cerr << "Error: input file name not provided after -f option" << endl;
                exit(1);
            }
        } else if (string(argv[i]) == "-o") {
            if (i + 1 < argc) {
                output_file = string(argv[i+1]);
                i++;
            } else {
                cerr << "Error: output file name not provided after -o option" << endl;
                exit(1);
            }
        } else if (string(argv[i]) == "-i") {
            if (i + 1 < argc) {
                s = stoi(string(argv[i+1]));
                i++;
            } else {
                cerr << "Error: vertex number not provided after -i option" << endl;
                exit(1);
            }
        } else if (string(argv[i]) == "-s") {
            print_tree_flag = true;
        } else if (string(argv[i]) == "-h") {
            cout << "Usage: " << argv[0] << " [-f input_file] [-o output_file] [-i starting_vertex] [-s]\n";
            cout << "-f input_file: Specifies the input file name.\n";
            cout << "-o output_file: Specifies the output file name.\n";
            cout << "-i starting_vertex: Specifies the starting vertex number for Prim's algorithm.\n";
            cout << "-s: Prints the minimum spanning tree in ascending order.\n";
            cout << "-h: Prints this help message.\n";
            exit(0);
        } else {
            cerr << "Error: invalid option " << string(argv[i]) << endl;
            exit(1);
        }
    }
}