//
// Created by vsx on 2024/3/3.
//

#include "EntryInFile.h"
EntryInFile::EntryInFile() {
    byte=0;
}

char *EntryInFile::getCode() const {
    char *code=new char[(this->code.length()-1)/8+1];
    std::string temp=this->code;
    while(temp.length()%8!=0){
        temp.push_back('0');
    }
    char byte=0;
    for(int i=0;i<temp.length();i++){
        if(temp[i]=='1'){
            byte=byte | 1;
        }
        if(i%8==7){
            code[i/8]=byte;
            byte=0;
        }else{
            byte=byte<<1;
        }

    }
    return code;
}

int EntryInFile::getBits() const {
    return code.length();
}

std::string EntryInFile::visual() const {
    std::string temp=code;
    while(temp.length()%8!=0){
        temp.push_back('0');
    }
    return code;
}

int EntryInFile::getCodeLength() const {
    return (this->code.length()-1)/8+1;
}

void EntryInFile::setCode(char *code, char bits) {
    this->code.clear();
    int realbits=bits-CHAR_MIN+1;
    char byte;

    for(char i=0;i<realbits;i++){
        if(i%8==0)
            byte=code[i/8];
        if((byte & 0b10000000) == 0b10000000){
            this->code.push_back('1');
        }else if((byte & 0b10000000) == 0b00000000){
            this->code.push_back('0');
        }
        byte=byte<<1;
    }


}


