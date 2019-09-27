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

      // 2. Incoming range should be a valid range.
      // For e.g. IF we already have something like: -min-0: A, 0-10: B, 10-max: A
      // then assign(-1, 2, D) is not valid as keyBegin and keyEnd are not falling
      // in the allowed range. But assign(0, 5, D) is valid.
      auto kIter = m_map.upper_bound(keyBegin);
      if (m_map.end() != kIter) {
         if (kIter->first < keyEnd)
            return;
      }

      // 3. Check if incoming value is canonically same as the next value
      auto nextVal = (*this)[keyEnd];
      if (val == nextVal) {
         // Cannot insert the new value. It is canonically same as the next value.
         return;
      }

      // 4. Check if incoming value is canonically same as the previous value       
      auto mIter = m_map.lower_bound(keyBegin);
      if (m_map.begin() != mIter) {
         if ((--mIter)->second == val) {
            return;
         }
      }

      V oldVal = (*this)[keyBegin];
      if (!(oldVal  == val)) {       
         // Remove the existing value
         m_map.erase(keyBegin);
         m_map.insert(make_pair(keyBegin, val));
      }

      // As pat of the initialization, entire range would be having a single value.
      // Only the range that is getting assigned would have the new value.
      // the next range would retain its previous value.
      if (keyEnd < std::numeric_limits<int>::max()) {
         m_map[keyEnd] = nextVal;
      }      
   }

   // look-up of the value associated with key
   V const& operator[]( K const& key ) const {
      return ( --m_map.upper_bound(key) )->second;
   }

   void printMap()
   {
      static int count = 1;
      cout<<count<<" Map contents:";
      // std::map<K,V>::iterator iter = m_map.begin();
      for (auto iter = m_map.begin(); iter != m_map.end(); ++iter) {
         cout<<" "<<iter->first<<" : " <<iter->second;
      }
      cout<<endl;
      ++count;
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

   // TC1: No overwrite: canonical issue
   // -min:C, 1:B
   imap.assign(3,5,'B');
   imap.printMap();

   // TC2: Add values within the range of 3 to max
   // -min:C, 1:B, 3:A, 5: B
   imap.assign(3,5,'A');
   imap.printMap();

   // TC3: Replace existing value in the range
   // -min:C, 1:B, 3:C, 5: B
   imap.assign(3,5,'C');
   imap.printMap();

   // TC4: Replace existing with same value. Caonical issue
   // -min:C, 1:B, 3:C, 5: B
   imap.assign(5, std::numeric_limits<int>::max(), 'C');
   imap.printMap();

   // TC5: Replace existing value in the range
   // -min:C, 1:B, 3:C, 5: D, max-1:B
   imap.assign(5, std::numeric_limits<int>::max()-1, 'D');
   imap.printMap();
   
   // TC6: Overwrite existing value in the range
   // -min:C, 1:B, 3:C, 5: D, max-1:E
   imap.assign(std::numeric_limits<int>::max()-1, std::numeric_limits<int>::max(), 'E');
   imap.printMap();

   // TC7: Inititalization
   interval_map<int, char> imap1('A');
   // -min:A
   imap1.printMap();

   // TC8: Range initialization
   // -min:A, 1:E, 5:A
   imap1.assign(1, 5,'E');
   imap1.printMap();
   
   // TC9: Invalid range
   // -min:A, 1:E, 5:A
   imap1.assign(-1, 5,'E');
   imap1.printMap();   
   
   // TC10: Invalid range
   // -min:A, 1:E, 5:A
   imap1.assign(1, 8,'E');
   imap1.printMap();      
   getchar();
}

int main(int argc, char* argv[]) {
   IntervalMapTest();
   return 0;
}
