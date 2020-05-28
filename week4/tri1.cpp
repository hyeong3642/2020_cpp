#include <iostream>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;

  for(int i=0; i<numTestCases; i++){
    int a,b,c,tmp;
    int aa, bb, cc;
    cin >> a;
    cin >> b;
    cin >> c;
    aa = a*a;
    bb = b*b;
    cc = c*c;
    if(a+b<=c){
      cout << "0" << endl;
    }
    else if(aa==bb && bb==cc && cc==aa){
      cout << "1" <<endl;
    }
    else if(cc-bb-aa==0){
      cout << "2" << endl;
    }
    else if((a==b || b==c) && a!=c){
      cout <<"3" << endl;
    }
    else{
      cout <<"4" << endl;
    }

  }
}
