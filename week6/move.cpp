#include <iostream>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    int sz=0;
    cin >> sz;
    int a[sz];
    int count;
    int tmp = 0;
    for(int j=0; j<sz; j++){
      cin >> a[j];
    }
    int k;
    cin >> k;
    count = sz-k+1;
    int b[count];
    for(int i=0; i<count; i++){
      b[i] = 1;
      for(int j=0; j<k; j++){
        tmp += a[i+j];
      }
      b[i] *= tmp/k;
      tmp = 0;
    }
    cout << count << " ";
    for(int i=0; i<count; i++){
      cout << b[i] << " ";
    }
    cout << endl;

  }
}
