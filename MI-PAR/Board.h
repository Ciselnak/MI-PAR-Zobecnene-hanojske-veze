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
   int items; 
public:
    Board(int);
    Board(const Board&);
    virtual ~Board();
    bool isMoveCorrect(Move &) const;
    void performMove(Move &);
    void pushItem(int,int);
    int size(void) const;
    inline int getItems(void){return items;};
    bool operator==(const Board& );
    friend ostream& operator<<(ostream&,const Board &);
   
    
};


#endif	/* BOARD_H */

