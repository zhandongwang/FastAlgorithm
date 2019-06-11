//
//  Sort.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2019/1/9.
//  Copyright © 2019年 2dfire. All rights reserved.
//

#include "Sort.hpp"
#include <iostream>
#include <vector>
using namespace std;

//MARK:二分查找
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

//MARK:数组中的第K个最大元素
// k-1个小于key的、len-k个大于Key的

int KthInArray(vector<int>&data, int left, int right, int k){
    int i = left, j = right;
    int pivot = data[j];
    //从大到小排序
    if (left < right) {
        while (i < j) {
            while (i < j && data[i] >= pivot) {//从左边找第一个比pviot小的数
                i++;
            }
            data[j] = data[i];
            while (i < j && data[j] < pivot) {
                j--;
            }
            data[i] = data[j];
        }
        data[j] = pivot;//此时i = j
        
        int which_max = i-left+1;//which_max表示第几大的数
        if (which_max == k) {
            return pivot;
        } else if (which_max < k) {//第k大的数在k的右边
            return KthInArray(data, i+1, right, k-which_max);
        } else {
            return KthInArray(data, left, i-1, k);
        }
    } else {
        return pivot;
    }
}


//MARK:快速排序--填坑法
int partition(int a[], int left, int right) {
    int p = a[left];//选取第一个元素为参考值，并将这个点变成一个坑
    while (left<right) {
        while (a[right]>=p && left<right) {
            right--;
        }
        a[left] = a[right];//将此元素填到之前的坑中，并将此节点作为新的坑
        
        while (a[left]<p && left<right) {
            left++;
        }
        a[right]=a[left];
    }
    a[left] = p;//将参考值填入left的位置
    return left;
}

void qs(int a[], int left, int right){
    if(left >= right){
        return;
    }
    int mid = partition(a, left, right);
    qs(a, left, mid-1);
    qs(a, mid+1, right);
}

//MARK:冒泡排序
void BubbleSort(int a[], int len) {
    int temp = 0;
    int k = len;
    int flag = k;//flag用于记录每次扫描发生交换的位置
    while (flag > 0) {
        k = flag;
        flag = 0;
        for (int j = 1; j < k; ++j) {
            if (a[j] < a[j-1]) {
                temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
                flag = j;//更新flag
            }
        }
    }
}


/*
int main(int argc, const char * argv[]) {
    vector<int>v = {2,1,4,9,6};
    cout << KthInArray(v, 0, 4, 4) <<endl;
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
}
 */
