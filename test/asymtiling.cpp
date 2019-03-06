#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
int cache[101];
// 2*width 크기의 사각형을 채우는 방법의 수를 MOD로 나눈 나머지를 반환한다.
int tiling(int width){
    // 기저사례: width가 1이하일 때 
    if(width <= 1) return 1;
    // 메모이제이션 
    int &ret = cache[width];
    if(ret != -1) return ret;
    return ret = (tiling(width-2) + tiling(width-1)) % MOD;
}

// 2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
// MOD를 더하여 리턴값이 음수가 되는 문제를 해결한다.
int asymmetric(int width){
    if(width % 2 == 1)
    return (tiling(width) - tiling(width/2) + MOD) % MOD;

    int ret = tiling(width);
    ret = (ret - tiling(width/2) + MOD) % MOD;
    ret = (ret - tiling(width/2-1) + MOD) % MOD;
    return ret;
}

int cache2[101];
// 2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
int asymmetric2(int width){
    // 기저사례: 너비가 2이하인 경우 
    if(width <= 2) return 0;

    // 메모이제이션 
    int& ret = cache2[width];
    if(ret != -1) return ret;
    ret = asymmetric2(width - 2) % MOD;
    ret = (ret + asymmetric2(width - 4)) % MOD;
    ret = (ret + tiling(width - 3)) % MOD;
    ret = (ret + tiling(width - 3)) % MOD;
}

int main(){
    int TC, n;
    int result;

    cin >> TC;
    while(TC--){
        cin >> n;
        if(n < 1 && n > 100){
            cout << "사각형 너비 범위 초과" << endl;
            return -1;
        }
        memset(cache, -1, sizeof(cache));

        result = asymmetric(n);
        cout << result << endl;
    }

    return 0;
}