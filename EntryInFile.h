//
// Created by vsx on 2024/3/3.
//

#ifndef HUFFMANCOMPRESSCPRO_ENTRYINFILE_H
#define HUFFMANCOMPRESSCPRO_ENTRYINFILE_H


class EntryInFile {
public:
    char byte;
    char bits;
    char code;//TODO �޸ĳ�string���ͣ�ͬʱ����ȥ��bits ������Ҫʹ�ú�������ȡ���Ⱥ�charָ�룬�����8�ı���λ�ı䳤�洢
    EntryInFile();
    int getCodeLength()const;
    char* getCode()const;
};


#endif //HUFFMANCOMPRESSCPRO_ENTRYINFILE_H
