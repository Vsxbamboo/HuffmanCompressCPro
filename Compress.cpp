//
// Created by vsx on 2024/2/27.
//

#include "Compress.h"
#include <iostream>
Compress::Compress() {
    filelength=0;
}
Compress::~Compress() {
    readfile.close();
    writefile.close();
}
int Compress::open(std::string filepath) {
    //检查文件路径是否为空
    if(filepath==nullptr)
        return FILE_NOT_FOUND;
    //打开文件
    readfile.open(filepath,std::ios::in | std::ios::binary);
    //检查打开文件是否成功
    if(!readfile.is_open())
        return FILE_OPEN_FAILURE;
    //获取文件长度
    readfile.seekg(0,std::ios::end);
    filelength=readfile.tellg();
    readfile.seekg(0,std::ios::beg);
    if(filelength==0)
        return FILE_EMPTY_ERROR;
    return 0;
}

int Compress::compress(std::string readfilepath,std::string writefilepath) {
    int openresult=open(readfilepath);
    if(openresult!=0)
        return openresult;

    //检查是否已经读取文件到readbuf
    if(!readfile.is_open())
        return FILE_NOT_READ;

    //统计各个char值出现次数
    int count[256]={0};
    for(int i=0;i<filelength;i++){
        char buf;
        readfile.read(&buf,1);
        count[buf-CHAR_MIN]++;
    }
    readfile.seekg(0,std::ios::beg);
    //输出统计的次数
    for(int i=0;i<256;i++){
        std::cout<<count[i]<<" ";
    }
    std::cout<<std::endl;

    //根据次数构建哈夫曼树
    huffman.build(count,256);
    //生成压缩编码
    char **code;
    huffman.generate(code,256);

    //翻译并写入
    write(writefilepath,code);
    readfile.close();
    writefile.close();
    return 0;
}

int Compress::write(char *filepath,char **code) {
    char readbuf;//存储读入字节
    char tranbuf[TRANBUF_LENGTH+1]={0};//存储翻译字符串
    int tbp=0;//tranbuf pointer,存储翻译字符串使用程度
    char writebuf;//存储写入字节
    std::fstream writefile(filepath,std::ios::app | std::ios::binary);
    for(int i=0;i<filelength;i++){
        std::cout<<"\rcurrent i:"<<i<<"/"<<filelength<<std::endl;
        if(i==33){
            i=33;
        }
        readfile.read(&readbuf,1);
        int codelength=strlen(code[(int)readbuf-CHAR_MIN]);
        std::cout<<"index:"<<(int)readbuf-CHAR_MIN<<",strlen:"<<strlen(code[(int)readbuf-CHAR_MIN])<<std::endl;
        for(int j=0;j<codelength;j++){
            if(tbp+j==TRANBUF_LENGTH){
                str2byte(tranbuf,writebuf);
                //std::cout<<"i:"<<i<<","<<tranbuf<<":"<<(int)(writebuf-CHAR_MIN)<<std::endl;
                writefile.write(&writebuf,1);
                //清空tranbuf
                for(int k=0;k<TRANBUF_LENGTH;k++)
                    tranbuf[k]='\0';
                tbp=0;
            }
            tranbuf[tbp+j]=code[(int)readbuf-CHAR_MIN][j];
        }
        tbp+=codelength;
    }
    if(tbp!=0){
        for(int i=0;i+tbp<TRANBUF_LENGTH;i++){
            tranbuf[tbp+i]='0';
        }
    }
    return 0;
}

void Compress::str2byte(char* str,char& byte){
    byte=0;
    for(int i=0;i<8;i++){
        byte=byte<<1;
        byte=byte | (str[i]-'0');
    }
}

int Compress::evaluate() {
    std::cout<<"#"<<filelength;

    return 0;
}




