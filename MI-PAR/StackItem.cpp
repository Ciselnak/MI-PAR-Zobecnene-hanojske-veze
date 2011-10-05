#include "StackItem.h"
StackItem::StackItem(const Board& b, const Move& m,int d ):board(b),move(m),dep(d)
{    
}

Board StackItem::getBoard() const{
    return board;
    
}
