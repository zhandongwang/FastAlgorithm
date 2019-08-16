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
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr){}
};

//删除倒数第K个结点
ListNode* removeNthFromEnd(ListNode *head, int n) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }
    ListNode *pFast = head;
    ListNode *pSlow = head;
    for (int i = 0; i < n; ++i) {
        pFast = pFast->next;
    }
    if (pFast == NULL) {//删除第一个节点
        return head->next;
    }
    while (pFast->next != NULL) {
        pSlow = pSlow->next;
        pFast = pFast->next;
    }
    pSlow->next = pSlow->next->next;
    
    return head;
}

ListNode* MergeTwoSortedList_2(ListNode *head1, ListNode *head2) {
    if (head1 == NULL) {
        return head2;
    }
    if (head2 == NULL) {
        return head1;
    }
    ListNode *curr = NULL;
    if (head1->val <= head2->val) {
        curr = head1;
        curr->next = MergeTwoSortedList_2(head1->next, head2);
    } else {
        curr = head2;
        curr->next = MergeTwoSortedList_2(head1, head2->next);
    }
    return curr;
}


ListNode* MergeTwoSortedList_1(ListNode *head1, ListNode *head2) {
    if (head1 == NULL) {
        return head2;
    }
    if (head2 == NULL) {
        return head1;
    }
    ListNode *dummyNode = new ListNode(-1);
    ListNode *curr = dummyNode;
    while (head1 && head2) {
        if (head1->val <= head2->val) {
            curr->next = head1;
            curr = curr->next;
            head1 = head1->next;
        } else {
            curr->next = head2;
            curr = curr->next;
            head2 = head2->next;
        }
    }
    if (head1) {
        curr->next = head1;
    }
    if (head2) {
        curr->next = head2;
    }
    return dummyNode->next;
}


//反转链表
ListNode* Reverselist_1(ListNode **pHead) {
    if (*pHead == nullptr) {
        return nullptr;
    }
    ListNode *pCurrent, *pPre = *pHead, *pNext;
    pCurrent = pPre->next;
    while (pCurrent) {
        pNext = pCurrent->next;//保存后继节点
        
        pCurrent->next = pPre;
        pPre = pCurrent;//在被改之前引用它
        pCurrent = pNext;
    }
    (*pHead)->next = nullptr;
    *pHead = pPre;//头指针被改写
    
    return *pHead;
}
//尾部插入
ListNode* AddNodeAtTail_1(ListNode **pHead, int value) {
    ListNode *node = new ListNode(value);
    if (*pHead == nullptr) {
        *pHead = node;
    } else {
        ListNode *pNode = *pHead;
        while (pNode->next) {
            pNode = pNode->next;
        }
        pNode->next = node;
    }
    
    return *pHead;
}

int HasCircle_1(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {//空链表或者只有一个节点
        return -1;
    }
    ListNode *pFast = head;
    ListNode *pSlow = head;
    ListNode *pEntry = head;
    while (pFast->next != nullptr && pFast->next->next != nullptr) {
        pFast = pFast->next->next;
        pSlow = pSlow->next;
        if (pFast == pSlow) {
            int index = 0;
            while (pEntry != pSlow) {
                pEntry = pEntry->next;
                pSlow = pSlow->next;
                ++index;
            }
            return index;
        }
    }
    return -1;
}

ListNode* MidNode_1(ListNode *head) {
    if (head == nullptr) {
        return nullptr;
    }
    ListNode *pFast = head;
    ListNode *pSlow = head;
    while (pFast->next != nullptr && pFast->next->next != nullptr) {
        pFast = pFast->next->next;
        pSlow = pSlow->next;
    }
    if (pFast->next == nullptr) {
        return pSlow;
    } else {
        return pSlow->next;
    }
    
    return nullptr;
}




void PrintLinkList(ListNode *pHead) {
    while (pHead) {
        cout << pHead->val << " ";
        pHead = pHead->next;
    }
    cout << endl;
}

unsigned int GetListLength(ListNode *pHead) {
    unsigned int length = 0;
    ListNode *node = pHead;
    while (node->next != nullptr) {
        ++length;
        node = node->next;
    }
    return length;
}

//MARK:面试题56 链表中环的入口节点  https://www.qiujiawei.com/leetcode-problem-142/
ListNode *findCycleEntry(ListNode *head) {
    if (!head || head->next == nullptr) {
        return nullptr;
    }
    ListNode *pFast = head;
    ListNode *pSlow = head;
    while (pFast != nullptr && pFast->next->next != nullptr) {
        pFast = pFast->next->next;
        pSlow = pSlow->next;
        if (pFast == pSlow) {
            break;//此时slow和fast相遇
        }
    }
    pSlow = head;//slow指向起点
    while (pSlow != pFast) {
        pSlow = pSlow->next;
        pFast = pFast->next;
    }
    return pSlow;
}


