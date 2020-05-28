#include <iostream>
using namespace std;

int main(void){
  int numTestCases;
  cin >> numTestCases;
  int k;

  for(int i=0; i<numTestCases; i++){
    int k = 0;
    cin >> k;
    int h = k/2;
    char g[k];

    for (int j=0; j<k; j++){
      g[j] = '.';
    }
    for (int n=k; n>h+1; n--){
      g[h] = 'I';
      g[n-1] = '*';
      for (int u=0; u<k; u++){
        cout << g[u];
      }
      for(int v =0; v<k; v++){
        g[v] = '.';
      }
      cout << endl;
    }
    for (int o = 0; o<h; o++){
      cout << '+';
    }
    cout <<'O';
    for (int t = 0; t<h; t++){
      cout << '+';
    }
    cout << endl;
    for (int p=h; p>0; p--){
      g[p-1] = '*';
      g[h] = 'I';
      for (int y=0; y<k; y++){
        cout << g[y];
      }
      for(int e =0; e<k; e++){
        g[e] = '.';
      }
      cout <<endl;
    }
}
}
