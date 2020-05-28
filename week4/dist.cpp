#include <iostream>
#include <cmath>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    int ax,ay,bx,by,px,py,d1,d2;
    cin >> ax;
    cin >> ay;
    cin >> bx;
    cin >> by;
    cin >> px;
    cin >> py;
    if((ax<=px) && (px<=bx)){
      if((ay<=py) && (py <= by)){
        cout << "0" << " " << "0" << endl;
      }
      else if(py>by){
        d1 = py -by;
        d2 = py -by;
        cout << d1*d1 << " " << d2 << endl;
      }
      else{
        d1 = ay-py;
        d2 = ay-py;
        cout << d1*d1 << " " << d2 << endl;
      }
    }
    else if((ay<=py)&& (py<=by)){
      if(px>bx){
        d1 = px-bx;
        d2 = px-bx;
        cout << d1*d1 << " " << d2 << endl;
      }
      else{
        d1 = ax-px;
        d2 = ax-px;
        cout << d1*d1 << " " << d2 << endl;
      }
    }
    else if(px>bx){
      if(py>by){
        d1 = pow(px-bx,2)+pow(py-by,2);
        d2 = abs(px-bx)+abs(py-by);
        cout << d1<< " " << d2 << endl;
      }
      else{
        d1 = pow(px-bx,2)+pow(ay-py,2);
        d2 = abs(px-bx)+abs(ay-py);
        cout << d1 << " " << d2 << endl;
      }
    }
    else{
      if(py>by){
        d1 = pow(ax-px,2)+pow(py-by,2);
        d2 = abs(ax-px)+abs(py-by);
        cout << d1 << " " << d2 << endl;
      }
      else{
        d1 = pow(ax-px,2)+pow(ay-py,2);
        d2 = abs(ax-px)+abs(ay-py);
        cout << d1 << " " << d2 << endl;
      }
      }

    }
}
