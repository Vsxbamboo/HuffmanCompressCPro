//
// Created by vsx on 2024/2/27.
//

#ifndef HUFFMANCOMPRESSCPRO_HUFFMAN_H
#define HUFFMANCOMPRESSCPRO_HUFFMAN_H

class Huffman {
    typedef struct{
        int weight;
        int parent,lchild,rchild;
    } HTNode, *HuffmanTree;

    typedef char **HuffmanCode;
};


#endif //HUFFMANCOMPRESSCPRO_HUFFMAN_H
