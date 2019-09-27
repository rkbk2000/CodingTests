#include <map>
#include <limits>
#include <iostream>

using namespace std;

template <class K, class V>
class interval_map
{
   friend void IntervalMapTest();

private:
   std::map<K, V> m_map;

public:
   // constructor associates whole range of K with val by inserting (K_min, val)
   // into the map
   interval_map(V const &val)
   {
      m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
   };

   // Assign value val to interval [keyBegin, keyEnd).
   // Overwrite previous values in this interval.
   // Do not change values outside this interval.
   // Conforming to the C++ Standard Library conventions, the interval
   // includes keyBegin, but excludes keyEnd.
   // If !( keyBegin < keyEnd ), this designates an empty interval,
   // and assign must do nothing.
   void assign(K const &keyBegin, K const &keyEnd, const V &val)
   {
      // Empty interval, do nothing.
      if (!(keyBegin < keyEnd))
      {
         return;
      }

      // Find key such that key >= keyBegin or map.end(), first O(log N) operation.
      auto lbKeyBegin = m_map.lower_bound(keyBegin);

      // Find key such that keyEnd < key, or map.end(), second O(log N) operation.
      auto ubKeyEnd = m_map.upper_bound(keyEnd);

      // The entry just before the end element in the range
      auto prevUBKeyEnd = std::prev(ubKeyEnd);

      // The new end iterator based on the input val, it could be map.end() as well.
      typename std::map<K, V>::iterator newEnd;

      // The next interval after (keyBegin,keyEnd) starts at keyEnd only if the previous value is not same
      if (!(prevUBKeyEnd->second == val))
      {
         // prevUBKeyEnd is either less than the new end being inserted, or same
         if (!(prevUBKeyEnd->first < keyEnd) && !(keyEnd < prevUBKeyEnd->first))
            newEnd = prevUBKeyEnd;
         else
            newEnd = m_map.insert_or_assign(ubKeyEnd, keyEnd, prevUBKeyEnd->second);
      }
      else
      {
         // Value being inserted is same as the previous value
         newEnd = ubKeyEnd;
      }

      // The new begin iterator based on the input val, it could be map.begin() as well.
      typename std::map<K, V>::iterator newBegin;
      if (lbKeyBegin != m_map.begin())
      {
         auto prevLBKeyBegin = std::prev(lbKeyBegin);
         if (!(prevLBKeyBegin->second == val))
         {
            // New value is not same as the existing value.
            newBegin = m_map.insert_or_assign(lbKeyBegin, keyBegin, val);
         }
         else
         {
            // New value is same as existing value. Merge newBegin with previous begin.
            newBegin = prevLBKeyBegin;
         }
      }
      else
      {
         // Previous interval does not exist
         newBegin = m_map.insert_or_assign(lbKeyBegin, keyBegin, val);
      }

      // Erase all map elements between new begin and end, so that we have only one value for the range
      auto nextBegin = std::next(newBegin);
      if (nextBegin != m_map.end())
      {
         // Linear complexity
         m_map.erase(nextBegin, newEnd);
      }
   }

   // look-up of the value associated with key
   V const &operator[](K const &key) const
   {
      return (--m_map.upper_bound(key))->second;
   }

   void checkCanonicalCorrectness()
   {
#ifdef _DEBUG
      // Checking for canonical correctness
      for (auto mIter = m_map.begin(); mIter != m_map.end(); ++mIter)
      {
         auto next = std::next(mIter);
         if (next != m_map.end() && mIter->second == next->second)
         {
            throw;
         }
      }
#endif
   }

   void printMap()
   {
      static int count = 1;
      checkCanonicalCorrectness();
      cout << "Test " << count << ", Map contents:";
      for (auto iter = m_map.begin(); iter != m_map.end(); ++iter)
      {
         cout << " (" << iter->first << ", " << iter->second << ")";
      }
      cout << endl;
      ++count;
   }
};

