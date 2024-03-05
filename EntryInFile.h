//
// Created by vsx on 2024/3/3.
//

#ifndef HUFFMANCOMPRESSCPRO_ENTRYINFILE_H
#define HUFFMANCOMPRESSCPRO_ENTRYINFILE_H

#include <iostream>
#include <string>

class EntryInFile {
public:
    char byte;
    std::string code;
    EntryInFile();
    int getBits()const;
    int getCodeLength()const;
    char* getCode()const;
    void setCode(char *code,char bits);
    std::string visual()const;
};


#endif //HUFFMANCOMPRESSCPRO_ENTRYINFILE_H
