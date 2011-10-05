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
class Solver{
private:
    stack<StackItem>* myStack;
    Board initState;
    vector<Move>* solution;
    vector<Move>* actualSolution;
    int maxDepth;
    int bestSolutionsDepth;
    int targetTower;
    
    void expandItem(void);
   // void backtrackMoves(void);//nevim jestli budu chtit....zatim asi ne
public:
    Solver(const Board&, int, int);
   ~Solver();
    vector<Move> solve();
    
};


#endif	/* SOLVER_H */

