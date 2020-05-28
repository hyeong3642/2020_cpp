#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#ifndef _MY_HAMMING_CODE_H_
#define _MY_HAMMING_CODE_H_
class MyHammingCode
{
public:
 // constructors
 MyHammingCode ();
 MyHammingCode (unsigned int val);
 // accessor/mutator functions
 unsigned int getEncodedValue();
 unsigned int getDecodedValue();
private:
 unsigned int value;
 unsigned int encodedValue;
 unsigned int decodedValue;
 unsigned int copyBits(unsigned int n, int from, int num, int to);
 unsigned int setParityBit(unsigned int n, int pos);
 unsigned int checkParityBit(unsigned int n);
 int hammingWeight(unsigned int n);
 unsigned int setBit(unsigned int n, int pos);
 unsigned int clearBit(unsigned int n, int pos);
 int checkBit(unsigned int n, int pos);
 unsigned int negateBit(unsigned int n, int pos);
 unsigned int _xor(unsigned int x, unsigned int y);
  };
#endif // _MY_HAMMING_CODE_H_

// constructors
MyHammingCode::MyHammingCode ()
:value(0)
{
}
MyHammingCode::MyHammingCode (unsigned int val)
:value(val)
{
}
// utility functions
unsigned int MyHammingCode::getEncodedValue ()
{
 encodedValue = 0;
 encodedValue |= copyBits(value, 0, 1, 2);
 encodedValue |= copyBits(value, 1, 3, 4);
 encodedValue |= copyBits(value, 4, 7, 8);
 encodedValue |= copyBits(value, 11, 15, 16);
 encodedValue = setParityBit(encodedValue, 1);
 encodedValue = setParityBit(encodedValue, 2);
 encodedValue = setParityBit(encodedValue, 4);
 encodedValue = setParityBit(encodedValue, 8);
 encodedValue = setParityBit(encodedValue, 16);
 return encodedValue;
}
unsigned int MyHammingCode::getDecodedValue ()
{
 int errorPos;
 decodedValue = 0;
 errorPos = checkParityBit(value);
 if (errorPos > 0)
 value = negateBit(value, errorPos-1);
 decodedValue |= copyBits(value, 2, 1, 0);
 decodedValue |= copyBits(value, 4, 3, 1);
 decodedValue |= copyBits(value, 8, 7, 4);
 decodedValue |= copyBits(value, 16, 15, 11);
 return decodedValue;
}
/*
* 정수 n의 from-번째 비트부터 num개의 비트를
* 다른 정수 num의 to-번째 비트로 복사하는 함수
*/
unsigned int MyHammingCode::copyBits(unsigned int n, int from, int num, int to)
{
 unsigned int mask = 0;
 unsigned int code = 0;
 /* num 비트 만큼의 mask 를 만듬 */
 do
 {
 mask <<= 1;
 mask |= 0x01;
 } while (--num);
 /* n의 from-번째 비트부터 num개의 비트를 골라내어 복사함 */
 n >>= from;
 n &= mask;
 code |= n;
 code <<= to;
 return code;
}
/* 패리티 비트를 만드는 함수 */
unsigned int MyHammingCode::setParityBit(unsigned int n, int pos)
{
 unsigned int mask[5] = { 0x55555554, 0x66666664, 0x78787870,
 0x7F807F00, 0x7FFF0000 };
 int count;
 unsigned int checkBits;
 switch (pos)
 {
 case 1:
 checkBits = n & mask[0];
 break;
 case 2:
 checkBits = n & mask[1];
 break;
 case 4:
 checkBits = n & mask[2];
 break;
 case 8:
 checkBits = n & mask[3];
 break;
 case 16:
 checkBits = n & mask[4];
 break;
 }
 count = hammingWeight(checkBits);
 if (count % 2)
 n = setBit(n, pos-1);
 return n;
}
/*
* 패리티 비트를 검사하는 함수
* 단, 에러가 발생하는 경우에는 한 비트에서만 오류가 발생한 것을 가정하여,
* 에러가 발생한 비트의 위치를 찾아서 리턴해준다.
*/
unsigned int MyHammingCode::checkParityBit(unsigned int n)
{
  unsigned int mask[5] = { 0x55555555, 0x66666666, 0x78787878,
  0x7F807F80, 0x7FFF8000 };
  unsigned int errorPos = 0;
  for(int i=0; i<5; i++){
    if(hammingWeight(n & mask[i])%2==1){
      errorPos += (0x01 << i);
    }
  }
  return errorPos;
}
/* 정수에서 비트가 1인 자리수의 개수를 계산하는 함수 */
int MyHammingCode::hammingWeight(unsigned int n)
{ unsigned int tmp;
  unsigned int result =0;
  tmp = n;
  while(tmp!=0){
    result ++;
    tmp = tmp&(tmp-1);
  }
  return result;
}
/* 정수의 pos 자리수의 비트를 1로 만드는 함수 */
unsigned int MyHammingCode::setBit(unsigned int n, int pos)
{return n | (1 << pos);
}
/* 정수의 pos 자리수의 비트를 0으로 만드는 함수 */
unsigned int MyHammingCode::clearBit(unsigned int n, int pos)
{return n & ~(1 <<pos);
}
/* 정수의 pos 자리수가 0인지 1인지를 확인하는 함수 */
int MyHammingCode::checkBit(unsigned int n, int pos)
{return n &(1 <<pos);
}
/* 정수의 pos 자리수를 반대로 만드는 함수 */
unsigned int MyHammingCode::negateBit(unsigned int n, int pos)
{return n ^(1<<pos);
}
/* Exclusive OR 를 계산하는 함수 */
unsigned int MyHammingCode::_xor (unsigned int x, unsigned int y)
{
 return !x ^ !y;
}


int main()
{
 int numTestCases;
 cin >> numTestCases;
 for(int i=0; i<numTestCases; i++)
 {
 int type;
 unsigned int num;
 cin >> type >> num;
 MyHammingCode hamCode(num);
 if (type == 0)
 cout << hamCode.getEncodedValue() << endl;
 else
 cout << hamCode.getDecodedValue() << endl;
 }
 return 0;
}
