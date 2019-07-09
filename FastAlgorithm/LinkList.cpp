//
//  LinkList.cpp
//  FastAlgorithm
//
//  Created by 凤梨 on 2018/12/13.
//  Copyright © 2018年 2dfire. All rights reserved.
//

#include "LinkList.hpp"
#include <iostream>
#include <stack>
using namespace std;

struct ListNode {
    int m_nValue;
    ListNode *m_pNext;
    ListNode(int x):m_nValue(x),m_pNext(nullptr){}
};

void PrintLinkList(ListNode *pHead) {
    while (pHead) {
        cout << pHead->m_nValue << " ";
        pHead = pHead->m_pNext;
    }
    cout << endl;
}

unsigned int GetListLength(ListNode *pHead) {
    unsigned int length = 0;
    ListNode *node = pHead;
    while (node->m_pNext != nullptr) {
        ++length;
        node = node->m_pNext;
    }
    return length;
}

//MARK:面试题56 链表中环的入口节点  https://www.qiujiawei.com/leetcode-problem-142/
ListNode *findCycleEntry(ListNode *head) {
    if (!head || head->m_pNext == nullptr) {
        return nullptr;
    }
    ListNode *pFast = head;
    ListNode *pSlow = head;
    while (pFast != nullptr && pFast->m_pNext->m_pNext != nullptr) {
        pFast = pFast->m_pNext->m_pNext;
        pSlow = pSlow->m_pNext;
        if (pFast == pSlow) {
            break;//此时slow和fast相遇
        }
    }
    pSlow = head;//slow指向起点
    while (pSlow != pFast) {
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext;
    }
    return pSlow;
}


//MARK:链表是否有环
bool hasCircle(ListNode *head) {
    if (!head || head->m_pNext == nullptr) {
        return false;
    }
    ListNode *pFast = head;
    ListNode *pSlow = head;
    while (pFast != nullptr && pFast->m_pNext->m_pNext != nullptr) {
        pFast = pFast->m_pNext->m_pNext;
        pSlow = pSlow->m_pNext;
        if (pFast == pSlow) {
            return true;
        }
    }
    return false;
}


//MARK:旋转列表
ListNode* RotateList(ListNode *head, int k) {
    if (head == nullptr) {
        return nullptr;
    }
    int listNum = 1;
    ListNode *tail = head;
    while (tail->m_pNext) {
        listNum++;
        tail = tail->m_pNext;
    }
    tail->m_pNext = head;//形成环
    int newHeadIndex = listNum - k%listNum;
    for (int i = 0 ; i < newHeadIndex; ++i) {
        tail = tail->m_pNext;
    }
    head = tail->m_pNext;//断开环
    tail->m_pNext = nullptr;
    
    return head;
}


//MARK:将偶数位节点排到奇数位节点后面
ListNode* oddEvenList(ListNode *head) {
    if (head == nullptr || head->m_pNext == nullptr) {
        return head;
    }
    ListNode *first = nullptr;
    ListNode *second = nullptr;
    ListNode *curFirst = nullptr;
    ListNode *curSecond = nullptr;
    ListNode *cur = head;//先处理奇数
    while (cur) {
        ListNode *tempNode = cur->m_pNext;
        cur->m_pNext = nullptr;
        if (first == nullptr) {
            first = cur;
            curFirst = first;
        } else {
            curFirst->m_pNext = cur;
            curFirst = curFirst->m_pNext;
        }
        cur = tempNode;
        if (cur) {//有偶数继续处理偶数
            ListNode *tempNode2 = cur->m_pNext;
            cur->m_pNext = nullptr;
            if (second == nullptr) {
                second = cur;
                curSecond = second;
            } else {
                curSecond->m_pNext = cur;
                curSecond = curSecond->m_pNext;
            }
            cur = tempNode2;
        }
    }
    curFirst->m_pNext = second;
    
    return first;
}

//MARK:面试题37:两个链表的第一个公共节点
//思路:长的链表的指针先向前走diffLength步,然后两个指针同时向前走，直至遇到第一个相同的节点
ListNode *findFirstCommonNode(ListNode *pHead1, ListNode *pHead2) {
    unsigned int length1 = GetListLength(pHead1);
    unsigned int length2 = GetListLength(pHead2);

    int diffLength = length1 - length2;
    ListNode *pListLong = pHead1;
    ListNode *pListShort = pHead2;
    
    if (diffLength < 0) {
        diffLength = length2 - length1;
        pListLong = pHead2;
        pListShort = pHead1;
    }
    //长的链表的指针先向前走n步
    for (int i = 0; i < diffLength; ++i) {
        pListLong = pListLong->m_pNext;
    }
    while (pListLong->m_pNext != nullptr &&
           pListShort->m_pNext != nullptr &&
           pListLong->m_nValue != pListShort->m_nValue) {
        pListShort = pListShort->m_pNext;
        pListLong = pListLong->m_pNext;
    }
    ListNode *node = pListLong;
    
    return node;
}

