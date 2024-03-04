//
// Created by vsx on 2024/3/2.
//

#ifndef HUFFMANCOMPRESSCPRO_HUFFMAN_H
#define HUFFMANCOMPRESSCPRO_HUFFMAN_H

#include <iostream>
#include "SqList.h"
#include "HuffmanTree.h"


//HuffmanTree Pointer，用来配合SqList规范
struct HTP{
    HuffmanTree* p;
    bool operator<(const HTP& rHTP)const{
        return *p<*rHTP.p;
    }
    bool operator>(const HTP& rHTP)const{
        return *p>*rHTP.p;
    }
    HTP& operator=(const HTP& rHTP){
        if(this==&rHTP)
            return *this;
        p=rHTP.p;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os,const HTP& htp){
        os<<htp.p->id<<":"<<htp.p->weight;
        return os;
    }
};

//用于在遍历生成编码时保存编码
struct Code{
    std::string value;
};

class Huffman {
private:
    //用作postTraversal时的临时变量
    Code code;
    //建树
    void build(const int *count,int length,HuffmanTree& root);
    //生成编码
    void generate(const HuffmanTree& root,std::string*& codes,int length);
    //先序遍历并生成编码
    void postTraversal(const HuffmanTree* rootp,std::string*& codes,int length);
public:
    void buildAndGenerate(const int *count,int length,std::string*& codes);
};


#endif //HUFFMANCOMPRESSCPRO_HUFFMAN_H