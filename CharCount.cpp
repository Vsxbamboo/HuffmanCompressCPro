//
// Created by vsx on 2024/3/2.
//

#include "CharCount.h"

CharCount::CharCount(){
    count=new int[256]{0};
};

void CharCount::plus(const char& byte) {
    count[byte-CHAR_MIN]++;
}

int CharCount::get(const char& byte) const{
    return count[byte-CHAR_MIN];
}

int* CharCount::getIntArray() const{
    return count;
}


void CharCount::show() {
    std::cout<<"CharCount:"<<std::endl<<"-----------------------------------------------------------------"<<std::endl;
    for(int i=0;i<256;i++){
        std::cout<<i+CHAR_MIN<<"\t:"<<count[i]<<"\t|";
        if(i%4==3)
            std::cout<<std::endl<<"-----------------------------------------------------------------"<<std::endl<<std::endl;
    }
}

