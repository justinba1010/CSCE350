#include <stdlib.h>
#include <iostream>

using namespace std;

void swap(int a[], int i, int j) {
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

int partition(int a[], int l, int r) {
  int p = a[r];
  int s = l;
  for(int i = l; i < r; ++i) {
    if (a[i] < p) {
      swap(a, s, i);
      ++s;
    }
  }
  swap(a, s, r);
  return s;
}

int book_partition(int a[], int l, int r) {
  int p = a[l];
  int s = l;
  for(int i = l+1; i <= r; ++i) {
    cout << "i: " << i << endl;
    if(a[i] < p) {
      cout << "s: " << s << endl;
      s++;
      swap(a, s, i);
    }
  }
  swap(a, l, s);
  return s;
}

int quickselect(int a[], int k, int l, int r) {
  int s = book_partition(a, l, r);
  if (s == k) return a[s];
  if (s > l + k) return quickselect(a, k, l, s-1);
  return quickselect(a, k - s, s + 1, r);
}

int main(int argc, char *argv[]) {
  int x;
  cin >> x;
  int a[x];
  for(int i = 0; i < x; ++i) cin >> a[i];
  int k;
  cin >> k;
  //int s =partition(a, 0, x-1);
  //cout << s<< endl;
  int v = quickselect(a, k, 0, x-1);
  for(int i = 0; i < x; ++i) i == 0  ? (cout << "*" << a[i] << endl) : (cout << a[i] << endl);
  cout << v << endl;
  return 0;
}

