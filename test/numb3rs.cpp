#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n, d, p, q;
// connected[i][j] = 마을 i, j의 연결 여부 
// deg[i] = 마을 i와 연결된 마을의 개수 
int connected[51][51], deg[51];
double search(vector<int>& path){
    // 기저사례: d일이 지난 경우
    if(path.size() == d+1){
        // 이 시나리오가 q에서 끝나지 않는다면 무효 
        if(path.back() != q) return 0.0;
        // path의 출현 확률을 계산한다.
        double ret = 1.0;
        for(int i = 0; i + 1 < path.size(); i++){
            ret /= deg[path[i]];
        }
        return ret;
    }

    double ret = 0;
    // 경로의 다음 위치를 결정한다.
    for(int there = 0; there < n; there++){
        if(connected[path.back()][there]){
            path.push_back(there);
            ret += search(path);
            path.pop_back();
        }
    }
    return ret;
}

double cache[51][101];
// days일째에 here번 마을에 숨어있다고 가정하고,
// 마지막 날에 q번 마을에 숨어있을 조건부 확률을 반환한다.
double search2(int here, int days){
    // 기저사례: d일이 지난 경우 
    if(days == d) return (here == q ? 1.0 : 0.0);
    // 메모이제이션 
    double& ret = cache[here][days];
    if(ret > -0.5) return ret;
    ret = 0.0;
    for(int there = 0; there < n; there++){
        if(connected[here][there])
            ret += search2(there, days+1) / deg[here];
    }
    return ret;
}

double search3(int here, int days){
    // 기저사례: 0일 째 
    if(days == 0) return (here == p ? 1.0 : 0.0);
    // 메모이제이션 
    double& ret = cache[here][days];
    if(ret > -0.5) return ret;
    ret = 0.0;
    for(int there = 0; there < n; there++){
        if(connected[here][there])
            ret += search3(there, days-1) / deg[there];
    }
    return ret;
}

int main(){
    int testcase, t;
    cin >> testcase;
    while (testcase--)
    {
        cin >> n >> d >> p;
        for (int i = 0; i < n; i++)
        {
            deg[i] = 0;
            for (int j = 0; j < n; j++)
            {
                cin >> connected[i][j];
                if (connected[i][j] == 1)
                    deg[i]++;
            }
        }

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= d; j++)
            {
                cache[i][j] = -1.0;
            }
        }

        cin >> t;
        cout.precision(8);
        for (int i = 0; i < t; i++)
        {
            cin >> q;
            cout << search3(q, d) << " ";
        }
        cout << endl;
    }
    return 0;
}