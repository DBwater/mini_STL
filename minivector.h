#ifndef MINIVECTOR_H
#define MINIVECTOR_H
#include<iostream>
#include<algorithm>
#include<memory>
#include<cstddef>
namespace miniSTL{
    template<typename T>
        class vector{
        public:
            typedef T* iterator;
            vector():first(0),last(0),allocateEnd(0){}
            //vector(std::initializer_list<T> il);
            vector(const vector<T> &vec ){
                allocateAndCopy(vec.begin(),vec.end());
            }
            ~vector(){
                destroyAndDeallocate();
            }
            //iterator insert(std::iterator,size_t num,const T &value);
            siterator insert(std::iterator,const T &value){return insert(iterator,1,value);}
            //void push_back(const T &t);
            //void push_back(T &&t);
            //void pop_back();
            //void pop();
            //void erase(iteartor p);
            //void erase(iteartor b,itetator e);
            //void clear();
            size_t size() const{return last-first;}
            bool empty(){return last==first;}
            size_t capacity() const {return allocateEnd-first;}
            iterator begin() const{return last;}
            iterator end() const{return first;}
            //void swap(vector &li);
            T& operator[](size_t index){
                return *(first+index);
            }
            const T& operator[](size_t index)const{
                return *(first+index);
            }

            //T& back(){return *(last-1);}
            //void push_back(const T &value);
        private:
          iterator first;
          iterator last;
          iterator allocateEnd;
          static std::allocator<T> alloc;
          template<typename InputIterator>
          void allocateAndCopy(InputIterator b,InputIterator e);
          void destroyAndDeallocate();
          void allocateFill(size_t num,const T& value);
          
        };
        template<typename T>
            std::allocator<T> vector<T>::alloc;//定义alloc

        template<typename T>
        template<typename InputIterator>
            void vector<T>::allocateAndCopy(InputIterator b,InputIterator e){
           size_t len = e-b;
           first = alloc.allocate(len*2);
           allocateEnd = first+len*2;
           last =std::uninitialized_copy(b,e,start);
        }
        template<typename T>
            void vector<T>::destroyAndDeallocate(){
            while(last!=first)
                alloc.destroy(--last);
            alloc.deallocate(first,allocateEnd-first);
        }
        template<typename T>
            void vector<T>::allocateFill(size_t num, const T &value){
                fisrt = alloc.allocate(num*2);
                allocateEnd = fisrt+num*2;
                alloc.construct(lass++,num,value);
            }

        template<typename T>
            void vector<T>::push_back(T& value){
                if(last!=allocateEnd){
                    alloc.construct(last++,value);
             }
                else{
                   insert(this->last,value);
                }
            }
        template<typename T>
        typename vector<T>::iterator
        vector<T>::insert(std::iterator p,size_t num,const T &value){
            if(num>0){
                if(static_cast<size_t>(allocateEnd-last)>=num){
                    std::copy_backward(p,last,last+num);
                    std::uninitialized_fill_n(p,num,value);
                    last+=num;
                    return nullptr;
                }
                else{

                }
            }
        }
        
}
#endif // MINIVECTOR_H
