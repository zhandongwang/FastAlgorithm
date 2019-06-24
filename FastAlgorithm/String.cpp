//
//  String.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2019/1/21.
//  Copyright © 2019年 2dfire. All rights reserved.
//

#include "String.hpp"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

struct Book {
    char title[50];
    int  book_id;
};

//面试题49:字符串转成整数
enum Status {kValid = 0, kInValid};
int g_nStatus = kValid;

long long StrToIntCore(const char *digit, bool minus) {
    long long num = 0;
    while (*digit != '\0') {
        cout <<"current digit is:"<< *digit<<endl;
        cout <<"digit is:"<< *digit - '0'<<endl;
        if (*digit >= '0' && *digit <= '9') {
            int flage = minus ? -1 : 1;
            num = num * 10 + flage * (*digit - '0');
            //溢出问题
            if ((!minus && num > 0x7FFFFFFF) || (minus && (signed int)num < 0x80000000)) {
                num = 0;
                break;
            }
            digit++;
        } else {
            num = 0;
            break;
        }
    }
    if (*digit == '\0') {
        g_nStatus = kValid;
    }
    return num;
}

int StrToInt(const char *str) {
    g_nStatus = kInValid;
    long long num = 0;
    //字符串为NULL或""
    if (str == NULL || *str == '\0') {
        return (int)num;
    }
    bool minus = false;
    if (*str == '+') {
        ++str;
    } else if (*str == '-') {
        ++str;
        minus = true;
    }
    //考虑只有一个'+'或者'-'的情况
    if (*str != '\0') {
        num = StrToIntCore(str, minus);
    }
    return (int)num;
}

void ReverseWord(char *pBegin, char *pEnd) {
    if (pBegin == NULL || pEnd == NULL) {
        return;
    }
    while (pBegin < pEnd) {
        char temp = *pBegin;
        *pBegin = *pEnd;
        *pEnd = temp;
        pBegin++;
        pEnd--;
    }
    
}
//面试题42：反转字符串  eg I am a student --> student a am I

char* ReverseSentence(char *pdata) {
    if (pdata == NULL) {
        return NULL;
    }
    
    char *pBegin = pdata;
    char *pEnd = pdata;
    while (*pEnd != '\0') {
        ++pEnd;
    }
    pEnd--;
    //反转整个句子
    ReverseWord(pBegin, pEnd);
    //反转单词
    pBegin = pEnd = pdata;
    while (*pBegin != '\0') {
        if (*pBegin == ' ') {
            pBegin++;
            pEnd++;
        } else if (*pEnd == ' ' || *pEnd == '\0' ) {
            ReverseWord(pBegin, --pEnd);
            pBegin = ++pEnd;
        } else {
            pEnd++;
        }
    }
    return pdata;
}

//面试题4:替换字符串中的空格为20%  从后向前
void replaceBlank(char string[], int length) {
    if (string == NULL || length <= 0) {
        return;
    }
    int originalLength = 0;
    int numberOfBlank = 0;
    int i = 0;
    //统计字符串长度和空格数
    while (string[i] != '\0') {
        ++originalLength;
        if (string[i] == ' ') {
            ++numberOfBlank;
        }
        ++i;
    }
    //
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

//面试题12：打印1到最大的n位数
//思路:
void PrintNumber (char *number) {
    bool isBeginning0 = true;
    unsigned long nLength = strlen(number);
    for (int i = 0; i < nLength; ++i) {
        if (isBeginning0 && number[i] != '0') {
            isBeginning0 = false;
        }
        if (!isBeginning0) {
            printf("%c", number[i]);
        }
    }
    printf("\t");
}

void PrintToMaxOfNdigitsRecursively(char *number, int length, int index) {
    if (index == length - 1 ) {//到达最低位
        PrintNumber(number);
        return;
    }
    for (int i = 0 ; i < 10 ; ++i) {
        number[index + 1] = i + '0';//从高位到低位依次置0
        PrintToMaxOfNdigitsRecursively(number, length, index + 1);
    }
    printf("\n");
}

void Print1ToMaxOfDigits(int n) {
    if (n <= 0) {
        return;
    }
    char *number = new char[n + 1];
    number[n] = '\0';
    for (int i = 0; i < 10; ++i) {
        number[0] = i + '0';//修改最高位 0~9
        PrintToMaxOfNdigitsRecursively(number, n, 0);//向后修改低位
    }
    delete [] number;
}



//int main(int argc, const char * argv[]) {
////    char digit[] = "";
////    cout << StrToInt(digit)<< endl <<"g_nStatus is:" << g_nStatus <<endl;
//    Print1ToMaxOfDigits(3);
////    int num = 0;
////    for (int i = 0 ; i < 10 ; ++i) {
////        num = num + i;
////        printf("%d",i);
////    }
//    struct Book book1;
//    struct Book book2;
//    
//    strcpy(book1.title, "C++");
//    book1.book_id = 22;
//    
//    cout << book1.book_id << book1.title;
//    
//}
