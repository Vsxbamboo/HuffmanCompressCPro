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
    q.push(const_cast<HuffmanTree *>(this)); // ����ǰ�ڵ�ѹ�������

    int currentLevelCount = 1; // ��ǰ��Ľڵ�����
    int nextLevelCount = 0; // ��һ��Ľڵ�����

    while (!q.empty()) {
        HuffmanTree *current = q.front();
        q.pop();
        current->show();
        std::cout << " "; // ����ڵ���Ϣ����ӿո�

        if (current->lchild) {
            q.push(current->lchild);
            nextLevelCount++; // ÿѹ��һ�����ӣ���һ��ڵ���������
        }
        if (current->rchild) {
            q.push(current->rchild);
            nextLevelCount++; // ÿѹ��һ���Һ��ӣ���һ��ڵ���������
        }

        // ��ǰ��Ľڵ���������1
        currentLevelCount--;

        // ��ǰ��Ľڵ��Ѿ�ȫ���������
        if (currentLevelCount == 0) {
            std::cout << std::endl; // �������
            currentLevelCount = nextLevelCount; // ���µ�ǰ��Ľڵ�����Ϊ��һ��Ľڵ�����
            nextLevelCount = 0; // ������һ��Ľڵ�����
        }
    }
    std::cout<<std::endl;
    std::cout<<"-----------------------------------------------------------------"<<std::endl<<std::endl;
}
