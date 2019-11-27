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

bool isPalindrome(string line, int i, int j) {
  for(;j >= i; --j, ++i) {
    if (line[i] != line[j]) return false;
  }
}


int main(int argc, char *argv[]) {
  while (1) {
    string line;
    getline(cin, line);
    if (cin.eof()) {
      return 0;
    }

    // Algorithm
    int strLen = line.length();
