#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class ChessBoardArray {
  protected:
  class Row {
    public:
    Row(ChessBoardArray &a, int i):chessBoardArray(a), row(i) {}
    int & operator [] (int i) const{
      return chessBoardArray.select(row, i);
    }
    
    private:
    ChessBoardArray &chessBoardArray;
    int row;
  };
  class ConstRow {
    public:
    ConstRow(const ChessBoardArray &a, int i) : chessBoardArray(a), row(i) {};
    int operator [] (int i) const {
      return chessBoardArray.select(row, i);
    }

    private:
    const ChessBoardArray &chessBoardArray;
    int row;
  };

  public:
    ChessBoardArray(unsigned size=0, unsigned base=0) : data(new int[(size*size+1)/2]), thebase(base), thesize(size) {}
    
    ChessBoardArray(const ChessBoardArray &a) : data(new int[(a.thesize*a.thesize+1)/2]), thebase(a.thebase), thesize(a.thesize) {
      for(unsigned i=0; i<((thesize*thesize+1)/2); ++i) data[i]=a.data[i];
      }

    ~ChessBoardArray() {delete [] data;}

    ChessBoardArray & operator = (const ChessBoardArray &a) {
      delete [] data;
      thebase=a.thebase;
      thesize=a.thesize;
      data=new int[(thesize*thesize+1)/2];
      for(unsigned i=0; i<((thesize*thesize+1)/2); ++i) data[i]=a.data[i];
      return *this;
      }

    int & select(int i, int j) {
      return data[loc(i,j)];
    }
    int select(int i, int j) const {
      return data[loc(i,j)];
    }

    const Row operator [] (int i) {
      return Row(*this,  i);
    }
    const ConstRow operator [] (int i) const {
      return ConstRow(*this, i);
    }

    friend ostream & operator << (ostream &out, const ChessBoardArray &a) {
    	for(int line=0; line<a.thesize; ++line) {
    		for(int sthlh=0; sthlh<a.thesize; ++sthlh) {
    			cout<<setw(4);
    			if((line+sthlh)%2==0) 
    				cout<<a.select(line+a.thebase,sthlh+a.thebase);
    			else cout<<0;
    		}
    		cout<<endl;
    	}
    	return out;
    }
      
    
    protected:
    int *data;
    int thebase;
    unsigned thesize;

    unsigned int loc(int i, int j) const throw(out_of_range) {
      int di=i-thebase, dj=j-thebase;
      if(di<0 || di>=thesize || dj<0 || dj>=thesize || (i+j)%2==1) throw out_of_range("invalid index");
      return (di*thesize +dj)/2;
    }

};

 

