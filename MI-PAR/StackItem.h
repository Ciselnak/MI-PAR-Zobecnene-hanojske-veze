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

/*
 * Třída reprezentující objekt, který ukládáme na zásobník.
 */
class StackItem {
private:
    Move move;
    Board board;
    int dep;
public:

    /**
     * Konstruktor.
     * @param Board aktuální stav hrací desky
     * @param Move tah, který desku do tohoto stavu přivedl (=poslední tah)
     * @param int hloubka v prohledávaném prostoru
     */
    StackItem(const Board&, const Move&, int);
    
    
    /**
     * Kopirujici konstruktor.
     * @param Puvodni instance.
     */
    StackItem(const StackItem&);

    /**
     * Funkce vracející hloubku prvku v prohledávaném prostoru
     * @return int hloubka prvku
     */
    inline int getDepth() const {
        return dep;
    };

    /**
     * Funkce vracející tah uložený v objektu.
     * @return Move poslední tah
     */
    inline Move getMove() const {
        return move;
    };

    /**
     * funkce vracející herní desku v ojektu.
     * @return Board herní deska
     */
    Board getBoard()const;
};


#endif	/* STACKITEM_H */

