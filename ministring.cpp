#include "ministring.h"
#include<cstring>
namespace miniSTL{
    string::string(const string &_str){
        allocateAndCopy(_str.first,_str.last);
    }

    string::string(const string &_str, size_t pos, size_t len){
        size_t _strlen=(_str.last-_str.first);
        if(pos>(_strlen-1)){
            //cerr<<"please check parameter"<<endl;
            exit(1);
        }
        allocateAndCopy(_str.first+pos,_str.last+pos+len);
    }

    string::string(size_t n, char c){
        allocateAndFill(n,c);
    }

    string::string(const char *s){
        allocateAndCopy(const_cast<char*>(s),const_cast<char*>(s)+strlen(s));
    }

    string& string::operator= (const string& _str){
            if(this!=&_str){
                destroyAndDeallocate();
                allocateAndCopy(_str.first,_str.last);
            }
            return *this;
    }

    string& string::operator=(const char *s){
        destroyAndDeallocate();
        allocateAndCopy(s,s+strlen(s));
        return *this;
    }
    string::~string(){
     destroyAndDeallocate();
    }
    void string::allocateAndCopy(const char *start,const char *finish){
        first = alloc.allocate((start-finish)*2);
       // allocateEnd = first+(start-finish)*2;
        last = uninitialized_copy(start,finish,first);
    }
    void string::allocateAndFill(size_t n,char c){
       allocateEnd = first+n*2;
       last = uninitialized_fill_n(first,n,c);
    }
    void string::destroyAndDeallocate(){
        auto finish = last;
         while(first!=last)
             alloc.destroy(--last);
         alloc.deallocate(first,finish-first);
    }
}
