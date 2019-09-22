#include <string>
#include <stack>
#include <array>

//S is empty;
//S has the form "(U)" or "[U]" or "{U}" where U is a properly nested string;
//S has the form "VW" where Vand W are properly nested strings.
//For example, the string "{[()()]}" is properly nested but "([)()]" is not.

int matches(std::stack<char>& chars, char expected) {
   char startb = chars.top();
   chars.pop();
   if (startb != expected) {
      return 0;
   }
   return 1;
}

int solution(std::string& S)
{
   int result = 1;
   std::stack<char> chars;
   if (!S.empty()) {
      for (auto c : S) {
         switch (c) {
         case '(':
         case '{':
         case '[':
            chars.push(c);
            break;
         case ')': result = matches(chars, '(');
            break;
         case ']': result = matches(chars, '[');
            break;
         case '}': result = matches(chars, '{');
            break;
         }
         if (!result) {
            break;
         }
      }
   }
   if (!chars.empty()) {
      result = 0;
   }
   return result;
}