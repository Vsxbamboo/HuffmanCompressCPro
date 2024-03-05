//
// Created by vsx on 2024/3/3.
//

#include "CodeBuffer.h"

CodeBuffer::CodeBuffer(std::fstream& file, Dictionary& dict):file(file),dict(dict){}
CodeBuffer::CodeBuffer(std::fstream &file, Dictionary &dict, int validbits):file(file),dict(dict),validbits(validbits){
    savedseekg=file.tellg();
    file.seekg(0,std::ios::end);
    filelength=file.tellg();
    file.seekg(savedseekg,std::ios::beg);
}
Status CodeBuffer::write(const std::string& strbin) {
//    std::cout<<"strbin"<<strbin<<std::endl;
    if(!file.is_open())
        return FILE_OPEN_ERROR;
    if(strbin.length()+strbuf.length()<=8){//小于一个char的长度的时候不写入
        strbuf.append(strbin);
    }else{//大于一个char的长度时，多次写入直到小于8
        //如果strbuf>=8，先连续写入，直到小于8
        strbuf+=strbin;
        while(strbuf.length()>8){
            io = strbuf2byte();
            file.write(&io, 1);
            strbuf = strbuf.substr(8,strbuf.length()-8);
        }

//            int remainLength = 8 - strbuf.length();
//            strbuf += strbin.substr(0, remainLength);
//
////        std::cout<<"write:"<<strbuf<<std::endl;
//
//            io = strbuf2byte();
//            file.write(&io, 1);
//            strbuf = strbin.substr(remainLength);

//        std::cout<<"afterwrite,strbuf:"<<strbuf<<" "<<std::endl;

    }
    return 0;
}

char CodeBuffer::strbuf2byte() const{
    char byte;
    byte=byte & 0b00000000;
    for(int i=0;i<8;i++){
        byte=byte<<1;
        if(strbuf[i]=='1'){
            byte=byte | 0b00000001;
        }
    }
    return byte;
}

std::string CodeBuffer::byte2str(char byte) const{
    std::string str;
    for(char i=0;i<8;i++){
        if((byte & 0b00000001) == 0b00000001){
            str='1'+str;
        }else if((byte & 0b00000001) == 0b00000000){
            str='0'+str;
        }
        byte=byte>>1;
    }
    return str;
}

void CodeBuffer::fillAndWrite() {
    std::string complement;
    for(int i=strbuf.length();i<8;i++){
        complement.push_back('0');
    }
    complement.push_back('0');
    write(complement);
}

Status CodeBuffer::read(char& byte) {
    //函数每次输出一个翻译出来的字节
    char readbuf;
    if(savedseekg<filelength){
        //不涉及validbits
        //如果strbuf耗尽，就读入
        if(strbuf.empty() || strpos==strbuf.length()){
            file.read(&readbuf,1);
            strbuf=byte2str(readbuf);
            strpos=0;
            savedseekg++;
        }
        //进行树查找，直到找到，找到后记录数据并返回
        Status result;
        do{
            result=dict.treeSearch(strbuf[strpos],byte);
            if(strpos<strbuf.length()-1){
                strpos++;
            }else{
                file.read(&readbuf,1);
                strbuf= byte2str(readbuf);
                strpos=0;
                savedseekg++;
            }
        }while(result!=NODE_FOUND);
        return 0;
    }else if(savedseekg==filelength){
        std::cout<<"arrive last line"<<std::endl;
        savedseekg++;
        //涉及最后一个字节的validbits
        //进行读入并截取substr，拼接到strbuf
        file.read(&readbuf,1);
        strbuf+=byte2str(readbuf).substr(0,validbits);
        //进行树查找，直到找到，找到后记录数据并返回
        Status result;
        do{
            result=dict.treeSearch(strbuf[strpos],byte);
            if(strpos<strbuf.length()-1){
                strpos++;
            }
        }while(result!=NODE_FOUND);
        return 0;
    }else if(savedseekg>filelength){
        Status result;
        do{
            result=dict.treeSearch(strbuf[strpos],byte);
            if(strpos<=strbuf.length()-1){
                strpos++;
            }else{
                return CB_EOF;
            }
        }while(result!=NODE_FOUND);
        return 0;
    }
    return CB_EOF;
}




