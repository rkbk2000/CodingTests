#include <map>
#include <limits>
#include <iostream>

using namespace std;

template<class K, class V>
class interval_map {
    friend void IntervalMapTest();

private:
    std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.begin(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    };
    
    // Assign value val to interval [keyBegin, keyEnd). 
    // Overwrite previous values in this interval. 
    // Do not change values outside this interval.
    // Conforming to the C++ Standard Library conventions, the interval 
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval, 
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, const V& val) 
    {
   // INSERT YOUR SOLUTION HERE

       // 1. Check for the empty interval.
       if (!(keyBegin < keyEnd )) {          
          // Key provides only < operator
          return;
       }

       // 2. Make sure that keyBegin and keyEnd are in the allowed range
       if (keyBegin < std::numeric_limits<K>::lowest()) {
          return;
       }

       // 3. keyEnd shpould be less than the maximum
       if (!(keyEnd < std::numeric_limits<K>::max())) {
          return;
       }

       // 4. Incoming range should be a valid range.
       // For e.g. IF we already have something like: -min-0: A, 0-10: B, 10-max: A
       // then assign(-1, 2, D) is not valid as keyBegin and keyEnd are not falling
       // in the allowed range. But assign(0, 5, D) is valid.
       auto kIter = m_map.upper_bound(keyBegin);
       if (m_map.end() != kIter) {
          if (kIter->first < keyEnd)
             return;
       }

       // 5. Check if incoming value is canonically same as the next value
       auto nextVal = (*this)[keyEnd];
       if (val == nextVal) {
          // Cannot insert the new value. It is canonically same as the next value.
          return;
       }
       
       /*// Check if incoming value is canonically same as the previous value       
       auto mIter = std::prev(m_map.lower_bound(keyBegin));       
       if (m_map.begin() != mIter) {
          if ((--mIter)->second == val) {
             return;
          }
       }*/

       V oldVal = (*this)[keyBegin];
       if (!(oldVal  == val)) {       
          // Remove the existing value
          m_map.erase(keyBegin);
          m_map.insert(make_pair(keyBegin, val));
       }
       m_map[keyEnd] = nextVal;
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
       return ( --m_map.upper_bound(key) )->second;
    }

    void printMap()
    {
       cout<<"Map contents:"<<endl;
       // std::map<K,V>::iterator iter = m_map.begin();
       for (auto iter = m_map.begin(); iter != m_map.end(); ++iter) {
          cout<<iter->first<<" : " <<iter->second<<endl;
       }
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.


void IntervalMapTest()
{
   //const char A='A';
   interval_map<int, char> imap('B');

   // -min:C, 1:B
   imap.assign(std::numeric_limits<int>::lowest(), 1, 'C');

   // No change
   imap.assign(0,0,'B');
   imap.assign(1,0,'B');

   // No change
   imap.assign(0,3,'A');

   // No change: 1 + is already B
   imap.assign(3,5,'B');
   imap.printMap();
   
   // -min:C, 1:B, 3:A, 5: B
   imap.assign(3,5,'A');
   imap.printMap();

   // -min:C, 1:B, 3:C, 5: B
   imap.assign(3,5,'C');
   imap.printMap();
   getchar();
}

int main(int argc, char* argv[]) {
    IntervalMapTest();
    return 0;
}
