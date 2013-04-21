/* dictintersectJAP.cpp by Joseph Peacock for CSE 250 Spring 2013 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Valli.h"
#include "StackPairJAP.h"
using namespace std;

string wordturn(const string &word) {	

		string inputString = word; 
		int len = inputString.length();
		TwoStacks<char> stacks(len*2);
		string newWord;
		int half = len / 2; //Truncated
		
		for(int i=0, j=half; i<half, j<len; j++, i++) { 
			//Middle letter is added to the B stack
			if (i == half){	// Only True when trying to push the final char
							// Makes up for the extra middle char
							// If it is true, only push one more time to B
							// Then break; 
				stacks.pushB(inputString[j]);
				break;
			} else {
				stacks.pushA(inputString[i]);
				stacks.pushB(inputString[j]);
			}	
		}
		for(int i=0; i<len; i++) {
			if (i<half) { 
				//Pop all of the stackA elements
				newWord += stacks.popA();
			}
			else { 		  
				//Pop all of the stackB elements
				newWord += stacks.popB();
			}
		} //End for loop

		stacks.~TwoStacks();
		return newWord;
	};

int main(int argc, char* argv[]) {
	if (argc < 2) { 
		cout << "Usage: ./filename input_file" << endl;
	} else {
		string input_string = argv[1];
		vector<string> o_words;
		Valli<string> r_words;
		ifstream fin(input_string.c_str());

		// REQ fin must be valid file.
		if (fin.is_open()) {
			int count = 0; 			
			cout << "File: pairs.txt created." << endl;
			// REQ fin must not be at the end of the file.
			while (!fin.eof()) {
				string line;
				getline(fin, line);
				string newWord = wordturn(line);
				// INV only words > 3 char in length with be written
				// and turned.				
				if (line.length() > 3) {
					o_words.push_back(line);
					r_words.insert(newWord);
				} // ENS A vector o_Words is filled with input words,
				  // and Valli r_words is filled with the turned words.
			}	
			fin.close();	

			ofstream fout("pairs.txt"); 
			for (int i =0; i < o_words.size(); i++) {
				if (r_words.find(o_words[i]) != r_words.end()) {
					fout << o_words[i] << endl;
					count++;
				}
			}
			cout << "There were " << count << " matched words." << endl;
			fout.close();
			
		} else {
			cout << "File doesn't exist!" << endl;			
		}
	}

}