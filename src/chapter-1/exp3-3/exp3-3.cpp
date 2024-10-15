#include <iostream>
#include "sqqueue.h"
#include "StatusCode.h"
using namespace std;

/*
3、教材P118实验题3：实现环形队列的各种基本运算的算法
编写一个程序sqqueue.cpp，实现环形队列（假设队列中元素类型ElemType为char）的各种基本运算，并在此基础上设计一个程序exp3-3.cpp完成以下功能。
（1）初始化队列q。
（2）判断队列q是否非空。
（3）依次进队元素a、b、c。
（4）出队一个元素，输出该元素。
（5）依次进队元素d、e、f。
（6）输出出队序列。
（12）释放队列。
*/

int main()
{
    ElemType e;
    ElemType a[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int length;

    cout << "1.初始化队列q" << endl;
    SqQueue q;
    InitQueue(q);

    cout << endl
         << "2.判断队列q是否非空（1空/0非空）：" << QueueEmpty(q) << endl;

    cout << endl
         << "3.依次进队元素a、b、c：" << endl;
    for (int i = 0; i < 3; i++)
        EnQueue(q, a[i]);

    cout << endl
         << "4.出队一个元素，输出该元素" << endl;
    DeQueue(q, e);
    cout << "  该元素为：" << e << endl;

    cout << endl
         << "5.依次进队元素d、e、f：" << endl;
    for (int i = 3; i < 6; i++)
        EnQueue(q, a[i]);

    cout << endl
         << "6.输出出队序列：" << endl;
    length = QueueLength(q);
    for (int i = 0; i < length; i++)
    {
        DeQueue(q, e);
        cout << "  " << e << endl;
    }

    cout << endl
         << "12.释放队列" << endl;
    DestroyQueue(q);
    return 0;
}