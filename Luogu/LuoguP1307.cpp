// problem statement: https://www.luogu.com.cn/problem/P1307

#include <bits/stdc++.h>

using namespace std;

string number;

int main(){
	ios::sync_with_stdio(false);
    bool negative = false;
	cin >> number;
	if (number.front() == '-'){
        negative = true;
        number = number.substr(1);	
	}
    while (number.length() > 1 && number.back() == '0') { number.pop_back(); }
    reverse(number.begin(), number.end());
    if (negative && number.front() != '0') { number = "-" + number; }
    cout << number << endl;
	return 0;
}
