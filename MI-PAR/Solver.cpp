#include "Solver.h"

Solver::Solver(const Board& b, int i, int t):initState(b), maxDepth(i),targetTower(t){
  myStack = new stack<StackItem>;  
  solution = new vector<Move>;
  actualSolution = new vector<Move>;
}

Solver::~Solver(){
    delete myStack;
    delete solution; 
    delete actualSolution;
}

void Solver::expandItem(){
    
}
/*
void Solver::backtrackMoves(){
    myStack.
}*/

vector<Move> Solver::solve(){
    
    while(!myStack->empty()){
   // cout<<targetTower<<endl;
        
    }
    return *new vector<Move>;
}