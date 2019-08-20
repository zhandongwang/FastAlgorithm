//
//  Queue.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2018/12/22.
//  Copyright © 2018年 2dfire. All rights reserved.
//

#include "Queue.hpp"
#include <stack>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

#define QUEUE_CAPACITY 10

class ArrayQueue {
private:
    string items[QUEUE_CAPACITY];
    int head = 0;
    int tail = 0;
public:
    bool enqueue(string x) {
        if (tail == QUEUE_CAPACITY) {
            if (head == 0) {
                return false;
            }
            for (int i = head; i < tail; ++i) {
                items[i-head] = items[i];
            }
            tail -= head;
            head = 0;
        }
        items[tail] = x;
        tail++;
        return true;
    }
    string dequeue(){
        if (head == tail) {
            return nullptr;
        }
        string value = items[head];
        head++;
        return value;
    }
    int size() {
        return sizeof(items) / sizeof(items[0]);
    }
};
struct Node {
    string value;
    Node *next;
    Node(string item):value(item),next(NULL){};
};

class LinkedQueue {
private:
    int size = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
    
public:
    bool enqueue(string item) {
        Node *newNode = new Node(item);
        if (size == 0) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        size++;
        
        return true;
    }
    string dequeue(){
        if (size == 0) {
            return nullptr;
        }
        if (size == 1) {
            tail = nullptr;
        }
        string value = head->value;
        head = head->next;
        size--;
        
        return value;
    }
};


class CircleQueque {
private:
    string items[QUEUE_CAPACITY];
    int head = 0;
    int tail = 0;
    
public:
    bool enqueue(string x) {
        if ((tail+1) % QUEUE_CAPACITY == head) {//队满
            return false;
        }
        items[tail] = x;
        tail = (tail+1) % QUEUE_CAPACITY;

        return true;
    }
    
    string dequeue(){
        if (head == tail) {//队空
            return nullptr;
        }
        string value = items[head];
        head = (head+1) % QUEUE_CAPACITY;
        return value;
    }
};


//int main(int argc, const char * argv[]){
//    ArrayQueue queue = ArrayQueue();
//    queue.enqueue("1");
//    queue.enqueue("2");
//    queue.enqueue("3");
//    cout << queue.size();
//}
