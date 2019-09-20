//This is a demo task.
//
//Write a function :
//
//int solution(vector<int>& A);
//
//that, given an array A of N integers, returns the smallest positive integer(greater than 0) that does not occur in A.
//
//For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.
//
//Given A = [1, 2, 3], the function should return 4.
//
//Given A = [-1, -3], the function should return 1.
//
//Write an efficient algorithm for the following assumptions :
//
//N is an integer within the range[1..100, 000];
//each element of array A is an integer within the range[-1, 000, 000..1, 000, 000].

// you can use includes, for example:
#include <algorithm>
#include <vector>
#include <unordered_set>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(std::vector<int>& A) {
   // write your code in C++14 (g++ 6.2.0)
   int result = 1;

   // Remove duplicates and negatives
   std::unordered_set<int> positive_int_set;
   for (int value : A) {
      if (value > 0) {
         positive_int_set.insert(value);
      }
   }
   std::vector<int> positive_ints;
   positive_ints.reserve(positive_int_set.size());
   positive_ints.assign(positive_int_set.begin(), positive_int_set.end());

   // Sort the values
   std::sort(positive_ints.begin(), positive_ints.end());

   // Now we have only the positive integers
   for (auto value : positive_ints) {
      if (value != result) {
         break;
      }
      ++result;
   }
   return result;
}