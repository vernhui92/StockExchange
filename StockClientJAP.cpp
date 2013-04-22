/* dictintersectJAP.cpp by Joseph Peacock for CSE 250 Spring 2013 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include "StockJAP.h"
using namespace std;

Stock StockInputBuffer(const string &input) {
	vector<string> split; // Create vector to hold our words
	string buf; // Have a buffer string
	stringstream ss(input); // Insert the string into a stream 

	int actionIn = input.find('?');
	if (actionIn > 0) {
		string action = input.substr(0, actionIn);
		if (action == "add") {
			while (ss >> buf) {
				split.push_back(buf);
			}
			int size = split.size()-1;
			int priceStart = split[size].find('s'); // get location of 's' in last pos of vec.
			size_t priceEnd = split[size].size(); // get the size of the last element in the vec
			split.push_back(split[size].substr(priceStart+1, priceEnd)); // get the price and append
			split[size] = split[size].substr(0, priceStart); // replace the second last with volume

			double initPrice = atof(split[3].c_str());

			Stock StockItem = new Stock(split[1], atoi(split[2].c_str()), initPrice);

			// Slap this Stock Item into the HashTable at position based on StockItem.name hash

			string StockName = StockItem.name;

			// This gives us a Hashtable full of StockItem Obects.

			StockItem.process_trade(1400, 14.75);
			StockItem.process_trade(1400, 14.75);

			cout << StockName << " starts at " << StockItem.init_price << endl;
			cout << StockItem.PercentUp() << "% change" << endl;

			// TODO: Insert into HashTable here.. 

			return StockItem;

		}
		else if (action == "whisper") {
			cout << input.substr(actionIn+2, input.size()) << endl;
		}
		else if (action == "pause") {
			cout << "Pausing..." << endl;
		}
	} 
	else {
		while (ss >> buf) {
			split.push_back(buf);
		} 
		cout <<  split[0] <<  " " << split[1] << endl;
	}

};

int main(int argc, char* argv[]) {
	if (argc < 2) { 
		cout << "Usage: ./filename input_file" << endl;
	} else {
		string input_string = argv[1];
		ifstream fin(input_string.c_str());	
		vector<int> vec;

		// REQ fin must be valid file.
		if (fin.is_open()) {
			// REQ fin must not be at the end of the file.
			while (!fin.eof()) {
				string line;
				getline(fin, line);

				int actionIn = line.find('?');
				if (actionIn > 0) {
					string action = line.substr(0, actionIn);
					if (action == "add") {
						cout << &StockInputBuffer(line) << endl;
/*						vec.push_back(&StockInputBuffer(line));						
*/					}
				}

			}	
			fin.close();			
		} else {
			cout << "File doesn't exist!" << endl;			
		}
	}

}