//
// Created by vsx on 2024/3/2.
//

#include "Dictionary.h"


void Dictionary::codes2dict(std::string *&codes,const int length) {
    //建树实现treeSearch

    //复制codes,实现getbyByte
    for(int i=0;i<length;i++){
        this->codes[i]=codes[i];
        if(!codes[i].empty()){
            addBranch(i,codes[i]);
        }
    }

    pos=root;
    //单测输出
    std::cout<<std::endl<<"-----------------------------------------------------------------"<<std::endl;
    std::cout<<"Dictionary:"<<std::endl;
    for(int i=0;i<length;i++){
        std::cout<<i+CHAR_MIN<<":"<<this->codes[i]<<"\t";
        if(i%4==3){
            std::cout<<std::endl;
        }
    }
    std::cout<<"-----------------------------------------------------------------"<<std::endl;

    std::cout<<"DictHuffmanTree:"<<std::endl;
    (*root).levelOrderTraversal();
}


Dictionary::Dictionary() {
   codes=new std::string[DICTSIZE];
   root=new HuffmanTree{-1,0, nullptr, nullptr, nullptr};
   pos=nullptr;
}

std::string Dictionary::getbyByte(char byte) const {
    return codes[byte-CHAR_MIN];
}

Status Dictionary::treeSearch(char bit, char &byte) {
    if(root==nullptr){
        return ROOT_NOT_INIT;
    }
    if(bit=='0'){
        pos=pos->lchild;
    }else if(bit=='1'){
        pos=pos->rchild;
    }else{
        return DICTIONARY_BIT_ERROR;
    }
    if(pos==nullptr){
        return NODE_NOT_EXIST;
    }
    if(pos->id!=-1){
        byte=pos->id+CHAR_MIN;
        pos=root;
        return NODE_FOUND;
    }

    return NODE_UNFOUND;
}

Status Dictionary::addBranch(const int index,const std::string &strbin) {
    HuffmanTree *p;
    p=root;
    for(int i=0;i<strbin.length();i++){
        if(strbin[i]=='0'){
            if(p->lchild==nullptr){
                p->lchild=new HuffmanTree{-1,0,p,nullptr, nullptr};
            }
            p=p->lchild;
        }else if(strbin[i]=='1') {
            if (p->rchild == nullptr) {
                p->rchild = new HuffmanTree{-1, 0, p, nullptr, nullptr};
            }
            p = p->rchild;
        }else{
            return DICTIONARY_BIT_ERROR;
        }
    }
    p->id=index;
    return 0;
}

char Dictionary::strbin2byte(const std::string &str) const {
    char byte=0;
    for(int i=0;i<str.length();i++){
        byte=byte<<1;
        if(str[i]=='1'){
            byte=byte | 0b00000001;
        }
    }
    return byte;
}
