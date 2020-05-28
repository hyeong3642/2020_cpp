#include <iostream>
#include <cmath>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    double a1,a2,b1,b2,c1,c2;
    cin >> a1;
    cin >> a2;
    cin >> b1;
    cin >> b2;
    cin >> c1;
    cin >> c2;
    double area = 0.5*((b1-a1)*(c2-a2)-(c1-a1)*(b2-a2));
    double douarea = 2*abs(area);
    if(area ==0){
      cout << "0" << " " << "0" << endl;
    }
    else if (area>0){
      cout << douarea << " " << "1" << endl;
    }
    else if (area <0) {
      cout << douarea << " " << "-1" << endl;
    }
  }
}
