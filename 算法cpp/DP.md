# 动态规划


考虑两方面：

1. 状态表示
2. 状态计算

> 状态表示

状态属于哪些集合

表示什么属性：Min，Max，数量等


> 状态计算

对应 集合的划分(划分子集)

划分原则：

1. 不重：（求个数必须满足）两个元素不同时属于两个集合
2. 不漏：（必须满足）元素必须属于某个集合


# 背包问题

## 01背包

状态表示：

选法：f（i，j）前i个物体，总体积 <=j

属性：最大值

集合划分：

f（i，j）:

1. 不包含 i 选法的集合
2. 包含 i 选法的集合


```cpp
const int NN = 1010;

int f[NN][NN];
int N, V;
int v[NN], w[NN];

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= V; j++)
        {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])
                f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
        }

        cout << f[N][V];
}
```



滚动数组优化二维数组空间：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

const int NN = 1010;

int f[NN];
int N, V;
int v[NN], w[NN];

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];

    for (int i = 1; i <= N; i++)
        for (int j = V; j >= v[i]; j--)
        {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }

    cout << f[V];
}
```


## 完全背包

状态表示：同01背包

状态计算：

f（i，j）：

1. 选0个
2. 选1个
3. ... 选了k个

朴素做法：

转移方程：

f（i，j） = max（f（i，j），f（i-1，j - vi * k）+ wi  * k） (k * vi <= j)

```cpp
#include <iostream>
#include <cmath>
using namespace std;

const int NN = 1010;

int f[NN][NN];
int N, V;
int v[NN], w[NN];

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= V; j++)
        {
            for (int k = 0; k * v[i] <= j; k++)
            {
                f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);
            }
        }

    cout << f[N][V];
}
```


由于我们的

f (i , j) = max( f(i, j ) , f(i - 1, j - vi) + w, ... f(i-1 , j - k * vi) + k * w)

f (i, j - v) = max (f(i - 1, j - v), f(i - 1, j - 2 * v) + w, ... f (i-1, j - k * vi) + (k - 1) * w)


f (i, j )和 f (i, j - v) 后面一坨是一样的，重复运算了。

可将方程修改为 f (i ,  j) =  max (f(i, j ) + f (i, j - vi) + wi)

```cpp
#include <iostream>
#include <cmath>
using namespace std;

const int NN = 1010;

int f[NN][NN];
int N, V;
int v[NN], w[NN];

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= V; j++)
        {
            f[i][j] = f[i - 1][j];
            if (v[i] <= j)
                f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]);
        }

    cout << f[N][V];
}
```


同样，之后我们可以优化空间

```cpp
#include <iostream>
#include <cmath>
using namespace std;

const int NN = 1010;

int f[NN];
int N, V;
int v[NN], w[NN];

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];

    for (int i = 1; i <= N; i++)
        for (int j = v[i]; j <= V; j++)
        {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }

    cout << f[V];
}
```


## 多重背包

暴力做法：O[N * V * s]

```cpp
#include <iostream>
#include <cmath>
using namespace std;

const int NN = 1010;

int f[NN][NN];
int N, V;
int v[NN], w[NN],s[NN];

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i] >> s[i];

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= V; j++)
        {
            for (int k = 0; k * v[i] <= j && k <= s[i]; k++)
            {
                f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);
            }
        }

    cout << f[N][V];
}

```

二进制优化：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

const int NN = 10100;

int f[NN];
int N, V;
int v[NN], w[NN], s[NN];
int cnt;

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        int k = 1;
        while (k <= c)
        {
            cnt++;
            v[cnt] = k * a;
            w[cnt] = k * b;
            c -= k;
            k *= 2;
        }

        if (c > 0)
        {
            cnt++;
            v[cnt] = a * c;
            w[cnt] = b * c;
        }
    }

    N = cnt;
    for (int i = 1; i <= N; i++)
        for (int j = V; j >= v[i]; j--)
        {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }

    cout << f[V];
}

```
