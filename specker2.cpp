#include <iostream>
using namespace std;

class Player {
  public:
    Player(const string &n){
      name=n;
    };
    virtual ~Player();

    virtual const string & getType() const=0;
    virtual Move play(const State &s) =0;

    friend ostream & operator << (ostream &out, const Player &player);

  protected:string name;
};


class GreedyPlayer :public Player {
  public:

  GreedyPlayer(const string &n): Player(n) {
    playertype="Greedy";
  }

   const string & getType() const override {
    return playertype;
  }
  Move play(const State &s) override {
    int sHeap=0;
    int sCoins=0;
    for(int i=0; i<s.getHeaps(); i++)
    if(s.getCoins(i)>sCoins) { 
      sHeap=i;
      sCoins=s.getCoins(i);
    }
    Move Greedyplay(sHeap, sCoins, 0, 0);
    return Greedyplay;
  }

  private:
  string playertype;
};

class SpartanPlayer: public Player {
  public:
  SpartanPlayer(const string &n): Player(n) {
    playertype="Spartan";
  }

  const string & getType() const override {
    return playertype;
  }

  Move play(const State &s) override {
    int sHeap=0;
    int sCoins=0;
    for(int i=0; i<s.getHeaps(); i++)
    if(s.getCoins(i)>sCoins) { 
      sHeap=i;
      sCoins=s.getCoins(i);
    }
    Move Spartanplay(sHeap, 1, 0, 0);
    return Spartanplay;
  }

  private:
  string playertype;
};

class SneakyPlayer:public Player {
  public:
  SneakyPlayer(const string &n): Player(n) {
    playertype="Sneaky";
  }

  const string & getType() const override {
    return playertype;
  }

  Move play(const State &s) override {
    int sHeap=0;
    int sCoins;
      if(s.getCoins(0)>0) sCoins=s.getCoins(0);
      else sCoins=100;
    for(int i=1; i<s.getHeaps(); i++) {
      if(s.getCoins(i)<sCoins && s.getCoins(i)>0) { 
        sHeap=i;
        sCoins=s.getCoins(i);
      }
    }
    Move Sneakyplay(sHeap, sCoins, 0, 0);
    return Sneakyplay;
  }

  private:
  string playertype;
};

class RighteousPlayer: public Player {
  public:
  RighteousPlayer(const string &n): Player(n){
    playertype="Righteous";
  }

  const string & getType() const override {
    return playertype;
  }

  Move play(const State &s) override {
    int sHeap=0;
    int tHeap=0;
    int maxCoins=0;
    int minCoins=s.getCoins(0);
    for(int i=0; i<s.getHeaps(); i++) {
      if(s.getCoins(i)>maxCoins) { 
        sHeap=i;
        maxCoins=s.getCoins(i);
      }
      if(s.getCoins(i)<minCoins ){
        tHeap=i;
        minCoins=s.getCoins(i);
      }
    }     
    Move Righteousplay(sHeap, (maxCoins+1)/2, tHeap, ((maxCoins+1)/2)-1);
    return Righteousplay; 
  }

  private:
  string playertype;
};

ostream & operator << (ostream &out, const Player &player) {
  out<<player.getType()<<" player "<<player.name;
  return out;
}

Player::~Player() {name.clear();}




