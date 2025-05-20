// problem statement: http://bailian.openjudge.cn/practice/3750/

#include <bits/stdc++.h>

constexpr int MAXN = 25;

using namespace std;

int kase;
int cityNum, redWealth, blueWealth, T, endTime;
array<int, 5> hp, attack;
int redID, blueID;
int nowTime;
queue<int> redSequence, blueSequence;
array<int, MAXN> cityWealth;
const array<string, 5> fighterName = {"dragon", "ninja", "iceman", "lion", "wolf"};

enum FLAG_TYPE { NONE, RED_FLAG, BLUE_FLAG };

struct Fighter {
    int type, id, hp, attack, killTime;
};

vector<Fighter> cityRedFighter[MAXN], cityBlueFighter[MAXN];
array<FLAG_TYPE, MAXN> cityFlag;
array<pair<int, int>, MAXN> cityWinTime;

void outputTime(int x) {
    int hour = x / 60;
    int minute = x % 60;
    cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute;
}

void clearQueue(queue<int> &q) {
    while (!q.empty()) { q.pop(); }
}

void init() {
    clearQueue(redSequence);
    clearQueue(blueSequence);

    redSequence.push(2);
    redSequence.push(3);
    redSequence.push(4);
    redSequence.push(1);
    redSequence.push(0);

    blueSequence.push(3);
    blueSequence.push(0);
    blueSequence.push(1);
    blueSequence.push(2);
    blueSequence.push(4);

    nowTime = 0;

    fill(cityWealth.begin(), cityWealth.end(), 0);

    redID = blueID = 0;

    fill(cityRedFighter, cityRedFighter + MAXN, vector<Fighter>());
    fill(cityBlueFighter, cityBlueFighter + MAXN, vector<Fighter>());

    fill(cityFlag.begin(), cityFlag.end(), NONE);

    fill(cityWinTime.begin(), cityWinTime.end(), pair<int, int>{0, 0});
}

void createFighter() {
    int redFighterType = redSequence.front();
    if (redWealth >= hp[redFighterType]) {
        outputTime(nowTime);
        cout << " red " << fighterName[redFighterType] << " " << ++redID << " born\n";
        cityRedFighter[0].push_back(
            {redFighterType, redID, hp[redFighterType], attack[redFighterType], 0});
        redSequence.pop();
        redSequence.push(redFighterType);
        redWealth -= hp[redFighterType];
    }

    int blueFighterType = blueSequence.front();
    if (blueWealth >= hp[blueFighterType]) {
        outputTime(nowTime);
        cout << " blue " << fighterName[blueFighterType] << " " << ++blueID << " born\n";
        cityBlueFighter[cityNum + 1].push_back(
            {blueFighterType, blueID, hp[blueFighterType], attack[blueFighterType], 0});
        blueSequence.pop();
        blueSequence.push(blueFighterType);
        blueWealth -= hp[blueFighterType];
    }

    nowTime += 10;
}

