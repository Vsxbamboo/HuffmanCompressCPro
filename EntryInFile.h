//
// Created by vsx on 2024/3/3.
//

#ifndef HUFFMANCOMPRESSCPRO_ENTRYINFILE_H
#define HUFFMANCOMPRESSCPRO_ENTRYINFILE_H


class EntryInFile {
public:
    char byte;
    char bits;
    char code;//TODO 修改成string类型，同时可以去掉bits 对外需要使用函数来读取长度和char指针，变成以8的倍数位的变长存储
    EntryInFile();
    int getCodeLength()const;
    char* getCode()const;
};


#endif //HUFFMANCOMPRESSCPRO_ENTRYINFILE_H
