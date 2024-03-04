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

#define Status int //表示函数执行状态
#define FILE_OPEN_ERROR (-1) //文件打开错误
#define HEAD_DATA_ERROR (-2) //文件头函数参数错误
#define EMPTY_FILE_ERROR (-3) //空文件不支持错误
class Compress {
private:
    //初始化文件对象，并计算各个char取值的次数
    Status generateCount(std::fstream& readfile,CharCount& count);
    //根据字典翻译并输出文件
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

    //对外的压缩接口
    Status compress(const std::string& readfilepath,const std::string& writefilepath);
    //对外的解压接口
    Status decompress(std::string readfilepath,std::string writefilepath);
    //评估函数，用来计算压缩率等
    void evaluate();
};


#endif //HUFFMANCOMPRESSCPRO_COMPRESS_H
