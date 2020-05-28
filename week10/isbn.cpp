#include "cstring"
#include <iostream>
#include <vector>
using namespace std;

#ifndef _MY_ISBN_H_
#define _MY_ISBN_H_
const int max_length = 256;
class MyISBN
{
public:
 // constructors
 MyISBN ();
 MyISBN (char isbn_number[]);
 // utility functions
 bool isCorrectNumber() const;
private:
 char isbn[max_length+11];
 bool isSyntaxValid() const;
 bool isCheckSumValid() const;
};
#endif // _MY_ISBN_H_


// constructors
MyISBN::MyISBN ()
{
isbn[0] = '\0';
}
MyISBN::MyISBN (char isbn_number[])
{
strcpy(isbn, isbn_number);
}
// utility functions
bool MyISBN::isCorrectNumber() const
{
if (isSyntaxValid() && isCheckSumValid())
return true;
else
return false;
}
vector <char> check2;
// private functions
bool MyISBN::isSyntaxValid() const
{vector<char> first;
  vector <char> second;
  vector <char> third;
  vector <char> fourth;
  vector <char> check;
  int i =0;
  while(1){
    if(isdigit(isbn[i])){
      first.push_back(isbn[i]);
      check.push_back(isbn[i]);
      i++;
    }
    else if(isbn[i]=='-'){
      check.push_back(isbn[i]);
      i++;
      break;
    }
    else{
      i++;
      return 0;
    }
  }
  while(1){
    if(isdigit(isbn[i])){
      second.push_back(isbn[i]);
      check.push_back(isbn[i]);
      i++;
    }
    else if(isbn[i]=='-'){
      check.push_back(isbn[i]);
      i++;
      break;
    }
    else{
      i++;
      return 0;
    }
  }
  while(1){
    if(isdigit(isbn[i])){
      third.push_back(isbn[i]);
      check.push_back(isbn[i]);
      i++;
    }
    else if(isbn[i]=='-'){
      check.push_back(isbn[i]);
      i++;
      break;
    }
    else{
      i++;
      return 0;
    }
  }
  check.push_back(isbn[i]);
  fourth.push_back(isbn[i]);
  if(isbn[i+1]=='-'||isdigit(isbn[i+1])){
    return 0;
  }
  check2 = check;

  int count =0;
  for(int u=0; u<check.size(); u++){
    if(check[u]=='-'){
      count +=1;
    }
  }
  if(count !=3){
    return 0;
  }

  if(first.size()<1 || first.size()>5){
    return 0;
  }
  else if(second.size()<1 || second.size()>7){
    return 0;
  }
  else if(third.size()<1 || third.size()>6){
    return 0;
  }
  else if(fourth.size()!=1){
    return 0;
  }
  else if((first.size()+second.size()+third.size())>9){
    return 0;
  }
  return 1;
}
bool MyISBN::isCheckSumValid() const
{
  for(int i=0; i<check2.size()-1; i++){
    if(check2[i]=='-'){
      check2.erase(check2.begin()+i);
    }
  }
  int result =0;
  int multi =10;
  for(int j=0; j<9; j++){
    result += (check2[j]-48) * multi;
    multi -=1;
  }

if(check2[check2.size()-1] == 'X'){
  if((result + 10)%11==0){
    return 1;
  }
  else{return 0;}
}
else{
  if(((check2[check2.size()-1]-48)+result)%11==0){
    return 1;
  }
  else{
    return 0;
  }
}
}


int main()
{
 int numTestCases;
 cin >> numTestCases;
 for (int i=0; i<numTestCases; i++)
 {
 char isbn[max_length+1];
 cin >> isbn;
 MyISBN bookNumber(isbn);
 if(bookNumber.isCorrectNumber())

 cout << "1" << endl;
 else
 cout << "0" << endl;
 }
}
