#include <iostream>
#include <stack>
using namespace std;

int main(){
  int numTestCases;
  cin >> numTestCases;

  for(int i=0; i<numTestCases; i++){
    string gualho;
    cin >> gualho;
    int result =1;
    stack<char> gual;

    for(int j=0; j<gualho.length(); j++){
      if(gualho[j]=='('){
        gual.push(gualho[j]);
      }
      else if(gualho[j]=='{'){
        gual.push(gualho[j]);
      }
      else if(gualho[j]=='['){
        gual.push(gualho[j]);
      }
      else if(gualho[j]==')'){
        if(gual.empty()==true){
          result =0;
          break;
        }
        else if(gual.top()=='('){
          gual.pop();
        }
        else{
          result =0;
          break;
        }
      }
      else if(gualho[j]=='}'){
        if(gual.empty()==true){
          result =0;
          break;
        }
        else if(gual.top()=='{'){
          gual.pop();
        }
        else{
          result =0;
          break;
        }
      }
      else if(gualho[j]==']'){
        if(gual.empty()==true){
          result =0;
          break;
        }
        else if(gual.top()=='['){
          gual.pop();
        }
        else{
          result =0;
          break;
        }
      }
    }
    if(gual.empty()==false){
      result =0;
    }
    cout << result << endl;

  }
}
