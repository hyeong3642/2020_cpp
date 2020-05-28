#include <iostream>
#include "Bvector.h"
using namespace std;

Bvector::Bvector(int nbits) : Kvector((nbits+31)/32, 0), NBITS(nbits){
  cout << this << " : Bvector(" << nbits <<")\n";
  u_m = (unsigned int *)m;
}
Bvector::Bvector(const Bvector& e): Kvector(e), NBITS(e.NBITS){
  cout << this << " : Bvector(*" << &e << ")\n";
  u_m = (unsigned int *)m;
}
Bvector& Bvector::operator=(const Bvector& v){
  cout << "Bvector::operator=" << &v << endl;
  if(NBITS == v.NBITS){
    for(int i=0; i<len; i++) m[i] = v.m[i];
  }
  return *this;
}
void Bvector::print() const{
  cout << "Bvector with " << NBITS << " bits\n";
  for(int i=0; i<NBITS; i++) cout << bit(i) << " ";
  cout << endl;
}
ostream& operator<< (ostream& os, const Bvector&v){
  for(int i=0; i<v.NBITS; i++) os<< v.bit(i) << " ";
  return os;
}
bool Bvector::bit(int pos) const{
  if(pos>=NBITS) return false;
  unsigned int element = u_m[pos/32];
  int pos_bit = pos %32;
  unsigned int mask =1 <<pos_bit;
  int value = element & mask;
  return value;
}
void Bvector::reset(int pos){
  if(pos>= NBITS) return;
  unsigned int &element = u_m[pos/32];
  int pos_bit = pos % 32;
  unsigned int mask = 1 << pos_bit;
  mask = ~mask;
  element &= mask;
}
void Bvector::set(int pos){
  if(pos>=NBITS) return;
  unsigned int &element = u_m[pos/32];
  int pos_bit = pos %32;
  unsigned int mask = 1 << pos_bit;
  element |= mask;

}
