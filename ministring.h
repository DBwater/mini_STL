#ifndef MINISTRING_H
#define MINISTRING
#include<cstddef>
#include<memory>
//#include<iostream>
using  namespace std;
namespace miniSTL{
    class string{
    public:    
        string()=default;
        string(const string &_str);
        string(const string &_str, size_t pos, size_t len);
        string(size_t n, char c);
        string(const char* s);
        string& operator =(const string &_str);
        string& operator =(const char *c);
        //string& operator +=(const string &_str);
        //string& operator +=(const char*);
        //string& operator >>(istream in,string &str);
        //string& operator <<(ostream out, const string &_str);
        //char& operator[](size_t n);
        //friend string operator+(const &_str1,const &_str2);
        char *begin(){return first;}
        char *end(){return last;}
        size_t size() const {return last-first;}
        size_t length(){return last-first;}
        size_t capacity(){return allocateEnd-first;}
        ~string();
    private:
    char *first;
    char *last;
    char *allocateEnd;
    allocator<char> alloc;
    void allocateAndCopy(const char *start,const char *finish);
    void allocateAndFill(size_t n,char c);
    void destroyAndDeallocate();
    };
}
#endif // MINISTRING_H

