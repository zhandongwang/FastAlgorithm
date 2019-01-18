//
//  main.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2018/12/12.
//  Copyright © 2018年 2dfire. All rights reserved.
//

#include <iostream>
using namespace std;
void testFindValue();
int reverse(int x);
long long Fibonacci(unsigned n);

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

//面试题4:替换字符串中的空格  从后向前
void replaceBlank(char string[], int length) {
    if (string == NULL || length <= 0) {
        return;
    }
    int originalLength = 0;
    int numberOfBlank = 0;
    int i = 0;
    while (string[i] != '\0') {
        ++originalLength;
        if (string[i] == ' ') {
            ++numberOfBlank;
        }
        ++i;
    }
    int newLength = originalLength + numberOfBlank * 2;
    int indexOfOriginal = originalLength;
    int indexOfNew = newLength;
    
    while (indexOfOriginal > 0 && indexOfNew > indexOfOriginal) {
        if (string[indexOfOriginal] == ' ') {
            string[indexOfNew--] = '0';
            string[indexOfNew--] = '2';
            string[indexOfNew--] = '\%';
        } else {
            string[indexOfNew--] = string[indexOfOriginal];
        }
        --indexOfOriginal;

    }
}

int main(int argc, const char * argv[]) {
    // insert code here...

    int array[5] = {1,4,7,8,9};
    ResortArray(array, 5, isEven);
    
    for (int i = 0; i < 5; ++i) {
        cout << array[i] << " ";
    }
    
    return 0;
}
