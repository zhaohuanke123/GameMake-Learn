#include <iostream>
#include <cmath>
using namespace std;

const int NN = 1000;

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