#include <iostream>
#include <cmath>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    unsigned long int value;
    int count = 0;
    cin >> value;
    unsigned long int tmp = value;
    for(int j=31; j>-1; j--){
      if(tmp>=pow(2,j)){
        count +=1;
        tmp -= pow(2,j);
      }
    }
    if(count%2==0){
      cout << value << endl;
    }
    else{
      cout << value + (unsigned int)pow(2,31) << endl;
    }

  }
}
