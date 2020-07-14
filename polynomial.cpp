#include <iostream>
using namespace std;

class Polynomial {
  public:
  class Term {
    public:
    int exponent;
    int coefficient;
    Term *next;
    protected:
    Term(int exp, int coeff, Term *n) : exponent(exp), coefficient(coeff), next(n){}; 
    friend class Polynomial;
  };

  Term *head;
  int degree;
  int size;

  Polynomial():head(nullptr), degree(0), size(0) {}
  Polynomial(const Polynomial &p): head(nullptr), degree(0), size(0) {copy(p);};
  ~Polynomial() {purge();}

  Polynomial & operator =(const Polynomial &p) {clear(); copy(p); return *this;}
  
  void purge() { 
    Term *l=head;
    degree=0;
    size=0;
    while(l!=nullptr) {
      Term *q=l;
      l=l->next;
      delete q;
    }
  }

    void clear() {
    purge();
    head=nullptr;
    degree=0;
    size=0;
  }

  void remove(int exp) /* AFAIREI STOIXEIO*/ {  
    Term* temp=head;  
    Term* prev;  
    if(head==nullptr) return; 
    else {  
      if(head->exponent==exp) {  
        head=head->next;  
        delete temp;  
      }
      else {  
        for(temp = head;temp->next!=nullptr && temp->exponent !=exp;temp = temp->next) {  
          prev=temp;  
        }  
        if(temp->exponent==exp) {  
          prev->next = temp->next;  
          delete temp;  
        }
        else  return;  
      }  
      --size;  
    }  
  }



  void addTerm(int expon, int coeff) {  
    if(coeff==0 || expon<0) return;  
    Term *newTerm = new Term(expon,coeff,nullptr);  
    Term *temp = head;  
    if(expon>degree) degree=expon;  
    if(head==nullptr) {  
      newTerm->next=nullptr;  
      head=newTerm;  
      ++size;  
      return;  
    }  
    if(expon>head->exponent) {  
      newTerm->next=head;  
      head=newTerm;  
      ++size;  
      return;  
    }  
    if(expon==head->exponent) /* HERE */ {  
      head->coefficient=head->coefficient+newTerm->coefficient;  
      if(head->coefficient==0) remove(head->exponent);  
      return;  
    }  
    while(temp->next!=nullptr) {  
      if(expon==temp->exponent) /*here*/ {  
        temp->coefficient=temp->coefficient+newTerm->coefficient;  
        if(temp->coefficient==0)  
        remove(temp->exponent); 
        return;  
      }  
      if(expon>temp->next->exponent) {  
        newTerm->next = temp->next;  
        temp->next = newTerm;  
        return;  
      }  
     temp = temp->next;  
    }  
    if(newTerm->exponent==temp->exponent) /*HERE*/ {  
      temp->coefficient=temp->coefficient + newTerm->coefficient;  
      if(temp->coefficient==0) remove(temp->exponent);  
      return;  
    }  
    else {  
      newTerm->next=nullptr;  
      temp->next=newTerm;  
      //temp->coefficient=temp->coefficient+newTerm->coefficient;  
      ++size;  
    }  
    return;  
  }  

  double evaluate(double x) {
    double sum=0;
    int exp;
    for(Term *l=head; l!=nullptr; l=l->next) {
      exp=l->exponent;
      double expvalue=1;
      if (exp==0) expvalue=1;
      else {
        for(int i=0; i<exp; ++i) {
        expvalue*=x;
        }
      }
      sum+=(l->coefficient)*expvalue;
    }
    return sum;
  }

