/* dictintersectJAP.cpp by Joseph Peacock for CSE 250 Spring 2013 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Valli.h"
#include "StackPairJAP.h"
using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) { 
		cout << "Usage: ./filename input_file" << endl;
	} else {
		string input_string = argv[1];

		ifstream fin(input_string.c_str());

		// REQ fin must be valid file.
		if (fin.is_open()) {
			cout << "File: pairs.txt created." << endl;
			// REQ fin must not be at the end of the file.
			while (!fin.eof()) {
				string line;
				getline(fin, line);

			}	
			fin.close();			
		} else {
			cout << "File doesn't exist!" << endl;			
		}
	}

}