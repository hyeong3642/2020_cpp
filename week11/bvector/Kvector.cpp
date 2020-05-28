#include <iostream>
#include "Kvector.h"
using namespace std;

Kvector::Kvector(int sz, int value): len(sz){
  cout << this << " : "<< "Kvector(" << sz << ","<< value << ")\n";
  if(!sz){m=NULL; return;}
  m = new int[sz];
  for(int i=0; i<sz; i++) m[i] = value;
}
Kvector::Kvector(const Kvector& v){
  cout << this << " : Kvector(* " << &v << ")\n";
  len = v.len;
  if(!len){m=NULL; return;}
  m = new int[len];
  for(int i=0; i<len; i++) m[i] =v.m[i];
}
Kvector::~Kvector(){
  cout << this << " : ~Kvector() \n";
  delete[] m;
}
Kvector& Kvector::operator=(const Kvector& v){
  cout << "Kvector::opreator= " << &v << endl;
    delete[] m;
    len = v.len;
    m = new int[len];
    for(int i=0; i<len; i++)m[i] = v.m[i];
    return *this;
}

bool operator==(const Kvector& v, const Kvector& w){
  if(v.len != w.len) return false;
  for(int i=0; i<v.len; i++)
    if(v.m[i]!=w.m[i]) return false;
  return true;
}
bool operator!=(const Kvector& v, const Kvector& w){
  return !(v==w);
}
ostream& operator<<(ostream& os, const Kvector& v){
  for(int i=0; i<v.len; i++) os << v.m[i] << " ";
  return os;
}
