#pragma once
#include <cassert>
#include <stack>
#include <vector>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

class Solution {
public:
   Solution() {
      // write your code in C++14 (g++ 6.2.0)
   }

   void push(int value) {
         m_stack.push(value);
         if (m_transactions) {
            // store -1 to indicate a push operation
            m_temp_values.push_back(-1);
         }
   }

   int top() {
      if (m_stack.empty()) {
         return 0;
      }
      return m_stack.top();
   }

   void pop() {
      if (!m_stack.empty()) {
         if (m_transactions) {
            m_temp_values.push_back(m_stack.top());
         }
         m_stack.pop();
      }
   }

   void begin() {
      ++m_transactions;
      m_temp_values.push_back(0);
   }

   bool rollback() {
      if (m_transactions) {
         while (m_temp_values.back() != 0) {
            int value = m_temp_values.back();
            if (-1 == value) {
               // A push has happened, reverse it
               m_stack.pop();
            }
            else {
               // A pop has done, restore the value
               m_stack.push(value);
            }
            m_temp_values.pop_back();
         }
         --m_transactions;
         m_temp_values.pop_back();
         return true;
      }
      return false;
   }

   bool commit() {
      if (m_transactions) {
         while (m_temp_values.back() != 0) {
            // Remove stored temporary vaalues
            m_temp_values.pop_back();
         }
         m_temp_values.pop_back();
         --m_transactions;
         return true;
      }
      return false;
   }

private:

   std::stack<int> m_stack;
   
   std::vector<int> m_temp_values; // To hold the values temporarily, 0 means begin
   // -1 means push, positive means pop

   int m_transactions{ 0 };
};




