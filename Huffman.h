//
// Created by vsx on 2024/3/2.
//

#ifndef HUFFMANCOMPRESSCPRO_HUFFMAN_H
#define HUFFMANCOMPRESSCPRO_HUFFMAN_H

#include <iostream>
#include "SqList.h"
#include "HuffmanTree.h"


//HuffmanTree Pointer���������SqList�淶
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

//�����ڱ������ɱ���ʱ�������
struct Code{
    std::string value;
};

class Huffman {
private:
    //����postTraversalʱ����ʱ����
    Code code;
    //����
    void build(const int *count,int length,HuffmanTree& root);
    //���ɱ���
    void generate(const HuffmanTree& root,std::string*& codes,int length);
    //������������ɱ���
    void postTraversal(const HuffmanTree* rootp,std::string*& codes,int length);
public:
    void buildAndGenerate(const int *count,int length,std::string*& codes);
};


#endif //HUFFMANCOMPRESSCPRO_HUFFMAN_H