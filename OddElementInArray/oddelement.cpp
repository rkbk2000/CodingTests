#include <vector>
#include <algorithm>

int solution(std::vector<int>& A)
{
   if (A.size() == 1) {
      return A[0];
   }

   std::sort(A.begin(), A.end());

   int result = A[A.size() - 1]; // Last element for the last case
   for (size_t idx = 0; idx < A.size(); idx+=2) {
      if (A[idx] != A[idx + 1]) {
         result = A[idx];
         break;
      }
   }
   return result;
}