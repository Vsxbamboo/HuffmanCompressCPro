#include <iostream>
#include "Compress.h"
#include "SqList.h"
int main(int argc,char *argv[]) {
//    std::string mode=argv[1];
//    std::string readfilepath=argv[2];
//    std::string writefilepath=argv[3];
//    std::string destfilepath=argv[4];
    //用参数或者其他形式输入两个地址
    std::string readfilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\Pic.bmp.huf.huf.huf.huf)";
    std::string writefilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\Pic.bmp.huf.huf.huf.huf.huf)";
    std::string destfilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\Pic.bmp.huf.huf.dest.huf)";
//    std::string readfilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\test.mp4)";
//    std::string writefilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\test.mp4.huf)";
//    std::string destfilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\test.dest.mp4)";
    //使用Compress.compress(readfilepath,writefilepath)压缩
    Compress c;
    Status compressResult=c.compress(readfilepath,writefilepath);
    if(compressResult==0){
        std::cout<<"Compress Success!"<<std::endl;
    }else{
        std::cout<<"ErrorCode:"<<compressResult;
    }

    Status decompressResult=c.decompress(writefilepath,destfilepath);
    if(compressResult==0){
        std::cout<<"Decompress Success!"<<std::endl;
    }else{
        std::cout<<"ErrorCode:"<<decompressResult;
    }


    return 0;
}
