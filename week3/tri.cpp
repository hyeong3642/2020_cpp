#include <iostream>
using namespace std;

int main(void){
  int numTestCases;
  cin >> numTestCases;

  for(int i=0; i<numTestCases; i++){
    int k = 0;
    cin >> k;
    int num = 1;
    for(int j = 1; j<=k; j++){
      num = j;
      int sum = k -1;
      for(int u = 0; u<j; u++){
        cout<< num << " ";
        num += sum;
        sum -= 1;
      }
      cout << ' ' << endl;
      }


    }
  }
