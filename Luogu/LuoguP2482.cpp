// problem statement: https://www.luogu.com.cn/problem/P2482

#include <bits/stdc++.h>

using namespace std;

struct Card
{
    int roleID;
    int targetID = -1;
    bool valid;
    enum CARD_TYPE
    {
        PEACH = 1,
        KILL = 2,
        DODGE = 4,
        FIGHT = 8,
        ARROW = 16,
        INVASION = 32,
        INVALIDATION = 64,
        CROSSBOW = 128
    } type;
    explicit Card() : roleID(-1), valid(false) {}
    explicit Card(int roleID, int targetID, CARD_TYPE type) : roleID(roleID), targetID(targetID), type(type) {}
    explicit Card(int roleID, bool valid, const string &cardType) : roleID(roleID), valid(valid)
    {
        if (cardType == "P") { type = PEACH; }
        else if (cardType == "K") { type = KILL; }
        else if (cardType == "D") { type = DODGE; }
        else if (cardType == "F") { type = FIGHT; }
        else if (cardType == "N") { type = INVASION; }
        else if (cardType == "W") { type = ARROW; }
        else if (cardType == "J") { type = INVALIDATION; }
        else { type = CROSSBOW; }
    }

    explicit operator string() const
    {
        if (type == PEACH) { return "P"; }
        if (type == KILL) { return "K"; }
        if (type == DODGE) { return "D"; }
        if (type == FIGHT) { return "F"; }
        if (type == INVASION) { return "N"; }
        if (type == ARROW) { return "W"; }
        if (type == INVALIDATION) { return "J"; }
        return "Z";
    }
};
queue<Card> pile;

struct Role
{
    int id;
    int hp;
    bool hasWeapon;
    enum ROLE_TYPE
    {
        MAIN,
        LOYAL,
        REBEL
    } type;
    enum ATTITUDE {
        BAD,
        BAD_LIKE,
        GOOD,
        NONE
    };
    list<Card> handCard;
    unordered_map<int, ATTITUDE> attitude;
    int killTime;
    void getCardFromPile(int num);
    void startMyTurn();
    Card tryPlayCard(const Card &lastCard);
    ATTITUDE getAttitude(int id);
    int waitInvalidationFinish(Card lastCard);
    Card tryPlayInvalidation(const Card &lastCard);
    bool tryPlayPeachWhenDead();
    bool playArrowOrInvasion(Card &card);
    int findFirstAliveBadGuyWithinOneDistance();
    int findFirstAliveBadGuy();
    void tryThrowOrGetCard(int deadOneID);
};
vector<Role> allRole;

enum GAME_RESULT
{
    UNFINISHED,
    MAIN_WIN,
    REBEL_WIN
};

GAME_RESULT checkGameState()
{
    bool mainPigAlive = false;
    int rebelPigNum = 0;
    for (auto &&role : allRole) {
        if (role.hp <= 0) { continue; }
        if (role.type == Role::MAIN) { mainPigAlive = true; }
        else if (role.type == Role::REBEL) { rebelPigNum++; }
    }
    if (!mainPigAlive) { return REBEL_WIN; }
    if (rebelPigNum == 0) { return MAIN_WIN; }
    return UNFINISHED;
}

int pigNum, cardNum;
string pig, tempCard;
GAME_RESULT result;

ostream& operator<<(ostream &os, const Role &role)
{
    os << "[";
    os << "[id: " << role.id << "], ";
    os << "[type: " << role.type << "], ";
    os << "[hp: " << role.hp << "], ";
    os << "[weapon: " << role.hasWeapon << "], ";
    os << "[handCard: ";
    for (auto &card : role.handCard) {
        if (!card.valid) { continue; }
        os << string(card) << " ";
    }
    os << "]";
    os << "]";
    return os;
}

