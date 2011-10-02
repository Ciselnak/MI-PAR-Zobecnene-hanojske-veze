/* 
 * File:   StackItem.h
 * Author: adam
 *
 * Created on 30. září 2011, 0:28
 */

#ifndef STACKITEM_H
#define	STACKITEM_H
#include<vector>
#include "Board.h"      
#include "Move.h"
using namespace std;
class StackItem{

private:
    vector<Move> history;
    Board board;
public:
    StackItem();
    StackItem(const Board&);
    StackItem(const Board&, vector<Move>);
    int depth();
};


#endif	/* STACKITEM_H */

