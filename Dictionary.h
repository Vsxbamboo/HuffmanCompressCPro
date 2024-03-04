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
 * Dictionary��Ҫʵ��������Ĺ���:
 *  1.�ڱ���ʱchar->string������ʹ��string����
 *  2.�ڽ���ʱstring->char������ʹ�����ṹ
 *  3.���ļ��б����ʱ��������ṹ�ȽϺ���
 * */
class Dictionary {
private:
    int usage;//�ֵ�ʹ����
    std::string* codes;
    HuffmanTree* root;
    HuffmanTree* pos;
    Status addBranch(int index,const std::string& strbin);
    char strbin2byte(const std::string& strbin)const;
public:
    Dictionary();
    //����string����codes�����ֵ����
    void codes2dict(std::string*& codes,int length);
    //����ʱ����byte����
    std::string getbyByte(char byte)const;
    //����ʱ��λ�����в���
    Status treeSearch(char bit,char& byte);
};


#endif //HUFFMANCOMPRESSCPRO_DICTIONARY_H
