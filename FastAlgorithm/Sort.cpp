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

//MARK:数组中的第K个最大元素
// k-1个小于key的、len-k个大于Key的

int KthInArray(vector<int>&data, int left, int right, int k){
    int i = left, j = right;
    int pivot = data[j];//选最后一个值作为支点
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
        
        int which_max = i-left+1;//which_max表示当前i指向第几大的数
        if (which_max == k) {
            return pivot;
        } else if (which_max < k) {//第k大的数在i的右边
            return KthInArray(data, i+1, right, k-which_max);
        } else {//第k大的数在i的左边
            return KthInArray(data, left, i-1, k);
        }
    } else {
        return pivot;
    }
}

//MARK:插入排序
void InsertSort(int a[], int n) {
    for (int j = 1; j < n; ++j) {//开始的时候把第1个元素作为有序组
        int k = a[j];//未排序的第一个数
        int i = j - 1;//有序的最后一个数的下标
        while (i >= 0 && k < a[i]) {//比k大的数都要后移
            a[i+1] = a[i];
            i--;
            
        }
        a[i+1] = k;
    }
}

//MARK:快速排序--挖坑填坑法,新坑填旧坑，支点填入最后一个坑
//支点的选择是关键点，选最大火最小，会导致排序一边倒，性能受到影响
//时间复杂度O(nlogn),空间复杂度O(1)
int partition(int a[], int left, int right) {
    int p = a[left];//选取第一个元素作为坑，并暂存其值
    while (left<right) {
        while (a[right]>=p && left<right) {
            right--;
        }
        a[left] = a[right];//将此元素填到之前的坑中，并将此节点作为新坑
        
        while (a[left]<p && left<right) {
            left++;
        }
        a[right]=a[left];//将此元素填到之前的坑中，并将此节点作为新坑
    }
    a[left] = p;//将暂存值填入坑中
    return left;
}

void QuickSort(int a[], int left, int right){
    if(left >= right){
        return;
    }
    int mid = partition(a, left, right);
    QuickSort(a, left, mid-1);
    QuickSort(a, mid+1, right);
}

//MARK:冒泡排序:相邻元素比较，每次找到最大的元素放到末尾，适合基本有序的数据。
//时间复杂度O(n*n),空间复杂度O(1)
void BubbleSort2(int a[], int len) {
    for (int i = 0; i < len-1; i++) {
        bool isChanged = false;
        for (int j = 0; j < len-1-i; j++) {
            if (a[j] > a[j+1]) {
                int temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
                isChanged = true;
            }
        }
        if (!isChanged) {
            break;
        }
    }
}

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
    int a[] = {3,1,2,9,7,6,8,5,4};
    int len = sizeof(a)/sizeof(int);
//    BubbleSort2(a, 9);
    InsertSort(a, len);
    for (int i = 0; i < 9; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
    
//    vector<int>v = {2,1,4,9,6};
//    cout << KthInArray(v, 0, 4, 4) <<endl;
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
