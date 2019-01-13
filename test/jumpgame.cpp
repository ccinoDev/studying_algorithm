#include <iostream>
#include <string.h>

using namespace std;

int n, board[100][100];
int cache[100][100];
int jump2(int y, int x){
    // 기저사례 
    if(y >= n || x >= n) return 0;
    if(y == n-1 && x == n-1) return 1;

    // 메모이제이션 
    int& ret = cache[y][x];
    if(ret != -1) return ret;
    int jumpSize = board[y][x];
    return ret = (jump2(y + jumpSize, x) || jump2(y, x + jumpSize));
}

int main(){
    int numTest = 0;
    int result = 0;
    char cInput;
        
    cin >> numTest;
    while(numTest--){
        cin >> n;

        memset(cache, -1, sizeof(cache));
        for(int i =0; i < n; i++){
            for(int j = 0; j<n; j++){
                cin >> cInput;
                board[i][j] = cInput - '0';
            }
        }

        result = jump2(0, 0);

        if(result) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}