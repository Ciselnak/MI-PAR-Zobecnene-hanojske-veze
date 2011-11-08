/* 
 * File:   Solver.h
 * Author: adam
 *
 * Created on 5. říjen 2011, 23:02
 */

#ifndef SOLVER_H
#define	SOLVER_H

#include "StackItem.h"
#include <stack>

using namespace std;

/**
 * Třída řešící algoritmus. 
 */
class Solver {
private:
    vector<StackItem>* myStack;
    Board initState;
    vector<Move>* solution;
    vector<Move>* actualSolution;
    int maxDepth;
    int bestSolutionsDepth;
    int targetTower;

    /**
     * Funkce provede expanzi vrchního prvku na zásobníku.
     */
    void expandTop();
    
    // void backtrackMoves(void);//nevim jestli budu chtit....zatim asi ne
public:

    /**
     * Konstruktor
     * @param Board výchozí stav hrací plochy
     * @param int index věže na které chci získat řešení
     * @param int maximální délka hledaného řešení (=hloubka prohledávání)
     */
    Solver(const Board&, int, int);

    /**
     * Destruktor
     */
    ~Solver();

    /**
     * Funkce vyřeší zadanou hru
     * @return vector<Move> posloupnost tahů vedoucích k řešení,
     * prázdný vector pokud řešení neexistuje
     */
    vector<Move> solve();

    
    /**
     * inicialzace MPI a procesu
     */
    void init();
    
    /**
     * ypracuje vrchol zasobniku
     * vraci 0 pokud se v dalsim kroku nema expandovat 1 pokud se ma expandovat
     */
    int processTop();
};


#endif	/* SOLVER_H */

