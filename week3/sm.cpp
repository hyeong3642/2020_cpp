#include <iostream>
using namespace std;

int main(void){
  int numTestCases;
  cin >> numTestCases;

  for(int i=0; i<numTestCases; i++){
    int numData, data;
    unsigned int last1Digit =1;
    cin >> numData;

    for(int j=0; j<numData; j++){
      cin>>data;
      last1Digit *= data;
      last1Digit %= 10;
    }
    cout << last1Digit % 10 << endl;
  }
  return 0;
}
