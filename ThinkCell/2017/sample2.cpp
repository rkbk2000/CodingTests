#include <assert.h>
#include <map>
#include <limits>
#include <iostream>
#include <algorithm>

void IntervalMapTest();

template<class K, class V>
class interval_map {
	friend void IntervalMapTest();

private:
	std::map<K, V> m_map;

public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	interval_map(V const& val) {
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	};

	// Assign value val to interval [keyBegin, keyEnd). 
	// Overwrite previous values in this interval. 
	// Do not change values outside this interval.
	// Conforming to the C++ Standard Library conventions, the interval 
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval, 
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, const V& val) {
		// INSERT YOUR SOLUTION HERE
		if (!(keyBegin < keyEnd))
			return;

		std::map<K, V>::iterator itBegin = --m_map.upper_bound(keyBegin);
		V oldValue = itBegin->second;
		if (itBegin->first == keyBegin)
			itBegin->second = val;
		else
			itBegin = m_map.insert(itBegin, std::make_pair(keyBegin, val));

		std::map<K, V>::iterator itEnd = m_map.upper_bound(keyEnd);

		if (std::distance(itBegin, itEnd) > 1)
		{
			oldValue = (--itEnd)->second;
			itEnd = m_map.erase(++itBegin, ++itEnd);
		}

		if (keyEnd == std::numeric_limits<K>::max())
			return;
		if (itEnd != m_map.end() && itEnd->second == keyEnd)
			return;
		m_map.insert(--itEnd, std::make_pair(keyEnd, oldValue));
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}

	void print()
	{
		for (auto v = m_map.begin(); v != m_map.end(); ++v)
			std::cout << v->first << " " << v->second << std::endl;
		std::cout << std::endl;
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.

int main(int argc, char* argv[]) {
	IntervalMapTest();
	int k;
	std::cin >> k;
	return 0;
}

void IntervalMapTest()
{
	interval_map<int, double> map(-5);
	map.print();
	map.assign(0, 2, .0);
	map.print();
	map.assign(2, std::numeric_limits<int>::max(), 2.1);
	map.print();
	map.assign(3, std::numeric_limits<int>::max(), 3.8);
	map.print();
	map.assign(1, 3, 1.1);
	map.print();
	map.assign(0, 4, 0.2);
	map.print();
}
