#include <bits/stdc++.h>

using namespace std;

string date;
int number;

int getMonthDay(int i) {
    static int day[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return day[i];
}

int getDays(string date1, string date2)
{
    int month1 = 0, month2 = 0, day1 = 0, day2 = 0;
    for (int i = 4; i < 6; i++) {
        month1 = month1 * 10 + date1[i] - '0';
        month2 = month2 * 10 + date2[i] - '0';
    }
    for (int i = 6; i < 8; i++) {
        day1 = day1 * 10 + date1[i] - '0';
        day2 = day2 * 10 + date2[i] - '0';
    }
    if (month1 > month2) {
        swap(month1, month2);
        swap(day1, day2);
    } else if (month1 == month2) {
        if (day1 > day2) {
            swap(day1, day2);
        }
    }
    int res = 0;
    while (month1 < month2) {
        res += getMonthDay(month1) - day1;
        day1 = getMonthDay(month1);
        res++;
        day1 = 1;
        month1++;
    }
    res += day2 - day1;
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> date >> number;
    if (getDays(date, "20221201") % 7 == 0) {
        cout << number * 50 << endl;
    } else {
        cout << "0\n";
    }
    return 0;
}