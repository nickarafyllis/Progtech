#include <iostream>  
using namespace std;  
  
class Move {  
  public:  
  Move(int sh, int sc, int th, int tc) ;   
  
  int getSource() const;  
  int getSourceCoins() const;  
  int getTarget() const;  
  int getTargetCoins() const;  
  
  friend ostream & operator << (ostream &out, const Move &move);  
  
  int a;  
  int b;  
  int c;  
  int d;  
  
};  
  
Move::Move(int sh, int sc, int th, int tc) {  
    a=sh;  
    b=sc;  
    c=th;  
    d=tc;  
  }  
  
int Move::getSource() const {return a;}  
  
int Move::getSourceCoins() const {return b;}  
  
int Move::getTarget() const {return c;}  
  
int Move::getTargetCoins() const {return d;}  
  
ostream & operator << (ostream &out, const Move &move) {  
  out<<"takes "<<move.b<<" coins from heap "<<move.a<<" and puts ";  
  if(move.d>0) out<<move.d<<" coins to heap "<<move.c;  
  else out<<"nothing";  
  return out;  
}  
  
class State {  
  public:  
  //state with h heaps, where the i-th heaps starts with c[i] coins.  
  State(int h, const int c[]);  
  ~State();  
  
  void next(const Move &move) throw(logic_error);  
  bool winning() const;  
  
  int getHeaps() const;  
  int getCoins(int h) const throw(logic_error);  
  
  friend ostream & operator << (ostream &out, const State &state);  
      
  private:  
  int *heap; 
  int heapsum; 
};  
  
State::State(int h, const int c[]) {  
  heap=new int[h];  
  heapsum=h;  
  for(int i=0; i<heapsum; i++)  heap[i]=c[i];  
}  
  
State::~State() {delete[] heap; }  
  
void State::next(const Move &move) throw(logic_error) {  
  
  if(move.a<0 || move.a>=heapsum || move.c<0 || move.c>=heapsum)throw logic_error("invalid heap");  
  
  else if(move.b<=0 || move.d<0 || heap[move.a]<move.b || move.d>=move.b)   
  throw logic_error("invalid coin quantity");  
  
  else {  
  heap[move.a]-=move.b;  
  heap[move.c]+=move.d;  
  }  
}  
  
bool State::winning() const {  
  bool win=true;  
  for(int i=0; i<heapsum; i++)  
  if(heap[i]!=0) win=false;
return win;  
}  
  
int State::getHeaps() const {  
  return heapsum;  
}  
  
int State::getCoins(int h) const throw(logic_error) {  
  if(h<0 || h>=heapsum) throw logic_error("invalid heap");  
  else return heap[h];  
}  
  
ostream & operator << (ostream &out, const State &state) {  
 out << state.heap[0];
      for (int i = 1; i < state.heapsum; i++)
        out << ", " << state.heap[i];
      return out;
    }
  
 
