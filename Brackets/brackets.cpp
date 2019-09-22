#include <string>
#include <stack>

int solution(std::string& S);

//S is empty;
//S has the form "(U)" or "[U]" or "{U}" where U is a properly nested string;
//S has the form "VW" where Vand W are properly nested strings.
//For example, the string "{[()()]}" is properly nested but "([)()]" is not.

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
         case ')':
         {
            char startb = chars.top();
            chars.pop();
            if (startb != '(') {
               result = 0;
               break;
            }
         }
         break;
         case ']':
         {
            char startb = chars.top();
            chars.pop();
            if (startb != '[') {
               result = 0;
               break;
            }
         }
         break;

         case '}':
         {
            char startb = chars.top();
            chars.pop();
            if (startb != '{') {
               result = 0;
               break;
            }
         }
         break;
         }
      }
   }
   if (!chars.empty()) {
      result = 0;
   }
   return result;
}