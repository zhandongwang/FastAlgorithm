//
//  Sort.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2019/1/9.
//  Copyright © 2019年 2dfire. All rights reserved.
//

#include "Sort.hpp"
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
int a[101];
void quicksort(int left, int right) {
    int i, j, t, temp;
    if (left > right) {
        return;
    }
    temp = a[left];
    i = left;
    j = right;
    while (i != j) {
        while (a[j] >= temp && i < j) {
            j--;
        }
        while (a[i]<= temp && i < j) {
            i++;
        }
        if (i < j) {
            t = a[i];
            a[i]=a[j];
            a[j]=t;
        }
    }
    a[left] = a[i];
    a[j] = t;
    quicksort(left, i-1);
    quicksort(i+1, right);
    
}
