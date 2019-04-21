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
};

//MARK:面试题56 链表中环的入口节点
//若果环中有n个节点，快指针先向前移动n步，然后快慢指针同速度移动，
//当两指针相遇，快指针走了一圈时，慢指针指向入口
//关键是先要计算出环中有几个节点
ListNode* MeetingNode(ListNode *pHead) {
    if (pHead == NULL) {
        return NULL;
    }
    ListNode *pSlow = pHead->m_pNext;
    if (pSlow == NULL) {
        return NULL;
    }
    ListNode *pFast = pSlow->m_pNext;
    while (pFast!=NULL && pSlow != NULL) {
        if (pFast == pSlow) {
            return pFast;
        }
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext;
        if (pFast != NULL) {
            pFast = pFast->m_pNext;//pFast每次走两步
        }
    }
    return NULL;
}

ListNode* EntryNodeOfLoop(ListNode *pHead) {
    ListNode *meetingNode = MeetingNode(pHead);
    if (meetingNode == NULL) {
        return NULL;
    }
    int nodesInLoop = 1;
    ListNode *pNode1 = meetingNode;
    //计算环中的节点个数
    while (pNode1->m_pNext != meetingNode) {
        pNode1 = pNode1->m_pNext;
        ++ nodesInLoop;
    }
    //pNode1先走n步
    pNode1 = pHead;
    for (int i = 0; i < nodesInLoop; ++i) {
        pNode1 = pNode1->m_pNext;
    }
    ListNode *pNode2 = pHead;
    while (pNode1 != pNode2) {
        pNode1 = pNode1->m_pNext;
        pNode2 = pNode2->m_pNext;
    }
    
    return pNode1;
}


unsigned int GetListLength(ListNode *pHead) {
    unsigned int length = 0;
    ListNode *node = pHead;
    while (node->m_pNext != NULL) {
        ++length;
        node = node->m_pNext;
    }
    return length;
}

//MARK:面试题37:两个链表的第一个公共节点
//思路:长的链表的指针先向前走n步,然后两个指针同时向前走，直至遇到第一个相同的节点
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
    while (pListLong->m_pNext != NULL &&
           pListShort->m_pNext != NULL &&
           pListLong->m_nValue != pListShort->m_nValue) {
        pListShort = pListShort->m_pNext;
        pListLong = pListLong->m_pNext;
    }
    ListNode *node = pListLong;
    
    return node;
}


//尾部插入,当链表为空时，新插入的节点就是链表的头指针，此时需要修改头指针
void AddToTail(ListNode **pHead, int value) {
    ListNode *node = new ListNode();
    node->m_nValue = value;
    node->m_pNext = NULL;
    if (*pHead == NULL) {
        *pHead = node;
    } else {
        ListNode *pNode = *pHead;
        while (pNode->m_pNext != NULL) {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = node;
    }
}

void RemoveNode(ListNode **pHead, int value) {
    if (pHead == NULL || *pHead == NULL) {
        return;
    }
    ListNode *pToBeDeleted = NULL;
    if ((*pHead)->m_nValue == value) {
        pToBeDeleted = *pHead;
        *pHead = (*pHead)->m_pNext;
    } else {
        ListNode *pNode = *pHead;
        while (pNode->m_pNext != NULL && pNode->m_pNext->m_nValue != value ) {
            pNode = pNode->m_pNext;
        }
        if (pNode->m_pNext != NULL && pNode->m_pNext->m_nValue == value) {
            pToBeDeleted = pNode->m_pNext;
            pNode->m_pNext = pNode->m_pNext->m_pNext;
        }
    }
    if (pToBeDeleted != NULL) {
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
}
//MARK:面试题5：从尾到头打印链表
void PrintListReversingly(ListNode *pHead) {
    stack<ListNode *>nodes;//借助于stack
    ListNode *pNode = pHead;
    while (pHead != NULL) {
        nodes.push(pNode);
        pNode = pNode->m_pNext;
    }
    while (!nodes.empty()) {
        pNode = nodes.top();
        cout << pNode->m_nValue;
        nodes.pop();
    }
}

//面试题13：在O(1)时间删除链表节点  利用后面节点覆盖要删除的节点
void DeleteNode(ListNode **pListHead, ListNode *pToBeDeleted) {
    if (!pListHead || !pToBeDeleted) {
        return;
    }
    if (pToBeDeleted->m_pNext != NULL) {//删除的不是尾节点
        ListNode *pNext = pToBeDeleted->m_pNext;
        pToBeDeleted->m_nValue = pNext->m_nValue;
        pToBeDeleted->m_pNext = pNext->m_pNext;
        delete pNext;
        pNext = NULL;
    } else if(*pListHead == pToBeDeleted){//只有一个节点
        delete pToBeDeleted;
        pToBeDeleted = NULL;
        *pListHead = NULL;
    } else {//删除的是尾节点
        ListNode *pNode = *pListHead;
        while (pNode->m_pNext != pToBeDeleted) {
            pNode = pNode->m_pNext;
        }
        pNode->m_pNext = NULL;
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
}
//MARK:面试题15 链表中倒数第k个节点， 快慢指针,快指针先走k步
ListNode *FindKthToTail(ListNode *pListHead, unsigned int k) {
    if (pListHead == NULL || k <= 0) {
        return NULL;
    }
    ListNode *pFast = pListHead;
    for (unsigned int i = 0; i < k-1; ++i) {
        if (pFast->m_pNext != NULL) {
            pFast = pFast->m_pNext;
        } else {//节点总数少于k
            return NULL;
        }
    }
    ListNode *pSlow = pListHead;
    while (pFast ->m_pNext != NULL) {
        pFast = pFast ->m_pNext;
        pSlow = pSlow->m_pNext;
    }
    return pSlow;
}

//面试题17 合并两个递增有序的链表
//思路:得到值较小的头节点并把它链接到已合并链表的尾部
ListNode* Merge(ListNode *pHead1, ListNode *pHead2) {
    if (pHead1 == NULL) {
        return pHead2;
    }
    if (pHead2 == NULL) {
        return pHead1;
    }
    
    ListNode *pMergedHead = NULL;
    if (pHead1->m_nValue < pHead2->m_nValue) {
        pMergedHead = pHead1;
        pMergedHead->m_pNext = Merge(pHead1->m_pNext, pHead2);
    } else {
        pMergedHead = pHead2;
        pMergedHead->m_pNext = Merge(pHead1, pHead2->m_pNext);
    }
    return pMergedHead;
}

//反转链表
ListNode* ReverseList(ListNode *pHead) {
    ListNode *pReversedHead = NULL;
    ListNode *pNode = pHead;
    ListNode *pPrev = NULL;
    while (pNode != NULL) {
        ListNode *pNext = pNode->m_pNext;//后一个节点
        if (pNext == NULL) {
            pReversedHead = pNode;
        }
        pNode->m_pNext = pPrev;
        
        pPrev = pNode;
        pNode = pNext;
    }
    return pReversedHead;
    
}
