#include <iostream>
using namespace std;

class Game{
public:
  Game(int heaps, int players);
  ~Game();

  void addHeap(int coins) throw(logic_error);
  void addPlayer(Player *player) throw(logic_error);
  void play(ostream &out) throw(logic_error);

  int heapnum;
  int playernum;
  int *c;
  int currentheap;
  int currentplayer;
  Player **playerlist;
};

Game::Game(int heaps, int players) {
  currentheap=0;
  currentplayer=0;
  heapnum=heaps;
  playernum=players;
  c=new int[heaps];
  playerlist= new Player*[players];
}

Game::~Game() {
  delete[] c;
  delete[] playerlist;
}

void Game::addHeap(int coins) throw(logic_error) {
if(coins<0) throw logic_error("negative coins");
else if(currentheap>heapnum) throw logic_error("heap overflow");
else c[currentheap++]=coins;
}

void Game::addPlayer(Player *player) throw(logic_error) {
  if(currentplayer>playernum) throw logic_error("Player overflow");
  else playerlist[currentplayer++]=player;
}

void Game::play(ostream &out) throw(logic_error) {
  if(currentplayer!=playernum || currentheap!=heapnum) throw logic_error("Not filled player or heap positions");
  else {
    int y=0;
    State state(heapnum, c);
    while(!state.winning()) {
      out<<"State: "<<state<<endl;
      out<<*playerlist[y%playernum]<<" "<<playerlist[y%playernum]->play(state)<<endl;
      state.next(playerlist[y%playernum]->play(state));
      y++;
    }
    out<<"State: "<<state<<endl;
    out<<*playerlist[(y-1)%playernum]<<" wins"<<endl;
  }
}


