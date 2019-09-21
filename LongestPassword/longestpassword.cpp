#include<string>
#include <algorithm>

// Should be alphanumeric
// Should contain even number of letters
// Should contain odd number of digits

bool IsAlphaNumeric(const std::string& str) {
   bool result = std::all_of(str.begin(), str.end(), [](int i) { return isalnum(i); });
   return result;
}

bool HasEvenNumberOfLetters(const std::string& str) {
   int count = std::count_if(str.begin(), str.end(), [](int i) { return isalpha(i); });
   return (count % 2 == 0);
}

bool HasOddNumberOfDigits(const std::string& str) {
   int count = std::count_if(str.begin(), str.end(), [](int i) { return isdigit(i); });
   return (count % 2 != 0);
}

constexpr static char SPACE = ' ';
std::string GetNextPassword(std::string& str, size_t curpos) {
   size_t nextspace = str.find(SPACE, curpos);
   std::string result;

   if (nextspace != std::string::npos) {
      result = str.substr(curpos, nextspace - curpos);
   }
   else if (curpos < str.length()) {
      result = str.substr(curpos, str.length() - curpos);
   }
   return result;
}

bool IsValidPassword(const std::string& str) {
   if (IsAlphaNumeric(str) && HasEvenNumberOfLetters(str) && HasOddNumberOfDigits(str)) {
      return true;
   }
   return false;
}

int solution(std::string& S) {
   std::string password;
   int maxlen = 0;
   size_t offset = 0;
   bool validpasswordpresent = false;
   do {      
      password = GetNextPassword(S, offset);
      size_t len = password.length();

      if (IsValidPassword(password)) {
         validpasswordpresent = true;
         if (len > maxlen) {
            maxlen = len;
         }
      }
      offset += (len + 1);
   } while (!password.empty());
   return validpasswordpresent ? maxlen: -1;
}
