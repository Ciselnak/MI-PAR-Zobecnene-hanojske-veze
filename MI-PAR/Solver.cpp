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
static int pushed = 0; //ukládá kolik prvků bylo v průběhu výpočtu uloženo na zásobník

void Solver::expandTop() {
    int dept = myStack->top().getDepth() + 1;
    Board act = myStack->top().getBoard();

    Move lastMov = myStack->top().getMove();
    for (int i = 0; i < act.size(); i++) { // vytvořím všechny představitelné tahy
        for (int j = 0; j < act.size(); j++) {
            if (i != j) {
                Move *m = new Move(i, j, act.getTowerTop(i));


                if (act.isMoveCorrect(*m)) {// ověřím zda je tah na dané desce možný
                    if (m->isReverse(lastMov)) {// ověřím jestli tahem nevznikce cyklus délky 1
                        delete m;
                        continue;
                    }
                    Board b = act;
                    b.performMove(*m);
                    if ((dept + b.getDolniMez(targetTower)) > bestSolutionsDepth) {//ověřím jestli krok může z definice dolní meze vést k řešení                         
                        delete m;
                        // cout<<b<<"D"<<b.getDolniMez(targetTower)<<"fik"<<bestSolutionsDepth<<endl;
                        //cout<<act<<act.getDolniMez(targetTower)<<dept<<endl;
                        continue;
                    }
                    StackItem *s = new StackItem(b, *m, dept);
                    //  cout << "inserting item: "  << *m <<" dep: "<< dept << endl;
                    myStack->push(*s);
                    // cout<<b<<endl;
                    pushed += 1;
                    delete m;
                    delete s;
                } else {
                    delete m;
                }
            }
        }
    }
}

vector<Move> Solver::solve() {
    int dolniMez = initState.getDolniMez(targetTower);
    //cout<<"dolniM: "<<dolniMez;
    if (initState.isTowerComplete(targetTower)) {//zadani je rovnou reseni
        return *solution;
    }
    bestSolutionsDepth = maxDepth;
    Move *foo = new Move(0, 0, 0);
    StackItem *s = new StackItem(initState, *foo, 0);
    delete foo;
    myStack->push(*s);
    delete s;
    expandTop();
    int actualDepth = 1;

    while (!myStack->empty()) {
        if (solution->size() == dolniMez) {// pokud jsme nasli reseni rovne dolni mezi. už nemůžeme najít lepší
            //  cout<<"terminated...low bound"<<endl;
            break;
        }
        // cout << "acualDept: " << actualDepth << endl;
        // cout << "StackItem dpth: " << myStack->top().getDepth() << endl;
        // cout << "StackSize: " << myStack->size() << endl;
        if (actualDepth > myStack->top().getDepth()) {//odstrani jiz expandovany stav ze zasobniku pri navratu do nej
            // cout << "removing BT: " << myStack->top().getMove() << myStack->top().getDepth() << endl;
            myStack->pop();
            actualSolution->pop_back();
            actualDepth -= 1;
            continue;
        }
        if (myStack->top().getBoard().isTowerComplete(targetTower)) {//nasel sem reseni
            //  cout<<"SOLUTION FOUND!"<<endl;
            actualSolution->push_back(myStack->top().getMove());
            if ((solution->size() == 0) || (solution->size() > actualSolution->size())) {// reseni je lepsi nez nejlepsi zatim nalezene
                delete solution;
                solution = actualSolution;
                actualSolution = new vector<Move>;
                for (int i = 0; i < solution->size(); i++) {
                    actualSolution->push_back((*solution)[i]);
                }
                bestSolutionsDepth = solution->size();
            }
            //  cout << "removing SOL: " << myStack->top().getMove() << myStack->top().getDepth() << endl;
            actualSolution->pop_back(); //
            int dep = myStack->top().getDepth();

            //  while (myStack->top().getDepth() >= dep) {//vzházim ze zásobníku uzly se stejnou hloubkou...nemuže v nich bejt lepší řešení
            myStack->pop();
            //  }
            continue;
        }

        if (myStack->top().getDepth() >= bestSolutionsDepth) {// jsem ve vetsi hloubce nez moje nejlepsi
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
    cout << "Pushed: " << pushed << endl; //výpis počtu uložených prvků
    return *solution;
}