//MARK:链表是否有环
bool hasCircle(ListNode *head) {
    if (!head || head->next == nullptr) {
        return false;
    }
    ListNode *pFast = head;
    ListNode *pSlow = head;
    while (pFast != nullptr && pFast->   next->next != nullptr) {
        pFast = pFast->next->next;
        pSlow = pSlow->next;
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
    while (tail->next) {
        listNum++;
        tail = tail->next;
    }
    tail->next = head;//形成环
    int newHeadIndex = listNum - k%listNum;
    for (int i = 0 ; i < newHeadIndex; ++i) {
        tail = tail->next;
    }
    head = tail->next;//断开环
    tail->next = nullptr;
    
    return head;
}


//MARK:将偶数位节点排到奇数位节点后面
ListNode* oddEvenList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *first = nullptr;
    ListNode *second = nullptr;
    ListNode *curFirst = nullptr;
    ListNode *curSecond = nullptr;
    ListNode *cur = head;//先处理奇数
    while (cur) {
        ListNode *tempNode = cur->next;
        cur->next = nullptr;
        if (first == nullptr) {
            first = cur;
            curFirst = first;
        } else {
            curFirst->next = cur;
            curFirst = curFirst->next;
        }
        cur = tempNode;
        if (cur) {//有偶数继续处理偶数
            ListNode *tempNode2 = cur->next;
            cur->next = nullptr;
            if (second == nullptr) {
                second = cur;
                curSecond = second;
            } else {
                curSecond->next = cur;
                curSecond = curSecond->next;
            }
            cur = tempNode2;
        }
    }
    curFirst->next = second;
    
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
        pListLong = pListLong->next;
    }
    while (pListLong->next != nullptr &&
           pListShort->next != nullptr &&
           pListLong->val != pListShort->val) {
        pListShort = pListShort->next;
        pListLong = pListLong->next;
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
        if (pFast->next) {
            pFast = pFast->next;
        } else {
            return nullptr;
        }
    }
    ListNode *pSlow = pHead;
    while (pFast->next) {
        pSlow = pSlow->next;
        pFast = pFast->next;
    }
    
    return pSlow;
}

//MARK:Leetcode Add two sum
ListNode *addTwoNum(ListNode *pHead1, ListNode *pHead2) {
    ListNode *dummy = new ListNode(-1);
    ListNode *cur = dummy;
    int carry = 0;//进位
    while (pHead1 || pHead2) {
        int val1 = pHead1 ? pHead1->val : 0;
        int val2 = pHead2 ? pHead2->val : 0;
        int sum = val1 + val2 + carry;
        carry = sum / 10;//修改进位
        cur->next = new ListNode(sum % 10);
        cur = cur->next;
        if (pHead1) {
            pHead1 = pHead1->next;
        }
        if (pHead2) {
            pHead2 = pHead2->next;
        }
    }
    if (carry) {
        cur->next = new ListNode(1);
    }
    return dummy->next;
}

ListNode *subTwoNum (ListNode *pHead1, ListNode *pHead2) {
    ListNode *dummy = new ListNode(-1);
    ListNode *cur = dummy;
    int num = 0;//标识借位
    while (pHead1 || pHead2) {
        int val1 = pHead1 ? pHead1->val : 0;
        int val2 = pHead2 ? pHead2->val : 0;
        int sub = 0;
        val1 = val1 - num;
        if (val1 >= val2) {
            sub = val1 - val2;
            num = 0;
        } else {
            sub = val1 + 10 - val2;
            num = 1;
        }
        cur->next = new ListNode(sub);
        cur = cur->next;
        if (pHead1) {
            pHead1 = pHead1->next;
        }
        if (pHead2) {
            pHead2 = pHead2->next;
        }
    }
    return dummy->next;
}


//MARK:面试题17 合并两个有序链表
ListNode* mergeTwoSortedList(ListNode *pHead1, ListNode *pHead2) {
    if (pHead1 == nullptr) {
        return pHead2;
    }
    if (pHead2 == nullptr) {
        return pHead1;
    }
    ListNode *pRetHead = nullptr;
    if (pHead1->val < pHead2->val) {
        pRetHead = pHead1;
        pRetHead->next = mergeTwoSortedList(pHead1->next, pHead2);
    }
    else {
        pRetHead = pHead2;
        pRetHead->next = mergeTwoSortedList(pHead1, pHead2->next);
    }
    return pRetHead;
}

