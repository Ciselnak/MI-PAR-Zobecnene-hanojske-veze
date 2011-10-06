#include "Solver.h"

Solver::Solver(const Board& b, int t, int i) : initState(b), maxDepth(i), targetTower(t) {
    myStack = new stack<StackItem>;
    solution = new vector<Move>;
    actualSolution = new vector<Move>;
}

Solver::~Solver() {
    delete myStack;
    delete solution;
    delete actualSolution;
}

void Solver::expandTop() {
    Board act = myStack->top().getBoard();
    for (int i = 0; i < act.size(); i++) {
        for (int j = 0; j < act.size(); j++) {
            if (i != j) {
                Move *m = new Move(i, j);
                if (act.isMoveCorrect(*m)) {
                    Board b = act;
                    b.performMove(*m);
                    StackItem *s = new StackItem(b, *m, myStack->top().getDepth() + 1);
                    myStack->push(*s);
                    delete m;
                    delete s;
                }
            }
        }
    }


}

/*
void Solver::backtrackMoves(){
    myStack.
}*/

vector<Move> Solver::solve() {
    Move *foo = new Move(0, 0);
    StackItem *s = new StackItem(initState, *foo, 0);
    delete foo;

    myStack->push(*s);
    delete s;

    while(!myStack->empty()){
     //   if(myStack->top().getBoard().)
    expandTop();
   // cout << myStack->top().getBoard().getItems() << endl;
      }
    return *new vector<Move>;
}