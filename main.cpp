#include <iostream>
#include "Compress.h"
#include "SqList.h"
int main() {
    //�ò�������������ʽ����������ַ
    std::string readfilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\Pic.bmp.buf)";
    std::string writefilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\Pic.bmp.buf.buf)";

    //ʹ��Compress.compress(readfilepath,writefilepath)ѹ��
    Compress c;
    c.compress(readfilepath,writefilepath);

    //ʹ��Compress.evaluate(readfilepath,writefilepath)����ѹ���ʵļ���
    c.evaluate();

    return 0;

}