void updateAllRoleAttitudeWithFloy()
{
    for (int k = 0; k < allRole.size(); k++) {
        for (int i = 0; i < allRole.size(); i++) {
            for (int j = 0; j < allRole.size(); j++) {
                if (allRole[i].getAttitude(k) == Role::NONE ||
                    allRole[k].getAttitude(j) == Role::NONE ||
                    allRole[i].getAttitude(k) == Role::BAD_LIKE ||
                    allRole[k].getAttitude(j) == Role::BAD_LIKE) { continue; }
                if (allRole[i].getAttitude(k) == Role::GOOD) {
                    allRole[i].attitude[j] = allRole[k].getAttitude(j);
                } else if (allRole[i].getAttitude(k) == Role::BAD) {
                    allRole[i].attitude[j] = allRole[k].getAttitude(j) == Role::BAD ? Role::GOOD : Role::BAD;
                }
            }
        }
    }
}

void updateAllRoleAttitude(const Card &nowCard, const Card &lastCard)
{
    if (nowCard.roleID == 0) {
        return;
    } else if (lastCard.roleID == -1 && nowCard.type & (Card::FIGHT | Card::KILL)) {
        allRole[nowCard.roleID].attitude[nowCard.roleID] = Role::GOOD;
        allRole[nowCard.targetID].attitude[nowCard.roleID] = Role::BAD;
        allRole[nowCard.roleID].attitude[nowCard.targetID] = Role::BAD;
    } else if (lastCard.roleID != -1 && lastCard.type != Card::INVALIDATION) {
        allRole[nowCard.roleID].attitude[nowCard.roleID] = Role::GOOD;
        allRole[lastCard.targetID].attitude[nowCard.roleID] = Role::GOOD;
        allRole[nowCard.roleID].attitude[lastCard.targetID] = Role::GOOD;
        if (lastCard.type == Card::FIGHT) {
            allRole[nowCard.roleID].attitude[lastCard.roleID] = Role::BAD;
            allRole[lastCard.roleID].attitude[nowCard.roleID] = Role::BAD;
        }
    } else if (nowCard.type == Card::INVALIDATION) {
        allRole[nowCard.roleID].attitude[nowCard.roleID] = Role::GOOD;
        allRole[lastCard.roleID].attitude[nowCard.roleID] = Role::BAD;
        allRole[nowCard.roleID].attitude[lastCard.roleID] = Role::BAD;
    }

    updateAllRoleAttitudeWithFloy();
}


void updateAllRoleAttitudeWhenDeath(int deathID)
{
    for (auto &&role : allRole) {
        if (role.type == allRole[deathID].type ||
            (role.type == Role::MAIN && allRole[deathID].type == Role::LOYAL)) {
            role.attitude[deathID] = Role::GOOD;
        } else {
            role.attitude[deathID] = Role::BAD;
        }
    }
    
    updateAllRoleAttitudeWithFloy();
}

int main(){
	ios::sync_with_stdio(false);
    cin >> pigNum >> cardNum;
    for (int i = 0; i < pigNum; i++) {
        cin >> pig;
        Role role = {i, 4, false};
        if (pig == "MP") { role.type = Role::MAIN; }
        else if (pig == "ZP") { role.type = Role::LOYAL; }
        else { role.type = Role::REBEL; }
        for (int j = 0; j < 4; j++) {
            cin >> tempCard;
            Card card{i, true, tempCard};
            card.roleID = i;
            role.handCard.push_back(std::move(card));
        }
        allRole.push_back(std::move(role));
    }
    for (int i = 0; i < cardNum; i++) {
        cin >> tempCard;
        Card card{-1, true, tempCard};
        pile.push(std::move(card));
    }
    for (auto &&role : allRole) {
        if (role.type == Role::MAIN) { role.attitude[0] = Role::GOOD; }
        else if (role.type == Role::LOYAL) { role.attitude[0] = Role::GOOD; }
        else { role.attitude[0] = Role::BAD; }
    }
    auto iter = allRole.begin();
    while ((result = checkGameState()) == UNFINISHED) {
        iter->startMyTurn();
        iter++;
        if (iter == allRole.end()) { iter = allRole.begin(); }
    }
    if (result == MAIN_WIN) { cout << "MP\n"; }
    else { cout << "FP\n"; }
    for (auto &&role : allRole) {
        if (role.hp <= 0) { cout << "DEAD\n"; }
        else {
            for (auto &&card : role.handCard) {
                if (!card.valid) { continue; }
                cout << (string)card << " ";
            }
            cout << "\n";
        }
    }
	return 0;
}

