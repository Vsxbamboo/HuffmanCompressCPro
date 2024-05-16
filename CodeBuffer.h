//
// Created by vsx on 2024/3/3.
//

#ifndef HUFFMANCOMPRESSCPRO_CODEBUFFER_H
#define HUFFMANCOMPRESSCPRO_CODEBUFFER_H

#include <string>
#include <fstream>
#include "Dictionary.h"

#define CB_FILE_OPEN_ERROR -1
#define CB_EOF 1

class CodeBuffer {
private:
    char io=0b00000000;
    std::string strbuf;
    int strpos=0;
    Dictionary& dict;
    std::fstream& file;
    int rp=0;
    int validbits=0;
    int savedseekg=0;
    int filelength=0;
    char strbuf2byte()const;
    std::string byte2str(char byte)const;
public:
    CodeBuffer(std::fstream& file,Dictionary& dict);
    CodeBuffer(std::fstream& file,Dictionary& dict,int validbits);
    Status write(const std::string& strbin);
    Status read(char& byte);
    
    void fillAndWrite();
};


#endif //HUFFMANCOMPRESSCPRO_CODEBUFFER_H
