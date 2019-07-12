//
//  BinaryTree.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2018/12/20.
//  Copyright © 2018年 2dfire. All rights reserved.
//

#include "BinaryTree.hpp"
#include <iostream>
#include <sstream>
#include <stack>
#include <queue>
using namespace std;

//二叉搜索（排序）树：或者是一颗空树，或者是具有下列性质的二叉树：若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值； 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值； 它的左、右子树也分别为二叉排序树。
typedef struct BinarySearchTreeNode {
    int key;
    BinarySearchTreeNode* left;
    BinarySearchTreeNode* right;
    BinarySearchTreeNode* parent;
    BinarySearchTreeNode(int key):key(key),left(nullptr),right(nullptr), parent(nullptr){}
}*BSTree;
//MARK:二叉树搜索树的第k个节点
BinarySearchTreeNode *KthNode(BinarySearchTreeNode *pRoot, int k) {
    if (pRoot == nullptr) {
        return pRoot;
    }
    int p = 0;
    stack<BinarySearchTreeNode*>s;
    BinarySearchTreeNode *curNode = pRoot;
    while (curNode != nullptr || !s.empty()) {
        while (curNode != nullptr) {
            s.push(curNode);
            curNode =  curNode->left;
        }
        if (!s.empty()) {
            curNode = s.top();
            s.pop();
            p++;
            if (p == k) {
                return curNode;
            }
            curNode = curNode->right;
        }
    }
    return nullptr;
}

//MARK:二叉搜索树的最大最小值
BinarySearchTreeNode* BST_Minimum(BSTree T){
    while (T->left != nullptr) {
        T = T->left;
    }
    return T;
}

BinarySearchTreeNode* BST_Maximum(BSTree T) {
    while (T->right != nullptr) {
        T = T->right;
    }
    return T;
}


//MARK:给定一个二叉树的节点，求出它在中序遍历中的前驱与后继。如果所有关键字都不相同，则
//某节点x的后继是:
//1.若x的右子树不为空，则x的后继是它的右子树中Key最小的节点
//2.若x的右子树为空，为了寻找其后继，从x开始向上查找，知道遇到一个祖先节点y,y的左儿子也是x的祖先，则y就是x的后继
//也就是，对于y，x是y的前驱，x应当是y的左子树中的key最大的
BinarySearchTreeNode* BST_Successor(BinarySearchTreeNode *node){
    if (node->right != nullptr) {
        return BST_Minimum(node->right);
    }
    BinarySearchTreeNode *p = node->parent;
    while (p != nullptr && p ->right == node) {
        node = p;
        p = p->parent;
    }
    return p;
}

BinarySearchTreeNode* BST_Predecessor(BinarySearchTreeNode *node){
    if (node->left != nullptr) {
        return BST_Maximum(node->left);
    }
    BinarySearchTreeNode* p = node->parent;
    while (p != nullptr && p->left == node) {
        node = p;
        p = p->parent;
    }
    
    return p;
}


//MARK:二叉树结构
struct BinaryTreeNode {
    int m_nValue;
    BinaryTreeNode *m_pLeft;
    BinaryTreeNode *m_pRight;
    BinaryTreeNode(int x):m_nValue(x),m_pLeft(nullptr), m_pRight(nullptr){}
};

//MARK:二叉树的序列化与反序列化

void aSerialize(BinaryTreeNode* pRoot, ostringstream& out) {
    if (pRoot) {
        //以空格分隔
        out << pRoot->m_nValue << " ";
        aSerialize(pRoot->m_pLeft, out);
        aSerialize(pRoot->m_pRight, out);
    } else {
        out << "$ ";
        return;
    }
}

BinaryTreeNode* aDeSerialize(istringstream& in){
    string val;
    in >> val;//从流中读取值到变量val
    if (val == "$") {
        return nullptr;
    }
    BinaryTreeNode *root = new BinaryTreeNode(stoi(val));
    root->m_pLeft = aDeSerialize(in);
    root->m_pRight = aDeSerialize(in);
    
    return root;
}


void Serialize(BinaryTreeNode* pRoot, ostream& stream) {
    if (pRoot == nullptr) {
        stream << "$,";
        return;
    }
    stream << pRoot->m_nValue << ",";
    Serialize(pRoot->m_pLeft, stream);
    Serialize(pRoot->m_pRight, stream);
}

bool ReadStream(istream& stream, int* number)
{
    if(stream.eof())
        return false;
    
    char buffer[32];
    buffer[0] = '\0';
    
    char ch;
    stream >> ch;
    int i = 0;
    while(!stream.eof() && ch != ',')
    {
        buffer[i++] = ch;
        stream >> ch;
    }
    
    bool isNumeric = false;
    if(i > 0 && buffer[0] != '$')
    {
        *number = atoi(buffer);
        isNumeric = true;
    }
    
    return isNumeric;
}

void DeSerialize(BinaryTreeNode* pRoot, istream& stream) {
    int number;
    if (ReadStream(stream, &number)) {
        pRoot = new BinaryTreeNode(number);
        DeSerialize(pRoot->m_pLeft, stream);
        DeSerialize(pRoot->m_pRight, stream);
    }
}

