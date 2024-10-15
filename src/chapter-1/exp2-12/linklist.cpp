#include "linklist.h"

// 初始化
Status InitList(LinkList &L)
{
    L = new LNode;
    L->next = NULL;
    if (!L)
        return ERROR;
    else
        return OK;
}
// 销毁
Status Destroy(LinkList &L)
{
    LNode *p;
    while (L)
    {
        p = L;
        L = L->next;
        delete p;
    }
    if (!L)
        return OK;
    else
        return ERROR;
}

// 判空
Status IsEmpty(LinkList L)
{
    if (!L->next)
        return 1;
    else
        return 0;
}
// 求长
int ListLength(LinkList L)
{
    int count = 0;
    LNode *p = L->next;
    while (p)
    {
        p = p->next;
        count++;
    }
    return count;
}

// 取值
Status GetElem(LinkList L, int i, ElemType &e)
{
    int count = 0;
    LNode *p = L->next;
    while (p && count <= i)
    {
        count++;
        if (count == i)
        {
            e = p->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

// 打印输出链表
Status PrintList(LinkList L)
{
    if (!L)
    {
        cout << "链表已经被销毁！" << endl;
        return ERROR;
    }

    if (!L->next)
    {
        cout << "空表" << endl;
        return ERROR;
    }

    LNode *p = L->next;

    while (p)
    {
        cout << p->data;
        p = p->next;
    }
    return OK;
}

// 前插法创建链表
Status CreateList_Head(LinkList &L, ElemType e)
{
    LNode *s = new LNode;
    s->data = e;
    s->next = L->next;
    L->next = s;
    return OK;
}