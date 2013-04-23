/** File HeapJAP.h built by Joseph Peacock for CSE 250, Spring 2013

*/

#ifndef StockExchange_HeapJAP_h
#define StockExchange_HeapJAP_h

#include <vector>

template<class I>
class Heap {
	std::vector<I*> elements;
	std::vector<I>* results;

public:
	Heap(std::vector<I*> Ptrs);
	void makeHeap();
	std::vector<I> getTopResults(int ItemsToReturn);
};

template <class I>
Heap<I>::Heap(std::vector<I*> Ptrs) {
	elements = Ptrs;
	results = new std::vector<I>;
}

template <class I>
void Heap<I>::makeHeap() {
	std::cout << "Hello World" << std::endl;
	for (int i=0; i <elements.size(); i++) {
		std::cout << "Pointers currently in heap " << elements[i]->name << std::endl;
		std::cout << "With volume: " << elements[i]->Volume() << std::endl;
	}

	// Receive proxy type
	// Sort with proxy
	// Done.
}

template <class I>
std::vector<I> Heap<I>::getTopResults(int ItemsToReturn) {
	for (int i=0; i<ItemsToReturn; i++) {
		I item = elements.pop();
		results->push_back(item);
		elements.push_back(item);
	}
	return results;
}

#endif
