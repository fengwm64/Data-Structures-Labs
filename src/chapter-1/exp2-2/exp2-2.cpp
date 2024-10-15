/*
1、教材P74实验题2：实现单链表的各种基本运算的算法
编写一个程序linklist.cpp，实现单链表中的各种基本运算和整体建表算法（假设单链表的元素类型ElemType为cha），并在此基础上设计一个程序exp2-2.cpp完成以下功能。
（1）初始化单链表h。
（2）依次采用尾插法插入a、b、c、d、e元素。
（3）输出单链表h。
（4）输出单链表h的长度。
（5）判断单链表h是否为空。
（6）输出单链表h的第3个元素。
（7）输出元素a的位置。
（8）在第4个元素位置上插入f元素。
（9）输出单链表h。
（10）删除单链表h的第3个元素。
（11）输出单链表h。
（12）释放单链表h。
*/

#include <iostream>
#include "linklist.h"

using namespace std;

int main()
{
    LinkList h = NULL;
    ElemType e;

    cout << "1.初始化单链表h" << endl;
    InitList(h);

    char InsertElem[] = {'a', 'b', 'c', 'd', 'e'};
    cout << endl
         << "2.依次采用尾插法插入a、b、c、d、e元素" << endl;
    for (int i = 1; i < 6; i++)
        ListInsert(h, i, InsertElem[i - 1]);

    cout << endl
         << "3.输出单链表h如下：" << endl;
    PrintList(h);

    cout << endl
         << "4.输出单链表h的长度：" << ListLength(h) << endl;

    cout << endl
         << "5.判断单链表h是否为空（1空/0非空）：" << IsEmpty(h) << endl;

    cout << endl
         << "6.输出单链表h的第3个元素：" << GetElem(h, 3) << endl;

    cout << endl
         << "7.输出元素a的位置：" << LocateElem(h, 'a') << endl;

    cout << endl
         << "8.在第4个元素位置上插入f元素" << endl;
    ListInsert(h, 4, 'f');

    cout << endl
         << "9.插入后输出链表h如下：" << endl;
    PrintList(h);

    cout << endl
         << "10.删除单链表h的第3个元素" << endl;
    ListDelete(h, 3, e);
    cout << endl
         << "   被删除的元素为：" << e << endl;
    cout << endl
         << "11.删除后输出链表h如下：" << endl;
    PrintList(h);

    cout << endl
         << "12.删除链表" << endl;
    Destroy(h);
    PrintList(h);

    return 0;
}