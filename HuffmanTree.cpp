//
// Created by vsx on 2024/3/2.
//

#include "HuffmanTree.h"
bool HuffmanTree::operator<(const HuffmanTree& rt)const{
    return weight<rt.weight;
}
bool HuffmanTree::operator>(const HuffmanTree& rt)const{
    return weight>rt.weight;
}
HuffmanTree& HuffmanTree::operator=(const HuffmanTree& rt) {
    if (this == &rt)
        return *this;
    id = rt.id;
    weight = rt.weight;
    parent = rt.parent;
    lchild = rt.lchild;
    rchild = rt.rchild;
    return *this;
}

void HuffmanTree::show() const {
    std::cout << "ID: " << id << ", Weight: " << weight;
}

void HuffmanTree::levelOrderTraversal() const {
    std::cout<<"-----------------------------------------------------------------"<<std::endl;
    std::cout<<"HuffmanTree:"<<std::endl;
    std::queue<HuffmanTree *> q;
    q.push(const_cast<HuffmanTree *>(this)); // 将当前节点压入队列中

    int currentLevelCount = 1; // 当前层的节点数量
    int nextLevelCount = 0; // 下一层的节点数量

    while (!q.empty()) {
        HuffmanTree *current = q.front();
        q.pop();
        current->show();
        std::cout << " "; // 输出节点信息后添加空格

        if (current->lchild) {
            q.push(current->lchild);
            nextLevelCount++; // 每压入一个左孩子，下一层节点数量增加
        }
        if (current->rchild) {
            q.push(current->rchild);
            nextLevelCount++; // 每压入一个右孩子，下一层节点数量增加
        }

        // 当前层的节点数量减少1
        currentLevelCount--;

        // 当前层的节点已经全部处理完毕
        if (currentLevelCount == 0) {
            std::cout << std::endl; // 输出换行
            currentLevelCount = nextLevelCount; // 更新当前层的节点数量为下一层的节点数量
            nextLevelCount = 0; // 清零下一层的节点数量
        }
    }
    std::cout<<std::endl;
    std::cout<<"-----------------------------------------------------------------"<<std::endl<<std::endl;
}
