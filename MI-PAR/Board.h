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

/**
 * třída reprezentující hrací desku
 */

class Board {
private:
    vector <vector <int>* >* towers;
    int items;
public:

    /**
     * Konstruktor vytvoří prázdnou hrací desku
     * @param int udává počet věží
     */
    Board(int);

    /**
     * Kopírující konstruktor
     * @param Board kopírovaná hrací deska
     */
    Board(const Board&);

    /**
     * Destruktor
     */
    virtual ~Board();

    /**
     * Funkce rozhodne zda je na dané hrací desce možné provést daný tah
     * za dodržený všech pravidel.
     * @param Move tah, jehož uskutečnitelnost posuzujeme.
     * @return bool 1 pokud je tah možný 0 pokud není možný
     */
    bool isMoveCorrect(Move &) const;

    /**
     * Provede na hrací desce zadaný tah.
     * @param Move prováděný tah
     */
    void performMove(Move &);

    /**
     * Umístí do hrací plochy nový token.
     * !!! Funkce NEkontroluje dodržování pravidel při vkládání tokenu. Je třeba ošetřit vňe fce.
     * @param int udává pořadí věže, na kterou je token umístěn
     * @param int udává hodnotu tokenu
     */
    void pushItem(int, int);

    /**
     * Funkce určuje zda je věž kompletní (hledaný stav)
     * @param int udává pořadí věže, která je kontrolována
     * @return bool 1 pokud je věž kompletní, 0 pokud není kompletní
     */
    bool isTowerComplete(int) const;

    /**
     * Funkce vracející dolní mez řešení (minimální možný počet tahů, který je schopen
     * transformovat plochu do hledaného řešení).
     * @param int udává pořadí věže, kterou se snažíme kompletovat
     * @return int počet tahů nutných k transformaci 
     */
    int getDolniMez(int)const;

    /**
     * Funkce vracející token na vrcholu věže
     * @param int udává pořadí věže jejíž vrcholek požedujeme
     * @return int velikost vrchního tokenu
     */
    int getTowerTop(int) const;

    /**
     * Funkce vracející počet věží na hrací desce.
     * @return int počet věží
     */
    int size(void) const;

    /**
     * Funkce vracející počet tokenů na hrací desce.
     * @return int počet tokenů
     */
    inline int getItems(void) {
        return items;
    };

    /**
     * Operátor porovnání dvou desek
     * NEimplementován!!
     * @param Board deska se kterou tuto desku porovnávám
     * @return 1 pokud se desky shodují, 0 pokud se neshodují
     */
    bool operator==(const Board&);

    /**
     * Operátor << pro výpis desky do výstupního proudu
     * @param ostream výstupní proud
     * @param Board vypisovaná deska
     */
    friend ostream& operator<<(ostream&, const Board &);


};


#endif	/* BOARD_H */

