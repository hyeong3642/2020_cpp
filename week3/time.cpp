#include <iostream>
using namespace std;

int main(void){
  int numTestCases;

  cin >> numTestCases;
    for(int i=0; i<numTestCases; i++){
      int H,M,S,h,m,s;
      int sumhh = 0;
      int summm = 0;
      int sumss = 0;
      int day = 0;
      int k = 0;
      cin >> k;
      for(int j=0; j<k; j++){
        cin >> H;
        cin >> M;
        cin >> S;
        cin >> h;
        cin >> m;
        cin >> s;
        int sumh = h - H;
        int summ = m - M;
        int sums = s - S;

        while(summ < 0){
          sumh -= 1;
          summ += 60;
        }
        while(sums< 0){
          summ -= 1;
          sums += 60;
        }
        sumhh += sumh;
        summm += summ;
        sumss += sums;
      }
      while(sumss>=60){
        summm +=1;
        sumss -= 60;
      }
      while (summm >= 60){
        sumhh += 1;
        summm -= 60;
      }
      while (sumhh >=24){
        day +=1;
        sumhh -= 24;
      }
      cout << day << " " << sumhh << " " << summm << " "<< sumss << endl;
    }
  }
