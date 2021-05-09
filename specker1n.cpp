#include <iostream>
#include <stdexcept>

using namespace std;

class Move {
public:

    // Take sc coins from heap sh and put tc coins to heap th.

    Move(int sh, int sc, int th, int tc) {
        sourceHeap = sh;
        sourceCoins = sc;
        targetHeap = th;
        targetCoins = tc;
    }

    int getSource() const { return sourceHeap; }
    int getSourceCoins() const { return sourceCoins; }
    int getTarget() const { return targetHeap; }
    int getTargetCoins() const { return targetCoins; }

    friend ostream & operator << (ostream &out, Move &move) {

        if (move.getTargetCoins() != 0) {
            out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts " << move.getTargetCoins() << " coins to heap " << move.getTarget();
        }
        else {
            out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts nothing";
        }
        return out;

    }

private:

    int sourceHeap, sourceCoins, targetHeap, targetCoins;

};

class State {
public:

    // State with h heaps, where the i-th heap starts with c[i] coins.
    // A total of n players are in the game, numbered from 0 to n-1,
    // and player 0 is the first to play.

    State(int h, const int c[], int n) {

        maxHeaps = h;
        coins = new int[maxHeaps];
        for (int i = 0; i < maxHeaps; i++) {
            coins[i] = c[i];
        }
        maxPlayers = n;
        playing = 0;
    }

    State(const State &s) {
        maxHeaps = s.maxHeaps;
        coins = new int[maxHeaps];
        for (int i = 0; i < maxHeaps; i++) {
            coins[i] = s.coins[i];
        }
        maxPlayers = s.maxPlayers;
        playing = s.playing; 
    }

    ~State() {
        delete[] coins;
    }

    int getHeaps() const { return maxHeaps; }
    int getCoins(int h) const throw(logic_error) {
        if (h < 0 || h >= maxHeaps) {
            throw logic_error("Invalid heap");
        }
        else {
            return coins[h];
        }
    }

    int getPlayers() const { return maxPlayers; }
    int getPlaying() const { return playing; }

    void next(const Move &move) throw(logic_error) {
        if ((move.getSource() < 0 || move.getSource() >= maxHeaps) || (move.getTarget() < 0 || move.getTarget() >= maxHeaps)) {
            throw logic_error("Heaps go from 0 to " + maxHeaps);
        }
        else if (move.getSourceCoins() < 1 || move.getTargetCoins() < 0) {
            throw logic_error("Invalid move");
        }
        else if (move.getSourceCoins() <= move.getTargetCoins() || move.getSourceCoins() > getCoins(move.getSource())) {
            throw logic_error("Not enough coins");
        }
        else {
            
            
            coins[move.getSource()] -= move.getSourceCoins();
            coins[move.getTarget()] += move.getTargetCoins();
            
            if (playing == maxPlayers - 1) playing = 0;
            else playing++;
            
        }
    }
    bool winning() const {
        int total;
        for (int i = 0; i < maxHeaps; i++) {
            total += coins[i];
        }
        if (total != 0) return false;
        else return true;
    }


    friend ostream & operator << (ostream &out, const State &state) {
        out << state.getCoins(0);
        for (int i = 1; i < state.getHeaps(); i++) {
                out << ", " << state.getCoins(i);
            }
        out << " with " << state.getPlaying() << "/" << state.getPlayers() << " playing next";
        return out;
        }

private:

    int maxHeaps, maxPlayers, playing;
    int *coins;
};