//MARK:面试题15 链表中倒数第k个节点， 快慢指针,快指针先走k步
ListNode* FindKthToTail(ListNode *pHead, int k) {
    if (pHead == nullptr || k <= 0) {
        return nullptr;
    }
    ListNode *pFast = pHead;
    for (int i = 0; i < k-1; ++i) {//不足k个节点
        if (pFast->m_pNext) {
            pFast = pFast->m_pNext;
        } else {
            return nullptr;
        }
    }
    ListNode *pSlow = pHead;
    while (pFast->m_pNext) {
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext;
    }
    
    return pSlow;
}

//MARK:Leetcode Add two sum
ListNode *addTwoSum(ListNode *pHead1, ListNode *pHead2) {
    ListNode *dummy = new ListNode(-1);
    ListNode *cur = dummy;
    int carry = 0;//进位
    while (pHead1 || pHead2) {
        int val1 = pHead1 ? pHead1->m_nValue : 0;
        int val2 = pHead2 ? pHead2->m_nValue : 0;
        int sum = val1 + val2 + carry;
        carry = sum / 10;//修改进位
        cur->m_pNext = new ListNode(sum % 10);
        cur = cur->m_pNext;
        if (pHead1) {
            pHead1 = pHead1->m_pNext;
        }
        if (pHead2) {
            pHead2 = pHead2->m_pNext;
        }
    }
    if (carry) {
        cur->m_pNext = new ListNode(1);
    }
    return dummy->m_pNext;
}


//MARK:面试题17 merge two sorted list
ListNode* mergeTwoSortedList(ListNode *pHead1, ListNode *pHead2) {
    if (pHead1 == nullptr) {
        return pHead2;
    }
    if (pHead2 == nullptr) {
        return pHead1;
    }
    ListNode *pRetHead = nullptr;
    if (pHead1->m_nValue < pHead2->m_nValue) {
        pRetHead = pHead1;
        pRetHead->m_pNext = mergeTwoSortedList(pHead1->m_pNext, pHead2);
    }
    else {
        pRetHead = pHead2;
        pRetHead->m_pNext = mergeTwoSortedList(pHead1, pHead2->m_pNext);
    }
    return pRetHead;
}

//MARK:链表排序,链表从中间断开，递归排序
ListNode* sortList(ListNode *pHead){
    //没有节点或者只有一个节点
    if (!pHead || !pHead->m_pNext) {
        return pHead;
    }
    ListNode dummy(-1);
    dummy.m_pNext = pHead;
    ListNode *pSlow=&dummy, *pFast=&dummy;//快慢指针，找出链表的中间节点
    while (pFast && pFast->m_pNext) {
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext->m_pNext;
    }
    ListNode *right_begin = pSlow->m_pNext;
    pSlow->m_pNext = nullptr;//断开链表
    //归并排序
    ListNode *l1 = sortList(dummy.m_pNext);
    ListNode *l2 = sortList(right_begin);
    
    return mergeTwoSortedList(l1,l2);
}

//MARK:面试题5：从尾到头打印链表:借助stack
void ReversePrintList(ListNode *head) {
    if (head == nullptr) {
        return;
    }
    ListNode *pNode = head;
    stack<ListNode *> nodes;
    while (pNode) {
        nodes.push(pNode);
        pNode = pNode->m_pNext;
    }
    while(!nodes.empty()) {
        ListNode *node = nodes.top();
        cout << node -> m_nValue << " ";
        nodes.pop();
    }
    cout << endl;
    
}

//MARK:反转链表
ListNode* ReverseList(ListNode **pHead) {
    if (*pHead == nullptr) {
        return nullptr;
    }
    ListNode *pCurrent, *pPre=*pHead, *pNext;//pPre初始指向Head
    pCurrent = pPre->m_pNext;
    while (pCurrent) {
        //1.缓存pCurrent后面的节点，防止断开
        pNext = pCurrent->m_pNext;
        //2.修改指针
        pCurrent->m_pNext = pPre;
        //3.同步后移
        pPre = pCurrent;
        pCurrent = pNext;
    }
    (*pHead)->m_pNext = nullptr;//原头节点的Next置空
    *pHead = pPre;//pHead指向新的头结点
    
    return *pHead;
    
}

//MARK:尾部插入节点,当链表为空时，新插入的节点就是链表的头指针，此时需要修改头指针
ListNode* AddNodeAtTail(ListNode **pHead, int value) {
    ListNode *node = new ListNode(value);
    //链表为空
    if (*pHead == nullptr) {
        *pHead = node;
    } else {
        ListNode *pNode = *pHead;
        while (pNode->m_pNext != nullptr) {
            pNode = pNode->m_pNext;
            
        }
        pNode->m_pNext = node;
    }
    return *pHead;
}

