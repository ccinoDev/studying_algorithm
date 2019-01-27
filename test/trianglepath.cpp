#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

int n, triangle[100][100];
int cache[100][100];
// (y,x) 위치부터 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로의 합을 반환한다.
int path(int y, int x)
{
    // 기저 사례
    if (y == n - 1)
        return triangle[y][x];
    // 메모이제이션
    int &ret = cache[y][x];
    if (ret != -1)
        return ret;

    return ret = max(path(y + 1, x), path(y + 1, x + 1)) + triangle[y][x];
}

int main()
{
    int numTC, maxSum;

    cin >> numTC;
    if (numTC < 0 || numTC > 50)
        exit(-1);

    while (numTC--)
    {
        cin >> n;
        if (n < 2 || n > 100)
            exit(-1);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i + 1; j++)
            {
                cin >> triangle[i][j];
                if (triangle[i][j] < 1 || triangle[i][j] > 100000)
                    exit(-1);
            }
        }

        memset(cache, -1, sizeof(cache));

        maxSum = path(0, 0);
        cout << maxSum << endl;
    }

    return 0;
}