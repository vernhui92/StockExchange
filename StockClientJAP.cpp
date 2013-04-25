/* dictintersectJAP.cpp by Joseph Peacock for CSE 250 Spring 2013 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include "StockJAP.h"
#include "HeapJAP.h"
#include "ChainedHash.h"
using namespace std;

vector<string> split(const string &input) {
	vector<string> split; // Create vector to hold our words
	string buf; // Have a buffer string
	stringstream ss(input); // Insert the string into a stream 

	while (ss >> buf) {
		split.push_back(buf);
	}

	int size = split.size()-1;
	int priceStart = split[size].find('s'); // get location of 's' in last pos of vec.
	size_t priceEnd = split[size].size(); // get the size of the last element in the vec
	split.push_back(split[size].substr(priceStart+1, priceEnd)); // get the price and append
	split[size] = split[size].substr(0, priceStart); // replace the second last with volume

	double initPrice = atof(split[3].c_str());

	return split;
};

int main(int argc, char* argv[]) {
	StockHash<Stock> table;
	Heap<Proxy_byVolume> heap_byVolume;
	Heap<Proxy_byPercentUp> heap_byPercentUp;
	Heap<Proxy_byPercentDown> heap_byPercentDown;
	Heap<Proxy_byPercentChange> heap_byPercentChange;
	Heap<Proxy_byMomentum> heap_byMomentum;
	Heap<Proxy_byTrend> heap_byTrend;

	if (argc < 2) { 
		cout << "Usage: ./filename input_file" << endl;
	} else {
		string input_string = argv[1];
		ifstream fin(input_string.c_str());	
		vector<Stock*> HeapVec; // Populated by pointers to stock objects and passed to 
		// heap class temporarily because I do not have the Hashtable files yet.

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
						// Split the input String
						vector<string> add = split(line); 

						int volume = atoi(add[2].c_str());
						double price = atof(add[3].c_str());
						string name = add[1];

						// Create Stock Object
						Stock stock(name, volume, price);
						Stock* stock_ptr = &*table.insert(stock);

						// Add Stock Pointer to each heap
						heap_byVolume.push(stock_ptr);
						heap_byPercentUp.push(stock_ptr);
						heap_byPercentDown.push(stock_ptr);
						heap_byPercentChange.push(stock_ptr);
						heap_byMomentum.push(stock_ptr);
						heap_byTrend.push(stock_ptr);

					} else if (action == "whisper") {
						cout << line.substr(actionIn+2, line.size()) << endl;
					} else if (action == "pause") {
						cout << "Pausing..." << endl;
					} else if (action == "GetProxyByVolume") {

						int NumtoDisplay = atoi((line.substr(actionIn+2, line.size())).c_str());

						heap_byVolume.makeHeap();
						vector<Proxy_byVolume> top;
					

						for (size_t i = 0; i < NumtoDisplay && heap_byVolume.size() > 0; i++) {
							top.push_back(heap_byVolume.pop());
							const Stock& stock = *top[top.size() - 1];
						}

						for (size_t i = 0; i < top.size(); i++) {
							heap_byVolume.push(top[i]); 
						}

					}
				} else {
					// Split Input
					vector<string> trade = split(line);
					string StockName = trade[0];
					int Shares = atoi(trade[1].c_str());
					double Price = atof(trade[2].c_str());
					// Process Actual Trade
					Stock* stock_ptr = &*table.find(StockName);
					stock_ptr->process_trade(Shares, Price);
				}

			}
	
			fin.close();			
		} else {
			cout << "File doesn't exist!" << endl;			
		}
	}
	return 0;
}