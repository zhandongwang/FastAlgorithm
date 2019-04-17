//
//  Sort.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2019/1/9.
//  Copyright © 2019年 2dfire. All rights reserved.
//

#include "Sort.hpp"
#include <iostream>
using namespace std;

int BinaryS(int array[], int n , int value) {
    int left = 0;
    int right = n -1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (array[middle] == value) {
            return middle;
        } else if (array[middle] < value) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}


//二分查找
int BinarySearch(int array[], int n, int value) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int middle = left + ((right - left) >> 1);
        if (array[middle] > value) {
            right = middle - 1;
        } else if (array[middle] < value) {
            left = middle + 1;
        } else {
            return middle;
        }
    }
    return -1;
}
//快速排序
void quicksort(int a[], int left, int right) {
    int i, j, t, temp;
    if (left > right) {
        return;
    }
    temp = a[left];//temp中存储基准数
    i = left;
    j = right;
    while (i != j) {
        while (a[j] >= temp && i < j) {
            j--;
        }
        while (a[i]<= temp && i < j) {
            i++;
        }
        if (i < j) {//交换两个数在数组中的位置
            t = a[i];
            a[i]=a[j];
            a[j]=t;
        }
    }
    //将基准数归位
    a[left] = a[i];
    a[i] = temp;
    quicksort(a,left, i-1);
    quicksort(a,i+1, right);
}

//冒泡排序
void BubbleSort(int a[], int len) {
    int temp = 0;
    int k = len;
    int flag = k;//flag用于记录每次扫描发生交互的位置
    while (flag > 0) {
        k = flag;
        flag = 0;
        for (int j = 1; j < k; ++j) {
            if (a[j] < a[j-1]) {
                temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
                flag = j;
            }
        }
    }
}



//int main(int argc, const char * argv[]) {
////    int array[6] = {1,2,4,6,9};
////    BinaryS(array,5,1);
//    int a[10] = {6,1,2,7,9, 3, 4, 5, 10, 8};
////    quicksort(a, 0, 9);
//    BubbleSort(a, 10);
//    
//    for (int i = 0; i < 10; ++i) {
//        cout << a[i] << "\t";
//    }
//    cout <<endl;
//    
//}
