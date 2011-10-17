#include "StackItem.h"
StackItem::StackItem(const Board& b, const Move& m,int d ):board(b),move(m),dep(d)
{    
}

StackItem::StackItem(const StackItem& param):board(param.board),move(param.move),dep(param.dep) {
   
}

Board StackItem::getBoard() const{
    return board;
    
}


