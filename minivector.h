#ifndef MINIVECTOR_H
#define MINIVECTOR_H
#include<iostream>
#include<memory>
#include<cstddef>
namespace miniSTL{
    template<typename T>
        class vector{
        public:
            vector();
            vector(std::initializer_list<T> il);
            vector(const vector<T> &ve );
            void push_back(const T &t);
            void push_back(T &&t);
            void pop_back();
            void pop();
            void erase();
            size_t size() const;
            bool empty();
            begin();
            end();
            T& operator[](size_t i);
        private:
           vector<T> *element;
        };
}
#endif // MINIVECTOR_H
