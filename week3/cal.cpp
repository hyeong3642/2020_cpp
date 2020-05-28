#include <iostream>
using namespace std;

int main(void){
  int numTestCases;
  cin >> numTestCases;
  int size, count = 0;

  for(int i=0; i<numTestCases; i++){
    cin >> size;
    unsigned long int a[size];
    int sum = 1;
    for(int j=0; j< size; j++){
      cin >> a[j];
    }
    for(int u=0; u< size; u++){
      a[u] %= 10;
    }
    for (int n =0; n<size; n++){
      sum *= a[n];
      sum %= 10;
    }
    cout << sum << endl;
  }
}
