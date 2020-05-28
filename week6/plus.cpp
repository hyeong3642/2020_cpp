#include <iostream>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i =0; i<numTestCases; i++){
    int row, column;
    cin >> row;
    cin >> column;
    int a[row][column];
    int b[row][column];
    for(int j=0; j<row; j++){
      for(int k=0; k<column; k++){
        cin >> a[j][k];
      }
    }
    for(int j=0; j<row; j++){
      for(int k=0; k<column; k++){
        cin >> b[j][k];
      }
    }
    for(int j=0; j<row; j++){
      for(int k=0; k<column; k++){
        a[j][k] += b[j][k];
      }
    }
    for(int j=0; j<row; j++){
      for(int k=0; k<column; k++){
        cout << a[j][k] << " ";
      }
      cout << endl;
    }
  }
}
