//#include "ministring.h"
#include<iostream>
#include<string>
using namespace std;
int main()
{
   string s("Asd");
   string s1(s);
   string s2(10,'a');
   string s3="hello";
   string s4=s1;
   cout<<s.length()<<" "<<s1.length()<<" "<<s2.length()<<" "<<s3.length()<<" "<<s4.length()<<endl;
}
