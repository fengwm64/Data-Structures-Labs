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
// 清空
Status ClearList(LinkList &L)
{
    LNode *q, *p = L->next; // 注意！！！q为前驱指针，p为后驱指针
    while (p)
    {
        q = p;
        p = p->next;
        delete q;
    }
    L->next = NULL;
    return OK;
}
// 插入
Status ListInsert(LinkList &L, int i, ElemType e)
{
    int count = 0;
    LNode *p = L;
    if (i < 1)
        return ERROR;

    while (p->next && count < i - 1)
    {
        p = p->next;
        count++;
    }

    LNode *s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}
// 删除
Status ListDelete(LinkList &L, int i, ElemType &e)
{
    int count = 0;
    LNode *q = L;
    if (i < 1)
        return ERROR;
    while (q && count < i - 1)
    {
        q = q->next;
        count++;
    }
    LNode *p = q->next;
    q->next = p->next;
    e = p->data;
    delete p;
    return OK;
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
/*
 * 查找：
 * 根据指定数据获取数据所在的 位置地址
 * 根据指定数据获取数据 位置序号
 */
int LocateElem(LinkList L, ElemType e)
{
    LNode *p = L->next;
    int count = 0;
    while (p)
    {
        count++;
        if (p->data == e)
            return count;
        p = p->next;
    }
    return ERROR;
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

// 取值，返回所取元素
ElemType GetElem(LinkList L, int i)
{
    int count = 1;
    LNode *p = L->next;
    if (!p || i < 0)
        return ERROR;
    while (count < i)
    {
        p = p->next;
        count++;
    }
    return p->data;
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
        cout << p->data << endl;
        p = p->next;
    }
    return OK;
}