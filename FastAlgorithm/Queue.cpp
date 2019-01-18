//
//  Queue.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2018/12/22.
//  Copyright © 2018年 2dfire. All rights reserved.
//

#include "Queue.hpp"
#include <stack>
using namespace std;

template <typename T>
class CQueue {
public:
    void push(int node) {
        stackIn.push(node);
    }
    
    int pop() {
        if (stackOut.size() <= 0) {
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
    
private:
    stack<int>stackIn;
    stack<int>stackOut;
};


struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) {
            return NULL;
        }
        if (head->next == NULL) {
            return head;
        }
        ListNode *current = head;
        while (current->next != NULL) {
            if (current->next->val == current->val) {
                current->next = current->next->next;
            } else {
                current = current->next;
            }
        }
        return head;
    }
};
