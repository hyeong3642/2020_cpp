#include <iostream>
#include "Kvector.h"

#define N 3
class Avector : public Kvector{
  char table[N];
public :
  Avector(int sz=0, int v=0, const char *t="abc");
  void setTable(const char *t);
  void print() const;
friend std::ostream& operator<<(std::ostream& os, const Avector& v);
};
