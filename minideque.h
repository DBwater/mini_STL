#ifndef MINIDEQUE_H
#define MINIDEQUE_H
#include<cstring>
#include<utility>
#include<algorithm>
#include<memory>
#include<stddef.h>
namespace miniSTL{
    template<typename T>
     class deque;
     template<typename T>
     class deque_iterator{ //deque的迭代器
     public:
          typedef deque_iterator<T>									iterator;
          typedef T*													pointer;
          typedef const T*											const_pointer;
          typedef T													value_type;
          typedef T&													reference;
          typedef const T&											const_reference;
          typedef size_t												size_type;
         typedef ptrdiff_t											difference_type;
          typedef T**													map_pointer;
         //friend class deque<T>;
         deque_iterator():first(NULL),current(NULL),last(NULL),node(NULL){}
         void set_new_node(map_pointer new_node){
          node = new_node;
          first = *node;
          last = first + buffer_size;
         }
         //void swap(iterator &it);

         //重载运算符
         reference operator *() { return *current; }
         const_reference operator *() const { return *current; }
         //pointer operator ->(){}
         //const_reference operator ->() const{}
         //iterator& operator ++(){}
         //iterator operator ++(int){}
         //iterator & operator --(){}
         //iterator operator --(int){}
         //bool operator ==(const iterator& it);
         //bool operator !=(const iterator& it);
         //difference_type operator-(const &iterator)const{
          //return static_cast<difference_type>()
         //}
         //template<class T>
            //friend deque_iterator<T> operator +(const deque_iterator<T>& it,typename deque_iterator<T>::difference_type n);
         //template<class T>
           // friend deque_iterator<T> operator +(typename deque_iterator<T>::difference_type n, const deque_iterator<T>& it);
         //template<class>
           // friend deque_iterator<T> operator -(const deque_iterator<T>& it,typename deque_iterator<T>::difference_type n);
         //template<class T>
           // friend deque_iterator<T> operator -(typename deque_iterator<T>::difference_type n, const deque_iterator<T>& it);
         //template<calss T>
            //friend typename deque_iterator::difference_type operator -(const deque<T> &lhs, const deque<T> &rhs);

     private:
         static const int buffer_size = 64;
         friend class deque<T>;
         T *first;
         T *current;
         T *last;
         map_pointer node;//指向中控器
     };
     template<typename T>
     class deque{
     public:
         typedef T													         	  value_type;
          typedef size_t												          size_type;
          typedef typename deque_iterator<T>::iterator			  iterator;
          typedef T&													          reference;
          typedef const T&											          const_reference;
         deque():start(),finish(),map(NULL),mapsize(0){alloc_map_and_buff(0);}
         deque(size_t n,const T& value){allocate_and_fill(n,value);}
         //deque(const deque &rhs){allocate_and_copy(deque.begin(),deque.end())};
         //template<typename InuputIterator>
         //deque(InputIterator b, InputIterator e){allocate_and_copy(b,e);}
         ~deque(){
          clear();
          data_alloc.deallocate(start.first, buffersize);
          map_alloc.deallocate(map,mapsize);
         }
         iterator begin()const {return start;}
         iterator end()const{return finish;}

         void push_back(const T& value);
         void push_front(const T& value);
         void pop_back();
         void pop_front();
         void push_back_aux(const T& value);
         void push_front_aux(const T& value);
         bool empty() const{return finish == start;}
         int size() const {return finish-start;}
         size_t get_mapsize(){return mapsize;}
         iterator insert(iterator p,T& value);
         template<typename InputIterator>
          void insert(iterator p,InputIterator b,InputIterator e);
         reference front(){return *(--end());}
         reference back() {return *(begin());}
         iterator erase(iterator p);
         iterator erase(iterator b,iterator e);
         void clear();
         bool mapisfull(){return finish.node - map >= mapsize;}
         void alloc_map_and_buff(size_t element_size);
         void reallocate_map(size_t need_map_size ,bool is_back_full);  //重新分配中控器,bool判断中控器是需要哪端的空间
         void full_front(size_t need_map_size = 1){
          if(start.node-need_map_size<map){
              reallocate_map(need_map_size,false);
          }
         }
         void full_back(size_t need_map_size = 1){
          if(finish.node-map+need_map_size >= mapsize){
              reallocate_map(need_map_size,true);
          }
         }

