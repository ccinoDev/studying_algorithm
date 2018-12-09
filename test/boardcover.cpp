#include <iostream>
#include <vector>

using namespace std;

int testCases;
int HEIGHT, WIDTH;
//char **gameArea;

const int coverType[4][3][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}}};

bool set(vector<vector<int> > &board, int y, int x, int type, int delta)
{
    bool ok = true;
    for (int i = 0; i < 3; ++i)
    {
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];
        if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
        {
            ok = false;
        }
        else if ((board[ny][nx] += delta) > 1)
        {
            ok = false;
        }
    }

    return ok;
}

int cover(vector<vector<int> >& board){
    int y = -1, x = -1;
    for(int i=0; i< board.size(); ++i){
        for(int j = 0; j < board[i].size(); ++j){
            if(board[i][j] == 0){
                y = i;
                x = j;
                break;
            }
        }
        if(y != -1) break;
    }

    if(y == -1) return 1;
    int ret = 0;
    for(int type=0; type < 4; ++type){
        if(set(board, y, x, type, 1)){
            ret += cover(board);
        }

        set(board, y, x, type, -1);
    }
    return ret;
}

int main()
{
    vector<vector<int> > board;
    char tmp;
    int cnt = 0;
    int result;

    cin >> testCases;

    if (testCases > 30 && testCases < 0)
    {
        cout << "테스트 케이스 입력범위 오류" << endl;
    }

    while (testCases--)
    {
        cin >> HEIGHT >> WIDTH;

        if (HEIGHT < 1 || WIDTH > 20)
        {
            cout << "높이, 가로 입력범위 오류" << endl;
        }

        board.assign(HEIGHT, vector<int>(WIDTH, 0));
        for (int i = 0; i < HEIGHT; ++i)
        {
            for (int j = 0; j < WIDTH; ++j)
            {
                cin >> tmp;
                if (tmp == '#')
                {
                    board[i][j] = 1;
                }
                else if(tmp == '.'){
                    cnt++;
                    board[i][j] = 0;
                }
            }
        }

        if(cnt%3 != 0){
            cout << '0' << endl;
            cnt = 0;
            board.clear();
            continue;
        }
        else{
            result = cover(board);
            cout << result << endl;
            board.clear();
        }

    }

    return 0;
}