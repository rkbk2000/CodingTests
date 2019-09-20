#include <stack>
#include <algorithm>
#include <iostream>
#include <array>

int solution(int number);

void RunATest(int number, int result)
{
   int actual = solution(number);

   std::cout << "Number = " << number << ", expected = " << result
      << ", actual =" << actual << " test result = " <<
      ((actual == result) ? "passed" : "failed")
      << std::endl;
}

void RunTests()
{
   RunATest(1041, 5);
   RunATest(32, 0);
   RunATest(1610612737, 28);
   RunATest(1073741825, 29);
}

constexpr static int MAX_DIGITS = 32;

int solution(int number) {

   // Get all the binary digits
   std::array<int, MAX_DIGITS> digits;

   std::uint32_t to_find_digit = (std::uint32_t)INT32_MAX + 1;
   //for (auto i = MAX_DIGITS-1; i >=0 ; --i) {
   for (auto i = 0; i < MAX_DIGITS; ++i) {
      digits[i] = ((number & to_find_digit) ? 1 : 0);
      to_find_digit >>= 1;
   }

   // For each ones do 
   // Find the next one and count zeros on the way.
   // Repeat for all the elements
   int length = 0;
   for (auto i = 0; i < MAX_DIGITS; ++i) {
      auto curlen = 0;
      if (1 == digits[i]) {
         bool found = false;
         for (auto j = i + 1; j < MAX_DIGITS; ++j) {
            if (1 == digits[j]) {
               // Found next 1
               found = true;
               break;
            }
            ++curlen;
         }
         if (found && (curlen > length)) {
            length = curlen;
         }
      }
   }
   return length;
}

int main(int argc, char** argv) {
   RunTests();
   return 0;
}