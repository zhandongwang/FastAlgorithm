//
//  BinaryTree.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2018/12/20.
//  Copyright © 2018年 2dfire. All rights reserved.
//

#include "BinaryTree.hpp"
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

//二叉搜索（排序）树：或者是一颗空树，或者是具有下列性质的二叉树：若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值； 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值； 它的左、右子树也分别为二叉排序树。
typedef struct BinarySearchTreeNode {
    int key;
    BinarySearchTreeNode* left;
    BinarySearchTreeNode* right;
    BinarySearchTreeNode* parent;
}*BSTree;

//MARK:二叉搜索树的插入
int BST_Insert(BSTree &T, int k, BinarySearchTreeNode *parent=NULL) {
    if (T == NULL) {//空树
        T = (BSTree)malloc(sizeof(BinarySearchTreeNode));
        T->key = k;
        T->right = NULL;
        T->left = NULL;
        T->parent = parent;
        return 1;
    } else if (k == T->key) {//树中存在相同关键字
        return 0;
    } else if (k < T->key) {
        return BST_Insert(T->left, k, T);
    } else {
        return BST_Insert(T->right, k, T);
    }
}


//MARK: 构建二叉搜索树
void Create_BST(BSTree &T, int arr[], int n) {
    T = NULL; //初始化一颗空树
    for (int i = 0; i < n; ++i) {
        BST_Insert(T, arr[i]);
    }
}

//MARK:二叉搜索树查找
BinarySearchTreeNode* BST_Search(BSTree T, int k) {
    if (T == NULL || k == T->key) {
        return T;
    }
    
    if (k < T->key) {
        return BST_Search(T->left, k);
    } else {
        return BST_Search(T->right, k);
    }
}

BinarySearchTreeNode* BST_Search_NonRecur(BSTree T, int k) {
    while (T != NULL && k != T->key) {
        if (k < T->key) {
            T = T->left;
        } else {
            T = T->right;
        }
    }
    return T;
}

//MARK:二叉搜索树的最大最小值
BinarySearchTreeNode* BST_Minimum(BSTree T){
    while (T->left != NULL) {
        T = T->left;
    }
    return T;
}

