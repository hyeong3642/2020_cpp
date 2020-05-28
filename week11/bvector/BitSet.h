#include <iostream>
#include <exception>
#include "Bvector.h"
class IncompatibleException : public std::exception{
  public :
    int v1;
    int v2;
    IncompatibleException(int v1=0, int v2=0) : v1(v1), v2(v2){};
};

class BitSet : public Bvector{
  public :
    BitSet(int sz=32);
void insert(int v);
friend BitSet operator+(const BitSet& v1, const BitSet& v2);
friend std::ostream& operator<<(std::ostream& os, const BitSet& s);
};