void Role::startMyTurn()
{
    if (hp <= 0) { return; }
    killTime = 0;
    getCardFromPile(2);
    // cout << id << " started turn.\n";
    // cout << *this << endl;
    Card emptyCard{};
    while (tryPlayCard(emptyCard).roleID != -1);
    // cout << id << " finished turn.\n";
    // cout << *this << endl << endl;
}

void Role::getCardFromPile(int num)
{
    while (num--) {
        pile.front().roleID = id;
        handCard.push_back(pile.front());
        if (pile.size() == 1) { continue; }
        pile.pop();
    }
}

int Role::waitInvalidationFinish(Card lastCard)
{
    int res = 0;
    bool hasINVALIDATION = false;
    do {
        Card tempCard{};
        hasINVALIDATION = false;
        for (int i = lastCard.roleID; i < allRole.size(); i++) {
            tempCard = allRole[i].tryPlayInvalidation(lastCard);
            if (tempCard.roleID == -1) { continue; }
            break;
        }
        if (tempCard.roleID != -1) {
            hasINVALIDATION = true;
            updateAllRoleAttitude(tempCard, lastCard);
            lastCard = tempCard;
            res++;
            continue;
        }
        for (int i = 0; i < lastCard.roleID; i++) {
            tempCard = allRole[i].tryPlayInvalidation(lastCard);
            if (tempCard.roleID == -1) { continue; }
            break;
        }
        if (tempCard.roleID != -1) {
            hasINVALIDATION = true;
            updateAllRoleAttitude(tempCard, lastCard);
            lastCard = tempCard;
            res++;
        }
    } while (hasINVALIDATION);
    return res;
}

Card Role::tryPlayInvalidation(const Card &lastCard)
{
    if (hp <= 0) { return Card{}; }
    for (auto iter = handCard.begin(); iter != handCard.end(); iter++) {
        if (!iter->valid || iter->type != Card::INVALIDATION ||
            getAttitude(lastCard.targetID) == NONE || getAttitude(lastCard.targetID) == BAD_LIKE) { continue; }
        if (lastCard.type == Card::INVALIDATION && getAttitude(lastCard.targetID) == BAD) { iter->targetID = id; }
        else if (lastCard.type != Card::INVALIDATION && getAttitude(lastCard.targetID) == GOOD) { iter->targetID = lastCard.targetID; }
        else { continue; }
        iter->valid = false;
        // cout << id << " played invalidation to " << iter->targetID << " for " << lastCard.targetID << "\n";
        // cout << *this << endl;
        return *iter;
    }
    return Card{};
}

bool Role::tryPlayPeachWhenDead()
{
    for (auto &&card : handCard) {
        if (!card.valid || card.type != Card::PEACH) { continue; }
        card.valid = false;
        card.targetID = id;
        hp++;
        // cout << id << " played peach when dead.\n";
        // cout << *this << endl;
        return true;
    }
    // cout << id << " dead.\n";
    // cout << *this << endl;
    return false;
}

void Role::tryThrowOrGetCard(int deadOneID)
{
    if (type == MAIN && allRole[deadOneID].type == LOYAL) {
        hasWeapon = false;
        for (auto &&card : handCard) { card.valid = false; }
    }
    if (allRole[deadOneID].type == REBEL) { getCardFromPile(3); }
    // cout << id << " after throw or get cards.\n";
    // cout << *this << endl;
}

