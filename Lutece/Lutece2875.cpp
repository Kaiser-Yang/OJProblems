#include <bits/stdc++.h>

using namespace std;

int T;
string guess, answer, output;
vector<int> cnt1(26), cnt2(26);

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> guess >> answer;
        for (int i = 0; i < 26; i++) { cnt1[i] = cnt2[i] = 0; }
        output = "-----";
        for (int i = 0; i < 5; i++) {
            if (guess[i] == answer[i]) { output[i] = 'g'; }
            cnt1[guess[i] - 'a']++;
            cnt2[answer[i] - 'a']++;
        }
        for (int i = 0; i < 5; i++) {
            if (output[i] != '-') { continue; }
            if (cnt1[guess[i] - 'a'] > cnt2[guess[i] - 'a']) {
                output[i] = 'x';
            } else {
                output[i] = 'y';
            }
        }
        cout << output << endl;
    }

    return 0;
}