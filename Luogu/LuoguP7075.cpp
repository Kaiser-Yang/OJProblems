// problem statement: https://www.luogu.com.cn/problem/P7075

#include <bits/stdc++.h>

constexpr int MAXN = 1e5 + 10;

using namespace std;

int n, pos;
pair<long long, int> delta[MAXN];
int monthDay[] = {0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Date
{
    int year, month, day;
    int getMonthDay() {
        if (month != 2) { return monthDay[month]; }
        if ((year < 0 && (abs(year) - 1) % 4 == 0) ||
            (year >= 1 && year <= 1582 && year % 4 == 0) ||
            (year > 1582 && (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)))) { return 29; }
        return 28;
    }
    Date operator++(int ) {
        Date res = *this;
        if (year == 1582 && month == 10 && day == 4) { day = 15; }
        else if (day < getMonthDay()) { day++; }
        else {
            day = 1;
            month++;
            if (month == 13) {
                month = 1;
                year++;
                if (year == 0) { year++; }
            }
        }
        return res;
    }
} ans[MAXN], temp[146097 + 5];

ostream & operator<<(ostream &os, const Date &date)
{
    os << date.day << " " << date.month << " " << abs(date.year);
    if (date.year < 0) { os << " BC"; }
    return os;
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> delta[i].first;
        delta[i].second = i;
    }
    sort(delta + 1, delta + 1 + n);
    for (int i = 1; i <= n; i++) {
        if (delta[i].first >= 2451545) { break; }
        pos = i;
    }
    Date now = {-4713, 1, 1};
    long long cnt = 0;
    for (int i = 1; i <= pos; i++) {
        while (cnt < delta[i].first) {
            now++;
            cnt++;
        }
        ans[delta[i].second] = now;
    }
    now = {2000, 1, 1};
    int len = 0;
    while (now.year < 2400) {
        temp[len++] = now;
        now++;
    }
    for (int i = pos + 1; i <= n; i++) {
        ans[delta[i].second] = {temp[(delta[i].first - 2451545) % 146097].year + int(400 * ((delta[i].first - 2451545) / 146097)), 
                                temp[(delta[i].first - 2451545) % 146097].month,
                                temp[(delta[i].first - 2451545) % 146097].day};
    }
    for (int i = 1; i <= n; i++) { cout << ans[i] << "\n"; }
	return 0;
}
