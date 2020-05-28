#include <iostream>
#ifndef __KVECTOR__
#define __KVECTOR__

class Kvector{
protected :
  int *m;
  int len;
public :
  static int total_len;
  Kvector(int sz=0, int value =0);
  Kvector(const Kvector& v);
virtual ~Kvector();
virtual void print() const{std::cout  << "Kvector\n";  }
  void clear(){delete[] m; m=NULL; len =0;}
  int size() const{ return len;}
Kvector& operator=(const Kvector& k);
friend bool operator==(const Kvector& v, const Kvector& w);
friend bool operator!=(const Kvector& v, const Kvector& w);
int& operator[](int idx){return m[idx];}
const int& operator[](int idx) const{return m[idx];}
friend std::ostream& operator<<(std::ostream& os, const Kvector& v);
};
#endif
