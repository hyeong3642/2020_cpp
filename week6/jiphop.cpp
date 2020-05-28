#include <iostream>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    int a[132];
    int b[132];
    int c[132];
    int d[132];
    int e[132];
    int anum, bnum;
    int count =0;
    cin >> anum;
    for(int j=0; j<132; j++){
      a[j] = 0;
      b[j] = 0;
      c[j] =0;
      d[j] =0;
      e[j] = 0;
    }
    for(int k=0; k<anum; k++){
      int tmp;
      cin >> tmp;
      a[tmp] = 1;
    }
    cin >> bnum;
    for(int l=0; l<bnum; l++){
      int tmp2;
      cin >> tmp2;
      b[tmp2] = 1;
    }
    for(int m=0; m<132; m++){
      if(a[m]==1&&b[m]==1){
        c[0] +=1;
        c[m] =1;
      }
    }
      cout << c[0] << " ";
      for(int n=1; n<132; n++){
        if(c[n]==1){
          cout << n << " ";
        }
      }
      cout << endl;
    for(int m=1; m<132; m++){
      if(a[m]==1||b[m]==1){
        d[0] +=1;
        d[m] =1;
      }
    }
    cout << d[0] << " ";
    for(int n=1; n<132; n++){
      if(d[n]==1){
        cout << n << " ";
      }
    }
    cout << endl;
    for(int z=1; z<132; z++){
      if(a[z]==1){
        e[z]=a[z]-b[z];
      }
      if(e[z]==1){
        count +=1;
      }
    }
    cout << count << " ";
    for(int i=1; i<132; i++){
      if(e[i]==1){
        cout << i << " ";
      }
    }
    cout << endl;

  }
}