template <class K, class V>
bool compareMaps(const std::map<K, V> &left, const std::map<K, V> &right)
{
   bool rc = true;

   if (left.size() == right.size())
   {
      auto lIter = left.begin();
      auto rIter = right.begin();

      for (; lIter != left.end(); ++lIter, ++rIter)
      {
         // Key has only < to compare
         bool keysEqual = !((lIter->first < rIter->first) || (rIter->first < lIter->first));
         bool valuesEqual = (lIter->second == rIter->second);

         if (!keysEqual || !valuesEqual)
         {
            rc = false;
            break;
         }
      }
   }
   else
   {
      rc = false;
   }
   return rc;
}

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.
void IntervalMapTest()
{
   // Prepare a map with A
   interval_map<std::uint32_t, char> mymap('A');

   // T1 : Now insert 10, 18, B
   // the map should look like (0,A), (10,B), (18,A)
   mymap.assign(10, 18, 'B');

   // Expected values
   std::map<std::uint32_t, char> expected = {{0, 'A'}, {10, 'B'}, {18, 'A'}};
   //expected.emplace(std::make_pair(0, 'A'));

   auto comparePrint = [&] {
      mymap.printMap();
      bool rc = compareMaps<std::uint32_t, char>(expected, mymap.m_map);

      if (rc)
      {
         cout << "Test passed" << endl;
      }
      else
      {
         cout << "Test failed" << endl;
      }
   };
   comparePrint();

   // T2: Assign the existing value in the range
   // No change in the map
   mymap.assign(2, 5, 'A');
   comparePrint();

   // T3: Assign a new value in the range
   // No change in the map
   mymap.assign(2, 5, 'C');
   expected = {{0, 'A'}, {2, 'C'}, {5, 'A'}, {10, 'B'}, {18, 'A'}};
   comparePrint();

   // T4: Invalid range
   mymap.assign(2, 1, 'C');
   comparePrint();

   // T5: Invalid range
   mymap.assign(2, 2, 'C');
   comparePrint();

   //const char A='A';
   interval_map<int, char> imap('B');

   // -min:C, 1:B
   imap.assign(std::numeric_limits<int>::lowest(), 1, 'C');

   // No change
   imap.assign(0, 0, 'B');
   imap.assign(1, 0, 'B');

   // No change
   imap.assign(0, 3, 'A');

   // TC1: No overwrite: canonical issue
   // -min:C, 1:B
   imap.assign(3, 5, 'B');
   imap.printMap();

   // TC2: Add values within the range of 3 to max
   // -min:C, 1:B, 3:A, 5: B
   imap.assign(3, 5, 'A');
   imap.printMap();

   // TC3: Replace existing value in the range
   // -min:C, 1:B, 3:C, 5: B
   imap.assign(3, 5, 'C');
   imap.printMap();

   // TC4: Replace existing with same value. Caonical issue
   // -min:C, 1:B, 3:C, 5: B
   imap.assign(5, std::numeric_limits<int>::max(), 'C');
   imap.printMap();

   // TC5: Replace existing value in the range
   // -min:C, 1:B, 3:C, 5: D, max-1:B
   imap.assign(5, std::numeric_limits<int>::max() - 1, 'D');
   imap.printMap();

   // TC6: Overwrite existing value in the range
   // -min:C, 1:B, 3:C, 5: D, max-1:E
   imap.assign(std::numeric_limits<int>::max() - 1, std::numeric_limits<int>::max(), 'E');
   imap.printMap();

   // TC7: Inititalization
   interval_map<int, char> imap1('A');
   // -min:A
   imap1.printMap();

   // TC8: Range initialization
   // -min:A, 1:E, 5:A
   imap1.assign(1, 5, 'E');
   imap1.printMap();

   // TC9: Invalid range
   // -min:A, 1:E, 5:A
   imap1.assign(-1, 5, 'E');
   imap1.printMap();

   // TC10: Invalid range
   // -min:A, 1:E, 5:A
   imap1.assign(1, 8, 'E');
   imap1.printMap();
   getchar();
}

int main(int argc, char *argv[])
{
   IntervalMapTest();
   return 0;
}
