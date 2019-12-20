/* Copyright 2019
** Justin Baum
** Dr. Okane's 350
** 21 November 2019
*/

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

#define HANDIN false; // Weird

using namespace std;

inline void printIt(vector<int> &partitions, vector<int> &partitions2, string line) {
  int cuts1 = partitions.size()-1;
  sort(partitions2.begin(), partitions2.end());
  int cuts2 = partitions2.size();
  int length = line.length();
  int count = 0;
  if (cuts1 < cuts2) {
    cout << cuts1 << " ";
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
  } else {
  cout << cuts2 << " ";
  count = 0;
  for (int i : partitions2) {
    for(;count < i; ++count) {
      cout << line[count];
    }
    cout << "|";
  }
  for (;count < length; ++count) {
    cout << line[count];
  }
  }
  cout << "\n";
}

int main(int argc, char *argv[]) {
  bool DEBUG, DEBUGPALINDROME;
  DEBUG = false;
  DEBUGPALINDROM = false;
  if (!(HANDIN)) {
    DEBUG = (argc >= 2);
    DEBUGPALINDROME = (argc >= 3);
  }
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

    // Greedy Solution 1
   
    vector<int> cuts3;
    for (int i = 0; i < strLen;) {
      // Subproblem
      int j;
      for (j = strLen - 1; j > i && !palindromes[i][j]; --j) {
      }
      cuts3.push_back(++j);
      if (DEBUG) cout << "j: " << j << endl;
      i = j;
    }
    // Dynamically Greedy 
    int cuts[strLen];
    int lpi[strLen];
    // O(n^2)
    for (int i = 0; i < strLen; ++i) {
      int j;
      cuts[i] = 0;
      lpi[i] = i;
      for (j = 0; j < i && !palindromes[j][i]; ++j) {}
      cuts[i] = cuts[(j == 0 ? 0 : j-1)] + (j == 0 ? 0 : 1);
      lpi[i] = j;
      if(DEBUG) cout << "cuts: " << cuts[i] << " lpi: " << lpi[i] << endl;
    }
    vector<int> cuts2;
    for(int i = strLen - 1; i != 0;) {
      if(lpi[i] != 0) {
        cuts2.push_back(lpi[i]);
        i = lpi[i] - 1;
      } else {
        i = 0;
      }
    }
    if (DEBUG) for(int i : cuts2) cout << "Cut at: " << i << endl;
    printIt(cuts3, cuts2, line);
    if (DEBUGPALINDROME) {
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
