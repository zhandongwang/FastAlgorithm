//
//  main.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2018/12/12.
//  Copyright © 2018年 2dfire. All rights reserved.
//

#include <iostream>
//#include "BinaryTree.cpp"

using namespace std;

void testFindValue();
int reverse(int x);
long long Fibonacci(unsigned n);


//面试题9
/*
 f(n) = 0  n = 0;
 f(n) = 1  n = 1;
 f(n) = f(n - 1) + f(n - 2)  n > 1;
 思路：从下向上计算，避免重复计算，时间复杂度为O(n)
*/

long long Fibonacci(unsigned n) {
    int  result[2] = {0 , 1};
    if (n < 2) {
        return result[n];
    }
    
    long long fibOne = 1;
    long long fibTwo = 0;
    long long fibN = 0;
    for (unsigned i = 2; i <= n ; ++i) {
        fibN = fibOne + fibTwo;
        fibOne = fibTwo;
        fibTwo = fibN;
        cout << fibN << endl;
    }
    return fibN;
}

//有符号整数反转
int reverse(int x) {
    int rev = 0;
    while (x != 0) {
        int pop = x % 10;
        x /= 10;
        //溢出检查
        if (rev > INT_MAX/10 || (rev == INT_MAX/10 && pop > 7)) {
            return 0;
        }
        if (rev > INT_MIN/10 || (rev == INT_MIN/10 && pop < -8)) {
            return 0;
        }
    }
    return rev;
}




//int main(int argc, const char * argv[]) {
//    // insert code here...
////    char gretting[] = "Hello world";
////    cout << strlen(gretting);
////
//    BinaryTreeNode *root = new BinaryTreeNode();
//    root->m_nValue = 8;
//    root->m_pLeft = NULL;
//    root->m_pRight = NULL;
//
//    InsertNode(root, 6);
//    InsertNode(root, 10);
//    InsertNode(root, 5);
//    InsertNode(root, 7);
//    InsertNode(root, 9);
//    InsertNode(root, 11);
//
//
//    return 0;
//}
