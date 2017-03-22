#ifndef MINIDEQUE_H
#define MINIDEQUE_H
#include<cstring>
#include<utility>
template<typename T>
class deque;
template<typename T>
class deque_iterator{ //deque的迭代器
public:
    typedef T*			iterator;
    typedef T&			reference;
    typedef const T& 	const_referece;
    deque_iterator():first(nullptr),current(nullptr),last(nullptr),node(nullptr){}

    ~deque_iterator();
private:
    friend class deque<T>;
    T *first;
    T *current;
    T *last;
    T **node;
};
template<typename T>
class deque{
public:
    typedef typename deque_iterator<T>::iterator    iterator;
    deque():start(nullptr),finish(nullptr),map(nullptr){}
    deque(size_t n,const T& value){allocate_and_fill(n,value);}
    //deque(const deque &rhs){allocate_and_copy(deque.begin(),deque.end())};
    template<typename InuputIterator>
    deque(InputIterator b, InputIterator e){allocate_and_copy(b,e);}
    ~deque();
    iterator begin(){return start;}
    iterator end(){return finish;}

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void push_back_axu();
    bool empty() const{return finish == start;}
    bool size() const {return finish-start;}
    iterator insert(iterator p,T& value);
    template<typename InputIterator>
        void insert(iterator p,InputIterator b,InputIterator e);
    T& front();
    T& back();
    iterator erase(iterator p);
    iterator erase(iterator b,iterator e);
    void clear();
    bool mapisfull(){return finish.node - map >= mapsize;}
    void reallocate_map(size_t need_map_size = 1,bool is_back_full){  //重新分配中控器

    }
private:
    iterator start;
    iterator finish;
    T** map;
    size_t mapsize;
    static std::allocator<T> data_alloc;//缓冲器分配器
    static std::allocator<T*> map_alloc;//中控器分配器
    template<typename InputIterator>
    void allocate_and_copy(InputIterator b,InputIterator e);//分配并复制
    void allocate_and_fill(size_t n,const T& value);//分配并填充
    void destroy_and_deallocate();//释放空间
};
template<typename T>
    std::allocator<T> deque<T>::data_alloc;
template<typename T>
    std::allocator<T> deque<T*>::map_alloc;
template<typename T>
    void deque<T>::alloc_map_and_buff(size_t element_size){
        size_t need_map = element_size/buffsize+1;
    }
template<typename T>
    void push_back_aux(const T& value){
        if(full_back()){//判断中控器是否还有空间，没有则分配
            reallocate_map();
        }

    }
template<typename T>
    void push_back_aux(const T& value){

    }

template<typename T>
    void deque<T>::push_back(const T& value){
        if((finish.current+1) != finish.last){
            data_alloc.construct(finish.current++,value);
        }
        else{
            push_back_aux(value);//现有尾缓冲区已满，分配一个新的缓冲区
        }
    }
template<typename T>
    void deque<T>::push_front(const T& value){
        if((start.current != start.first)){
            data_alloc.construct(--start.current,value);
        }
        else{
            push_front_aux(value);//头缓冲区已满，分配一个新的缓冲区
        }
    }
#endif // MINIDEQUE_H

