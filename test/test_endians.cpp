#include <iostream>

using namespace std;

int main(){
	int num = 0;
	unsigned int input = 0;
	unsigned int result = 0;

	cin >> num;
	while(num--){
		cin >> input;
		result = ((input >> 24)&0xFF) | ((input << 8)&0xFF0000) | ((input >> 8)&0xFF00) | ((input << 24)&0xFF000000);

		cout << result << endl;
	}

	return 0;
}
