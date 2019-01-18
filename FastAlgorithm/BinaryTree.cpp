//
//  BinaryTree.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2018/12/20.
//  Copyright © 2018年 2dfire. All rights reserved.
//

#include "BinaryTree.hpp"
#include <iostream>
using namespace std;

struct BinaryTreeNode {
    int m_nValue;
    BinaryTreeNode *m_pLeft;
    BinaryTreeNode *m_pRight;
};
//面试题6：根据前序遍历、中序遍历序列重建二叉树,假设序列中不含重复数字

BinaryTreeNode* ConstructCore(int *startPreOrder, int *endPreOrder, int *startInOrder, int *endInOrder) {
    int rootValue = startPreOrder[0];
    BinaryTreeNode *root = new BinaryTreeNode();
    root -> m_nValue = rootValue;
    root -> m_pLeft = root -> m_pRight = NULL;
    
    if (startPreOrder == endPreOrder) {
        //只有一个节点
        if (startInOrder == endInOrder && *startPreOrder == *startInOrder) {
            return root;
        } else {
            throw exception();
        }
    }
    //在中序序列中寻找根节点，中序序列中，左边的为左子树、右边的为右子树
    int *rootInOrder = startInOrder;
    while (rootInOrder <= endInOrder && *rootInOrder != rootValue) {
        ++rootInOrder;
    }
    //在中序序列中没有找到根节点
    if (rootInOrder == endInOrder && *rootInOrder != rootValue) {
        throw exception();
    }
    
    //左子树节点数量
    long leftLength = rootInOrder - startInOrder;
    int *leftPreOrderEnd = startPreOrder + leftLength;
    if (leftLength > 0) {
        //构建左子树
        root->m_pLeft = ConstructCore(startPreOrder + 1, leftPreOrderEnd, startInOrder,rootInOrder -1);
    }
    if (leftLength < endPreOrder - startPreOrder) {
        //构建右子树
        root->m_pRight = ConstructCore(leftPreOrderEnd+1, endPreOrder, rootInOrder+1, endInOrder);
    }
    
    
    return NULL;
}

BinaryTreeNode* Construct(int *preOrder, int *inOrder, int length) {
    if (preOrder == NULL || inOrder == NULL || length <= 0) {
        return NULL;
    }
    return ConstructCore(preOrder, preOrder + length - 1, inOrder, inOrder + length - 1);
}

