#include "StackItem.h"
StackItem::StackItem():board(*new Board(1)), history(*new vector<Move>){
   
}

StackItem::StackItem(const Board& b):board(b),history(*new vector<Move>){   
  
    
}

StackItem::StackItem(const Board& b, vector<Move> hist):board(b),history(hist){
   
}

int StackItem::depth(){
    this->history.size();   
}