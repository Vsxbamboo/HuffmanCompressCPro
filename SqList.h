//
// Created by vsx on 2024/2/27.
//

#ifndef HUFFMANCOMPRESSCPRO_SQLIST_H
#define HUFFMANCOMPRESSCPRO_SQLIST_H

#include <iostream>

#define ELEM_NOT_FOUND (-2)

template <class T>
class SqList {//从高到低的顺序表
private:
    T *elem;
    int length;
    int size;
    void increaseSize(){
        T *p=elem;
        elem=new T[2*size];
        for(int i=0;i<length;i++)
            elem[i]=p[i];
        size*=2;
        delete[] p;
    }
    void decrease(){
        T *p=elem;
        elem=new T[size/2];
        for(int i=0;i<length;i++)
            elem[i]=p[i];
        size/=2;
        delete[] p;

    }
    int binSearch(T e) {
        int high = length - 1, low = 0;
        int mid;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (elem[mid] < e) {
                high = mid - 1; // 在左半边继续查找
            } else {
                low = mid + 1; // 在右半边继续查找
            }
        }
        return low; // 返回插入位置
    }


public:
    SqList(){
        length=0;
        elem=new T[64];
        size=64;
    }
    SqList(const int initsize){
        length=0;
        elem=new T[initsize];
        size=initsize;
    }
    ~SqList(){
        delete[] elem;
    }
    int getLength()const{
        return length;
    }
    void insert(const T &e){
        if(length==size){
            increaseSize();
        }
        int pos=binSearch(e);
        for(int i=length;i>pos;i--)
            elem[i]=elem[i-1];
        elem[pos]=e;
        length++;
    }
    void del(const int index){
        for(int i=index;i<length-1;i++){
            elem[i]=elem[i+1];
        }
        length--;
        if(length<size/4){
            decrease();
        }
    }
    int get(const int index,T &e)const{
        if(0<=index && index<length){
            e=elem[index];
            return 0;
        }else{
            return ELEM_NOT_FOUND;
        }
    }
    void show()const{
        std::cout<<"-----------------------------------------------------------------"<<std::endl;
        std::cout<<"SqList:"<<std::endl;
        for(int i=0;i<length;i++) {
            std::cout << elem[i] << "\t";
            if(i%8==7)
                std::cout<<std::endl;
        }
        std::cout<<std::endl;
        std::cout<<"-----------------------------------------------------------------"<<std::endl<<std::endl;
    }
};


#endif //HUFFMANCOMPRESSCPRO_SQLIST_H