     private:
         typedef T**													map_pointer;
         typedef value_type*											pointer;
         iterator start;
         iterator finish;
         map_pointer map;
         size_t mapsize;
         static std::allocator<T> data_alloc;//缓冲器分配器
         static std::allocator<T*> map_alloc;//中控器分配器
         template<typename InputIterator>
         void allocate_and_copy(InputIterator b,InputIterator e);//分配并复制
         void allocate_and_fill(size_t n,const T& value);//分配并填充
         void destroy_and_deallocate();//释放空间
         void destroy(iterator p,const size_t  n){
          for(size_t i=0; i != n; i++){
              data_alloc.destroy(p.current+i);
          }
         }

         static const size_t buffersize = 64;
     };
     template<typename T>
         std::allocator<T> deque<T>::data_alloc;
     template<typename T>
         std::allocator<T*> deque<T>::map_alloc;
     template<typename T>
         const size_t deque<T>::buffersize;
     template<typename T>//初始化分配中控器和缓冲器
         void deque<T>::alloc_map_and_buff(size_t element_size){
          size_t need_map = element_size/buffersize+1;
          mapsize = (get_mapsize()>(need_map+2))?get_mapsize():need_map+2;
          map = map_alloc.allocate(mapsize);
          map_pointer map_start = map + (mapsize-need_map)/2;
          map_pointer map_finish = map_start + need_map - 1;
          for(map_pointer curr = map_start; curr <= map_finish;curr++){
              *curr = data_alloc .allocate(buffersize);
          }
          start.set_new_node(map_start);
          finish.set_new_node(map_finish);
          start.current = start.first;
          finish.current = finish.first + element_size%buffersize;
         }
     template<typename T>//重新分配中控器
         void deque<T>::reallocate_map(size_t need_map_size , bool is_back_full){
          size_t used_map = finish.node-start.node+1;
          size_t new_used_map = used_map+need_map_size;
          map_pointer new_map;
          if(mapsize > 2 * new_used_map){
              new_map = map+(mapsize-new_used_map)/2+(is_back_full? 0 : need_map_size);
              if(is_back_full){
               std::copy(start.node,finish.node+1,new_map);
              }
              else{
               std::copy_backward(start.node,finish.node+1,new_map);
              }
          }
          else{
              size_t new_mapsize = mapsize+(mapsize>need_map_size? mapsize : need_map_size)+2;
              map_pointer new_map = map_alloc.allocate(new_mapsize);
              new_map = new_map+(new_mapsize-need_map_size)/2+(is_back_full? 0:need_map_size);
              std::copy(start.node,finish.node+1,new_map);
              map_alloc.deallocate(map,mapsize);
              map = new_map;
              mapsize = new_mapsize;
          }
          start.set_new_node(new_map);
          finish.set_new_node(new_map+used_map-1);
         }
     template<typename T>
         void deque<T>::push_back_aux(const T& value){
          full_back();//判断中控器是否还有空间，没有则分配
          *(finish.node+1) = data_alloc.allocate(buffersize);
          finish.set_new_node(finish.node+1);
          finish.current = finish.first;
          data_alloc.construct(finish.current,value);
         }
     template<typename T>
         void deque<T>::push_front_aux(const T& value){
          full_front();
          *(start.node-1) = data_alloc.allocate(buffersize);
          start.set_new_node(start.node -1);
          start.current = start.last-1;
          data_alloc.allocate(start.current,value);
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
     template<typename T>
         void deque<T>::clear(){
          for(map_pointer curr = start.node+1; curr < finish.node; curr++){
              //destroy(static_cast<iterator>(*curr),buffersize);
              data_alloc.deallocate(*curr,buffersize);
          }
          if(start.node != finish.node){
              //destroy(finish.first,finish.current-finish.first);
              //destroy(start.current,start.last-start.current);
              data_alloc.deallocate(finish.first,buffersize);
          }
         // else
              //destroy(start.current,finish.current-start.current);
         }
}
#endif // MINIDEQUE_H

