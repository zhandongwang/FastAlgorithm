//
//  Stack.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2019/8/15.
//  Copyright © 2019 2dfire. All rights reserved.
//

#include "Stack.hpp"
#include<stack>
#include <string>
#include <iostream>

using namespace std;

class FLQueue {
private:
    stack<int>stackIn;
    stack<int>stackOut;
public:
    void push(int node) {
        stackIn.push(node);
    }
    int pop() {
        if (stackOut.size() == 0) {
            while (stackIn.size() > 0) {
                int data = stackIn.top();
                stackIn.pop();
                stackOut.push(data);
            }
        }
        if (stackOut.size() == 0) {
            throw new exception;
        }
        int head = stackOut.top();
        stackOut.pop();
        
        return head;
    }
    unsigned long size() {
        return stackIn.size() + stackOut.size();
    }
};

//MARK:leetcode---155最小栈
class MinStack {

private:
    stack<int>minStack;
public:
    MinStack(){
        minStack = stack<int>();
    }
    void push(int x) {
        if (minStack.empty()) {
            minStack.push(x);
            minStack.push(x);
        } else {
            int top = minStack.top();
            if (top < x) {
                minStack.push(x);
                minStack.push(top);
            } else {
                minStack.push(x);
                minStack.push(x);
            }
        }
    }
    
    void pop() {
        minStack.pop();
        minStack.pop();
    }
    int top() {
        int min = minStack.top();
        minStack.pop();
        int top = minStack.top();
        minStack.push(min);
        
        return top;
    }
    int getMin() {
        return minStack.top();
    }
};



//MARK:leetcode20---有效字符串
bool isValid(string s) {
    if (s.empty()) {
        return true;
    }
    stack<char>stackIn;
    for (string::iterator it = s.begin(); it != s.end(); ++it) {
        if (*it == '{' || *it == '[' || *it == '(') {
            stackIn.push(*it);
        } else {
            if (stackIn.size() == 0) {
                return false;
            }
            
            char top = stackIn.top();
            stackIn.pop();
            switch (*it) {
                case '}':
                    if (top != '{') {
                        return false;
                    }
                    break;
                case ']':
                    if (top != '[') {
                        return false;
                    }
                    break;
                case ')':
                    if (top != '(') {
                        return false;
                    }
                    break;
                default:
                    return false;
            }
        }
    }
    return stackIn.size() == 0;
}


/*
int main(int argc, const char * argv[]) {
    MinStack *minStack = new MinStack();
    minStack->push(-2);
    minStack->push(0);
    minStack->push(-3);
    cout << minStack->getMin();   //--> 返回 -3.
    minStack->pop();
    cout << minStack->top();      //--> 返回 0.
    cout << minStack->getMin();   //--> 返回 -2.
    
}*/
