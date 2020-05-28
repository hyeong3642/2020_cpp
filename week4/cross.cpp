#include <iostream>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    int x1,y1,x2,y2,x3,y3,x4,y4;
    int tmp;
    cin >> x1;
    cin >> y1;
    cin >> x2;
    cin >> y2;
    cin >> x3;
    cin >> y3;
    cin >> x4;
    cin >> y4;
    if(x1>x2){
      tmp = x1;
      x1 = x2;
      x2 = tmp;
    }
    if(y1>y2){
      tmp = y1;
      y1 = y2;
      y2= tmp;
    }
    if(x3>x4){
      tmp = x3;
      x3 = x4;
      x4 = tmp;
    }
    if(y3>y4){
      tmp = y3;
      y3 = y4;
      y4 = tmp;
    }
    if(x1==x2){
      if(((x3<=x1)&&(x1<=x4))&&((y1<=y3)&&(y3<=y2))){
        if((x3==x1)||(x4==x1)){
          cout << "2" << endl;
        }
        else if((y1==y3)||(y2==y3)){
          cout << "2" << endl;
        }
        else{
          cout << "1" << endl;
        }
      }
      else{
        cout << "0" <<endl;
      }
    }
    else if(y1==y2){
      if(((x1<=x3)&&(x3<=x2))&&((y3<=y1)&&(y1<=y4))){
        if((x1==x3)||(x2==x3)){
          cout << "2" << endl;
        }
        else if((y1==y3)||(y1==y4)){
          cout << "2" << endl;
        }
        else{
          cout << "1" << endl;
        }
      }
      else{
        cout << "0" << endl;
      }
    }

  }
}
