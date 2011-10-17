/* 
 * File:   Input.h
 * Author: Tomáš Čerevka
 *
 * Created on October 15, 2011, 5:16 PM
 */

#ifndef INPUT_H
#define	INPUT_H

#include <fstream>
#include <string>
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
     * Vrati pocet vezi.
     * @return Pocet vezi.
     */
    int getTowersCount(void);

    /**
     * Vrati pocet tokenu.
     * @return Pocet tokenu.
     */
    int getTokensCount(void);

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
     * Vrati nazev vstupniho souboru.
     * @return Nazev vstupniho souboru.
     */
    string getFileName(void);

    /**
     * Zpracuje vstupni parametry.
     * @param Pocet parametru.
     * @param Pole argumentu.
     */
    void parseArguments(int, char**);

    /**
     * Nacte soubor nastaveny v objektu Input.
     * Prvni radka: pocet_vezi cilova_vez maximalni_hloubka
     * Každá další řádka (odshora): token token token... 
     */
    void parseFile(void);

    /**
     * Vygeneruje desku dle aktualniho stavu objektu Input.     
     */
    void generateBoard(void);
    
    void printHelp(void);

private:

    /** Generovana deska. */
    Board* board;

    /** Pocet vezi. */
    int towersCount;

    /** Pocet tokenu. */
    int tokensCount;

    /** Index cilove veze. */
    int targetTower;

    /** Maximalni hloubka. */
    int maxDepth;

    /** Nazev vstupniho souboru. */
    string fileName;    
};

#endif	/* INPUT_H */

