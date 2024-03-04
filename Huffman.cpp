//
// Created by vsx on 2024/3/2.
//

#include "Huffman.h"

void Huffman::buildAndGenerate(const int* count,const int length, std::string*& codes) {
    HuffmanTree root;
    build(count,length,root);
    root.levelOrderTraversal();
    generate(root,codes,length);

}

void Huffman::build(const int *count,const int length, HuffmanTree &root) {
    SqList<HTP> list;
    for(int i=0;i<length;i++){
        if(count[i]==0)
            continue;
        HTP temp;
        temp.p=new HuffmanTree;
        temp.p->id=i;
        temp.p->weight=count[i];
        temp.p->parent=nullptr;
        temp.p->lchild=nullptr;
        temp.p->rchild=nullptr;
        list.insert(temp);
    }
    list.show();
    while(list.getLength()>=2){
        HTP lp,rp;//leftHTP,rightHTP
        list.get(list.getLength()-2,lp);
        list.get(list.getLength()-1,rp);
        HTP temp;
        temp.p=new HuffmanTree;
        temp.p->id=-1;
        temp.p->weight=lp.p->weight+rp.p->weight;
        temp.p->parent=nullptr;
        temp.p->lchild=lp.p;
        temp.p->rchild=rp.p;
        lp.p->parent=temp.p;
        rp.p->parent=temp.p;
        list.del(list.getLength()-2);
        list.del(list.getLength()-1);
        list.insert(temp);
    }
    HTP temp;
    //对list中只有零个或一个元素的情况先进行判断
    if(list.getLength()==0){
        root.id=-1;
        root.weight=0;
        root.parent=nullptr;
        root.lchild=nullptr;
        root.rchild=nullptr;
    }else{
        list.get(0,temp);
        if(temp.p->id!=-1){
            root.id=-1;
            root.weight=temp.p->weight;
            root.parent=nullptr;
            root.lchild=temp.p;
            root.rchild=nullptr;

            temp.p->parent=&root;
        }else if(temp.p->id==-1){
            root=*temp.p;
        }
    }
}

void Huffman::generate(const HuffmanTree &root, std::string*& codes, const int length) {
    codes=new std::string[length];
    postTraversal(&root,codes,length);
    std::cout<<"-----------------------------------------------------------------"<<std::endl;
    std::cout<<"Codes:"<<std::endl;
    for(int i=0;i<length;i++){
        if(codes[i]=="")
            continue;
        std::cout<<i<<":"<<codes[i]<<std::endl;
    }
    std::cout<<"-----------------------------------------------------------------"<<std::endl;
}

void Huffman::postTraversal(const HuffmanTree *rootp,std::string*& codes,const int length) {
    if(rootp==nullptr)
        return;

    if(rootp->parent!=nullptr) {
        if (rootp == rootp->parent->lchild) {
            code.value.push_back('0');
        } else if (rootp == rootp->parent->rchild) {
            code.value.push_back('1');
        } else {
            std::cout << std::endl << "#HuffmanTreeError" << std::endl;
        }
        if (rootp->id != -1) {
            codes[rootp->id] = code.value;
        }
    }
    postTraversal(rootp->lchild, codes, length);
    postTraversal(rootp->rchild, codes, length);
    code.value.pop_back();
}
