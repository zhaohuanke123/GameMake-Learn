#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int NN = 2010;

int f[NN][NN];

int main()
{

    int n;
    cin >> n;

    while (n--)
    {
        string s, t;
        cin >> s >> t;
        memset(f, 0, sizeof f);
        for (int i = 1; i <= s.size(); i++)
            f[i][0] = i;
        for (int j = 1; j <= t.size(); j++)
            f[0][j] = j;

        for (int i = 1; i <= s.size(); i++)
        {
            for (int j = 1; j <= t.size(); j++)
            {

                if (s[i - 1] == t[j - 1])
                {
                    f[i][j] = f[i - 1][j - 1];
                }
                else
                    f[i][j] = min(f[i - 1][j - 1], min(f[i][j - 1], f[i - 1][j])) + 1;
            }
        }
        for (int i = 1; i <= s.size(); i++)
        {
            for (int j = 1; j <= t.size(); j++)
            {

                cout << f[i][j] << " ";
            }
            cout << "\n";
        }

        cout << f[s.size()][t.size()] << "\n";
    }
}
