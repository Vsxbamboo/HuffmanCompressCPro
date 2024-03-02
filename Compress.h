//
// Created by vsx on 2024/2/27.
//

#ifndef HUFFMANCOMPRESSCPRO_COMPRESS_H
#define HUFFMANCOMPRESSCPRO_COMPRESS_H

#include <fstream>
#include "Huffman.h"

/*
 * ѹ����
 * ���ⲿֻ��Ҫ����һ�������Ϳ������ѹ������
 * ���磺Compress.compress(<source file path>,<destination file path>);
 * ��: int compress(char *readfilepath,char *writefilepath);
 * compress������ͨ������������������ɹ��ܣ���open,�ٽ���ѹ�������write()��
 *
 *
 * */

/*
 * �ֵ�ṹ
 * ��Ӧcharֵ ���볤�� ����+��0
 * �Ż���Ľ����ֵ�ṹ�����볤������
 * */

/*
 * �ļ�ͷ���ṹ
 * �������һ���ֽ���Чλ��
 * �ֵ�����
 * */

#define FILE_NOT_FOUND (-2)
#define FILE_OPEN_FAILURE (-3)
#define FILE_NOT_READ (-4)
#define FILE_EMPTY_ERROR (-5)
#define TRANBUF_LENGTH (sizeof(char)*8)
class Compress {
private:

    std::fstream readfile;//��ѹ���Ķ�ȡ�ļ�����
    std::fstream writefile;//ѹ�����д���ļ�����
    std::streampos filelength;//��ѹ���ļ�����
    Huffman huffman;

    void str2byte(char* str,char& byte);
    //���ڽ�8λ0,1�ַ���ת����char���ͣ�����write()��д��
public:
    Compress();
    ~Compress();


    int open(char *filepath);
    //open������Ҫ��֤�ļ����ںͳ�ʼ������readfile��ͬʱ��ʼ������ѭ�����õõ���filelength

    int compress(std::string readfilepath,std::string writefilepath);
    //compress�������ۺ��壬�����ⲿ����

    int write(char *filepath,char **code);
    //write����ѹ������ļ�������д��

    int evaluate();
    //evaluate�����������������ļ��Ƿ���ȷ��ȡ���жϡ�ѹ���ʵļ���
};


#endif //HUFFMANCOMPRESSCPRO_COMPRESS_H
