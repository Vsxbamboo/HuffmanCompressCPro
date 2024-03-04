//
// Created by vsx on 2024/3/2.
//

#ifndef HUFFMANCOMPRESSCPRO_COMPRESS_H
#define HUFFMANCOMPRESSCPRO_COMPRESS_H

#include <string>
#include <iostream>
#include <fstream>
#include "Dictionary.h"
#include "CharCount.h"
#include "Huffman.h"
#include "EntryInFile.h"
#include "CodeBuffer.h"

#define Status int //��ʾ����ִ��״̬
#define FILE_OPEN_ERROR (-1) //�ļ��򿪴���
#define HEAD_DATA_ERROR (-2) //�ļ�ͷ������������
#define EMPTY_FILE_ERROR (-3) //���ļ���֧�ִ���
class Compress {
private:
    //��ʼ���ļ����󣬲��������charȡֵ�Ĵ���
    Status generateCount(std::fstream& readfile,CharCount& count);
    //�����ֵ䷭�벢����ļ�
    Status translateAndWrite(Dictionary& dict,std::fstream& readfile,std::fstream& writefile);
    Status getValidBits(std::fstream& readfile,const Dictionary& dict,int& validbits)const;
    void getEntryLength(const Dictionary& dict,int& entryLength)const;
    void dict2EIF(const Dictionary& dict,EntryInFile*& eif)const;
    void EIF2dict(const EntryInFile* eif,const int entryLength,Dictionary& dict);
    char strbin2byte(const std::string& str)const;
    std::string byte2strbin(char code,const char bits)const;
    Status writeHead(std::fstream& writefile,int validbits,int entryLength,const EntryInFile* eif);
    Status readHead(std::fstream& readfile,int& validbits,int& entryLength,EntryInFile*& eif);
    Status writeBody(std::fstream& readfile,Dictionary& dict,std::fstream& writefile);
    Status readBody(std::fstream& readfile,Dictionary& dict,int validbits,std::fstream& writefile);
public:

    //�����ѹ���ӿ�
    Status compress(const std::string& readfilepath,const std::string& writefilepath);
    //����Ľ�ѹ�ӿ�
    Status decompress(std::string readfilepath,std::string writefilepath);
    //������������������ѹ���ʵ�
    void evaluate();
};


#endif //HUFFMANCOMPRESSCPRO_COMPRESS_H
