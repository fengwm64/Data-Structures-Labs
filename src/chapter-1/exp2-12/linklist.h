#pragma once

#include "StatusCode.h"
#include <iostream> // NULL定义在标准库中
#include <stdlib.h>
#include <time.h>
using namespace std;

typedef int ElemType; // 表里存放的数据类型

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

// 线性表的基本操作
Status InitList(LinkList &L); // 初始化
Status Destroy(LinkList &L);  // 销毁

Status IsEmpty(LinkList L);                     // 判空
Status ListLength(LinkList L);                  // 求长
Status GetElem(LinkList L, int i, ElemType &e); // 取值

Status PrintList(LinkList L); // 打印输出链表
Status CreateList_Head(LinkList &L, ElemType e);
