#include <iostream>
#include "Bvector.h"

class BitSet : public Bvector{
  public :
    BitSet(int sz=32);
void insert(int v);
friend BitSet operator+(const BitSet& v1, const BitSet& v2);
friend std::ostream& operator<<(std::ostream& os, const BitSet& s);
};
