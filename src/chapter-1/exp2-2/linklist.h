#pragma once

#include "StatusCode.h"
#include <iostream> // NULL定义在标准库中
#include <stdlib.h>
#include <time.h>
using namespace std;

/*
 * 链表 - 顺序存取
 * 优点：
 * 数据元素的个数可以自由扩充
 * 插入、删除等操作不必移动数据，只需修改链接指针，修改效率较高
 *
 *
 * 缺点：
 * 存储密度小
 * 存取效率不高，必须采用顺序存取，即存取数据元素时，只能按链表的顺序进行访问（顺藤摸瓜）
 *
 * END
 */

// 链表实现线性表及操作

typedef char ElemType; // 表里存放的数据类型

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

// 线性表的基本操作
Status InitList(LinkList &L);  // 初始化
Status Destroy(LinkList &L);   // 销毁
Status ClearList(LinkList &L); // 清空

Status ListInsert(LinkList &L, int i, ElemType e);  // 插入
Status ListDelete(LinkList &L, int i, ElemType &e); // 删除

Status IsEmpty(LinkList L);                     // 判空
Status ListLength(LinkList L);                  // 求长
int LocateElem(LinkList L, ElemType e);         //  查找
Status GetElem(LinkList L, int i, ElemType &e); // 取值
ElemType GetElem(LinkList L, int i);            // 取值，返回所取元素

Status PrintList(LinkList L); // 打印输出链表