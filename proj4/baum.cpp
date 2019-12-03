/* Copyright 2019
** Justin Baum
** Dr. Okane's 350
** 21 November 2019
*/

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

inline void printIt(vector<int> &partitions, string line) {
  int numOfCuts = partitions.size() - 1;
  int length = line.length();
  cout << numOfCuts << " ";
  int count = 0;
  for (int i : partitions) {
    if (i >= length) break;
    while(count < i) {
      cout << line[count];
      count++;
    }
    cout << "|";
  }
  for (;count < length; ++count) {
    cout << line[count];
  }
  cout << "\n";
}

#define DEBUG false

int main(int argc, char *argv[]) {
  while (1) {
    string line;
    getline(cin, line);
    if (cin.eof()) {
      return 0;
    }

    // Algorithm
    int strLen = line.length();
    bool palindromes[strLen + 1][strLen + 1]; // Palindromes Pre Computed
    // All substrings of length 1 are palindromes
    for (int i = 0; i < strLen; ++i) palindromes[i][i] = true;
    // Get all substrings of length 2 that are palindromes
    for (int i = 0; i < strLen - 1; ++i) palindromes[i][i+1] = line[i] == line[i+1];
    for (int subLen = 3; subLen <= strLen; ++subLen) {
      for (int start = 0; start <= strLen - subLen; ++start) {
        // Found this trick to optimize from O(n^3) to O(n^2) from GeeksForGeeks
        int end = start + subLen - 1;
        palindromes[start][end] = line[start] == line[end] && palindromes[start+1][end-1];
      }
    }
    // Done precomputing palindromes
    // Have matrix filled with all palindromes 
    // I think finding disjoint set forest is the best here
    // example: abba
    //    a b b a
    //  a 1 0 0 1
    //  b X 1 1 0
    //  b X X 1 0
    //  a X X X 1
    //  Maybe greedy approach of trying to go as far as possible works? I doubt it
    
    vector<int> cuts2;
    for (int i = 0; i < strLen;) {
      // Subproblem
      int j;
      for (j = strLen - 1; j > i && !palindromes[i][j]; --j) {
      }
      cuts2.push_back(++j);
      if (DEBUG) cout << "j: " << j << endl;
      i = j;
    }
    printIt(cuts2, line);
    if (DEBUG) {
    cout << "\t";
    for (int i = 0; i < strLen; ++i) cout << i << " ";
    cout << "\n";
    for (int i = 0; i < strLen; ++i) {
      cout << i << "\t";
      for (int j = 0; j < strLen; ++j) {
        cout << palindromes[i][j] << (j + 1 == strLen ? "" : "|");
      }
      cout << endl;
    }
    }
  }
}
