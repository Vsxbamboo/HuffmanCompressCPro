#include <iostream>
#include "Compress.h"
#include "SqList.h"
int main() {

    //用参数或者其他形式输入两个地址
//    std::string readfilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\Pic.bmp)";
//    std::string writefilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\Pic.bmp.huf)";
//    std::string destfilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\Pic.dest.bmp)";
    std::string readfilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\test.mp4)";
    std::string writefilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\test.mp4.huf)";
    std::string destfilepath=R"(C:\E\cpp\HuffmanCompressCPro\assets\test.dest.mp4)";
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


//    std::fstream file;
//    file.open(destfilepath,std::ios::in | std::ios::binary);
//    file.seekg(0,std::ios::end);
//    int filelength=file.tellg();
//    std::cout<<"filelength:"<<filelength<<std::endl;
//    file.seekg(0,std::ios::beg);
//    char byte;
//    for(int i=0;i<filelength;i++){
//        file.read(&byte,1);
//        std::cout<<(int)byte<<",";
//        std::string strbin;
//        for(int i=0;i<8;i++){
//            std::cout<<((byte>>7)&1);
//            byte=byte<<1;
//        }
//        std::cout<<strbin<<" ";
//    }
//    file.close();
//    system("pause");
    return 0;
}
