#include <iostream>
#include "Compress.h"
#include "SqList.h"
int main() {
    //用参数或者其他形式输入两个地址
    std::string readfilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\Pic.bmp.buf)";
    std::string writefilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\Pic.bmp.buf.buf)";

    //使用Compress.compress(readfilepath,writefilepath)压缩
    Compress c;
    c.compress(readfilepath,writefilepath);

    //使用Compress.evaluate(readfilepath,writefilepath)进行压缩率的计算
    c.evaluate();

    return 0;

}
