#include <iostream>
#include "Solution.h"

#define sprintf sprintf_s

void addn(char* msg) {
   unsigned char ck = 0;
   unsigned int pos;
   char temp[6];

   for (pos = 1; msg[pos]; ck ^= msg[pos++]) {

   }
   sprintf(temp, "*%02X\r\n", ck);
   strcat(msg, temp);
}

void data_copy(char* pstr) {
   struct data {
      std::uint8_t c[32];
      std::uint32_t  val;
   };

   struct data x = { {}, 0x12345678 };
   printf("Q1 = %08x\n", x.val);
   memcpy(x.c, pstr, strlen(pstr));
   printf("Q2 = %s\n", pstr);
   printf("Q3 = %08x\n", x.val);
}

void testSolution() {
   // Define your tests here
   Solution sol;
   sol.push(42);
   assert(sol.top() == 42);
}

void example1() {
   Solution sol;
   sol.push(5);
   sol.push(2);                    // stack: [5,2]
   assert(sol.top() == 2);
   sol.pop();                      // stack: [5]
   assert(sol.top() == 5);

   Solution sol2;
   assert(sol2.top() == 0);        // top of an empty stack is 0
   sol2.pop();                     // pop should do nothing
}

void example2() {
   Solution sol;
   sol.push(4);
   sol.begin();                    // start transaction 1
   sol.push(7);                    // stack: [4,7]
   sol.begin();                    // start transaction 2
   sol.push(2);                    // stack: [4,7,2]
   assert(sol.rollback() == true); // rollback transaction 2
   assert(sol.top() == 7);         // stack: [4,7]
   sol.begin();                    // start transaction 3
   sol.push(10);                   // stack: [4,7,10]
   assert(sol.commit() == true);   // transaction 3 is committed
   assert(sol.top() == 10);
   assert(sol.rollback() == true); // rollback transaction 1
   assert(sol.top() == 4);         // stack: [4]
   assert(sol.commit() == false);  // there is no open transaction
}
int main(int argc, char** argv)
{
   char string[] = "abcd\0efg\0\0\0\0\0\0";
   addn(string);
   printf(string);

   data_copy((char*)"this is the string passed for c \x30\x30\x7A\x42");
   testSolution();
   example1();
   example2();
   return 0;
}