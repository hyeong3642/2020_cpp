#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

#ifndef _MY_HAMMING_DISTANCE_H_
#define _MY_HAMMING_DISTANCE_H_
class MyBinaryNumber
{
public:
 // constructors
 MyBinaryNumber ();
 MyBinaryNumber (unsigned int val);
 // accessor/mutator functions
 unsigned int getValue() const;
 void setValue(unsigned int val);
 // utility function
 int getHammingWeight() const;
 int getHammingDistance(const MyBinaryNumber& bn) const;
 unsigned int value;
private:
 vector<int> vec;
};
#endif // _MY_HAMMING_DISTANCE_H_

#define XOR(a,b) (!(a)^!(b))
// constructors
MyBinaryNumber::MyBinaryNumber ()
:value(0)
{
}
MyBinaryNumber::MyBinaryNumber (unsigned int val)
:value(val)
{
  int result =0;
  int u =1;
  while(val!=0){
    vec.push_back(val%2);
    val /= 2;
  }
  for(int i=0; i<vec.size(); i++){
    result += vec[i] *u;
    u = u *10;
  }
  this->value = result;
}
// accessor functions
unsigned int MyBinaryNumber::getValue () const
{
 return value;
}
// mutator functions
void MyBinaryNumber::setValue (unsigned int val)
{
 value = val;
}
// 어떤 정수의 해밍 무게를 계산하는 함수
int MyBinaryNumber::getHammingWeight() const
{int count = 0;
  for(int i=0; i<vec.size(); i++){
    if(vec[i]==1){
      count +=1;
    }
}
  return count;
}
// comptue Hamming Distance
int MyBinaryNumber::getHammingDistance(const MyBinaryNumber& bn) const
{int count = 0;
  if(vec.size()>=bn.vec.size()){
    for(int i=0; i<bn.vec.size(); i++){
      if(vec[i]!=bn.vec[i]){
        count +=1;
      }
    }
    for(int u=bn.vec.size(); u<vec.size(); u++){
      if(vec[u]==1){
        count +=1;
      }
    }
  }
    else{
    for(int j=0; j<vec.size(); j++){
      if(bn.vec[j]!=vec[j]){
        count += 1;
      }
    }
    for(int k=vec.size(); k<bn.vec.size(); k++){
      if(bn.vec[k]==1){
        count +=1;
      }
    }
  }
  return count;
}


int main()
{
 int numTestCases;
 cin >> numTestCases;
 for(int i=0; i<numTestCases; i++)
{
 unsigned int num1, num2;
 cin >> num1 >> num2;
 MyBinaryNumber bn1(num1), bn2(num2);
 cout << bn1.getHammingWeight() << " " << bn2.getHammingWeight() << " "
 << bn1.getHammingDistance(bn2) << endl;
 }
return 0;
}
