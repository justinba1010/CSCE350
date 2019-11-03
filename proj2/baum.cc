// Justin Baum
// 24 October 2019
// CSCE350: Dr. Okane
// Cryptarithmetic Puzzles

#include <vector>
#include <iostream>
#include <string>
#include <map>
#define lettersize 100 // Make this large so no tricks are used up

int digits[] = {0,1,2,3,4,5,6,7,9};

using namespace std;
typedef map<char, int> jmappy;
typedef jmappy::iterator iter;

void insertZeroMap(char key, jmappy *mappy) {
  auto elem = mappy->find(key);
  if (elem == mappy->end()) {
    mappy->insert({key, 0});
  }
}

void printNumber(char word[], jmappy *mappy) {
  for (int i = 0; i < lettersize && word[i] != 0; ++i) {
    cout << (mappy->find(word[i]))->second;
  }
}

void printAnswer(char word1[], char word2[], char word3[], jmappy *mappy) {
  printNumber(word1, mappy);
  cout << "+";
  printNumber(word2, mappy);
  cout << "=";
  printNumber(word3, mappy);
  cout << endl;
}


void addLettersToMap(char *charArray, jmappy *mappy) {
  for (int i = 0; i < (sizeof(charArray))/sizeof(char) && charArray[i] != 0; ++i) {
    insertZeroMap(charArray[i], mappy);
  }
}

bool uniq(jmappy *mappy) {
  bool ten[10];
  for(int i = 0; i < 10; ++i) ten[i] = false;
  for(auto it = mappy->begin();it != mappy->end(); ++it) {
    int value = it->second;
    if (ten[value]) return false;
    ten[value] = true;
  }
  return true;
}

int getVal(char word[], jmappy *mappy) {
  int val = 0;
  for (int i = 0; i < lettersize && word[i] != 0; ++i) {
    val *= 10;
    val += (mappy->find(word[i]))->second;
  }
  return val;
}

bool checkFirst(char word[], jmappy *mappy) {
  return (mappy->find(word[0]))->second != 0;
}

bool checkFirsts(char word1[], char word2[], char word3[], jmappy *mappy) {
  return checkFirst(word1, mappy) && checkFirst(word2, mappy) && checkFirst(word3, mappy);
}

bool checkCrypt(char word1[], char word2[], char word3[], jmappy *mappy) {
  int w1 = getVal(word1, mappy);
  int w2 = getVal(word2, mappy);
  int w3 = getVal(word3, mappy);
  return (w1+w2) == w3;
}

bool addToMappyHelper(iter helper, iter end) {
  bool flag = true;
  while (helper != end) {
    if (helper->second == 9) {
      helper->second = 0;
      helper++;
    } else {
      helper->second += 1;
      return false;
    }
  }
  return true;
}

bool addToMappy(jmappy *mappy) {
  bool finished = false;
  iter start = mappy->begin();
  iter end = mappy->end();
  do {
    finished = addToMappyHelper(start, end);
  } while(!uniq(mappy) && !finished);
  return finished;
}

//bool calcValue(char charArray[], 


int main(int argc, char **argv) {
  while (1) {
    string line;
    getline(cin, line);
    if (cin.eof()) {
      return 0;
    }

    // Get 3 cryptarithmetic sides
    char first[lettersize];
    char second[lettersize];
    char third[lettersize];
    char j;
    int i = 0;
    int x = 0;
    int linelength = line.length();
    while(i < linelength && (j=line.at(i)) != '+') {
      first[x] = j;
      ++i;
      ++x;
    }
    // Make sure we have valid input, otherwise just try again
    if(i == linelength) continue;
    ++i; //skip over +
    first[x] = 0; //Make null characters (delimit)
    x = 0;
    while(i < linelength && (j=line.at(i)) != '=') {
      second[x] = j;
      ++i;
      ++x;
    }
    // Make sure we have valid input, --> start
    if(i == linelength) continue;
    ++i; // skip over =
    second[x] = 0; //delimit
    x = 0;
    while(i < linelength) {
      third[x] = line.at(i);
      ++i;
      ++x;
    }
    third[x] = 0; //delimit
    //Logic
    jmappy mappy;
    //cout << first << endl;
    //cout << second << endl;
    //cout << third << endl;
    addLettersToMap(first, &mappy);
    addLettersToMap(second, &mappy);
    addLettersToMap(third, &mappy);
    bool flag = false;
    while(!addToMappy(&mappy))  {
      if(checkCrypt(first, second, third, &mappy) && checkFirsts(first, second, third, &mappy)) {
        printAnswer(first, second, third, &mappy);
        flag = true;
      } 
    }
    if (!flag) {
      cout << "no solution" << endl;
    }
    cout << endl;
    //while (flag) {
    //  flag = !addToMappy(&mappy);
    //  if(checkCrypt(first, second, third, &mappy)) {
    //    cout << "Yes" <<endl;
    //  }
    //}
  }
}
