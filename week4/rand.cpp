#include <iostream>
#include <cstdlib>
using namespace std;
#include <ctime>

int main(int argc, char *argv[]){
  if (argc != 2){
    cout << "usage: ./rand n\n";
    return -1;
  }
  int s = atoi(argv[1]);
  srand(s);
  for (unsigned int i=0; i<10; i++){
    int dice = rand()%6 +1;
    cout << dice << " ";
  }
  cout << endl;
}
