
int solution(int A, int B, int K)
{
   auto lower = A;

   while (lower < B) {
      if (0 == (lower % K)) {
         break;
      }
      ++lower;
   }

   auto upper = B;
   while (upper > A) {
      if (0 == (upper % K)) {
         break;
      }
      --upper;
   }

   int result = (upper - lower) / K;

   if (upper == lower) {
      if (0 == (upper % K)) {
         ++result;
      }
   }
   else {
      ++result;
   }

   return result;
}

