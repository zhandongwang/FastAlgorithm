//
//  Array.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2019/1/21.
//  Copyright © 2019年 2dfire. All rights reserved.
//

#include "Array.hpp"
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <set>
using namespace std;

//面试题31:连续子数组的最大和
bool g_InvalidInput = false;
int MaxSumOfSubArray(int *pdata, int nLength) {
    if (pdata == NULL || nLength <= 0) {
        g_InvalidInput = true;
        return 0;
    }
    g_InvalidInput = false;
    int curSum = 0;
    int greatSum = INT_MAX;
    
    for (int i = 0; i < nLength; ++i) {
        if (curSum <= 0) {//如果当前和小于等于0， 加上pdata[i]后必然小于等于pdata[i]，所以抛弃当前和
            curSum = pdata[i];
        } else {
            curSum += pdata[i];
        }
        
        if (curSum > greatSum) {
            greatSum = curSum;
        }
    }
    return greatSum;
}


//面试题14，调整数组元素顺序，使奇数位于偶数前面
//思路：元素交换
void ResortArray(int *pData, unsigned int length, bool(*func)(int)) {
    if (pData == NULL || length == 0) {
        return;
    }
    int *pBegin = pData;
    int *pEnd = pData + length - 1;
    while (pBegin < pEnd) {
        while (pBegin < pEnd && !func(*pBegin)) {//找到第一个偶数
            pBegin++;
        }
        while (pBegin < pEnd && func(*pEnd)) {//找到第一个奇数
            pEnd--;
        }
        if (pBegin < pEnd) {
            int temp = *pBegin;
            *pBegin = *pEnd;
            *pEnd = temp;
        }
    }
}

bool isEven(int n) {
    return (n & 1) == 0;
}

//面试题3:二维数组中查找
bool findValue(int* matrix, int rows, int columns, int number) {
    bool found = false;
    
    if (matrix != NULL && rows > 0 && columns > 0) {
        int row = 0;
        int column =  columns - 1;
        
        while(row < rows && column > 0){
            if (matrix[row * columns + column] == number) {
                found = true;
                cout << "Found in (" << row << ","<< column << ")";
                break;
            }
            else if(matrix[row * columns + column] > number) {
                --column;
            } else {
                ++row;
            }
        }
    }
    return found;
}

void testFindValue() {
    int matrix[4][4] = {{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
    bool ret =  findValue(matrix[0], 4, 4, 9);
    if (!ret) {
        cout << "Not found" << endl;
    }
}
