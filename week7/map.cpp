#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



int numTestCases, n, m;
char arr[101][101];//[0~99][0~99]
char roomnumber='1';
vector<int> v;

bool check(int i,int j)
{
    if(i<0||i>99||j<0||j>99)    return false;
    if(arr[i][j]=='.') return true;
    return false;
}

int fill(int i, int j)
{
    int count=1;
    if(check(i-1,j))
    {
        arr[i-1][j]=roomnumber;
        count+=fill(i-1,j);
    }
    if(check(i,j+1))
    {
        arr[i][j+1]=roomnumber;
        count+=fill(i,j+1);
    }
    if(check(i+1,j))
    {
        arr[i+1][j]=roomnumber;
        count+=fill(i+1,j);
    }
    if(check(i,j-1))
    {
        arr[i][j-1]=roomnumber;
        count+=fill(i,j-1);
    }
    return count;
}



int main()
{
    cin >> numTestCases;
    for(int u=0; u<numTestCases; u++)
    {
        roomnumber='1';
        v.clear();
        cin >> m >> n ;
        int i,j;
        for(i=0; i<n; i++)
        {
            cin>>arr[i];
        }
        for(i=0; i<n; i++)
        {
            for(j=0; j<m; j++)
            {
                if(arr[i][j]=='+')
                {
                    continue;
                }
                else if(arr[i][j]=='.')
                {
                    arr[i][j]=roomnumber;
                    int count=fill(i,j);
                    v.push_back(count);
                    roomnumber++;
                }
            }
        }
        sort(v.begin(),v.end(),greater<int>());
        cout<<v.size()<<endl;
        for(int i=0; i<v.size(); i++)
        {
            cout<<v[i]<<' ';
        }
        cout<<endl;
    }

}
