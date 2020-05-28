#include <iostream>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    int count;
    int area = 0;
    cin >> count;
    int x[count+1];
    int y[count+1];
    int xi= 0;
    int yi = 0;
    for(int j=0; j<2*count; j++){
      if(j%2==0){
        cin >> x[xi];
        xi += 1;
      }
      else{
        cin >> y[yi];
        yi +=1;
      }
    }
    x[count] = x[0];
    y[count] = y[0];
    for(int u=0; u<count; u++){
      area += (x[u]+x[u+1])*(y[u+1]-y[u]);
    }
    if(area <0){
      cout << abs(area) << " " << "-1" << endl;
    }
    else{
      cout << area << " " << "1" << endl;
    }

  }
}
