#include <iostream>
#include <stdexcept>

using namespace std;

class Game {
public:
    Game(int h, int p) {
        maxHeaps = h; maxPlayers = p;
        heapCounter = 0;
        playerCounter = 0;
        heaps = new int[maxHeaps];
        players = new Player*[maxPlayers];
    }
    ~Game() {
        delete[] heaps;
        delete[] players;
    }

    void addHeap(int c) throw(logic_error) {
        if (c < 0) {
            throw logic_error("Coins can't be less than zero");
        }
        else if (heapCounter == maxHeaps) {
            throw logic_error("Cannot add more heaps");
        }
        else {
            heaps[heapCounter] = c;
            heapCounter++;
        }

    }
    void addPlayer(Player *p) throw(logic_error) {
        if (playerCounter == maxPlayers) {
            throw logic_error("Cannot add more players");
        }
        else {
            players[playerCounter] = p;
            playerCounter++;
        }
    }
    void play(ostream &out) throw(logic_error) {
        if (playerCounter != maxPlayers || heapCounter != maxHeaps) {
            throw logic_error("Not enough players/heaps");
        }
        else {
            State s(maxHeaps, heaps, maxPlayers);
            while (!s.winning()) {
                out << "State: " << s << endl;
                out << *getPlayer(s.getPlaying()) << " " << players[s.getPlaying()]->play(s) << endl;
                s.next(players[s.getPlaying()]->play(s));

            }
            out << "State: " << s << endl;
            int winner;
            if (s.getPlaying() == 0) winner = maxPlayers - 1;
            else winner = s.getPlaying() - 1;
            out << *players[winner] << " wins" << endl;
        }
    }
    

    int getPlayers() const { return maxPlayers; }
    
    const Player *getPlayer(int p) const throw(logic_error) {
        if (p < 0 || p > maxPlayers) {
            throw logic_error("No such player");
        }
        else {
            return players[p];
        }
    }

private:
    int maxHeaps, maxPlayers, heapCounter, playerCounter;
    int *heaps;
    Player **players;
};


