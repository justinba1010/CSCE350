/*
 * =====================================================================================
 *
 *       Filename:  baum.cc
 *
 *    Description:  Karatsuba Algorithm vs Pen & Pencil Algorithm 
 *
 *        Version:  1.0
 *        Created:  11/02/2019 19:54:35
 *       Revision:  none
 *       Compiler:  gcc
 *        License:  All Rights Reserved  
 *
 *         Author:  Justin Baum
 *   Organization:  
 *
 * =====================================================================================VV
 */
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

typedef vector<int> jnumby;
typedef jnumby::iterator iter;

struct answer {
  int carry;
  int value;
};

struct karatsuba {
  jnumby a;
  jnumby b;
  jnumby c;
  jnumby d;
  int shift;
};

// Chose  c
int getNum(char v) {
  return ((int)v) - 48;
}

answer multiply(int dig1, int dig2, int carry) {
  struct answer a;
  int mult = dig1 * dig2 + carry;
  a.carry = mult / 10;
  a.value = mult % 10;
  return a;
}


answer add(int dig1, int dig2, int carry) {
  struct answer a;
  int answer = dig1 + dig2 + carry;
  a.carry = answer/10;
  a.value = answer % 10;
  return a;
}

answer minuss(int dig1, int dig2, int carry) {
  struct answer a;
  a.carry = (dig1 < dig2) ? 1 : 0;
  dig1 += (a.carry == 0) ? 0 : 10;
  a.value = dig1 - dig2;
  return a;
}

void addFront(jnumby& num, int value) {
  jnumby result;
  result.push_back(value);
  for (iter i = num.begin(); i != num.end(); ++i) {
    result.push_back(*i);
  }
  num = result;
}

void addZerosBack(jnumby& num, int zeros) {
  for (; zeros > 0; --zeros) num.push_back(0);
}

void addZeros(jnumby& num, int zeros) {
  jnumby result;
  for (int i = 0; i < zeros; ++i) result.push_back(0);
  for (iter i = num.begin(); i != num.end(); ++i) {
    result.push_back(*i);
  }
  num = result;
}

void equalize(jnumby& num1, jnumby& num2) {
  int len1 = num1.size();
  int len2 = num2.size();
  if (len1 < len2) {
    addZeros(num1, len2 - len1);
  } else if (len2 < len1) {
    addZeros(num2, len1 - len2);
  }
}

void karatsubaEqualize(jnumby& num1, jnumby& num2);

karatsuba abcd(jnumby& num1, jnumby& num2) {
  karatsubaEqualize(num1, num2);
  struct karatsuba karat;
  jnumby a,b,c,d;
  int shift = num1.size()/2;
  iter n1, n2;
  n1 = num1.begin();
  n2 = num2.begin();
  for(int i = 0; i < shift; ++i, ++n1, ++n2) {
    a.push_back(*n1);
    c.push_back(*n2);
  }
  for(;n1 != num1.end() && n2 != num2.end(); ++n1, ++n2) {
    b.push_back(*n1);
    d.push_back(*n2);
  }
  karat.a = a;
  karat.b = b;
  karat.c = c;
  karat.d = d;
  karat.shift = num1.size() - shift;
  return karat;
}

jnumby addition(jnumby& num1, jnumby& num2) {
  jnumby result;
  struct answer carry;
  carry.carry = 0;
  equalize(num1, num2);
  iter n1, n2;
  for(n1 = num1.end()-1, n2 = num2.end()-1;;--n1, --n2) {
    carry = add(*n1, *n2, carry.carry);
    addFront(result, carry.value);
    if(n1 == num1.begin() || n2 == num2.begin())
      break;
  }
  if (carry.carry) addFront(result, carry.carry);
  return result;
}

jnumby stripZeros(jnumby& num) {
  jnumby result;
  iter start = num.begin();
  for(; start != num.end() && *start == 0; ++start) {}
  for(; start != num.end(); ++start) result.push_back(*start);
  return result;
}

