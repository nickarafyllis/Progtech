#include <iostream>
#include <list>
#include <vector>
#include <algorithm> 
using namespace std;

class Graph{
  private:
  int numofvertices; 
  list<int> *ptr;
  vector<int> color;
  vector<int> root;
  int startofcircle, endofcircle;

  bool DFS(int v) {
    color[v]=1;
    for(int u: ptr[v]){
      if(color[u]==0) {
        root[u]=v;
        if(DFS(u))
        return true;
      }
      else if(color[u]==1) {
        endofcircle=v;
        startofcircle=u;
        return true;
      }
    } 
    color[v]=2;
    return false;
  }

  
  public:

  Graph(int V): numofvertices(V) { ptr=new list<int>[numofvertices]; }

  ~Graph() { delete [] ptr;}

  void addEdge (int u, int v) {
    ptr[u].push_back(v);
  }

  bool cycle(vector<int> &cycle) {
    color.assign(numofvertices, 0);
    root.assign(numofvertices, -1);
    startofcircle=-1;

    for(int v=0; v<numofvertices; v++) {
      if(color[v]==0 && DFS(v))
      break;
    }

    if(startofcircle==-1)
    return false;
    else {
      cycle.push_back(startofcircle);
      for( int v=endofcircle; v!=startofcircle; v=root[v])
      cycle.push_back(v);

      reverse(cycle.begin(), cycle.end());
      return true;
    }
  }
};

