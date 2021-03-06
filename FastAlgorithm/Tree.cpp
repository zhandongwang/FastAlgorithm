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

//MARK:二叉搜索树数据结构
typedef struct BSTreeNode {
    int value;
    BSTreeNode *left;
    BSTreeNode *right;
    BSTreeNode *parent;
    BSTreeNode(int k):value(k), left(nullptr),right(nullptr), parent(nullptr){};
    
}*BSTree;

//MARK:二叉树数据结构
struct BNTreeNode {
    int m_nValue;
    BNTreeNode *m_pLeft;
    BNTreeNode *m_pRight;
    BNTreeNode(int x): m_nValue(x),m_pLeft(nullptr),m_pRight(nullptr){}
};

void BST_InsertNode(BSTreeNode **root, int value) {
    BSTreeNode *node =  new BSTreeNode(value);
    if (*root == nullptr) {
        *root = node;
        return;
    }
    if (value <= (*root)->value) {
        if ((*root)->left) {
            BST_InsertNode(&(*root)->left, value);
        } else {
            (*root)->left = node;
        }
    } else {
        if ((*root)->right) {
            BST_InsertNode(&(*root)->right, value);
        } else {
            (*root)->right = node;
        }
    }
}

//MARK:根据前序、中序序列构建二叉树
BNTreeNode* ConstructTree2(int *preOrder,int *inOrder, int len) {
    BNTreeNode *root = new BNTreeNode(preOrder[0]);
    int subTreeLen = 0;
    //在中序序列中没有找到前序序列的根节点
    while (subTreeLen < len && inOrder[subTreeLen] != preOrder[0]) {
        ++subTreeLen;
    }
    //有左子树
    if (subTreeLen > 0) {
        root->m_pLeft = ConstructTree2(preOrder+1, inOrder, subTreeLen);
    }
    //有右子树
    if (len-1-subTreeLen > 0) {
        root->m_pRight = ConstructTree2(preOrder+subTreeLen+1, inOrder+subTreeLen+1, len-1-subTreeLen);
    }
    
    return root;
}

//MARK:镜像二叉树
void MirroTree(BNTreeNode *pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    BNTreeNode *temp = pRoot ->m_pLeft;
    pRoot->m_pLeft = pRoot->m_pRight;
    pRoot->m_pRight = temp;
    MirroTree(pRoot->m_pLeft);
    MirroTree(pRoot->m_pRight);
    
}


bool DoseTreeHasTree2(BNTreeNode *pRoot1, BNTreeNode *pRoot2) {
    if (pRoot2 == nullptr) {
        return true;
    }
    if (pRoot1 == nullptr) {
        return false;
    }
    if (pRoot1->m_nValue != pRoot2->m_nValue) {
        return false;
    }
    
    return DoseTreeHasTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) &&  DoseTreeHasTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}

//MARK:面试题18，两颗二叉树A和B，判断B是不是A的子结构
bool HasSubTree(BNTreeNode *pRoot1, BNTreeNode *pRoot2) {
    if (pRoot1 == nullptr && pRoot2 == nullptr) {
        return true;
    }
    if (pRoot1 == nullptr || pRoot2 == nullptr) {
        return false;
    }
    
    bool result = false;
    if (pRoot1->m_nValue == pRoot2->m_nValue) {
        result = DoseTreeHasTree2(pRoot1, pRoot2);
    }
    if (!result) {
        result = HasSubTree(pRoot1->m_pLeft, pRoot2);
    }
    if (!result) {
        result = HasSubTree(pRoot1->m_pRight, pRoot2);
    }
    return result;
}



//MARK:二叉搜索树查找
BSTreeNode* BST_SearchRecursive(BSTree root, int k) {
    if (root == nullptr || root->value == k) {
        return root;
    }
    if (k < root->value) {
        return BST_SearchRecursive(root->left, k);
    } else {
        return BST_SearchRecursive(root->right, k);
    }
    
}

BSTreeNode* BST_SearchNoRecursive(BSTree root, int k) {
    if (root == nullptr || root->value == k) {
        return root;
    }
    while (root && root->value != k) {
        if (k < root->value) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

//MARK:二叉树第k层的节点个数
int GetKLevel (BNTreeNode *pRoot, int k) {
    if (pRoot == nullptr || k < 1) {
        return 0;
    }
    if (k == 1) {
        return 1;
    }
    return GetKLevel(pRoot->m_pLeft, k-1) + GetKLevel(pRoot->m_pRight, k-1);
}

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

/*
int main(int argc, const char * argv[]) {
//    BNTreeNode *root = nullptr;
//
//    BT_insertNode(&root, 5);
//    BT_insertNode(&root, 3);
//    BT_insertNode(&root, 7);
//    BT_insertNode(&root, 1);
//    BT_insertNode(&root, 4);
//    BT_insertNode(&root, 6);
//    BT_insertNode(&root, 9);
//
//    BT_InOrderRecursive(root);
//    cout << endl;
//    MirroTree(root);
//
//    BT_InOrderRecursive(root);
    
//    BT_BFSTree(root);
    
//    cout << BT_LefeCount(root) << endl;
    
//    BSTreeNode *node = BST_SearchRecursive(root, 7);

//    BSTreeNode *root = nullptr;
//    BST_InsertNode(&root, 5);
//    BST_InsertNode(&root, 3);
//    BST_InsertNode(&root, 7);
//    BST_InsertNode(&root, 1);
//    BST_InsertNode(&root, 4);
//    BST_InsertNode(&root, 6);
//    BST_InsertNode(&root, 9);
//    BSTreeNode *node = BST_SearchNoRecursive(root, 7);
    int preOrder[1] = {5};
    int inOrder[1] = {5};
    
    BNTreeNode *cRoot = ConstructTree2(preOrder, inOrder, 1); //ConstructTree(preOrder, preOrder+6, inOrder, inOrder+6);
    BT_InOrderRecursive(cRoot);
    
    return 0;
}
 */

