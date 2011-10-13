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
 static int pushed=0;
void Solver::expandTop() {
    int dept = myStack->top().getDepth() + 1;
    Board act = myStack->top().getBoard();
   
    Move lastMov = myStack->top().getMove();
    for (int i = 0; i < act.size(); i++) {
        for (int j = 0; j < act.size(); j++) {
            if (i != j) {
                 Move *m = new Move(i, j, act.getTowerTop(i));

                if (m->isReverse(lastMov)) {
                    delete m;
                    continue;
                }
                if (act.isMoveCorrect(*m)) {
                    Board b = act;
                    b.performMove(*m);
                     if((dept+b.getDolniMez(targetTower))>bestSolutionsDepth){//tady si pohrat s tim prorezavanim                          
                         delete m;  
                        // cout<<"d"<<dept+b.getDolniMez(targetTower)<<"fik"<<bestSolutionsDepth<<endl;
                         //cout<<act<<act.getDolniMez(targetTower)<<dept<<endl;
                         continue;
                                        }
                    StackItem *s = new StackItem(b, *m, dept);
                  //  cout << "inserting item: "  << *m <<" dep: "<< dept << endl;
                    myStack->push(*s);
                   // cout<<b<<endl;
                    pushed+=1;
                    delete m;
                    delete s;
                }   else {
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
    int  dolniMez= initState.getDolniMez(targetTower);
    //cout<<"dolniM: "<<dolniMez;
    if (initState.isTowerComplete(targetTower)) {//zadani je rovnou reseni
        return *solution;
    }
    bestSolutionsDepth=maxDepth;
    Move *foo = new Move(0, 0, 0);
    StackItem *s = new StackItem(initState, *foo, 0);
    delete foo;
    myStack->push(*s);
    delete s;
    expandTop();
    int actualDepth = 1;
    //dalo by se prohledavat pouze do hloubky nejlepsiho prozatimniho reseni
    //deje se tak    
    
    while (!myStack->empty()) {
        if(solution->size()==dolniMez){
          //  cout<<"terminated...low bound"<<endl;
             break;
        }
        //  cout << "acualDept: " << actualDepth << endl;
        // cout << "StackItem dpth: " << myStack->top().getDepth() << endl;
        //cout << "StackSize: " << myStack->size() << endl;
        if (actualDepth > myStack->top().getDepth()) {
         //   cout << "removing BT: " << myStack->top().getMove() << myStack->top().getDepth() << endl;
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
                bestSolutionsDepth= solution->size();
            }
          //  cout << "removing SOL: " << myStack->top().getMove() << myStack->top().getDepth() << endl;

            actualSolution->pop_back();
            myStack->pop();
            continue;

        }
        //mozne pridelat implementaci hledani jen do hloubky stavajiciho best reseni 
        //asi hotovo....
        if (myStack->top().getDepth() == bestSolutionsDepth) {
            //   cout<<"Delete - MaxDepth"<<endl;
          //  cout << "removing MD: " << myStack->top().getMove() << myStack->top().getDepth() << endl;

            myStack->pop();
            continue;
        }
        actualSolution->push_back(myStack->top().getMove());
        actualDepth += 1;
        expandTop();
        // cout << myStack->top().getBoard().getItems() << endl;
    }
    cout<<"Pushed: "<<pushed<<endl;
    return *solution;
}