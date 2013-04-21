/* dictintersectJAP.cpp by Joseph Peacock for CSE 250 Spring 2013 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include "StockJAP.h"
using namespace std;

vector<string> StockInputBuffer(const string &input) {
	vector<string> split; // Create vector to hold our words
    string buf; // Have a buffer string
    stringstream ss(input); // Insert the string into a stream 

	int actionIn = input.find('?');
	if (actionIn) {
		string action = input.substr(0, actionIn);
		if (action == "add") {
			while (ss >> buf) {
        		split.push_back(buf);
    		} 
			int size = split.size()-1;
			int priceStart = split[size].find('s'); // get location of 's' in last pos of vec.
		    size_t priceEnd = split[size].size();
		    split.push_back(split[size].substr(priceStart+1, priceEnd));
			split[size] = split[size].substr(0, priceStart);
		}
		else if (action == "whisper") {
			cout << input.substr(actionIn, input.size());
		}
	} 

	else {
		while (ss >> buf) {
    		split.push_back(buf);
    	} 
	}
	return split;    

/*    

    if (split[0] == 'whisper?') {
    	cout << split[1] endl;
    } else {

    	while (ss >> buf) {
        	split.push_back(buf);
    	}

	    int size = split.size()-1;
		int priceStart = split[size].find('s'); // get location of 's' in last pos of vec.
	    size_t priceEnd = split[size].size();
	    split.push_back(split[size].substr(priceStart+1, priceEnd));
		split[size] = split[size].substr(0, priceStart);

		return split;
	}*/
};

int main(int argc, char* argv[]) {
	if (argc < 2) { 
		cout << "Usage: ./filename input_file" << endl;
	} else {
		string input_string = argv[1];
		ifstream fin(input_string.c_str());	

		// REQ fin must be valid file.
		if (fin.is_open()) {
			// REQ fin must not be at the end of the file.
			while (!fin.eof()) {
				string line;
				getline(fin, line);
				vector<string> split = StockInputBuffer(line);
				cout << split[0] << endl;
/*				if (split[0] == "add?") {
					cout << "adding stock " << split[1] << " at " << split[3] << " and size " << split[2] << endl; 
				} else {
					cout << "function was not add" << endl;
				}
*/			}	
			fin.close();			
		} else {
			cout << "File doesn't exist!" << endl;			
		}
	}

}