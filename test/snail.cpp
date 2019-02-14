#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

#define MAX_N 1000

int n, m;
double cache[MAX_N][2*MAX_N+1];
// 달팽이가 days일 동안 climbed미터를 기어올라 왔다고 할 때,
// m일 전까지 n미터를 기어올라갈 수 있는 확률
double climb(int days, int climbed){
    // 기저사례: m일이 모두 지난 경우 
    if(days == m) return climbed >= n ? 1:0;
    // 메모이제이션 
    double& ret = cache[days][climbed];
    if(ret != -1) return ret;
    return ret = 0.25*climb(days+1, climbed+1) + 0.75*climb(days+1, climbed+2);
}

int main(){
    int C;
    double result;

    cin >> C;
    while(C--){
        cin >> n >> m;

        //memset(cache, -1.0, sizeof(cache)); // memset은 정수형에만 사용...
        for(int i = 0; i < MAX_N; i++){
            for(int j = 0; j < 2*MAX_N+1; j++){
                cache[i][j] = -1;
            }
        }

        result = climb(0, 0);

        cout.precision(11);
        cout << result << endl;

    }

    return 0;
}