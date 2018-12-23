#include <iostream>
#include <string>

using namespace std;
int main(){
	int num = 0;
	char game[5][5];
	string str;
	int count = 0;

	cin >> num;
	for(int i=0; i<5; ++i){
		cin >> game[i];
	}

	cin >> num;
	while(num--){
		cin >> str;
		for(int i=0; i<str.length(); ++i){
			for(int j=0; j<5; ++j){
				for(int k=0; k<5; ++k){
					if(game[j][k] == str[i]){
						count++;
					}
				}
			}
		}
		if(count == str.length()){
			cout << str << " YES" << endl;
		}
		else{
			cout << str << " NO" << endl;
		}

		count = 0;		
	}

	return 0;
}
