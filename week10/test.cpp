#include "cstring"
#include <iostream>
#include <vector>
using namespace std;

vector<char> test;

int main(){
  int num = 123;
  int num1 = 234;
  int num2 = 111;
  int num3 = 222;
  num = (num <<24) & 255;
  num1 = (num1 <<16) & 255;
  num2 = (num2 <<8) & 255;
  num3 = (num3 <<0) & 255;
  cout << num << endl;
  cout << num1 << endl;
  cout << num2 << endl;
  cout << num3 << endl;

  
}
