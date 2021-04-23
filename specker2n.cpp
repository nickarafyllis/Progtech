#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Player {
public:
    Player(const string &n) {
        playerName = n;
    }
    virtual ~Player() {
        playerName.clear();
    }

    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player) {
        out << player.getType() << " player " << player.playerName;
        return out;
    }

protected:
    string playerName;
};

class GreedyPlayer: public Player {
public:
    GreedyPlayer(const string &n) : Player(n) {
        playerType = "Greedy";
    }
    
    virtual const string & getType() const override { return playerType; }
    
    virtual Move play(const State &s) override {
        int mostCoins = 0;
        for (int i = 0; i < s.getHeaps(); i++) {
            if (s.getCoins(i) > s.getCoins(mostCoins)) {
                mostCoins = i;
            }
        }       
        return Move (mostCoins, s.getCoins(mostCoins), 0, 0);
    }

private:
    string playerType;
};

class SpartanPlayer: public Player {
public:
    SpartanPlayer(const string &n) : Player(n) {
        playerType = "Spartan";
    }
    
    virtual const string & getType() const override { return playerType; }
    
    virtual Move play(const State &s) override {
        int mostCoins = 0;
        for (int i = 0; i < s.getHeaps(); i++) {
            if (s.getCoins(i) > s.getCoins(mostCoins)) {
                mostCoins = i;
            }
        }
        return Move (mostCoins, 1, 0, 0);
    }

private:
    string playerType;
};

class SneakyPlayer: public Player {
public:
    SneakyPlayer(const string &n) : Player(n) {
        playerType = "Sneaky";
    }
    
    virtual const string & getType() const override { return playerType; }
    
    virtual Move play(const State &s) override {
        int i = 0;
        while(s.getCoins(i) == 0) { i++; }
        
        int leastCoins = i;
                
        for (int i = leastCoins + 1; i < s.getHeaps(); i++) {
            if (s.getCoins(i) != 0 && s.getCoins(i) < s.getCoins(leastCoins)) {
                leastCoins = i;
            } 
        }
        return Move(leastCoins, s.getCoins(leastCoins), 0, 0);
    }

private:
    string playerType;
};

class RighteousPlayer: public Player {
public:
    RighteousPlayer(const string &n) : Player(n) {
        playerType = "Righteous";
    }
    
    virtual const string & getType() const override { return playerType; }
    
    virtual Move play(const State &s) override {
        int mostCoins = 0, leastCoins = 0, coins;
        for (int i = 0; i < s.getHeaps(); i++) {
            if (s.getCoins(i) > s.getCoins(mostCoins)) {
                mostCoins = i;
            }
            if (s.getCoins(i) < s.getCoins(leastCoins)) {
                leastCoins = i;
            }
        }
        if (s.getCoins(mostCoins) % 2 == 0) {
            coins = s.getCoins(mostCoins) / 2;
        }
        else {
            coins = (s.getCoins(mostCoins) / 2) + 1;
        }
        return Move(mostCoins, coins, leastCoins, coins - 1);
        
    }

private:
    string playerType;
};

