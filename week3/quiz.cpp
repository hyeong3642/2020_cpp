#include <iostream>
using namespace std;

int main(){
  double d;
  char *cp;
  int *ip;
  float *fp;
  double *dp;

  cout << &d <<endl;

  d=3.141592;
  cp = (char *)&d;
  ip = (int *)&d;
  fp = (float *)&d;
  dp = &d;


  cout << "*cp ="<< *cp << endl;
  cout << "*ip =" << *ip <<endl;
  cout << "*fp ="<< *fp << endl;
  cout << "*dp =" << *dp << endl;

  return 0;
}
