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
            typedef T*            			iterator;
            typedef const T* 				const_iterator;
            typedef T&						reference;
            typedef	const T&				const_reference;
            typedef ptrdiff_t				refference_type;

            vector():first(nullptr),last(nullptr),allocateEnd(nullptr){}
            //vector(std::initializer_list<T> il);
            vector(const vector<T> &vec ){
                allocateAndCopy(vec.begin(),vec.end());
            }
            //vector(size_t, int n){}
            ~vector(){
                destroyAndDeallocate();
            }
            iterator insert(iterator p,size_t num,const T &value);
            iterator insert(iterator p,const T &value){return insert(p,1,value);}
            void push_back(const T &value);
            //void push_back(T &&t);
            void pop_back();
            iterator erase(iterator p);
            void erase(iterator b,iterator e);
            void clear(){earse(begin(),end());}
            size_t size() const{return last-first;}
            bool empty(){return last==first;}
            size_t capacity() const {return allocateEnd-first;}
            iterator begin() const{return first;}
            iterator end() const{return last;}
            void swap(vector &vec);
            /*T& operator[](size_t index){
                return *(first+index);
            }*/

            T& operator[](size_t index)const{
                return *(begin()+index);
            }

            T& back(){return *(last-1);}
            //friend operator ==(const vector<T> &lhs,const vector<T> &rhs);
            //friend opeartor !=(const vector<T> &lhs,const vector<T> &rhs);
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
           last =std::uninitialized_copy(b,e,first);
        }
        template<typename T>
            void vector<T>::destroyAndDeallocate(){
                while(last!=first)
                    alloc.destroy(--last);
            alloc.deallocate(first,allocateEnd-first);
            }
        template<typename T>
            void vector<T>::allocateFill(size_t num, const T &value){
                first = alloc.allocate(num*2);
                allocateEnd = first+num*2;
                alloc.construct(last++,num,value);
            }

        template<typename T>
            void vector<T>::push_back(const T &value){
                if(last!=allocateEnd){
                    alloc.construct(last++,value);
             }
                else{
                   insert(last,1,value);
                }
            }
        template<typename T>
            typename vector<T>::iterator
            vector<T>::insert(iterator p,size_t num,const T &value){
            if(num>0){
                if(static_cast<refference_type>(allocateEnd-last)>=num){
                    std::copy_backward(p,last,last+num);
                    std::uninitialized_fill_n(p,num,value);
                    last+=num;
                }
                else{
                    size_t len = size()+num;
                    iterator new_first = alloc.allocate(len*2);
                    iterator new_last = new_first;
                    iterator new_allocateEnd = new_first+len*2;
                    new_last = std::uninitialized_copy(first,p,new_last);
                    if(new_last==NULL)std::cout<<"ssss"<<std::endl;
                    std::uninitialized_fill_n(new_last,num,value);
                    std::cout<<num<<std::endl;
                    new_last += num;
                    std::cout<<*new_last<<std::endl;
                    std::cout<<"Sd"<<std::endl;
                    new_last = std::uninitialized_copy(p,last,new_last);
                    destroyAndDeallocate();
                    first = new_first;
                    last = new_last;
                    std::cout<<*first<<" "<<*last<<std::endl;
                    allocateEnd = new_allocateEnd;
                }
            }
            return nullptr;
        }
        template<typename T>
            typename vector<T>::iterator
            vector<T>::erase(iterator p){
                if(p+1 != last)
                    copy(p+1,last,p);
                last--;
                alloc.destroy(last);
                return p;
            }
        template<typename T>
            void vector<T>::erase(iterator b,iterator e){
                if(e != last)
                    copy(e,last,b);
                for(auto start=last-(e-b); start != last;start++)
                    alloc.destroy(start);
                last = last-(e-b);
                return ;
            }
        template<typename T>
            void vector<T>::pop_back(){
                last--;
                alloc.destroy(last);
            }
        template <typename T>
            void vector<T>::swap(vector<T> &vec){
                if(this!=&vec){
                    std::swap(first,vec.first);
                    std::swap(last,vec.last);
                    std::swap(allocateEnd,vec.allocateEnd);
                }
            }
}
#endif // MINIVECTOR_H
