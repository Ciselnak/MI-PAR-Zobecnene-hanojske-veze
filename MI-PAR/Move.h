/* 
 * File:   Move.h
 * Author: adam
 *
 * Created on 26. září 2011, 21:06
 */

#ifndef Move_H
#define	Move_H

#include<iostream>
using namespace std;

/*
 * Třída představující tah ve hře.
 */
class Move {
private:
    int from;
    int to;
    int value;
public:

    /**
     * Konstruktor vytvoří nový tah.
     * @param int index věže, ze které je odebrán vrchní token
     * @param int index věže, na kterou je token umístěn
     * @param int velikost přesunovaného tokenu
     */
    Move(int, int, int);

    /**
     * Funkce vracející index věže, ze které byl odebrán token.
     * @return int index veže
     */
    inline int getFrom() const {
        return from;
    }

    /**
     * Funkce vracející index veže, na kterou byl token umístěn.
     * @return int index věže
     */
    inline int getTo() const {
        return to;
    }

    /**
     * Funkce rozhodne zda se jedná o reverzní tahy. Po provedení reverzních 
     * tahů by na desce nedošlo ke žádné změně.
     * @param Move druhý porovnávaný tah
     * @return bool 1 pokud jsou tahy reverzní, 0 pokud nejsou reverzní
     */
    bool isReverse(const Move &) const;

    /**
     * Operátor << pro výpis tahu do výstupního proudu
     * @param ostream výstupní proud
     * @param Move vypisovaný tah
     */
    friend ostream& operator<<(ostream&, const Move &);
};

#endif	/* Move_H */