bool Role::playArrowOrInvasion(Card &card)
{
    card.valid = false;
    for (int i = id + 1; i < allRole.size(); i++) {
        if (allRole[i].hp <= 0) { continue; }
        card.targetID = i;
        if (waitInvalidationFinish(card) % 2 == 1) { continue; }
        if (allRole[card.targetID].tryPlayCard(card).roleID != -1) { continue; }
        allRole[card.targetID].hp--;
        if (allRole[card.targetID].hp == 0 &&
            !allRole[card.targetID].tryPlayPeachWhenDead() &&
            checkGameState() != UNFINISHED) { return false; }
        if (allRole[card.targetID].hp == 0) {
            updateAllRoleAttitudeWhenDeath(card.targetID);
            tryThrowOrGetCard(card.targetID);
        }
        if (card.targetID == 0 && allRole[0].getAttitude(id) == NONE) { allRole[0].attitude[id] = BAD_LIKE; }
    }
    for (int i = 0; i < id; i++) {
        if (allRole[i].hp <= 0) { continue; }
        card.targetID = i;
        if (waitInvalidationFinish(card) % 2 == 1) { continue; }
        if (allRole[card.targetID].tryPlayCard(card).roleID != -1) { continue; }
        allRole[card.targetID].hp--;
        if (allRole[card.targetID].hp == 0 &&
            !allRole[card.targetID].tryPlayPeachWhenDead() &&
            checkGameState() != UNFINISHED) { return false; }
        if (allRole[card.targetID].hp == 0) {
            updateAllRoleAttitudeWhenDeath(card.targetID);
            tryThrowOrGetCard(card.targetID);
        }
        if (card.targetID == 0 && allRole[0].getAttitude(id) == NONE) { allRole[0].attitude[id] = BAD_LIKE; }
    }
    return true;
}

int Role::findFirstAliveBadGuyWithinOneDistance()
{
    for (int i = id + 1; i < allRole.size(); i++) {
        if (allRole[i].hp <= 0) { continue;}
        if (getAttitude(i) == NONE || getAttitude(i) == GOOD) { return -1;}
        return i;
    }
    for (int i = 0; i < id; i++) {
        if (allRole[i].hp <= 0) { continue; }
        if (getAttitude(i) == NONE || getAttitude(i) == GOOD) { return -1;}
        return i;
    }
    return -1;
}

int Role::findFirstAliveBadGuy()
{
    if (type == REBEL) { return 0; }
    for (int i = id + 1; i < allRole.size(); i++) {
        if (allRole[i].hp <= 0 || getAttitude(i) == NONE || getAttitude(i) == GOOD) { continue;}
        return i;
    }
    for (int i = 0; i < id; i++) {
        if (allRole[i].hp <= 0 || getAttitude(i) == NONE || getAttitude(i) == GOOD) { continue; }
        return i;
    }
    return -1;
}

