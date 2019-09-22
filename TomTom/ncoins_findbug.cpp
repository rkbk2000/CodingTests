#include <vector>

// SCORE : 0
// There are bugs. Modify at most 3 lines to fix the bug.
// Problem s/m:
// Find max adjacency lists in an array representing coins 
// Head = 0, Tail = 1
// Find max possible adjacency lists by just flipping one coin
// The max adjacency list for 1,1,0,1,0,0 is 4


using namespace std;

int max(int a, int b) {
   return (a > b) ? a : b;
}

int solution(vector<int> & A) {
    int n = A.size();
    int result = 0;
    for (int i = 0; i < n - 1; i++) {
        if (A[i] == A[i + 1])
            result = result + 1;
    }
    int r = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        if (i > 0) {
            if (A[i - 1] != A[i])
                count = count + 1;
            else
                count = count - 1;
        }
        if (i < n - 1) {
            if (A[i + 1] != A[i])
                count = count + 1;
            else
                count = count - 1;
        }
        r = max(r, count);
    }
    return result + r;
}

