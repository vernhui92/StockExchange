/* dictintersectJAP.cpp by Joseph Peacock and Vern Hui LEE for CSE 250 Spring 2013 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include "StockJAP.h"
#include "HeapJAP.h"
#include "ChainedHashLEE.h"
#include "HiResTimer.h"
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
	Heap<Proxy_byTrendShares> heap_byTrendShares;

	if (argc < 2) { 
		cout << "Usage: ./filename input_file" << endl;
	} else {
		string input_string = argv[1];
		ifstream fin(input_string.c_str());	
		vector<Stock*> HeapVec; // Populated by pointers to stock objects and passed to 
		// heap class temporarily because I do not have the Hashtable files yet.
		
		HiResTimer* timer = new HiResTimer();
		timer->reset();
		
		// REQ fin must be valid file.
		if (fin.is_open()) {
			// REQ fin must not be at the end of the file.
			while (!fin.eof()) {
				string line;
				getline(fin, line);
				if (line != "") {
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
							heap_byTrendShares.push(stock_ptr);

						} else if (action == "whisper") {
							cout << line.substr(actionIn+2, line.size()) << endl;
						} else if (action == "pause") {
							cout << "Pausing..." << endl;
						} else if (action == "printTopByVolume") {

							int NumtoDisplay = atoi((line.substr(actionIn+2, line.size())).c_str());
							cout << "Displaying top " << NumtoDisplay << " results by Volume:" << endl;
							heap_byVolume.makeHeap();
							vector<Proxy_byVolume> top;

							for (int i = 0; i < NumtoDisplay && heap_byVolume.size() > 0; i++) {
								top.push_back(heap_byVolume.pop());
								const Stock& stock = *top[top.size() - 1];
								cout << stock.name << " " << stock.Volume() << endl;
							}

							for (int i = 0; i < top.size(); i++) {
								heap_byVolume.push(top[i]); 
							}

						} else if (action == "printTopByPercentUp") {

							int NumtoDisplay = atoi((line.substr(actionIn+2, line.size())).c_str());
							cout << "Displaying top " << NumtoDisplay << " results by Percent up:" << endl;
							heap_byPercentUp.makeHeap();
							vector<Proxy_byPercentUp> top;

							for (int i = 0; i < NumtoDisplay && heap_byPercentUp.size() > 0; i++) {
								top.push_back(heap_byPercentUp.pop());
								const Stock& stock = *top[top.size() - 1];
								cout << stock.name << " " << stock.PercentUp() << "%" << endl;
							}

							for (int i = 0; i < top.size(); i++) {
								heap_byPercentUp.push(top[i]); 
							}

						} else if (action == "printTopByPercentChange") {

							int NumtoDisplay = atoi((line.substr(actionIn+2, line.size())).c_str());
							cout << "Displaying top " << NumtoDisplay << " results by Percent Change:" << endl;
							heap_byPercentChange.makeHeap();
							vector<Proxy_byPercentChange> top;

							for (int i = 0; i < NumtoDisplay && heap_byPercentChange.size() > 0; i++) {
								top.push_back(heap_byPercentChange.pop());
								const Stock& stock = *top[top.size() - 1];
								cout << stock.name << " " << stock.PercentChange() << "%" << endl;
							}

							for (int i = 0; i < top.size(); i++) {
								heap_byPercentChange.push(top[i]); 
							}

						} else if (action == "printTopByPercentDown") {

							int NumtoDisplay = atoi((line.substr(actionIn+2, line.size())).c_str());
							cout << "Displaying top " << NumtoDisplay << " results by Percent Down:" << endl;
							heap_byPercentDown.makeHeap();
							vector<Proxy_byPercentDown> top;

							for (int i = 0; i < NumtoDisplay && heap_byPercentDown.size() > 0; i++) {
								top.push_back(heap_byPercentDown.pop());
								const Stock& stock = *top[top.size() - 1];
								cout << stock.name << " " << stock.PercentDown() << "%" << endl;
							}

							for (int i = 0; i < top.size(); i++) {
								heap_byPercentDown.push(top[i]); 
							}

						} else if (action == "printTopByMomentum") {

							int NumtoDisplay = atoi((line.substr(actionIn+2, line.size())).c_str());
							cout << "Displaying top " << NumtoDisplay << " results by Momentum:" << endl;
							heap_byMomentum.makeHeap();
							vector<Proxy_byMomentum> top;

							for (int i = 0; i < NumtoDisplay && heap_byMomentum.size() > 0; i++) {
								top.push_back(heap_byMomentum.pop());
								const Stock& stock = *top[top.size() - 1];
								cout << stock.name << " " << stock.Momentum() << endl;
							}

							for (int i = 0; i < top.size(); i++) {
								heap_byMomentum.push(top[i]); 
							}

						} else if (action == "printTopByTrendTrades") {

							int NumtoDisplay = atoi((line.substr(actionIn+2, line.size())).c_str());
							cout << "Displaying top " << NumtoDisplay << " results by Trend:" << endl;
							heap_byTrend.makeHeap();
							vector<Proxy_byTrend> top;

							for (int i = 0; i < NumtoDisplay && heap_byTrend.size() > 0; i++) {
								top.push_back(heap_byTrend.pop());
								const Stock& stock = *top[top.size() - 1];
								cout << stock.name << " " << stock.Trend() << endl;
							}

							for (int i = 0; i < top.size(); i++) {
								heap_byTrend.push(top[i]); 
							}

						} else if (action == "printTopByTrendShares") {

							int NumtoDisplay = atoi((line.substr(actionIn+2, line.size())).c_str());
							cout << "Displaying top " << NumtoDisplay << " results by TrendShares:" << endl;
							heap_byTrendShares.makeHeap();
							vector<Proxy_byTrendShares> top;

							for (int i = 0; i < NumtoDisplay && heap_byTrendShares.size() > 0; i++) {
								top.push_back(heap_byTrendShares.pop());
								const Stock& stock = *top[top.size() - 1];
								cout << stock.name << " " << stock.TrendShares() << endl;
							}

							for (int i = 0; i < top.size(); i++) {
								heap_byTrendShares.push(top[i]); 
							}

						} else if (action == "printAll") {
							// todo
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

			}
			cout << "Total timing : " << timer->elapsedTime() <<" "<< timer->getUnits() << endl;
			timer->reset();

			fin.close();			
		} else {
			cout << "File doesn't exist!" << endl;			
		}
		delete(timer);
	}
	return 0;
}

/* 

Heap Questions - Joseph Peacock

a) My heap stores proxy objects which contain pointers to the stock class.
b) No, my code uses the proxy object, which has the pointer to each stock object
   to get the information directly.
c) No, unless make_heap was called it was nothing more than an unsorted vector of proxy objects. 
d) My function objects take arguments of type const Stock*.
e) The function objects only used public methods of the stock class, therefore
   my Stock class was not "friends" with the proxy classes.
f) My stock class expects the client to parse the string, and then run the 
   process_trade() function on the stock pointer after looking it up in the hashtable.
g) My stock class, just maintains the fields. So the fields are updated and added/subtracted
   to/from when another transaction is made.
h) No I had not thought of this. You could do it in this particular case, however it kind
   of takes away from being entirely modular. So I could see how there is an up and a 
   down side to it.

Timing Tests w/ Hash:
Run 1:  328470 microseconds
Run 2:  330699 microseconds
Run 3:  333277 microseconds
Run 4:  330057 microseconds
Run 5:  329110 microseconds
Run 6:  332014 microseconds
Run 7:  328907 microseconds
Run 8:  330550 microseconds
Run 9:  358274 microseconds
Run 10: 329493 microseconds
AVG ->  333085 microseconds
	or	0.333085 seconds

// Need to do with std::set or Valli & Compare

// Report on differences & why | Combined answer





*/