BinarySearchTreeNode* BST_Maximum(BSTree T) {
    while (T->right != NULL) {
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
    if (node->right != NULL) {
        return BST_Minimum(node->right);
    }
    BinarySearchTreeNode *p = node->parent;
    while (p != NULL && p ->right == node) {
        node = p;
        p = p->parent;
    }
    return p;
}

BinarySearchTreeNode* BST_Predecessor(BinarySearchTreeNode *node){
    if (node->left != NULL) {
        return BST_Maximum(node->left);
    }
    BinarySearchTreeNode* p = node->parent;
    while (p != NULL && p->left == node) {
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
    BinaryTreeNode(int x):m_nValue(x),m_pLeft(NULL), m_pRight(NULL){}
};

//MARK:二叉树的序列化与反序列化
void Serialize(BinaryTreeNode* pRoot, ostream& stream) {
    if (pRoot == NULL) {
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
    if (pRoot == NULL || pRoot == pFirst || pRoot == pSecond) {
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
    if (root == NULL) {
        return false;
    }
    if (root->m_nValue == node->m_nValue) {
        return true;
    }
    //有无子节点
    if (root->m_pLeft != NULL) {
        path.push_back(root->m_pLeft);
        if (getNodePath(root->m_pLeft, node, path)) {
            return true;
        }
        //无左子树
        path.pop_back();
    }
    if (root->m_pRight != NULL) {
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
    if (pRoot == NULL || pFirst == NULL || pSecond == NULL) {
        return NULL;
    }
    vector<BinaryTreeNode*>firstPath;
    vector<BinaryTreeNode*>secondPath;
    firstPath.push_back(pRoot);
    secondPath.push_back(pRoot);
    
    getNodePath(pRoot, pFirst, firstPath);
    getNodePath(pRoot, pSecond, secondPath);
    //获取两条路径的最后一个公共节点
    BinaryTreeNode* retNode = NULL;
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
    if (root == NULL) {
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

//查找第一个k
int GetFirstK(int *data, int length, int k, int start ,int end) {
    if (start > end) {
        return -1;
    }
    int middleIdx = (start + end) / 2;
    int middleData = data[middleIdx];
    if (middleData == k) {
        if (middleIdx >= 0 && data[middleIdx-1] != k) {
            return middleIdx;
        } else {
            end = middleIdx -1;
        }
        
    } else if (middleData < k) {//第一个k在右半部分
        start = middleIdx + 1;
    } else {//第一个k在左半部分
        end = middleIdx - 1;
    }
    return GetFirstK(data, length, k, start, end);
}
//MARK:查找最后一个k
int GetLastK(int *data, int length, int k, int start ,int end) {
    if (start > end) {
        return -1;
    }
    int middleIdx = (start + end) / 2;
    int middleData = data[middleIdx];
    if (middleData == k) {
        if (middleIdx <= length-1 && data[middleIdx+1] != k) {
            return middleIdx;
        } else {
            start = middleIdx+1;
        }
        
    } else if (middleData < k) {//最后一个k在右半部分
        start = middleIdx + 1;
    } else {//最后一个k在左半部分
        end = middleIdx - 1;
    }
    return GetLastK(data, length, k, start, end);
}
//MARK:面试题38:数字在排序数组中出现的次数
int GetNumberOfK(int *data, int length, int k) {
    int number = 0;
    if (data != NULL && length > 0) {
        int first = GetFirstK(data, length, k, 0, length-1);
        int last = GetLastK(data, length, k, 0, length-1);
        
        if (first > -1 && last > -1) {
            number = last - first + 1;
        }
    }
    return number;
}

//MARK:面试题24:二叉搜索树的后序遍历序列：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历序列
//最后一个数字是根节点，数组中前面的数字可以分为2组，
//第一部分是左子树，都比根节点小
//第二部分是右子树，都比根节点大
bool VerifySequenceOfBST(int sequence[], int length) {
    if (sequence == NULL || length <= 0) {
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


//MARK:面试题23:从上往下打印二叉树
//思路:每次打印一个节点的时候，若果该节点有子节点，则把该节点的子节点入队。
//然后从队列头部取出一个节点
void PrintBinaryTreeTopToBottom(BinaryTreeNode *pRoot) {
    if (pRoot == NULL) {
        return;
    }
    queue<BinaryTreeNode *>nodeQueue;
    nodeQueue.push(pRoot);
    while (!nodeQueue.empty()) {
        BinaryTreeNode *node = nodeQueue.front();
        nodeQueue.pop();
        cout << node->m_nValue << endl;
        
        if (node->m_pLeft) {
            nodeQueue.push(node->m_pLeft);
        }
        if (node->m_pRight) {
            nodeQueue.push(node->m_pRight);
        }
        
    }
}

//MARK:构建二叉树
void InsertNode(BinaryTreeNode *pRoot, int value) {
    BinaryTreeNode *node = new BinaryTreeNode(value);
    
    if (pRoot == NULL) {
        pRoot = node;
        return;
    }
    if (value <= pRoot->m_nValue) {
        if (pRoot->m_pLeft == NULL) {
            pRoot->m_pLeft = node;
        } else {
            InsertNode(pRoot->m_pLeft, value);
        }
    } else {
        if (pRoot->m_pRight == NULL) {
            pRoot->m_pRight = node;
        } else {
            InsertNode(pRoot->m_pRight, value);
        }
    }
}

//MARK:前序遍历二叉树递归实现
void PreOrderBinaryTreeRecursive(BinaryTreeNode *pRoot) {
    if (pRoot == NULL) {
        return;
    }
    cout << pRoot->m_nValue << endl;
    PreOrderBinaryTreeRecursive(pRoot->m_pLeft);
    PreOrderBinaryTreeRecursive(pRoot->m_pRight);
}
//MARK:前序遍历二叉树非递归实现
void PreOrderBinaryTreeNoRecursive(BinaryTreeNode *pRoot) {
    if (pRoot == NULL) {
        return;
    }
    stack<BinaryTreeNode *> stack;
    stack.push(pRoot);
    while (!stack.empty()) {
        BinaryTreeNode *top = stack.top();
        cout << top->m_nValue << endl;
        stack.pop();
        if (top->m_pRight) {
            stack.push(top->m_pRight);
        }
        if (top->m_pLeft) {
            stack.push(top->m_pLeft);
        }
    }
}
//MARK:中序遍历二叉树递归实现
void InOrderBinaryTreeRecursive(BinaryTreeNode *root) {
    if (root == NULL) {
        return;
    }
    InOrderBinaryTreeRecursive(root->m_pLeft);
    cout << root->m_nValue << endl;
    InOrderBinaryTreeRecursive(root->m_pRight);
}

//MARK:中序遍历二叉树非递归实现
void InOrderBinaryTreeNoRecursive(BinaryTreeNode *root) {
    if (root == NULL) {
        return;
    }
    stack<BinaryTreeNode *>stack;
    BinaryTreeNode *node = root;
    while (node || !stack.empty()) {
        if (node) {
            stack.push(node);
            node = node->m_pLeft;
        } else {
            node = stack.top();
            cout << node->m_nValue << endl;
            stack.pop();
            node = node->m_pRight;
        }
    }
}

//MARK:后序遍历二叉树递归实现
void PostOrderBinaryTreeRecursive(BinaryTreeNode *root) {
    if (root == NULL) {
        return;
    }
    PostOrderBinaryTreeRecursive(root->m_pLeft);
    PostOrderBinaryTreeRecursive(root->m_pRight);
    cout << root->m_nValue << endl;
}
//MARK:后序遍历二叉树非递归实现
void PostOrderBinaryTreeNoRecursive(BinaryTreeNode *root) {
    if (root == NULL) {
        return;
    }
    //借助两个stack
    stack<BinaryTreeNode *> stack1;
    stack<BinaryTreeNode *> stack2;
    stack1.push(root);
    while (!stack1.empty()) {
        BinaryTreeNode *node = stack1.top();
        stack1.pop();
        stack2.push(node);
        if (node->m_pLeft) {
            stack1.push(node->m_pLeft);
        }
        if (node->m_pRight) {
            stack1.push(node->m_pRight);
        }
    }
    while (!stack2.empty()) {
        BinaryTreeNode *node = stack2.top();
        stack2.pop();
        cout << node->m_nValue << endl;
    }

}
//MARK:层次遍历二叉树
void BFS_BinaryTreeRecursive(BinaryTreeNode *root) {
    queue<BinaryTreeNode*>Q;
    Q.push(root);
    while (!Q.empty()) {
        BinaryTreeNode *node = Q.front();
        Q.pop();
        cout << node->m_nValue;
        if (node->m_pLeft) {
            Q.push(node->m_pLeft);
        }
        if (node->m_pRight) {
            Q.push(node->m_pRight);
        }
    }
}


bool DoesTreeHasTree2(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2) {
    if (pRoot2 == NULL) {
        return true;
    }
    if (pRoot1 == NULL) {
        return false;
    }
    if (pRoot1->m_nValue != pRoot2->m_nValue) {
        return false;
    }
    return DoesTreeHasTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) && DoesTreeHasTree2(pRoot1->m_pRight, pRoot2->m_pRight);
    
}
//MARK:面试题18，两颗二叉树A和B，判断B是不是A的子结构
bool HasSubTree(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2) {
    bool result = false;
    //先在A中找到与B的根节点值相同的节点R
    if (pRoot1->m_nValue == pRoot2->m_nValue) {
        //判断A中以R为根节点的子树是不是和B具有相同的结构
        result = DoesTreeHasTree2(pRoot1, pRoot2);
    }
    if (!result) {
        result = HasSubTree(pRoot1->m_pLeft, pRoot2);
    }
    
    if (!result) {
        result = HasSubTree(pRoot1->m_pRight, pRoot2);
    }
    return result;
}

//MARK:面试题6：根据前序遍历、中序遍历序列重建二叉树,假设序列中不含重复数字
BinaryTreeNode* ConstructCore(int *startPreOrder, int *endPreOrder, int *startInOrder, int *endInOrder) {
    int rootValue = startPreOrder[0];
    BinaryTreeNode *root = new BinaryTreeNode(rootValue);
    
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

int main(int argc, const char * argv[]) {
////     insert code here...
//    
    BinaryTreeNode *root = new BinaryTreeNode(5);

    InsertNode(root, 3);
    InsertNode(root, 2);
    InsertNode(root, 4);
    InsertNode(root, 7);
    InsertNode(root, 8);
    InOrderBinaryTreeRecursive(root);
//
//    cout<< isCousins(root, 5, 7) << endl;
//    
////    PrintBinaryTreeTopToBottom(root);
////
////    int array[10] = {1,2,3,3,4,6,8,8,8,10};
////    cout << GetNumberOfK(array, 10, 1) << endl;
//
    return 0;
}
