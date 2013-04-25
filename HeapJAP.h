/** File HeapJAP.h built by Joseph Peacock for CSE 250, Spring 2013

*/

#ifndef StockExchange_HeapJAP_h
#define StockExchange_HeapJAP_h

#include <vector>
using std::vector;

template<class I>
class Heap {
	vector<I> elements;

public:
	Heap();
	int size() const;
	void makeHeap();
	void fixDown(int index);
	I pop();
	void push(I newItem);
};

template <class I>
Heap<I>::Heap():elements(vector<I>(1)) { }

template <class I>
int Heap<I>::size() const{
	return elements.size()-1;
}

template <class I>
void Heap<I>::fixDown(int index) {
	I temp = elements[index];
	while(2*index <= size()) {
		int child = 2*index;
		if (child < size() && elements[child+1] > elements[child]) {
			child++;
		}
		if (temp >= elements[child]) {
			break;
		}
		elements[index] = elements[child];
		index = child;
	}
	elements[index] = temp;
}

template <class I>
void Heap<I>::makeHeap() {
	for (int index = (size()/2); index >= 1; index--) {
		fixDown(index);
	}
}

template <class I>
I Heap<I>::pop() {
	I temp = elements[1];
	elements[1] = elements[size()];
	elements.pop_back();
	if (size() > 0) {
		fixDown(1);
	}
	return temp;
}

template <class I>
void Heap<I>::push(I newItem) {
	elements.push_back(newItem);
}

#endif
