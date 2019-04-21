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
#include <string>
#include <algorithm>

using namespace std;

//数组整体右移动k位
void rotateArray(vector<int>& nums, int k) {
    int n = nums.size();
    if (n == 0 || k % n == 0) {
        return;
    }
    
    std::reverse(nums.begin(), nums.begin()+n-k);
    std::reverse(nums.end()-k, nums.end());
    std::reverse(nums.begin(), nums.end());
}


int* mergeSortedArray(int nums1[], int m, int nums2[], int n) {
    int p = m-- + n-- -1;//先计算P然后分别对m,n--
    while (m >= 0 && n >= 0) {
        nums1[p--] = nums1[m] > nums2[n] ? nums1[m--] : nums2[n--];
    }
    
    while (n >= 0) {
        nums1[p--] = nums2[n--];
    }
    return nums1;
}

//MARK:leetcode--169：找众数
//给定一个大小为 n 的数组，找到其中的众数。众数是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。
//思路:从第一个数开始count=1  遇到相同的就加1  遇到不同的就减1.减到0就重新换个数开始计数
int findMajorItem(int array[], int length) {
    int count = 1;
    int major = array[0];
    for (int i = 1; i< length; ++i) {
        if (array[i] == major) {
            count++;
        } else {
            count--;
            if (count == 0) {
                major = array[i+1];
            }
        }
    }
    return major;
}



//MARK:leetcode--136. 只出现一次的数字
//1. 交换律 a^b^c <=> a^c^b
//2. 0异或任何数仍为任何数
//3. 异或自己为0
//2 ^ 3 ^ 2 ^ 4 ^ 4等价于 2 ^ 2 ^ 4 ^ 4 ^ 3 => 0 ^ 0 ^3 => 3
int singleNumber(int array[], int length) {

    int result = 0;
    for (int i = 0; i < length; ++i) {
        result = result ^ array[i];
    }
    return result;
}


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

//MARK:面试题3:二维数组查找
//给你一个 n*m 的二维数组，每行元素保证递增，每列元素保证递增，试问如何使用优秀的时间复杂度找到某个数字（或者判断不存在）。
//从上到下，从右向左搜索
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

bool judge(char c) {
    return ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9');
}
//MARK:验证回文字
bool testString(string str) {
    if (str.empty()) {
        return true;
    }
    long int i = 0, j = str.length()-1;
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    while (i < j) {
        while (i < j && !judge(str.at(i))) {
            i++;
        }
        while (i < j && !judge(str.at(j))) {
            j--;
        }
        cout << str.at(i) << "---" << str.at(j);
        
        if (str.at(i) != str.at(j)) {
            return  false;
        } else {
            i++;
            j--;
        }
    }
    return true;
}


int main(int argc, const char * argv[]) {
    //     insert code here...
    
    vector<int>nums = {1,2,3,4,5,6,7};
    rotateArray(nums, 3);
    for (vector<int>::iterator it = nums.begin(); it!=nums.end(); it++) {
        cout << *it <<" ";
    }
    return 0;
}
