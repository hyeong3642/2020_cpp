#include <iostream>
using namespace std;

int main(void){
  int numTestCases;
  cin >> numTestCases;

  for(int i=0; i<numTestCases; i++){
    int k =0;
    cin >> k;
    char a[k][k];
    int h = k/2;
    int tmp = 0;

    for(int n=0; n<k; n++){
      for(int j=0; j<k; j++){
        a[n][j] = '-';
      }
    }

    for(int u=0; u<h; u++){
        for(int i=tmp; i<k-tmp; i++){
          if(u%2==0){
            if(i%2==0){
              a[u][i] = '*';
            }
            else{
              a[u][i] = '+';
            }
          }
          else{
            if(i%2==0){
              a[u][i] ='+';
            }
            else{
              a[u][i] ='*';
            }
          }
        }
        tmp += 1;
      }
    a[h][h] = '*';
    tmp -=1;
    for(int u=h+1; u<k; u++){
        for(int i=tmp; i<k-tmp; i++){
          if(u%2==0){
            if(i%2==0){
              a[u][i] = '*';
            }
            else{
              a[u][i] = '+';
            }
          }
          else{
            if(i%2==0){
              a[u][i]='+';
            }
            else{
              a[u][i] = '*';
            }
          }

        }
        tmp-=1;
      }

    for(int n=0; n<k; n++){
      for(int j=0; j<k; j++){
        cout <<a[n][j];
      }
      cout << endl;
    }

    }

  }