  friend Polynomial operator+ (const Polynomial &p, const Polynomial &q) {  
    Polynomial r;  
    Polynomial::Term *temp_p = p.head;  
    Polynomial::Term *temp_q = q.head;  
    while(!(temp_p==nullptr && temp_q ==nullptr)) {  
      if(temp_p==nullptr && temp_q!=nullptr) {  
        r.addTerm(temp_q->exponent,temp_q->coefficient);  
        temp_q=temp_q->next;  
        continue;  
      }  
      if(temp_q==nullptr && temp_p!=nullptr) {  
        r.addTerm(temp_p->exponent,temp_p->coefficient);  
        temp_p=temp_p->next;  
        continue;  
      }  
      if(temp_p->exponent == temp_q->exponent) {  
        r.addTerm(temp_p->exponent,temp_p->coefficient + temp_q ->coefficient);  
        temp_p=temp_p->next;  
        temp_q=temp_q->next;  
      }  
      else if(temp_p->exponent > temp_q ->exponent ) {  
        r.addTerm(temp_p->exponent, temp_p->coefficient);  
        temp_p=temp_p->next;  
      }
      else if(temp_p->exponent < temp_q->exponent) {  
        r.addTerm(temp_q->exponent,temp_q->coefficient);  
        temp_q = temp_q->next;  
      }  
    }  
    return r;  
}
  friend Polynomial operator* (const Polynomial &p, const Polynomial &q) {  
    Polynomial r[p.size+q.size+30];  
    Polynomial product;  
    int counter=0;  
    for(Polynomial :: Term *i = p.head; i!=nullptr; i = i->next) {  
      for(Polynomial :: Term * j= q.head; j!=nullptr; j = j->next) {  
          r[counter].addTerm(i->exponent+j->exponent, (i->coefficient)*(j->coefficient));  
      }  
      //cout<<r[counter];  
      ++counter;  
    }  
    product = r[0];  
    for(int i=1;i<counter;i++) {  
      product = product + r[i];  
    }  
    return product;  
}

  friend ostream & operator << (ostream &out, const Polynomial &p) {
    if(p.head==nullptr) {  
      out<<"0";  
      return out;  
    }  
    for(Polynomial::Term *i = p.head;i!=nullptr;i=i->next) {  
      if(i==p.head) {  
        if(i->exponent==0) {  
          if(i->coefficient < 0) out<<"- "<<-(i->coefficient);  
          else if(i->coefficient > 0) out<<i->coefficient;  
        }
        else if(i->exponent==1) {  
          if(i->coefficient < 0) {  
            if(i->coefficient==-1) out<<"- "<<"x";  
            else  out<<"- "<<-(i->coefficient)<<"x";  
          }  
          else if(i->coefficient > 0) {  
            if(i->coefficient==1) out<<"x";  
            else out<<i->coefficient<<"x";  
          }  
        }
        else if(i->exponent > 1) {  
          if(i->coefficient < 0) {  
            if(i->coefficient==-1) out<<"- "<<"x^"<<i->exponent;  
            else out<<"- "<<-(i->coefficient)<<"x^"<<i->exponent;  
          }
          else if(i->coefficient > 0) {  
            if(i->coefficient==1) out<<"x^"<<i->exponent;  
            else out<<i->coefficient<<"x^"<<i->exponent;  
          }  
        }  
      }  
      else {  
        if(i->exponent==0) {  
          if(i->coefficient < 0) out<<" - "<<-(i->coefficient);  
          else if(i->coefficient > 0) out<<" + "<<i->coefficient;   
        }
        else if(i->exponent==1) {  
          if(i->coefficient < 0) {  
            if(i->coefficient==-1) out<<" - "<<"x";  
            else out<<" - "<<-(i->coefficient)<<"x";  
          }  
          else if(i->coefficient > 0) {  
            if(i->coefficient==1) out<<" + "<<"x";  
            else out<<" + "<<i->coefficient<<"x";  
          }  
        }
        else if(i->exponent > 1) {  
          if(i->coefficient < 0) {  
           if(i->coefficient==-1) out<<" - "<<"x^"<<i->exponent;  
           else out<<" - "<<-(i->coefficient)<<"x^"<<i->exponent;  
          }  
          else if(i->coefficient > 0) {  
            if(i->coefficient==1) out<<" + "<<"x^"<<i->exponent;  
            else out<<" + "<<i->coefficient<<"x^"<<i->exponent;  
          }  
        }  
      }  
    }  
    //out<<"\n";  
    return out;  
  }

  private: 
   void copy(const Polynomial &p) {
    for(Term *l=p.head; l!=nullptr; l=l->next) addTerm(l->exponent, l->coefficient);
   }
};


