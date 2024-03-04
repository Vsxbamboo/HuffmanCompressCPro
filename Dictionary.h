//
// Created by vsx on 2024/3/2.
//

#ifndef HUFFMANCOMPRESSCPRO_DICTIONARY_H
#define HUFFMANCOMPRESSCPRO_DICTIONARY_H

#include <string>
#include <iostream>
#include "HuffmanTree.h"

#define Status int
#define DICTSIZE 256
#define NODE_FOUND 1
#define NODE_UNFOUND 0
#define NODE_NOT_EXIST (-3)
#define ROOT_NOT_INIT (-1)
#define DICTIONARY_BIT_ERROR (-2)
/*
 * Dictionary需要实现两方面的功能:
 *  1.在编码时char->string，建议使用string数组
 *  2.在解码时string->char，建议使用树结构
 *  3.在文件中保存的时候还是数组结构比较合适
 * */
class Dictionary {
private:
    int usage;//字典使用率
    std::string* codes;
    HuffmanTree* root;
    HuffmanTree* pos;
    Status addBranch(int index,const std::string& strbin);
    char strbin2byte(const std::string& strbin)const;
public:
    Dictionary();
    //根据string数组codes生成字典对象
    void codes2dict(std::string*& codes,int length);
    //编码时根据byte搜索
    std::string getbyByte(char byte)const;
    //解码时按位在树中查找
    Status treeSearch(char bit,char& byte);
};


#endif //HUFFMANCOMPRESSCPRO_DICTIONARY_H
