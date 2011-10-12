#include "Move.h"

/*
 mohl by konrolovat zapornost souradnic
 */

Move::Move(int f, int t, int v){
    this->from=f;
    this->to=t;
    this->value=v;
    
}

bool Move::isReverse(const Move &t) const{//vhodne pro kontrolu 1 cyklu
    return ((this->from==t.to)&&(this->to==t.from));    
}

ostream& operator<<(ostream & os,const Move &t){
    os<<t.value<<", "<<t.from<<"->"<<t.to;
    return os;
}