Card Role::tryPlayCard(const Card &lastCard)
{
    if (hp <= 0) { return Card{}; }
    bool isMyTurn = (lastCard.roleID == -1);
    for (auto iter = handCard.begin(); iter != handCard.end(); iter++) {
        if (!iter->valid) { continue; }
        if (isMyTurn && iter->type == Card::PEACH && hp < 4) {
            hp++;
            iter->valid = false;
            iter->targetID = id;
            // cout << id << " played peach.\n";
            // cout << *this << endl;
            return *iter;
        }
        if (isMyTurn && iter->type == Card::CROSSBOW) {
            hasWeapon = true;
            iter->valid = false;
            iter->targetID = id;
            // cout << id << " played crossbow.\n";
            // cout << *this << endl;
            return *iter;
        }
        if (iter->type == Card::KILL) {
            if (!isMyTurn && lastCard.type == Card::INVASION) {
                iter->valid = false;
                iter->targetID = lastCard.roleID;
                // cout << id << " played kill to invasion.\n";
                // cout << *this << endl;
                return *iter;
            }
            if (!isMyTurn && lastCard.type == Card::FIGHT) {
                if (type == LOYAL && lastCard.roleID == 0) { return Card{}; }
                iter->valid = false;
                iter->targetID = lastCard.roleID;
                // cout << id << " played kill to fight.\n";
                // cout << *this << endl;
                if (allRole[iter->targetID]
                    .tryPlayCard(Card{id, iter->targetID, Card::FIGHT})
                    .roleID == -1) { return *iter; }
                else { return Card{}; }
            }
            if (!isMyTurn || (killTime == 1 && !hasWeapon)) { continue; }
            int targetID = findFirstAliveBadGuyWithinOneDistance();
            if (targetID == -1) { continue; }
            killTime++;
            iter->valid = false;
            iter->targetID = targetID;
            // cout << id << " played kill to " << iter->targetID << "\n";
            // cout << *this << endl;
            updateAllRoleAttitude(*iter, Card{});
            if (allRole[targetID].tryPlayCard(*iter).roleID != -1) { return *iter; }
            allRole[targetID].hp--;
            if (allRole[targetID].hp == 0) { allRole[targetID].tryPlayPeachWhenDead(); }
            if (allRole[targetID].hp == 0) {
                if (checkGameState() != UNFINISHED) { return Card{}; }
                updateAllRoleAttitudeWhenDeath(targetID);
                tryThrowOrGetCard(targetID);
            }
            return *iter;
        }
        if (!isMyTurn && iter->type == Card::DODGE &&
            (lastCard.type & (Card::ARROW | Card::KILL))) {
            iter->valid = false;
            iter->targetID = lastCard.roleID;
            // cout << id << " played dodge to kill or arrow.\n";
            // cout << *this << endl;
            return *iter;
        }
        if (isMyTurn && iter->type == Card::FIGHT) {
            int targetID = findFirstAliveBadGuy();
            if (targetID == -1) { continue; }
            iter->valid = false;
            iter->targetID = targetID;
            // cout << id << " played fight to " << iter->targetID << "\n";
            // cout << *this << endl;
            updateAllRoleAttitude(*iter, Card{});
            int cnt = waitInvalidationFinish(*iter);
            if (cnt % 2 == 1) { return *iter; }
            if (allRole[targetID].tryPlayCard(*iter).roleID == -1) {
                allRole[targetID].hp--;
                if (allRole[targetID].hp == 0) { allRole[targetID].tryPlayPeachWhenDead(); }
                if (allRole[targetID].hp == 0) {
                    if (checkGameState() != UNFINISHED) { return Card{}; }
                    updateAllRoleAttitudeWhenDeath(targetID);
                    tryThrowOrGetCard(targetID);
                }
            } else {
                hp--;
                if (hp == 0) { tryPlayPeachWhenDead(); }
                if (hp == 0) {
                    if (checkGameState() != UNFINISHED) { return Card{}; }
                    updateAllRoleAttitudeWhenDeath(id);
                    allRole[targetID].tryThrowOrGetCard(id);
                    return Card{};
                }
            }
            return *iter;
        }
        if (isMyTurn && iter->type == Card::INVASION) {
            iter->valid = false;
            // cout << id << " played invasion.\n";
            // cout << *this << endl;
            if (!playArrowOrInvasion(*iter)) { return Card{}; }
            return *iter;
        }
        if (isMyTurn && iter->type == Card::ARROW) {
            iter->valid = false;
            // cout << id << " played arrow.\n";
            // cout << *this << endl;
            if (!playArrowOrInvasion(*iter)) { return Card{}; }
            return *iter;
        }
    }
    return Card{};
}


Role::ATTITUDE Role::getAttitude(int id)
{
    if (attitude.count(id) == 0) { return Role::NONE; }
    return attitude[id];
}
