#include <iostream>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    int prime;
    cin >> prime;
    int sosu = 1;
    for(int j=2; j<prime; j++ ){
      if(prime%j==0){
        sosu = 0;
      }
    }
    cout << sosu << endl;
  }
}