bool moveFighter() {
    for (int i = 1; i <= cityNum; i += 2) {
        for (auto &&fighter : cityRedFighter[i]) {
            if (fighterName[fighter.type] == "iceman") {
                fighter.hp -= 9;
                fighter.attack += 20;
                fighter.hp = max(fighter.hp, 1);
            }
        }
    }
    for (int i = cityNum; i >= 1; i -= 2) {
        for (auto &&fighter : cityBlueFighter[i]) {
            if (fighterName[fighter.type] == "iceman") {
                fighter.hp -= 9;
                fighter.attack += 20;
                fighter.hp = max(fighter.hp, 1);
            }
        }
    }
    for (auto &&fighter : cityBlueFighter[1]) {
        outputTime(nowTime);
        cout << " blue " << fighterName[fighter.type] << " " << fighter.id
             << " reached red headquarter with " << fighter.hp << " elements and force "
             << fighter.attack << "\n";
        cityBlueFighter[0].push_back(std::move(fighter));
    }
    bool res = false;
    if (cityBlueFighter[0].size() >= 2) {
        outputTime(nowTime);
        cout << " red headquarter was taken" << "\n";
        res = true;
    }
    for (int i = 1; i <= cityNum; i++) {
        for (auto &&fighter : cityRedFighter[i - 1]) {
            outputTime(nowTime);
            cout << " red " << fighterName[fighter.type] << " " << fighter.id << " marched to city "
                 << i << " with " << fighter.hp << " elements and force " << fighter.attack << "\n";
        }
        for (auto &&fighter : cityBlueFighter[i + 1]) {
            outputTime(nowTime);
            cout << " blue " << fighterName[fighter.type] << " " << fighter.id
                 << " marched to city " << i << " with " << fighter.hp << " elements and force "
                 << fighter.attack << "\n";
        }
    }
    for (auto &&fighter : cityRedFighter[cityNum]) {
        outputTime(nowTime);
        cout << " red " << fighterName[fighter.type] << " " << fighter.id
             << " reached blue headquarter with " << fighter.hp << " elements and force "
             << fighter.attack << "\n";
        cityRedFighter[cityNum + 1].push_back(std::move(fighter));
    }
    if (cityRedFighter[cityNum + 1].size() >= 2) {
        outputTime(nowTime);
        cout << " blue headquarter was taken" << "\n";
        res = true;
    }

    for (int i = cityNum; i >= 1; i--) { cityRedFighter[i] = cityRedFighter[i - 1]; }
    cityRedFighter[0].clear();
    for (int i = 1; i <= cityNum; i++) { cityBlueFighter[i] = cityBlueFighter[i + 1]; }
    cityBlueFighter[cityNum + 1].clear();
    nowTime += 10;
    return res;
}

void generateWealth() {
    for (int i = 1; i <= cityNum; i++) { cityWealth[i] += 10; }
    nowTime += 10;
}

void getWealth() {
    for (int i = 1; i <= cityNum; i++) {
        if (cityWealth[i] == 0) { continue; }
        if (cityRedFighter[i].size() + cityBlueFighter[i].size() == 1) {
            if (cityRedFighter[i].size() == 1) {
                redWealth += cityWealth[i];
                outputTime(nowTime);
                cout << " red " << fighterName[cityRedFighter[i][0].type] << " "
                     << cityRedFighter[i][0].id << " earned " << cityWealth[i]
                     << " elements for his headquarter\n";
            } else {
                blueWealth += cityWealth[i];
                outputTime(nowTime);
                cout << " blue " << fighterName[cityBlueFighter[i][0].type] << " "
                     << cityBlueFighter[i][0].id << " earned " << cityWealth[i]
                     << " elements for his headquarter\n";
            }
            cityWealth[i] = 0;
        }
    }
    nowTime += 10;
}

