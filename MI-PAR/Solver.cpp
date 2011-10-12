#include "Solver.h"

Solver::Solver(const Board& b, int i, int t) : initState(b), targetTower(i), maxDepth(t) {
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
    int dept = myStack->top().getDepth() + 1;
    Board act = myStack->top().getBoard();
    Move lastMov = myStack->top().getMove();
    for (int i = 0; i < act.size(); i++) {
        for (int j = 0; j < act.size(); j++) {
            if (i != j) {
                Move *m = new Move(i, j, act.getTowerTop(i));
                
                if(m->isReverse(lastMov)){
                    delete m;
                    continue;
                }
                if (act.isMoveCorrect(*m)) {
                    Board b = act;
                    b.performMove(*m);
                    StackItem *s = new StackItem(b, *m, dept);
                    myStack->push(*s);
                    delete m;
                    delete s;
                }
                else{
                    delete m;
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
    if (initState.isTowerComplete(targetTower)) {//zadani je rovnou reseni
        return *solution;
    }
    Move *foo = new Move(0, 0,0);
    StackItem *s = new StackItem(initState, *foo, 0);
    delete foo;
    myStack->push(*s);
    delete s;
    expandTop();
    int actualDepth = 1;
    //dalo by se prohledavat pouze do hloubky nejlepsiho prozatimniho reseni
    //deje se tak    
    while (!myStack->empty()) {
      //  cout << "acualDept: " << actualDepth << endl;
       // cout << "StackItem dpth: " << myStack->top().getDepth() << endl;
        //cout << "StackSize: " << myStack->size() << endl;
        if (actualDepth > myStack->top().getDepth()) {
          //  cout<<"remove opened"<<endl;
            myStack->pop();
            actualSolution->pop_back();
            actualDepth -= 1;
            continue;
        }
        if (myStack->top().getBoard().isTowerComplete(targetTower)) {
          //  cout<<"SOLUTION FOUND!"<<endl;
            actualSolution->push_back(myStack->top().getMove());
            if ((solution->size() == 0) || (solution->size() > actualSolution->size())) {
                delete solution;
                solution = actualSolution;
                actualSolution = new vector<Move>;
                for (int i = 0; i < solution->size(); i++) {
                    actualSolution->push_back((*solution)[i]);
                }
                actualSolution->pop_back();
                myStack->pop();
                continue;
            }
            actualSolution->pop_back();
            myStack->pop();
            continue;
            
        }
        //mozne pridelat implementaci hledani jen do hloubky stavajiciho best reseni 
        //asi hotovo....
        if ((myStack->top().getDepth() == maxDepth)||((!(solution->size()==0))&&(myStack->top().getDepth()>solution->size()))) {
         //   cout<<"Delete - MaxDepth"<<endl;
            myStack->pop();
            continue;
        }
        actualSolution->push_back(myStack->top().getMove());
        actualDepth += 1;
        expandTop();
        // cout << myStack->top().getBoard().getItems() << endl;
    }

    return *solution;
}