jnumby subtraction(jnumby& num1, jnumby& num2) {
  equalize(num1, num2);
  struct answer carry;
  carry.carry = 0;
  jnumby result;
  iter n1, n2;
  for(n1 = num1.end()-1, n2 = num2.end()-1;; --n1, --n2) {
    carry = minuss(*n1, *n2, carry.carry);
    addFront(result, carry.value);
    if(n1 == num1.begin() || n2 == num2.begin())
      break;
  }
  if (carry.carry) {
    cout << "Error: negative numbers not valid" << endl;
  }
  return result;
}

jnumby reverse(jnumby& num) {
  jnumby result;
  for(iter i = num.end()-1;;--i) {
    result.push_back(*i);
    if(i == num.begin()) return result;
  }
}

jnumby penalgo(jnumby& num1, jnumby& num2);

void karatsubaEqualize(jnumby& num1, jnumby& num2) {
  equalize(num1, num2);
  while (num1.size() % 4 != 0) {
    addFront(num1, 0);
    addFront(num2, 0);
  }
}

// Not tail recursive :'(
jnumby karatsuba(jnumby& num1, jnumby& num2) {
  if (num1.size() <= 2 || num2.size() <= 2) {
    return penalgo(num1, num2);
  }
  struct karatsuba karat = abcd(num1, num2);
  jnumby c2 = karatsuba(karat.a, karat.c);
  jnumby c0 = karatsuba(karat.b, karat.d);
  jnumby aplusb = addition(karat.a, karat.b);
  jnumby cplusd = addition(karat.c, karat.d);
  jnumby c1 = karatsuba(aplusb, cplusd);
  jnumby c0plusc2 = addition(c0, c2);
  c1 = subtraction(c1, c0plusc2);
  addZerosBack(c2, karat.shift*2);
  addZerosBack(c1, karat.shift);
  jnumby result = addition(c0,c1);
  result = addition(result, c2);
  return result;
}


jnumby penalgo(jnumby& num1, jnumby& num2) {
  jnumby result, rnum1, rnum2;
  iter n1, n2;
  struct answer carry;
  int shift;
  rnum1 = reverse(num1);
  rnum2 = reverse(num2);
  for(n1 = rnum1.begin(), shift = 0; n1 != rnum1.end(); ++n1, ++shift) {
    jnumby interim;
    addZeros(interim, shift);
    carry.carry = 0;
    for(n2 = rnum2.begin(); n2 != rnum2.end(); ++n2) {
      carry = multiply(*n1, *n2, carry.carry);
      interim.push_back(carry.value);
    }
    interim.push_back(carry.carry);
    interim = reverse(interim);
    result = addition(result, interim);
  }
  return result;
}

void printNum(jnumby& num) {
  iter i = num.begin();
  for (;i != num.end(); ++i)
    cout << *i;
  cout << endl;
}

void printSafe(jnumby& num) {
  iter i = num.begin();
  for (;i != num.end() && *i == 0; ++i) {}
  for (;i != num.end(); ++i)
    cout << *i;
  cout << endl;
}


int main(int argc, char *argv[]) {
  while (1) {
    string line;
    getline(cin, line);
    if (cin.eof()) {
      return 0;
    }
    jnumby num1, num2;
    /// Get num1
    int i, linelength;
    char j;
    for(i = 0, linelength = line.length(); i < linelength; ++i) { 
      j = line.at(i);
      if (j == '*') break;
      num1.push_back(getNum(j));
    }
    if (i == linelength) continue;
    /// Get num2
    for(++i; i < linelength; ++i) {
      j = line.at(i);
      num2.push_back(getNum(j));
    }
    // Keep going till we got valid input
    jnumby result = penalgo(num1, num2);
    jnumby result1 = karatsuba(num1, num2);
    if (argc != 2 && argc != 3) cout << "Result(pen): "; // For testing
    if (argc != 3) printSafe(result);
    if (argc != 2 && argc != 3) cout << "Result(karatsuba): "; // For testing
    if (argc != 2) printSafe(result1);

    //
  }
}