//MARK:链表排序,链表从中间断开，递归排序
ListNode* sortList(ListNode *pHead){
    //没有节点或者只有一个节点
    if (!pHead || !pHead->next) {
        return pHead;
    }
    ListNode dummy(-1);
    dummy.next = pHead;
    ListNode *pSlow=&dummy, *pFast=&dummy;//快慢指针，找出链表的中间节点
    while (pFast && pFast->next) {
        pSlow = pSlow->next;
        pFast = pFast->next->next;
    }
    ListNode *right_begin = pSlow->next;
    pSlow->next = nullptr;//断开链表
    //归并排序
    ListNode *l1 = sortList(dummy.next);
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
        pNode = pNode->next;
    }
    while(!nodes.empty()) {
        ListNode *node = nodes.top();
        cout << node -> val << " ";
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
    pCurrent = pPre->next;
    while (pCurrent) {
        //1.缓存pCurrent后面的节点，防止断开
        pNext = pCurrent->next;
        //2.修改指针,pCurrent->m_pNext指向前面的节点
        pCurrent->next = pPre;
        //3.同步后移
        pPre = pCurrent;
        pCurrent = pNext;
    }
    (*pHead)->next = nullptr;//原头节点的Next置空
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
        while (pNode->next != nullptr) {
            pNode = pNode->next;
            
        }
        pNode->next = node;
    }
    return *pHead;
}

//MARK:Remove Duplicates from sorted List II   Input:1->2->3->3->4->4->5  Output:1->2->5
//只有当前节点既不等于上一个节点也不等于下一个节点的值，才不重复
ListNode* RemoveDuplicateNodesII(ListNode *pHead) {
    //如果为空或者只有一个节点，直接返回
    if (!pHead || pHead->next == nullptr) {
        return pHead;
    }
    ListNode *resultHead = pHead;
    ListNode *p = nullptr;
    ListNode *lastRepeatNode = nullptr;
    while (pHead != nullptr) {
        //是尾节点，或者不是尾节点且当前节点值不等于下一个节点的值
        if ((pHead->next && pHead->val != pHead->next->val) ||
            pHead->next == nullptr) {
            //没有上一个重复节点，或者有上一个重复节点但其值与当前节点的值不等
            if (lastRepeatNode == nullptr || lastRepeatNode->val != pHead->val) {
                if (p == nullptr) {
                    resultHead = pHead;
                    p = resultHead;
                } else {
                    p->next = pHead;
                    p = p->next;
                }
            }
        } else {//不是尾节点，同时当前节点的值等于下一个节点的值
            lastRepeatNode = pHead;
        }
        pHead = pHead->next;
    }
    if (p != nullptr) {
        p->next = nullptr;
    }
    
    return resultHead;
}


//MARK:Remove Duplicates from sorted List
ListNode* RemoveDuplicateNodes(ListNode *pHead) {
    //如果为空或者只有一个节点，直接返回
    if (!pHead || pHead->next == nullptr) {
        return pHead;
    }
    ListNode *resultHead = pHead;
    ListNode *p = resultHead;
    while ((pHead = pHead->next) != nullptr) {
        if (p->val != pHead->val) {
            p->next = pHead;
            p = p->next;
        }
    }
    p->next = nullptr;
    
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
        ListNode *pTempNode = pHead->next;
        pHead->next = nullptr;
        //值不同就加入到结果链表
        if (pHead->val != value) {
            if (!rHead) {
                rHead = pHead;
                curr = pHead;
            } else {
                curr->next = pHead;
                curr = curr->next;
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
    if (pToBeDeleted->next != nullptr) {//删除的不是尾节点
        ListNode *pNext = pToBeDeleted->next;
        //用后面节点的值覆盖给要删除的节点
        pToBeDeleted->val = pNext->val;
        //指向后面的后面的节点
        pToBeDeleted->next = pNext->next;
        //删除后面节点
        delete pNext;
        pNext = nullptr;
    } else {//删除的是尾节点
        ListNode *pNode = *pListHead;
        while (pNode->next != pToBeDeleted) {
            pNode = pNode->next;
        }
        pNode->next = nullptr;
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
    }
}


/*
int main(int argc, const char * argv[]) {
    ListNode *head1 = new ListNode(1);
    AddNodeAtTail(&head1, 2);
    AddNodeAtTail(&head1, 4);
    AddNodeAtTail(&head1, 6);
    AddNodeAtTail(&head1, 9);
    ListNode *node = removeNthFromEnd(head1, 3);
    if (node) {
        cout << node->val;
    }
    
//    ListNode *head2 = new ListNode(1);
//    AddNodeAtTail(&head2, 3);
//    AddNodeAtTail(&head2, 4);
//
//    ListNode *ret = MergeTwoSortedList_2(head1, head2);
//    PrintLinkList(ret);
    
//    ListNode *head2 = new ListNode(5);
//    AddNodeAtTail(&head2, 6);
//    AddNodeAtTail(&head2, 4);
//    PrintLinkList(head);
    
//    ListNode *retHead = addTwoNum(head, head2);
//    ListNode *retHead = subTwoNum(head2, head);
    
    
//    ListNode *retHead = ReverseList(&head);
//    PrintLinkList(retHead);
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