//MARK:面试题50 二叉树中两个节点的最低公共祖先
//MARK:最低公共祖先--是二叉搜索树
BinaryTreeNode* BST_lowestCommomAncestor(BinaryTreeNode *pRoot,BinaryTreeNode * pFirst,BinaryTreeNode *pSecond) {
    if (pRoot == nullptr || pRoot == pFirst || pRoot == pSecond) {
        return pRoot;
    }
    if (pRoot->m_nValue > pFirst->m_nValue && pRoot->m_nValue > pSecond->m_nValue ) {
        return BST_lowestCommomAncestor(pRoot->m_pLeft, pFirst, pSecond);
    }
    else if (pRoot->m_nValue < pFirst->m_nValue && pRoot->m_nValue < pSecond->m_nValue ) {
        return BST_lowestCommomAncestor(pRoot->m_pRight, pFirst, pSecond);
    } else {
        return pRoot;
    }
}

//MARK:最低公共祖先--二叉搜索树，但是节点的数据结构中存储的有指向父节点的指针
//问题演变为求两个链表的第一个公共节点，参考
//findFirstCommonNode


//MARK:最低公共祖先--不是二叉搜索树，节点的数据结构中也没有有指向父节点的指针
bool getNodePath(BinaryTreeNode* root, BinaryTreeNode *node, vector<BinaryTreeNode*>& path) {
    if (root == nullptr) {
        return false;
    }
    if (root->m_nValue == node->m_nValue) {
        return true;
    }
    //有无子节点
    if (root->m_pLeft != nullptr) {
        path.push_back(root->m_pLeft);
        if (getNodePath(root->m_pLeft, node, path)) {
            return true;
        }
        //无左子树
        path.pop_back();
    }
    if (root->m_pRight != nullptr) {
        path.push_back(root->m_pRight);
        if (getNodePath(root->m_pRight, node, path)) {
            return true;
        }
        //无右子树
        path.pop_back();
    }
    return false;
}

BinaryTreeNode* lowestCommomAncestor(BinaryTreeNode *pRoot,BinaryTreeNode * pFirst,BinaryTreeNode *pSecond) {
    if (pRoot == nullptr || pFirst == nullptr || pSecond == nullptr) {
        return nullptr;
    }
    vector<BinaryTreeNode*>firstPath;
    vector<BinaryTreeNode*>secondPath;
    firstPath.push_back(pRoot);
    secondPath.push_back(pRoot);
    
    getNodePath(pRoot, pFirst, firstPath);
    getNodePath(pRoot, pSecond, secondPath);
    //获取两条路径的最后一个公共节点
    BinaryTreeNode* retNode = nullptr;
    for (int i = 0 ; i < firstPath.size() && i < secondPath.size(); ++i) {
        if (firstPath.at(i)->m_nValue == secondPath.at(i)->m_nValue) {
            retNode = firstPath.at(i);
        } else {
            break;
        }
    }
    
    return retNode;
}


//MARK:leetcode 993. 二叉树的堂兄弟节点判断(Cousins in Binary Tree)
bool getPath(BinaryTreeNode* root, int x, vector<int>& path) {
    if (root == nullptr) {
        return false;
    } else {
        path.push_back(root->m_nValue);
        if (root->m_nValue != x) {
            if (getPath(root->m_pLeft, x, path)) {
                return true;
            }
            if (getPath(root->m_pRight, x, path)) {
                return true;
            }
            path.pop_back();
            return false;
            
        } else {
            return true;
        }
        
    }
}

bool isCousins(BinaryTreeNode* root, int x, int y)
{
    vector<int> path1, path2;
    getPath(root, x, path1);
    getPath(root, y, path2);
    if (path1.size() != path2.size()) {
        return false;
    } else {
        path1.pop_back();
        path2.pop_back();
        //父节点不相同
        return path1.back() != path2.back();
    }
}

//MARK:面试题24:二叉搜索树的后序遍历序列：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历序列
//最后一个数字是根节点，数组中前面的数字可以分为2组，
//第一部分是左子树，都比根节点小
//第二部分是右子树，都比根节点大
bool VerifySequenceOfBST(int sequence[], int length) {
    if (sequence == nullptr || length <= 0) {
        return false;
    }
    int root = sequence[length - 1];
    //左子树的节点小于根节点
    int i = 0;
    for (; i < length-1; ++i) {
        if (sequence[i] > root) {
            break;
        }
    }
    int j = i;
    for (; j < length-1; ++j) {
        if (sequence[j] < root) {
            return false;
        }
    }
    bool left = true;
    if (i > 0) {
        length = VerifySequenceOfBST(sequence, i);
    }
    bool right = true;
    if (i < length-1) {
        right = VerifySequenceOfBST(sequence+i, length-i-1);
    }
    return (left && right);
}


/*
int main(int argc, const char * argv[]) {
//    fab(5);
//    BSTree root = BSTree();
//    root->key = 5;
//    root->left = nullptr;
//    root->right = nullptr;
//    int array [6] = {3,7,2,4,6,8};
//    Create_BST(root, array, 6);
    
////     insert code here...
//
    
    
    
    BinaryTreeNode *root = new BinaryTreeNode(5);

    InsertNode(root, 3);
    InsertNode(root, 2);
    InsertNode(root, 4);
    InsertNode(root, 7);
    InsertNode(root, 8);

    InOrderBinaryTreeRecursive(root);

    
//    stringstream buf1;
//    buf1 << 7;
//    int n = 0;
//    buf1 >> n;
//    cout << buf1.str() << endl;
//    cout << n << endl;
//
//    istringstream inbuf("-10");
//    inbuf >> n;
//    cout << n << endl;
//
//    ostringstream buf2("test");
//    buf2 << "1";
//    cout << buf2.str() << endl;
//
//
    return 0;
}
 
 */
