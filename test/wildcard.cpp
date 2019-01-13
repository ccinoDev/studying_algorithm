#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

// -1은 아직 답이 계산되지 않았음을 의미한다. 
// 1은 해당 입력들이 서로 대응됨을 의미한다. 
// 0은 해당 입력들이 서로 대응되지 않음을 의미한다.
int cache[101][101];
// 패턴과 문자열 
string W, S;
// 와일드카드 패턴 W[w..]가 문자열 S[s..]에 대응되는지 여부를 반환한다. 
bool matchMemoized(int w, int s){
    // 메모이제이션 
    int& ret = cache[w][s];
    if(ret != -1) return ret;
    // W[w]와 S[s]를 맞춰나간다. 
    if(w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s])){
        return ret = matchMemoized(w+1, s+1);
    }

    // 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참
    if(w == W.size()) return ret = (s == S.size());
    // *를 만나서 끝난 경우: *에 몇글자를 대응해야 할 지 재귀호출하면서 확인 
    if(W[w] == '*'){
        if(matchMemoized(w+1, s) || (s < S.size() && matchMemoized(w, s+1))){
            return ret = 1;
        }
    }

    // 이외의 경우는 모두 대응되지 않음 
    return  ret = 0;
}

int main(){
    int numTest, numFiles;
    bool result;
    vector<string> resultNames;

    cin >> numTest;
    while(numTest--){
        cin >> W;
        cin >> numFiles;
        while (numFiles--)
        {
            cin >> S;

            memset(cache, -1, sizeof(cache));
            result = matchMemoized(0, 0);

            if (result)
            {
                resultNames.push_back(S);
                //cout << S << endl;
            }
        }
        sort(resultNames.begin(), resultNames.end());

        for(int i = 0; i< resultNames.size(); i++){
            cout << resultNames[i] << endl;
        }

        resultNames.clear();
    }

    return 0;
}