/* 
 * File:   Board.h
 * Author: adam
 *
 * Created on 26. září 2011, 21:41
 */

#ifndef BOARD_H
#define	BOARD_H
#include <vector>
#include "Move.h"
using namespace std;
class Board{
private: 
   vector <vector <int>* >* towers; 
    
public:
    Board(int);
    Board(const Board&);
    virtual ~Board();
    const bool isMoveCorrect(Move &);
    void performMove(Move &);
    void pushItem(int,int);
    const int size(void);
    bool operator==(const Board& );
    friend ostream& operator<<(ostream&, Board &);
   
    
};


#endif	/* BOARD_H */

