// exp8-1.cpp
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
using namespace std;
const int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};

string st = "134 85726", ed = "32 418567";

// 计算曼哈顿距离，即代价
// 找的是两者对比的数字偏移，这里简单的用find查找了
int H(string &s)
{
    int res = 0;
    for (int i = 0; i < 9; ++i)
    {
        int idx = ed.find(s[i]);
        res += abs(idx - i);
    }
    return res;
}

// 估值总代价函数
// int F()
// {
//     return H(xxx) + depth...
// }

struct Node
{
    vector<string> path; // 枚举的路径
    int F;               // 估值
    int depth;           // 深度

    bool operator<(const Node &w) const
    {
        return F > w.F; // priority_queue，从小到大排序
    }
};

int main()
{
    unordered_set<string> mp;
    priority_queue<Node> q;
    q.push({{st}, H(st), 0});
    mp.insert(st);
    int time = 0; // 总枚举次数
    while (!q.empty())
    {
        auto t = q.top();
        q.pop();
        if (t.path.back() == ed)
        {
            for (int i = 0; i < t.path.size(); i++)
            {
                string &tmp = t.path[i];
                for (int j = 0; j < 9; j++)
                {
                    cout << tmp[j] << " \n"[j % 3 == 2];
                }
                puts("");
            }
            cout << "总查找次数: " << time << " 方案次数: " << t.path.size()
                 << " 估值F: " << t.F << " t.depth: " << t.depth << endl;
            break;
        }

        // blackspace
        int x1 = t.path.back().find(' ');
        int y1 = x1 % 3;
        x1 /= 3;

        ++t.depth;
        ++time;

        for (int k = 0; k < 4; k++)
        {
            int x = dx[k] + x1, y = dy[k] + y1;
            if (x < 0 || y < 0 || x > 2 || y > 2)
                continue;

            string tmp = t.path.back();
            swap(tmp[x1 * 3 + y1 % 3], tmp[x * 3 + y % 3]);
            if (mp.count(tmp))
                continue;
            mp.insert(tmp);
            t.path.emplace_back(tmp);
            t.F = H(tmp) + t.depth; // t.depth*3 能得到优解
            q.emplace(t);

            t.path.pop_back();
        }
    }

    return 0;
}