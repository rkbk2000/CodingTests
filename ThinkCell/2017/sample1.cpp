#include <assert.h>
#include <map>
#include<iostream>
#include <limits>

using namespace std;

template<class K, class V>
class interval_map {
    friend void IntervalMapTest();

private:
    std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    void print_map()
    {
        typedef typename std::map<K,V>::iterator MapIterator;
     for (MapIterator itr = m_map.begin(); itr != m_map.end(); ++itr)
     std::cout << itr->first << ':' << itr->second << '\n';
     std::cout << std::endl;
    }
    interval_map( V const& val) {
        m_map.insert(m_map.begin(),std::make_pair(std::numeric_limits<unsigned int>::min(),val));
    };

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Do not change values outside this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, const V& val ) {
// INSERT YOUR SOLUTION HERE
     // On encountering empty interval, assign must do nothing
       typedef typename std::map<K,V>::iterator MapIterator;
       MapIterator it = m_map.find(keyEnd);
       if (it == m_map.end() && it->second == val)
       return;
for(K kitr=keyBegin;kitr<keyEnd;kitr++)
{
 auto ret = m_map.insert(make_pair(kitr, val));
    if (!ret.second){
        m_map[kitr] = val;
    }
}

                                                                    }
    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.

void IntervalMapTest() {
    interval_map<unsigned int,char> test_map('a');
    //test corner cases
    test_map.assign(1, 4, 'b');
    test_map.print_map();
    test_map.assign(2, 3, 'c');
   test_map.print_map();
    test_map.assign(std::numeric_limits<unsigned int>::min(), 5, 'a');
    test_map.print_map();
    //print_map();
    test_map.assign(1, 2, 'a');
    test_map.print_map();
    //print_map();
    test_map.assign(1, 3, 'b');
    test_map.print_map();
    //print_map();
    test_map.assign(2, 4, 'a');
    test_map.print_map();
    //print_map();
    test_map.assign(0, std::numeric_limits<unsigned int>::max() + 1, 'b');
    test_map.print_map();
    test_map.assign(-1, 0, 'b');
    test_map.print_map();
    //print_map();

    //test random
    test_map.assign(std::numeric_limits<unsigned int>::min(),
            std::numeric_limits<unsigned int>::max(), 'a');
test_map.print_map();
  //  srand (time(NULL));


}

int main(int argc, char* argv[]) {

    IntervalMapTest();
    return 0;
}
#include <iostream>
using namespace std;

int main() {
   // your code goes here
   return 0;
}

