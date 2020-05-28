#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

class Kvector{
protected :
  int *m;
  int len;
public :
  static int total_len;
  Kvector(int sz=0, int value =0);
  Kvector(const Kvector& v);
  ~Kvector(){
    cout << this << " : ~Kvector() \n";
    delete[] m;
    total_len -= len;
  }
  void print() const{
    for(int i=0; i<len; i++) cout << m[i] << " ";
    cout << endl;
  }
  int size(){ return len;}
  void clear(){
    delete[] m;
    m = NULL;
    len = 0;
  }
  Kvector& operator=(const Kvector& k);
  friend bool operator==(const Kvector& k, const Kvector& v);
  friend bool operator!=(const Kvector& k, const Kvector& v);
  friend ostream& operator<<(ostream& os, const Kvector& k);
  int& operator[](int idx);
  const int& operator[](int idx) const{return m[idx];}
};
int Kvector::total_len = 0;
Kvector::Kvector(int sz, int value){
  cout << this << " : "<< "Kvector(" << sz << ","<< value << ")\n";
  if (sz==0){
    m = NULL;
  }
  else{
    m = new int[sz];
    fill_n(m, sz, value);
    len = sz;
    total_len += len;
  }
}
Kvector::Kvector(const Kvector& v){
  cout << this << " : Kvector(* " << &v << ")\n";
  m = new int[v.len];
  for(int i=0; i<v.len; i++){
    m[i] = v.m[i];
  }
  len = v.len;
  total_len += len;
}
Kvector& Kvector::operator=(const Kvector& k){
  if(&k != this){
    delete[] m;
    len = k.len;
    m = new int[len];
    for(int u=0; u<len; u++){
      m[u] = k.m[u];
    }
  }
  return *this;
}
ostream& operator<<(ostream& os, const Kvector& k){
  for(int i=0; i<k.len; i++){
    os << k.m[i] << " ";
  }
  return os;
}
bool operator==(const Kvector& k, const Kvector& v){
  bool equal = true;
  if(k.len != v.len){
    equal = false;
  }
  else{
    for(int i=0; i<k.len; i++){
      if(k.m[i]!=v.m[i]){
        equal = false;
    }
  }
  }
  return equal;
}
bool operator!=(const Kvector& k, const Kvector& v){
  return !(k==v);
}
int& Kvector::operator[](int idx){
  return m[idx];
}

#define N 3
class Avector : public Kvector{
  char table[N];
public :
  Avector(int sz=0, int v=0, const char *t="abc") : Kvector(sz, v){
    for(int i=0; i<N; i++){
      table[i] = t[i];
    }
    cout << this << " : "<< "Avector(" << sz << ","<< v << ","<<table <<")\n";
  }
  void setTable(const char *t){
    for(int i=0; i<N; i++){
      table[i] = t[i];
    }
  }
  friend ostream& operator<<(ostream& os, const Avector& v);
};
ostream& operator<<(ostream& os, const Avector& v){
  for(int i=0; i<v.len; i++){
    os << v.table[v.m[i]%N] << " ";
  }
  return os;
}

int main(int argc, char *argv[]){
  if(argc!=2){
    cout << "usage : ./avector pqr\n";
    return 1;
  }
  Avector v1(3); v1.print();
  Avector v2(2, 1, "xyz"); v2.print();
  Avector v3(v2); v3.print();
  cout << "v1 == v2 " << (v1 == v2) << endl;
  cout << "v3 == v2 " << (v3 == v2) << endl;
  v3 = v2 = v1;
  cout << "v1 : " << v1 << endl;
  v1.print();
  cout << "v2 : " << v2 << endl;
  v2.print();
  cout << "v3 : " << v3 << endl;
  v3. print();
  cout << "v3 != v2 " << (v3!=v2) << endl;
  v1[2] = 2;
  v2[0] = v1[2];
  v1.setTable(argv[1]);
  cout << "v1: " << v1 << "v2: " << v2 << "v3: "<<v3<<endl;
  v1.print();
  v2.print();
  v3.print();
  return 0;
}
