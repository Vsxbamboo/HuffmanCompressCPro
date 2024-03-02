//
// Created by vsx on 2024/2/27.
//

#ifndef HUFFMANCOMPRESSCPRO_COMPRESS_H
#define HUFFMANCOMPRESSCPRO_COMPRESS_H

#include <fstream>
#include "Huffman.h"

/*
 * 压缩类
 * 让外部只需要调用一个函数就可以完成压缩功能
 * 形如：Compress.compress(<source file path>,<destination file path>);
 * 即: int compress(char *readfilepath,char *writefilepath);
 * compress函数中通过调用其他函数来完成功能，先open,再建立压缩表，最后write()。
 *
 *
 * */

/*
 * 字典结构
 * 对应char值 编码长度 编码+补0
 * 优化后的解码字典结构按编码长度排列
 * */

/*
 * 文件头部结构
 * 编码最后一个字节有效位数
 * 字典数组
 * */

#define FILE_NOT_FOUND (-2)
#define FILE_OPEN_FAILURE (-3)
#define FILE_NOT_READ (-4)
#define FILE_EMPTY_ERROR (-5)
#define TRANBUF_LENGTH (sizeof(char)*8)
class Compress {
private:

    std::fstream readfile;//待压缩的读取文件对象
    std::fstream writefile;//压缩后的写入文件对象
    std::streampos filelength;//待压缩文件长度
    Huffman huffman;

    void str2byte(char* str,char& byte);
    //用于将8位0,1字符串转换成char类型，方便write()的写入
public:
    Compress();
    ~Compress();


    int open(char *filepath);
    //open函数需要验证文件存在和初始化对象readfile，同时初始化后面循环中用得到的filelength

    int compress(std::string readfilepath,std::string writefilepath);
    //compress是最后的综合体，交由外部调用

    int write(char *filepath,char **code);
    //write负责压缩后的文件翻译与写入

    int evaluate();
    //evaluate负责调试输出，例如文件是否正确读取的判断、压缩率的计算
};


#endif //HUFFMANCOMPRESSCPRO_COMPRESS_H
