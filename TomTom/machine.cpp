#include<string>
#include <stack>
// SCORE: 91

bool IsPOP(const std::string& str) {
   return (str == "POP");
}

bool IsDUP(const std::string& str) {
   return (str == "DUP");
}

bool IsAddition(const std::string& str) {
   return (str == "+");
}

bool IsSubtraction(const std::string& str) {
   return (str == "-");
}

int getNumber(const std::string& str) {
   return std::stoi(str);
}

constexpr static char SPACE = ' ';
std::string GetNextOp(std::string& str, size_t curpos) {
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

constexpr static size_t MINOPERATIONS = 2;
bool getTop2(std::stack<int>& operations, int& op1, int& op2) {
   if (operations.size() < MINOPERATIONS) {
      return false;
   }
   op1 = operations.top();
   operations.pop();
   op2 = operations.top();
   operations.pop();
   return true;
}

constexpr static int MAX20BIT = 1048575;

int solution(std::string& S) {
   std::string op;
   size_t offset = 0;
   std::stack<int> operations;
   bool error_found = false;

   do {
      op = GetNextOp(S, offset);
      size_t len = op.length();

      if (0 == len) {
         break;
      }
      if (IsAddition(op)) {
         // +
         int op1, op2;
         if (getTop2(operations, op1, op2)) {
            int sum = op1 + op2;
            if (sum > MAX20BIT) {
               // overflow
               error_found = true;
               break;
            }
            operations.push(sum);
         }
         else {
            error_found = true;
         }
      }
      else if (IsSubtraction(op)) {
         // -
         int op1, op2;
         if (getTop2(operations, op1, op2)) {
            int sub = op1 - op2;
            if (sub < 0) {
               error_found = true;
               // underflow
               break;
            }
            operations.push(sub);
         }
         else {
            error_found = true;
         }
      }
      else if (IsPOP(op)) {
         // POP
         operations.pop();
      }
      else if (IsDUP(op)) {
         if (!operations.empty()) {
            operations.push(operations.top());
         }
         else {
            error_found = true;
            break;
         }
      }
      else {
         // A number
         int num = getNumber(op);
         operations.push(num);
      }
      offset += (len + 1);
   } while (!op.empty());

   int result = -1;
   if (!error_found && !operations.empty()) {
      result = operations.top();
   }
   return result;
}
