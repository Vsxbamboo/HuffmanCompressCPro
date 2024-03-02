//
// Created by vsx on 2024/2/27.
//

#ifndef HUFFMANCOMPRESSCPRO_HUFFMAN_H
#define HUFFMANCOMPRESSCPRO_HUFFMAN_H

#include <iostream>
#include <string.h>
#include "SqList.h"
class Huffman {
private:
    struct HuffmanTree{
        int id;
        int weight;
        HuffmanTree *parent,*lchild,*rchild;
        bool operator>(const HuffmanTree& rt)const{
            if(this->weight>rt.weight)
                return true;
            else
                return false;
        }
        bool operator<(const HuffmanTree& rt)const{
            if(this->weight<rt.weight)
                return true;
            else
                return false;
        }
        HuffmanTree& operator=(const HuffmanTree& rt) {
            if(this==&rt)
                return *this;
            this->id=rt.id;
            this->weight=rt.weight;
            this->parent=rt.parent;
            this->lchild=rt.lchild;
            this->rchild=rt.rchild;
            return *this;
        }
    };
    struct HTP{
        HuffmanTree* p;
        bool operator<(HTP &rp)const{
            return *(this->p)<*(rp.p);
        }
        bool operator>(HTP &rp)const{
            return *(this->p)>*(rp.p);
        }
        HTP& operator=(const HTP &rp){
            if(this==&rp)
                return *this;
            this->p=rp.p;
            return *this;
        }
    };
    struct Word{
        char *value;
        int length;
    }word;
    SqList<HTP> treelist;
    HTP root;
    char **code;
public:
    Huffman();
    ~Huffman();
    void closeTree(HuffmanTree *rootp);
    void build(int count[],int length);
    //build用于建树，接收count数组，获取一组(数组序号:次数)关系，根据这个关系建树

    void generate(char** &code,int length);//code数组用来接收编码信息
    //generate用于根据树生成表，根据build中count数组的序号把编码以字符串的形式写入到code数组中，

    void traversal(int length);
    //traversal用于遍历树

    void subtraversal(const HuffmanTree *rootp);
    //subtraversal是traversal的子函数，用来递归遍历树

};


#endif //HUFFMANCOMPRESSCPRO_HUFFMAN_H
