#include <bits/stdc++.h>

using namespace std;

int T;
string str;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> str;
        bool https = false;
        if (str.substr(0, 5) == "https") { https = true; }
        if (https) { str.replace(0, 5, "http"); }
        for (int i = 7; i < str.length(); i++) {
            if (str[i] == ':') {
                str[i] = '-';
                i++;
                while (i < str.length() && isdigit(str[i])) { i++; }
                string ending = str.substr(i);
                str.replace(i, str.length() - i, "");
                str += "-p";
                if (https) { str += "-s"; }
                str += ".vpn.uestc.edu.cn:8118";
                str += ending;
                break;
            } else if (str[i] == '/') {
                string ending = str.substr(i);
                str.replace(i, str.length() - i, "");
                if (https) { str += "-s"; }
                str += ".vpn.uestc.edu.cn:8118";
                str += ending;
                break;
            } else if (str[i] == '.') {
                str[i] = '-';
            }
            if (i == str.length() - 1) {
                if (https) { str += "-s"; }
                str += ".vpn.uestc.edu.cn:8118";
                break;
            }
        }
        cout << str << endl;
    }
    return 0;
}