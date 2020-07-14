#include <iostream>  
#include <string>  
#include <array>  
using namespace std;  


int main() {  


  int N;
  int M;
  int u, v; 
  int per=0;  
  int pathpart[4];  

  cin>>N;  
  cin>>M;  

  int nodevalue[N];  

  for (int i=0; i<N; i++) {  
    nodevalue[i]=0;  
  }  

  for(int i=0; i<M; i++) {  
    cin>>u;  
    cin>>v;  
    nodevalue[u]++;  
    nodevalue[v]++;  
  }  
  for (int j=0; j<N; j++) {  
    if (nodevalue[j]%2!=0) {  
      pathpart[per]=j;  
      per++;  
      if (per>2){  
        cout<<"IMPOSSIBLE";  
        cout<<endl;  
        exit(0);  
      }  
    }  
  }  

  if (per==0) {  
    cout<< "CYCLE";  
    cout<<endl;  
  }  

  else if (per==2) {  
    cout<< "PATH ";  

    if (pathpart[0]<pathpart[1]) {  
      cout<<pathpart[0];  
      cout<<" ";  
      cout<<pathpart[1];  
      cout<<endl;  
    }  

    else {  
      cout<<pathpart[1];  
      cout<<" ";  
      cout<<pathpart[0];  
      cout<<endl;  
    }  
  }  
  
  else {  
    cout<<"IMPOSSIBLE";  
    cout<<endl;  
  }  
}

