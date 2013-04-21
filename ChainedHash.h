#ifndef STOCK_H_
#define STOCK_H_



#include <string>
#include <cmath>
using std::string;

class Stock
{
public:
	const string name;
	const size_t capital;
	const double init_price;


	Stock(const string& name, const size_t& capital, const size_t& init_price)
		:name(name), capital(capital), init_price(init_price){init();}

	Stock()
		:name(""), capital(0), init_price(0.0){init();}


	Stock(const string& name)
		:name(name), capital(0), init_price(0.0){init();}

	Stock(const char* name)
		:name(name), capital(0), init_price(0.0){init();}


	bool operator<(const Stock& rhs) const
	{
		return name < rhs.name;
	}

	bool operator==(const Stock& rhs) const
	{
		return name == rhs.name;
	}


	size_t Volume() const
	{
		return volume;
	}

	double PercentUp() const
	{
		return percent_up;
	}

	double PercentDown() const
	{
		return percent_down;
	}

	double PercentChange() const
	{
		return percent_change;
	}

	double Momentum() const
	{
		return momentum;
	}

	size_t Trend() const
	{
		return trend;
	}


	void process_trade(size_t shares, double price)
	{
		prev_price = curr_price;
		curr_price = price;
		volume += shares;
		percent_up = (curr_price - init_price) / init_price * 100.0;
		percent_down = -percent_up;
		percent_change = fabs(percent_up);
		momentum = percent_change * volume / capital;
		if (trend_sign == +1 && curr_price >= prev_price ||
			trend_sign == -1 && curr_price <= prev_price)
			trend++;
		else if (curr_price > prev_price)
		{
			trend = 1;
			trend_sign = +1;
		}
		else if (curr_price < prev_price)
		{
			trend = 1;
			trend_sign = -1;
		}
		else
		{
			trend = 0;
			trend_sign = 0;
		}
	}


private:
	size_t volume;
	double percent_up;
	double percent_down;
	double percent_change;
	double momentum;
	size_t trend;

	double curr_price;
	double prev_price;
	int trend_sign;

	void init()
	{
		volume = 0;
		percent_up = 0.0;
		percent_down = 0.0;
		percent_change = 0.0;
		momentum = 0.0;
		trend = 0;

		curr_price = init_price;
		prev_price = init_price;
		trend_sign = 0;
	}
};



class Proxy_byVolume
{
	const Stock* ptr;

public:
	Proxy_byVolume(const Stock* pointer)
		:ptr(pointer){}

	Proxy_byVolume()
		:ptr(NULL){}

	Proxy_byVolume(const Proxy_byVolume& rhs)
		:ptr(rhs.ptr){}

	Proxy_byVolume& operator=(const Proxy_byVolume& rhs)
	{
		ptr = rhs.ptr;
		return *this;
	}

	const Stock& operator*() const
	{
		return *ptr;
	}

	bool operator<(const Proxy_byVolume& rhs) const
	{
		return ptr->Volume() < rhs.ptr->Volume();
	}

	bool operator==(const Proxy_byVolume& rhs) const
	{
		return ptr->Volume() == rhs.ptr->Volume();
	}
};



class Proxy_byPercentUp
{
	 // To do ...
};



class Proxy_byPercentDown
{
	 // To do ...
};



class Proxy_byPercentChange
{
	 // To do ...
};



class Proxy_byMomentum
{
	 // To do ...
};



class Proxy_byTrend
{
	 // To do ...
};



template<class T>
inline bool operator<=(const T& lhs, const T& rhs)
{
	return lhs < rhs || lhs == rhs;
}

template<class T>
inline bool operator>(const T& lhs, const T& rhs)
{
	return !(lhs <= rhs);
}

template<class T>
inline bool operator>=(const T& lhs, const T& rhs)
{
	return lhs > rhs || lhs == rhs;
}

template<class T>
inline bool operator!=(const T& lhs, const T& rhs)
{
	return !(lhs == rhs);
}



#endif
