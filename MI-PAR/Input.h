/* 
 * File:   Input.h
 * Author: Tomáš Čerevka
 *
 * Created on October 15, 2011, 5:16 PM
 */

#ifndef INPUT_H
#define	INPUT_H

#include <fstream>
#include "Board.h"

using namespace std;

/**
 * Zajistuje nacitani vstupnich dat ze souboru.
 */
class Input {
public:

    /**
     * Konstruktor.
     */
    Input();    

    /**
     * Destruktor.
     */
    virtual ~Input(void);
    
    /**
     * Vrati vytvorenou desku.
     * ! Nestara se o jeji destrukci, musi si zajistit ten, kdo si ji nechal
     * vytvorit!
     * @return Ukazatel na desku.
     */
    Board* getBoard(void);
    
    /**
     * Vrati cilovou vez.
     * @return Index cilove veze.
     */
    int getTargetTower(void);
    
    /**
     * Vrati maximalni prohledavanou hloubku.
     * @return Maximalni hloubka.
     */
    int getMaxDepth(void);
    
    /**
     * Nacte soubor.
     * Prvni radka: pocet_vezi cilova_vez maximalni_hloubka
     * Každá další řádka (odshora): token token token... 
     * @param 
     */
    void parseFile(const char*);
private:

    Board* board;
    
    int towerCount;
    
    int targetTower;
    
    int maxDepth;
};

#endif	/* INPUT_H */

