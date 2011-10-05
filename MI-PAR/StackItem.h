/* 
 * File:   StackItem.h
 * Author: adam
 *
 * Created on 30. září 2011, 0:28
 */

#ifndef STACKITEM_H
#define	STACKITEM_H
#include "Board.h"      
#include "Move.h"
using namespace std;
class StackItem{

public:
    Move move;
    Board board;
    int dep;
//public:
    StackItem(const Board&, const Move&, int);    
    inline int getDepth() const {return dep;};
    inline Move getMove() const {return move;};
    Board getBoard()const ;
};


#endif	/* STACKITEM_H */

