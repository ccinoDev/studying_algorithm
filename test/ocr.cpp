#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

int n, m, q;
// 분류기가 반환한 문장. 단어 번호로 변환되어 있음
int R[100];
// T[i][j] = i 단어 이후에 j 단어가 나올 확률의 로그값
double T[501][501];
// M[i][j] = i 단어가 j 단어로 분류될 확률의 로그값
double M[501][501];
int choice[102][102];
double cache[102][502]; // 1로 초기화한다.

// Q[segment] 이후를 채워서 얻을 수 있는 최대 g() 곱의 로그값을 반환한다.
// Q[segment-1] == previousMatch라고 가정한다.
double recognize(int segment, int previousMatch)
{
    if (segment == n)
        return 0;
    double &ret = cache[segment][previousMatch];
    if (ret != 1.0)
        return ret;
    ret = -1e200; // log(0) = 음의 무한대에 해당하는 값
    int &choose = choice[segment][previousMatch];
    // R[segment]에 대응되는 단어를 찾는다.
    for (int thisMatch = 1; thisMatch <= m; thisMatch++)
    {
        // g(thisMatch) = T(previousMatch, thisMatch) * M(thisMatch, R[segment])
        double cand = T[previousMatch][thisMatch] + M[thisMatch][R[segment]] + recognize(segment + 1, thisMatch);
        if (ret < cand)
        {
            ret = cand;
            choose = thisMatch;
        }
    }
    return ret;
}

// 입력받은 단어들의 목록
string corpus[501];
string reconstruct(int segment, int previousMatch)
{
    int choose = choice[segment][previousMatch];
    string ret = corpus[choose];
    if (segment < n - 1)
    {
        ret = ret + " " + reconstruct(segment + 1, choose);
    }
    return ret;
}

int main()
{
    double B[501];
    char inputWords[501][11], classifyWords[501][11];

    scanf("%d %d", &m, &q);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", inputWords[i]);
    }

    for (int i = 1; i <= m; i++)
    {
        scanf("%lf", &B[i]);
        B[i] = log(B[i]);
    }

    for (int i = 0; i <= m; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            //책의 트릭을 이용하여 시작단어를 [0][j] 인덱스에 저장
            //즉, Q[0]가 항상 시작단어라고 지정
            //그렇게 하면 P(Q)=∏(T(Q[i-1], Q[i])) => Begin(Q[0])*∏(T(Q[i-1], Q[i]))보다 간단
            if (i == 0)
               T[i][j] = B[j];
            else
            {
                scanf("%lf", &T[i][j]);
                T[i][j] = log(T[i][j]);
            }
        }
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%lf", &M[i][j]);
            M[i][j] = log(M[i][j]);
        }
    }

    for (int i = 1; i <= m; i++)
    {
        corpus[i] = string(inputWords[i]);
    }

    while (q--)
    {
        scanf("%d", &n);

        // double 타입은 memset으로 초기화하면 문제발생
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                cache[i][j] = 1.0;
            }
        }
        memset(choice, -1, sizeof(choice));
        memset(R, -1, sizeof(R));

        for (int i = 0; i < n; i++)
        {
            scanf("%s", classifyWords[i]);
            for (int j = 1; j <= m; j++)
            {
                if (strcmp(classifyWords[i], inputWords[j]) == 0)
                {
                    R[i] = j;
                    break;
                }
            }
        }        

        recognize(0, 0);
        printf("%s\n", reconstruct(0, 0).c_str());
    }

    return 0;
}