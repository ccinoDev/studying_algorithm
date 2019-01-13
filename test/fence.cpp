#include <iostream>
#include <vector>

using namespace std;

vector<int> h;

int solve(int left, int right){
    // left ~ right 구간에서 찾을 수 있는 최대 직사각형의 넓이를 반환 
    // 기저: 판자가 하나일 경우 
    if(left == right) return h[left];
    int mid = (left + right)/2;
    int ret = max(solve(left,mid), solve(mid+1,right));
    
    // 부분문제 : 두 부분에 모두 걸치는 사각형 중 가장 큰 것을 찾는다 
    int lo = mid, hi = mid+1;
    int height = min(h[lo], h[hi]);
    ret = max(ret, height*2);
    while(left < lo || hi < right){
        // 항상 높이가 더 높은쪽으로 확장 
        if(hi < right && (lo == left || h[lo-1] < h[hi+1])){
            ++hi;
            height = min(height, h[hi]);
        }else{
            --lo;
            height = min(height, h[lo]);
        }
        ret = max(ret, (hi-lo+1)*height);
    }
    return ret;
}

int main(){
    int t, n, num;

    cin >> t;
    while(t--){
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> num;
            h.push_back(num);
        }
        int N = (int)h.size();
        int ans = solve(0, N-1);
        cout << ans << endl;
        h.clear();
    }

    return 0;
}