#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <bitset>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;
  for(int i=0; i<numTestCases; i++){
    int onetwo;
    cin >> onetwo;
    if(onetwo ==1){
      vector<long long int> v;
      string tmp;
      string input;
      cin >> input;
      int j=0;
      while(input.at(j)!='.'){
        tmp += input.at(j);
        j++;
      }
      j++;
      int tmpnum = stoi(tmp);
      while(tmpnum !=0){
        v.insert(v.begin(),tmpnum%2);
        tmpnum /= 2;
      }
      while(v.size()!=8){
        v.insert(v.begin(), 0);
      }

      tmp = "";
      while(input.at(j)!='.'){
        tmp += input.at(j);
        j++;
      }
      j++;
      tmpnum = stoi(tmp);
      while(tmpnum !=0){
        v.insert(v.begin()+8,tmpnum%2);
        tmpnum /= 2;
      }
      while(v.size()!=16){
        v.insert(v.begin()+8, 0);
      }

      tmp = "";
      while(input.at(j)!='.'){
        tmp += input.at(j);
        j++;
      }
      j++;
      tmpnum = stoi(tmp);
      while(tmpnum !=0){
        v.insert(v.begin()+16,tmpnum%2);
        tmpnum /= 2;
      }
      while(v.size()!=24){
        v.insert(v.begin()+16, 0);
      }

      tmp = "";
      while(j<input.size()){
        tmp += input.at(j);
        j++;
      }
      j++;
      tmpnum = stoi(tmp);
      while(tmpnum !=0){
        v.insert(v.begin()+24,tmpnum%2);
        tmpnum /= 2;
      }
      while(v.size()!=32){
        v.insert(v.begin()+24, 0);
      }
      long long int result =0;
      int d =31;
      for(int c=0; c<32; c++){
        result += (v[c] * pow(2,d));
        d -=1;
      }
      cout << result << endl;

  }
    else{
      long long int input;
      cin >> input;
      int one;
      int two;
      int three;
      int four;
      one = (input>>24) &255;
      two = (input>>16)&255;
      three =(input>>8)&255;
      four = input&255;
      cout << one << "." << two << "." << three <<"." <<four << endl;


    }
  }
}