void fight() {
    vector<bool> redAward(cityNum, false), blueAward(cityNum, false);
    for (int i = 1; i <= cityNum; i++) {
        if (cityRedFighter[i].size() == 1 && cityBlueFighter[i].size() == 1) {
            if (cityFlag[i] == RED_FLAG || (cityFlag[i] == NONE && i % 2 == 1)) {
                outputTime(nowTime);
                cout << " red " << fighterName[cityRedFighter[i][0].type] << " "
                     << cityRedFighter[i][0].id << " attacked blue "
                     << fighterName[cityBlueFighter[i][0].type] << " " << cityBlueFighter[i][0].id
                     << " in city " << i << " with " << cityRedFighter[i][0].hp
                     << " elements and force " << cityRedFighter[i][0].attack << "\n";
                int tempHP = cityBlueFighter[i][0].hp;
                cityBlueFighter[i][0].hp -= cityRedFighter[i][0].attack;
                if (cityBlueFighter[i][0].hp <= 0) {
                    outputTime(nowTime);
                    cout << " blue " << fighterName[cityBlueFighter[i][0].type] << " "
                         << cityBlueFighter[i][0].id << " was killed in city " << i << "\n";
                    cityWinTime[i].first++;
                    cityWinTime[i].second = 0;
                    cityRedFighter[i][0].killTime++;
                    if (cityRedFighter[i][0].killTime % 2 == 0 &&
                        fighterName[cityRedFighter[i][0].type] == "wolf") {
                        cityRedFighter[i][0].hp *= 2;
                        cityRedFighter[i][0].attack *= 2;
                    }
                    if (fighterName[cityBlueFighter[i][0].type] == "lion") {
                        cityRedFighter[i][0].hp += tempHP;
                    }
                    cityBlueFighter[i].pop_back();
                }
                if (!cityBlueFighter[i].empty() &&
                    fighterName[cityBlueFighter[i][0].type] != "ninja") {
                    outputTime(nowTime);
                    cout << " blue " << fighterName[cityBlueFighter[i][0].type] << " "
                         << cityBlueFighter[i][0].id << " fought back against red "
                         << fighterName[cityRedFighter[i][0].type] << " " << cityRedFighter[i][0].id
                         << " in city " << i << "\n";
                    tempHP = cityRedFighter[i][0].hp;
                    cityRedFighter[i][0].hp -= cityBlueFighter[i][0].attack / 2;
                    if (cityRedFighter[i][0].hp <= 0) {
                        outputTime(nowTime);
                        cout << " red " << fighterName[cityRedFighter[i][0].type] << " "
                             << cityRedFighter[i][0].id << " was killed in city " << i << "\n";
                        cityWinTime[i].first = 0;
                        cityWinTime[i].second++;
                        if (fighterName[cityRedFighter[i][0].type] == "lion") {
                            cityBlueFighter[i][0].hp += tempHP;
                        }
                        cityRedFighter[i].pop_back();
                    }
                }
                if (!cityRedFighter[i].empty() &&
                    fighterName[cityRedFighter[i][0].type] == "dragon") {
                    outputTime(nowTime);
                    cout << " red dragon " << cityRedFighter[i][0].id << " yelled in city " << i
                         << "\n";
                }
            } else {
                outputTime(nowTime);
                cout << " blue " << fighterName[cityBlueFighter[i][0].type] << " "
                     << cityBlueFighter[i][0].id << " attacked red "
                     << fighterName[cityRedFighter[i][0].type] << " " << cityRedFighter[i][0].id
                     << " in city " << i << " with " << cityBlueFighter[i][0].hp
                     << " elements and force " << cityBlueFighter[i][0].attack << "\n";
                int tempHP = cityRedFighter[i][0].hp;
                cityRedFighter[i][0].hp -= cityBlueFighter[i][0].attack;
                if (cityRedFighter[i][0].hp <= 0) {
                    outputTime(nowTime);
                    cout << " red " << fighterName[cityRedFighter[i][0].type] << " "
                         << cityRedFighter[i][0].id << " was killed in city " << i << "\n";
                    cityWinTime[i].first = 0;
                    cityWinTime[i].second++;
                    cityBlueFighter[i][0].killTime++;
                    if (cityBlueFighter[i][0].killTime % 2 == 0 &&
                        fighterName[cityBlueFighter[i][0].type] == "wolf") {
                        cityBlueFighter[i][0].hp *= 2;
                        cityBlueFighter[i][0].attack *= 2;
                    }
                    if (fighterName[cityRedFighter[i][0].type] == "lion") {
                        cityBlueFighter[i][0].hp += tempHP;
                    }
                    cityRedFighter[i].pop_back();
                }
                if (!cityRedFighter[i].empty() &&
                    fighterName[cityRedFighter[i][0].type] != "ninja") {
                    outputTime(nowTime);
                    cout << " red " << fighterName[cityRedFighter[i][0].type] << " "
                         << cityRedFighter[i][0].id << " fought back against blue "
                         << fighterName[cityBlueFighter[i][0].type] << " "
                         << cityBlueFighter[i][0].id << " in city " << i << "\n";
                    tempHP = cityBlueFighter[i][0].hp;
                    cityBlueFighter[i][0].hp -= cityRedFighter[i][0].attack / 2;
                    if (cityBlueFighter[i][0].hp <= 0) {
                        outputTime(nowTime);
                        cout << " blue " << fighterName[cityBlueFighter[i][0].type] << " "
                             << cityBlueFighter[i][0].id << " was killed in city " << i << "\n";
                        cityWinTime[i].first++;
                        cityWinTime[i].second = 0;
                        if (fighterName[cityBlueFighter[i][0].type] == "lion") {
                            cityRedFighter[i][0].hp += tempHP;
                        }
                        cityBlueFighter[i].pop_back();
                    }
                }
                if (!cityBlueFighter[i].empty() &&
                    fighterName[cityBlueFighter[i][0].type] == "dragon") {
                    outputTime(nowTime);
                    cout << " blue dragon " << cityBlueFighter[i][0].id << " yelled in city " << i
                         << "\n";
                }
            }
            if (cityRedFighter[i].size() + cityBlueFighter[i].size() == 1) {
                if (cityRedFighter[i].size() == 1) {
                    redAward[i] = true;
                    if (cityWealth[i] > 0) {
                        outputTime(nowTime);
                        cout << " red " << fighterName[cityRedFighter[i][0].type] << " "
                             << cityRedFighter[i][0].id << " earned " << cityWealth[i]
                             << " elements for his headquarter\n";
                    }
                } else {
                    blueAward[i] = true;
                    if (cityWealth[i] > 0) {
                        outputTime(nowTime);
                        cout << " blue " << fighterName[cityBlueFighter[i][0].type] << " "
                             << cityBlueFighter[i][0].id << " earned " << cityWealth[i]
                             << " elements for his headquarter\n";
                    }
                }
                if (cityWinTime[i].first == 2) {
                    if (cityFlag[i] != RED_FLAG) {
                        cityFlag[i] = RED_FLAG;
                        outputTime(nowTime);
                        cout << " red flag raised in city " << i << "\n";
                    }
                } else if (cityWinTime[i].second == 2) {
                    if (cityFlag[i] != BLUE_FLAG) {
                        cityFlag[i] = BLUE_FLAG;
                        outputTime(nowTime);
                        cout << " blue flag raised in city " << i << "\n";
                    }
                }
            } else {
                cityWinTime[i].first = cityWinTime[i].second = 0;
            }
        }
    }
    for (int i = cityNum; i >= 1; i--) {
        if (redAward[i] && redWealth >= 8) {
            redWealth -= 8;
            cityRedFighter[i][0].hp += 8;
        }
    }
    for (int i = 1; i <= cityNum; i++) {
        if (blueAward[i] && blueWealth >= 8) {
            blueWealth -= 8;
            cityBlueFighter[i][0].hp += 8;
        }
    }
    for (int i = 1; i <= cityNum; i++) {
        if (redAward[i]) {
            redWealth += cityWealth[i];
            cityWealth[i] = 0;
        } else if (blueAward[i]) {
            blueWealth += cityWealth[i];
            cityWealth[i] = 0;
        }
    }
    nowTime += 10;
}

void reportWealth() {
    outputTime(nowTime);
    cout << " " << redWealth << " elements in red headquarter\n";
    outputTime(nowTime);
    cout << " " << blueWealth << " elements in blue headquarter\n";
    nowTime += 10;
}

int main() {
    ios::sync_with_stdio(false);
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    cin >> T;
    while (T--) {
        cin >> redWealth >> cityNum >> endTime;
        blueWealth = redWealth;
        for (int i = 0; i < 5; i++) { cin >> hp[i]; }
        for (int i = 0; i < 5; i++) { cin >> attack[i]; }
        cout << "Case:" << ++kase << "\n";
        init();
        while (nowTime <= endTime) {
            createFighter();
            if (nowTime > endTime) { break; }
            if (moveFighter()) { break; }
            if (nowTime > endTime) { break; }
            generateWealth();
            if (nowTime > endTime) { break; }
            getWealth();
            if (nowTime > endTime) { break; }
            fight();
            if (nowTime > endTime) { break; }
            reportWealth();
        }
    }
    return 0;
}
