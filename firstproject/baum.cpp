// Copyright 2019 Justin Baum
// CSCE350

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
  int a,b,c,d;
  a = b = c = d = 1;
  while (1) {
    cin >> a;
    cin >> b;
    cin >> c;
    cin >> d;
    if  (
        a == 0 &&
        b == 0 &&
        c == 0 &&
        d == 0
        )
      exit(0);
    cout << (a + b + c + d) << "\n";
  }
}
