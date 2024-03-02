//
// Created by vsx on 2024/2/27.
//

#include "Huffman.h"


Huffman::Huffman() {

}

void Huffman::build(int *count, int length) {
    for(int i=0;i<length;i++){
        if(count[i]==0)
            continue;
        HuffmanTree* t=new HuffmanTree{i,count[i],nullptr,nullptr,nullptr};
        HTP tp{t};
        treelist.insert(tp);
    }
    HuffmanTree t{};
    while(treelist.getLength()>=2){
        HTP lt,rt;//left tree, right tree

        treelist.get(treelist.getLength()-2,lt);
        treelist.get(treelist.getLength()-1,rt);
        root.p=new HuffmanTree{-1,lt.p->weight+rt.p->weight,nullptr,lt.p,rt.p};
        lt.p->parent=root.p;
        rt.p->parent=root.p;

        treelist.del(treelist.getLength()-2);
        treelist.del(treelist.getLength()-1);
        treelist.insert(root);
    }
    //用来防止文件只有一种字节
    HTP one;
    treelist.get(0,one);
    if(one.p->id==0){
        root.p=new HuffmanTree{-1,one.p->weight,nullptr,one.p,nullptr};
    }

}

void Huffman::traversal(int length) {

    word.value=new char[length+1]{0};
    word.length=0;
    subtraversal(root.p);
}

void Huffman::subtraversal(const Huffman::HuffmanTree *rootp) {
    if(rootp==nullptr){
        return;

    }
    std::cout<<"id:"<<rootp->id<<",weight:"<<rootp->weight<<std::endl;
    //

    if(rootp->parent!=nullptr) {
        if (rootp->parent->lchild == rootp) {
            word.length++;
            word.value[word.length - 1] = '0';
        }else if (rootp->parent->rchild == rootp) {
            word.length++;
            word.value[word.length - 1] = '1';
        }
        if(rootp->id!=-1){
            strcpy(code[rootp->id],word.value);
        }
    }
    //

    subtraversal(rootp->lchild);
    subtraversal(rootp->rchild);

    //
    if(rootp->parent!=nullptr) {
        word.value[word.length - 1] = '\0';
        word.length--;
    }
    //

}

void Huffman::generate(char** &code,int length) {
    this->code=new char*[length];
    for(int i=0;i<length;i++){
        this->code[i]=new char[length+1]{0};
    }
    traversal(length);
    code=this->code;
    for(int i=0;i<length;i++){
        if(strlen(code[i])!=0)
            std::cout<<i<<":"<<code[i]<<std::endl;
    }
}

Huffman::~Huffman() {
    delete[] code;
    closeTree(root.p);
}

void Huffman::closeTree(Huffman::HuffmanTree *rootp) {
    if(rootp==nullptr)
        return;
    closeTree(rootp->lchild);
    closeTree(rootp->rchild);
    delete rootp;
}


