#include "Move.h"

/*
 mohl by konrolovat zapornost souradnic
 */

Move::Move(int from_, int to_){
    this->from=from_;
    this->to=to_;
    
}

const bool Move::isReverse(const Move &t){//vhodne pro kontrolu 1 cyklu
    return ((this->from==t.to)&&(this->to==t.from));    
}

ostream& operator<<(ostream & os,const Move &t){
    os<<t.from<<"->"<<t.to;
    return os;
}