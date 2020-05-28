#include <iostream>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    int r,s,t,sum;
    cin >> r >> s >> t;
    int a[r][s];
    int b[s][t];
    int c[r][t];
    for (int j=0; j<r; j++){
      for(int k=0; k<s; k++){
        cin >> a[j][k];
      }
    }
    for(int l=0; l<s; l++){
      for(int m=0; m<t; m++){
        cin >> b[l][m];
      }
    }
    for(int n=0; n<r; n++){
      for(int o=0; o<t; o++){
        sum =0;
        for(int p=0; p<s; p++){
          sum += a[n][p] * b[p][o];
        }
        c[n][o] = sum;
        sum = 0;
        cout << c[n][o] << ' ';
      }
      cout << endl;
    }
  }
}
