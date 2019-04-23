//
//  Heap.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2019/4/19.
//  Copyright © 2019年 2dfire. All rights reserved.
//

#include "Heap.hpp"
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class MinHeap {

public:
    vector<int>data;
    
    MinHeap(int capacity) {
        data = vector<int>(capacity);
    }
    MinHeap(){
        data = vector<int>();
    }

    void swapElement(vector<int> &data, unsigned long i, unsigned long j) {
        if (i <0 || i>= data.size() || j<0 || j >= data.size()) {
            return;
        }
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
    //堆中插入元素
    //新插入的元素和父节点的值作比较，比父节点大则交互
    void siftUP(unsigned long index) {
        if (data.size() == 1) {
            return;
        }
        unsigned long parentIdx = parent(index);
        while (index > 0 && data.at(index) < data.at(parentIdx)) {
            swapElement(data, index, parentIdx);
            index = parentIdx;
        }
        
    }
    void insertElemetn(int e) {
        data.push_back(e);//末尾插入
        siftUP(data.size() -1);
        printData();
    }
    
    void printData() {
        for (vector<int>::iterator it = data.begin(); it != data.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
    
private:
    unsigned long parent(unsigned long index) {
        return (index-1) / 2;
    }
    unsigned long leftChild(unsigned long index) {
        return index*2 + 1;
    }
    unsigned long rightChild(unsigned long index) {
        return index*2 + 2;
    }
    
};

int main(int argc, const char * argv[]) {
    MinHeap heap = MinHeap();
    heap.insertElemetn(3);
    heap.insertElemetn(5);
    heap.insertElemetn(7);
    heap.insertElemetn(9);
    heap.insertElemetn(11);
    heap.insertElemetn(13);
    heap.insertElemetn(6);
    
    return 0;
}
