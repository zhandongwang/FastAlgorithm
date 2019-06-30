//
//  Search.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2019/6/19.
//  Copyright © 2019 2dfire. All rights reserved.
//

#include "Search.hpp"
#include <vector>
#include <iostream>
using namespace std;

//MARK:二分查找
int BinarySearch(int key, int array[], int length) {
    if (length == 0) {
        return -1;
    }
    int low = 0;
    int high = length -1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (array[mid] == key) {
            return mid;
        } else if (array[mid] > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

unsigned long BinarySearch(int key, vector<int>array) {
    if (array.size() == 0) {
        return -1;
    }
    unsigned long low = 0;
    
    unsigned long high = array.size() -1;
    while (low <= high) {
        unsigned long mid = low + (high - low) / 2;
        if (array[mid] < key) {
            low = mid + 1;
        } else if (array[mid] > key) {
            high = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
    
}

void printBoolMatrix(bool array[][3], int length) {
     for (int i = 0; i < length; i++) {
         for (int j = 0; j < 3; j++) {
             cout <<"<"<< i << ","<< j << ">" << (array[i][j] == true ? "*" : " ") << "     ";
         }
         cout << endl;
     }
    
    
}

/*
int main(int argc, const char * argv[]) {
//    int array [5] = {2,5,9,13,58};
//    cout << BinarySearch(2, array, 5) <<endl;
    
//    vector<int>nums = {2,5,9,13,58};
//    cout << BinarySearch(58, nums) << endl;
    int N = 10;
    string s = "";
    for (int n = N; n >0; n/=2) {
        s = to_string(n % 2) + s;
    }
    cout << s << endl;

    bool array[3][3] = {
        {true,false,true},
        {false,true,false},
        {true,false,true},
    };
    printBoolMatrix(array, 3);
    
    
    return 0;
    
}
*/
