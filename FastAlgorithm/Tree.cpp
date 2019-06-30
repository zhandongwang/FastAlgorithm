//
//  Tree.cpp
//  FastAlgorithm
//
//  Created by 王战东 on 2019/6/30.
//  Copyright © 2019 2dfire. All rights reserved.
//

#include "Tree.hpp"
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

typedef struct BSTreeNode {
    int value;
    BSTreeNode *left;
    BSTreeNode *right;
    BSTreeNode *parent;
    BSTreeNode(int k):value(k), left(NULL),right(NULL), parent(NULL){};
    
}*BSTree;


struct BNTreeNode {
    int m_nValue;
    BNTreeNode *m_pLeft;
    BNTreeNode *m_pRight;
    BNTreeNode(int x): m_nValue(x),m_pLeft(nullptr),m_pRight(nullptr){}
};

//MARK:二叉树叶子节点数
int BT_LefeCount(BNTreeNode *pRoot) {
    if (pRoot == nullptr) {
        return 0;
    }
    static int leafNum = 0;
    if (pRoot->m_pLeft == nullptr && pRoot->m_pRight == nullptr) {
        leafNum++;
    }
    BT_LefeCount(pRoot->m_pLeft);
    BT_LefeCount(pRoot->m_pRight);
    
    return leafNum;
}



//MARK:二叉树深度
int BT_MAXTreeDepth(BNTreeNode *pRoot) {
    if (pRoot == nullptr) {
        return 0;
    }
    int leftDepth = BT_MAXTreeDepth(pRoot->m_pLeft);
    int rightDepth = BT_MAXTreeDepth(pRoot->m_pRight);
    if (leftDepth > rightDepth) {
        return leftDepth + 1;
    }
    return rightDepth + 1;
}

//MARK:层次遍历二叉树
void BT_BFSTree(BNTreeNode *pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    queue<BNTreeNode *>q;
    q.push(pRoot);
    while (!q.empty()) {
        BNTreeNode *front = q.front();
        cout << front->m_nValue << " ";
        q.pop();
        if (front->m_pLeft) {
            q.push(front->m_pLeft);
        }
        if (front->m_pRight) {
            q.push(front->m_pRight);
        }
    }
}

//MARK:递归后根遍历二叉树
void BT_PostOrderRecursive(BNTreeNode *pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    BT_PostOrderRecursive(pRoot->m_pLeft);
    BT_PostOrderRecursive(pRoot->m_pRight);
    cout << pRoot->m_nValue << " ";

}

void BT_PostOrderNoRecursive(BNTreeNode *pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    stack<BNTreeNode *>stack1;
    stack<BNTreeNode *>stack2;
    stack1.push(pRoot);
    while (!stack1.empty()) {
        BNTreeNode *top = stack1.top();
        stack1.pop();
        stack2.push(top);
        if (top->m_pLeft) {
            stack1.push(top->m_pLeft);
        }
        if (top->m_pRight) {
            stack1.push(top->m_pRight);
        }
    }
    while (!stack2.empty()) {
        BNTreeNode *top = stack2.top();
        cout << top->m_nValue << " ";
        stack2.pop();
    }
    
}

//MARK:递归先根遍历二叉树
void BT_InOrderRecursive(BNTreeNode *pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    BT_InOrderRecursive(pRoot->m_pLeft);
    cout << pRoot->m_nValue << " ";
    BT_InOrderRecursive(pRoot->m_pRight);
}

void BT_InOrderNoRecursive(BNTreeNode *pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    stack<BNTreeNode *>stack;
    BNTreeNode *node = pRoot;
    while (node || !stack.empty()) {
        if (node) {//有左孩子就入栈
            stack.push(node);
            node = node->m_pLeft;
        } else {//没有左孩子、栈顶出栈
            node = stack.top();
            cout << node->m_nValue << " ";
            stack.pop();
            node = node->m_pRight;
        }
    }
}

//MARK:递归先根遍历二叉树
void BT_PreOrderRecursive(BNTreeNode *pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    cout << pRoot->m_nValue << " ";
    BT_PreOrderRecursive(pRoot->m_pLeft);
    BT_PreOrderRecursive(pRoot->m_pRight);
}

void BT_PreOrderNoRecursive(BNTreeNode *pRoot)  {
    if (pRoot == nullptr) {
        return;
    }
    stack<BNTreeNode *>stack;
    stack.push(pRoot);
    while (!stack.empty()) {
        BNTreeNode *top = stack.top();
        cout << top->m_nValue << " ";//先打印栈顶元素
        stack.pop();
        if (top->m_pRight) {
            stack.push(top->m_pRight);
        }
        if (top->m_pLeft) {
            stack.push(top->m_pLeft);
        }
    }
}

//按二叉搜索树规则插入
void BT_insertNode(BNTreeNode **pRoot, int value) {
    BNTreeNode *node = new BNTreeNode(value);
    if (*pRoot == nullptr) {
        *pRoot = node;
        return;
    }
    if (value <= (*pRoot)->m_nValue) {
        if ((*pRoot)->m_pLeft == nullptr) {
            (*pRoot)->m_pLeft = node;
        } else {
            BT_insertNode(&(*pRoot)->m_pLeft, value);
        }
    } else {
        if ((*pRoot)->m_pRight == nullptr) {
            (*pRoot)->m_pRight = node;
        } else {
            BT_insertNode(&(*pRoot)->m_pRight, value);
        }
    }
}


int main(int argc, const char * argv[]) {
    BNTreeNode *root = nullptr;
    BT_insertNode(&root, 5);
    BT_insertNode(&root, 3);
    BT_insertNode(&root, 7);
    BT_insertNode(&root, 1);
    BT_insertNode(&root, 4);
    BT_insertNode(&root, 6);
    BT_insertNode(&root, 9);
    
    BT_BFSTree(root);
    
//    cout << BT_LefeCount(root) << endl;
    
    
    return 0;
}
