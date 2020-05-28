#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

vector<int> v;

int main(){
  for(int j=0; j<13; j++){
    for(int k=0; k<19; k++){
      for(int l=0; l<30; l++){
        int val = (int)pow(5,j)*pow(3,k)*pow(2,l);
        if(val <0) continue;
        v.push_back(val);
      }
    }
  }
    sort(v.begin(),v.end());
    int numTestCases, k;
    cin >> numTestCases;
    for(int i=0; i<numTestCases; i++){
      cin >> k;
      cout << v[k-1] << endl;
    }
    return 0;
}
