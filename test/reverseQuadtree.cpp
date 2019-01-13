#include <iostream>
#include <string>

using namespace std;

string reverse(string::iterator* it){
    char head = **it;
    (*it)++;

    if(head == 'b' || head == 'w'){
        return string(1, head);
    }

    string upperLeft = reverse(it);
    string upperRight = reverse(it);
    string lowerLeft = reverse(it);
    string lowerRight = reverse(it);
    
    return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main(){
    int num;
    string strInput;
    string::iterator pIt;
    string result;

    //cout << "문제 수를 입력하시오 : ";
    cin >> num;

    while(num--){
        cin >> strInput;
        pIt = strInput.begin();
        result = reverse(&pIt);

        cout << result << endl;
    }

    return 0;
}