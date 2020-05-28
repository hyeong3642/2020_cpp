#include <iostream>
#include <cmath>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    double a1,a2,b1,b2,c1,c2;
    double ab,bc,ca;
    double tmp;
    cin >> a1;
    cin >> a2;
    cin >> b1;
    cin >> b2;
    cin >> c1;
    cin >> c2;
    ab = pow(a1-b1,2)+pow(a2-b2,2);
    bc = pow(b1-c1,2)+pow(b2-c2,2);
    ca = pow(c1-a1,2)+pow(c2-a2,2);
    if(ab>bc){
      tmp = ab;
      ab = bc;
      bc = tmp;
    }
    if(bc>ca){
      tmp = bc;
      bc = ca;
      ca = tmp;
    }
    if((b1-a1)*(c2-b2)==(c1-b1)*(b2-a2)){
      cout << "0" << endl;
    }
    else if(ca-bc-ab==0){
      cout << "1" << endl;
    }
    else if(ca-bc-ab>0){
      cout << "2" << endl;
    }
    else{
      cout << "3" <<endl;
    }

  }



}
