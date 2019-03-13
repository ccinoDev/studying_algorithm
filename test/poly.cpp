#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 10*1000*1000;
int cache[101][101];
// n개의 정사각형으로 이루어졌고, 맨 위의 가로줄에 first개의 
// 정사각형을 포함하는 폴리오미노의 수를 반환한다.
int poly(int n, int first){
    // 기저사례: n == first
    if(n == first) return 1;
    // 메모이제이션 
    int& ret = cache[n][first];
    if(ret != -1) return ret;
    ret = 0;
    for(int second = 1; second <= n-first; ++second){
        int add = second + first - 1;
        add *= poly(n-first, second);
        add %= MOD;
        ret += add;
        ret %= MOD;
    }
    
    return ret;
}

int main(){
    int TC, n;
    int result;

    cin >> TC;
    while(TC--){
        cin >> n;

        result = 0;
        memset(cache, -1, sizeof(cache));
        for(int first = 1; first <= n; first++){
            result += poly(n, first);
            result %= MOD;
        }

        cout << result << endl;
    }

    return 0;
}