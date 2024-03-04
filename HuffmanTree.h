//
// Created by vsx on 2024/3/2.
//

#ifndef HUFFMANCOMPRESSCPRO_HUFFMANTREE_H
#define HUFFMANCOMPRESSCPRO_HUFFMANTREE_H

#include <iostream>
#include <queue>

class HuffmanTree {
public:
    int id;
    int weight;
    HuffmanTree *parent,*lchild,*rchild;

    bool operator<(const HuffmanTree& rt)const;
    bool operator>(const HuffmanTree& rt)const;
    HuffmanTree& operator=(const HuffmanTree& rt);
    void show()const;
    void levelOrderTraversal()const;
};


#endif //HUFFMANCOMPRESSCPRO_HUFFMANTREE_H