//MARK:Remove Duplicates from sorted List II   Input:1->2->3->3->4->4->5  Output:1->2->5
//只有当前节点既不等于上一个节点也不等于下一个节点的值，才不重复
ListNode* RemoveDuplicateNodesII(ListNode *pHead) {
    //如果为空或者只有一个节点，直接返回
    if (!pHead || pHead->m_pNext == nullptr) {
        return pHead;
    }
    ListNode *resultHead = pHead;
    ListNode *p = nullptr;
    ListNode *lastRepeatNode = nullptr;
    while (pHead != nullptr) {
        //是尾节点，或者不是尾节点且当前节点值不等于下一个节点的值
        if ((pHead->m_pNext && pHead->m_nValue != pHead->m_pNext->m_nValue) ||
            pHead->m_pNext == nullptr) {
            //没有上一个重复节点，或者有上一个重复节点但其值与当前节点的值不等
            if (lastRepeatNode == nullptr || lastRepeatNode->m_nValue != pHead->m_nValue) {
                if (p == nullptr) {
                    resultHead = pHead;
                    p = resultHead;
                } else {
                    p->m_pNext = pHead;
                    p = p->m_pNext;
                }
            }
        } else {//不是尾节点，同时当前节点的值等于下一个节点的值
            lastRepeatNode = pHead;
        }
        pHead = pHead->m_pNext;
    }
    if (p != nullptr) {
        p->m_pNext = nullptr;
    }
    
    return resultHead;
}


//MARK:Remove Duplicates from sorted List
ListNode* RemoveDuplicateNodes(ListNode *pHead) {
    //如果为空或者只有一个节点，直接返回
    if (!pHead || pHead->m_pNext == nullptr) {
        return pHead;
    }
    ListNode *resultHead = pHead;
    ListNode *p = resultHead;
    while ((pHead = pHead->m_pNext) != nullptr) {
        if (p->m_nValue != pHead->m_nValue) {
            p->m_pNext = pHead;
            p = p->m_pNext;
        }
    }
    p->m_pNext = nullptr;
    
    return resultHead;
}


//MARK:链表节点删除，有重复节点
void RemoveNodes(ListNode *pHead, int value) {
    if (pHead == nullptr) {
        return;
    }
    ListNode *curr = nullptr;
    ListNode *rHead = nullptr;
    while (pHead) {
        //1.缓存下一个节点，防止断裂
        ListNode *pTempNode = pHead->m_pNext;
        pHead->m_pNext = nullptr;
        //值不同就加入到结果链表
        if (pHead->m_nValue != value) {
            if (!rHead) {
                rHead = pHead;
                curr = pHead;
            } else {
                curr->m_pNext = pHead;
                curr = curr->m_pNext;
            }
        }
        pHead = pTempNode;
    }
}


//MARK:面试题13:o(1)时间内删除节点、利用后面节点覆盖要删除的节点
void DeleteNode(ListNode **pListHead, ListNode *pToBeDeleted) {
    if (!pListHead || !pToBeDeleted) {
        return;
    }
    if (pToBeDeleted->m_pNext != nullptr) {//删除的不是尾节点
        ListNode *pNext = pToBeDeleted->m_pNext;
        //用后面节点的值覆盖给要删除的节点
        pToBeDeleted->m_nValue = pNext->m_nValue;
        //指向后面的后面的节点
        pToBeDeleted->m_pNext = pNext->m_pNext;
        //删除后面节点
        delete pNext;
        pNext = nullptr;
    } else {//删除的是尾节点
        ListNode *pNode = *pListHead;
        while (pNode->m_pNext != pToBeDeleted) {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = nullptr;
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
    }
}

/*
int main(int argc, const char * argv[]) {
    ListNode *head = new ListNode(1);
    AddNodeAtTail(&head, 2);
    AddNodeAtTail(&head, 3);
//    AddNodeAtTail(&head, 4);
//    AddNodeAtTail(&head, 5);
    PrintLinkList(head);
    
    ListNode *retHead = RotateList(head, 4);
    
    
//    ReverseList(&head);
    PrintLinkList(retHead);
//
//    RemoveNode(&head, 4);
//    PrintLinkList(head);
//
//    ReversePrintList(head);
//    ListNode *head = new ListNode(2);
//    AddNodeAtTail(&head,4);
//    AddNodeAtTail(&head, 3);
    
//    ListNode *head2 = new ListNode(5);
//
//    AddNodeAtTail(&head2, 6);
//    AddNodeAtTail(&head2, 4);
//    AddNodeAtTail(&head2, 9);
//
//    ListNode *retHead = FindKthToTail(head2, 2);
//    cout << retHead->m_nValue;
    
    return 0;
}

*/
