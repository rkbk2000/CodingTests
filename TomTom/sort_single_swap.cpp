#include <vector>
#include <utility>
#include <algorithm>

// SCORE : 100
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

bool solution(std::vector<int>& A) {
   // write your code in C++14 (g++ 6.2.0)
   bool result = true;

   std::vector<std::pair<int, int>> org_pos;
   org_pos.resize(A.size());

   // Get the original posittions in the array
   for (size_t idx = 0; idx < A.size(); ++idx) {
      org_pos[idx].first = idx;
      org_pos[idx].second = A[idx];
   }

   // Sort the incoming array
   std::sort(A.begin(), A.end());

   int orgv1 = -1, newv1 = -1;
   int swapfound = 0;
   // Now traverse through the sorted array. There must be only
   // zero differences or two differences in the element positions
   for (size_t idx = 0; idx < A.size(); ++idx) {
      if (org_pos[idx].second != A[idx]) {
         ++swapfound;

         if (swapfound > 2) {
            result = false;
            break;
         }
         else if (swapfound == 1) {
            // Save the value for first difference
            orgv1 = org_pos[idx].second;
            newv1 = A[idx];
         }
         else if (swapfound == 2) {
            if ((orgv1 != A[idx]) || (newv1 != org_pos[idx].second)) {
               result = false;
               break;
            }
         }
      }
   }
   return result;
}
