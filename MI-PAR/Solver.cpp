#include "Solver.h"
#include "mpi.h"


static const int MASTER_RANK = 0;
static const int TOKEN_WHITE = 10;
static const int TOKEN_BLACK = 11;
//kody jednotlivych zprav
static const int MESSAGE_TOKEN = 100;
static const int MESSAGE_FINISHED = 101;

enum ProcessColor {
    BLACK,
    WHITE
};

int tokenColor;
ProcessColor processColor; // zmena barvy se provede pri poslani prace...zatim neimplementovano
bool requestWork;
int myRank;
bool tokenArrived;
bool finished;
int actualDepth = 1;
int dolniMez;

Solver::Solver(const Board& b, int i, int t) : initState(b), targetTower(i), maxDepth(t) {
    myStack = new vector<StackItem>;
    solution = new vector<Move>;
    actualSolution = new vector<Move>;
}

void Solver::init() {
    // na zacatku maji vsechny procesory bilou barvu
    processColor = WHITE;
    tokenColor = TOKEN_WHITE;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    cout << myRank << endl;
    requestWork = true;


    if (myRank == MASTER_RANK) {//master posle prvniho peska
        tokenArrived = true;
    } else {
        tokenArrived = false;
    }
}

void sendPesek() {

    processColor = WHITE;
    if (tokenArrived) {//prisel token od mastra takze muzu posilat dal svuj
        int p; //kolik je celkem procesu
        MPI_Comm_size(MPI_COMM_WORLD, &p);
        int dest = (myRank + 1) % p;

        MPI_Send(&tokenColor, 1, MPI_INT, dest, MESSAGE_TOKEN, MPI_COMM_WORLD);
        tokenArrived = false;
        cout << "Posilam peska pro: " << dest << endl;
    }
}

void broadcast(int message) {//Soch rikal ze nemame pouzivat metodu MPI_Bcast
    //tak jsem vztvoril tuhle mtodu, kera broadcast simuluje
    int p;
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    for (int dest = 0; dest < p; dest++) {
        if(myRank!=dest){
        MPI_Send(&message, 1, MPI_INT, dest, MESSAGE_FINISHED, MPI_COMM_WORLD);}

    }
    

}

void processMessages() {
    int pesek; //sem si ulozim peska az mi prijde
    int flag;

    MPI_Status status, status2;
    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
    while (flag) {  
        switch (status.MPI_TAG) {//tady staci rozsirit o ostatni messages a rozumim vsemu
            case MESSAGE_TOKEN:
            {
                MPI_Recv(&pesek, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, &status2);
                cout << "Prisel Pesek od: " << status.MPI_SOURCE << endl;
                tokenArrived = true;

                if (pesek != TOKEN_BLACK && pesek != TOKEN_WHITE) {
                    cout << "Nespravna hodnoa peska" << endl;
                    throw "vadny pesek!";
                }
                if (processColor == WHITE) {
                    tokenColor = TOKEN_WHITE;
                } else {
                    tokenColor = TOKEN_BLACK;
                }

                //osetreni pokud jsem master
                if (myRank == MASTER_RANK) {
                    
                    if (pesek == TOKEN_WHITE) {
                        cout<<"Jsem MAster a dorazil mi WHITE pesek...koncim"<<endl;
                        broadcast(MESSAGE_FINISHED);
                        finished=true;
                        return;
                    }
                }
                break;
            }

            case MESSAGE_FINISHED:
            {
                finished = true;
                return;
            }

        }
         MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
    }

}

Solver::~Solver() {
    delete myStack;
    delete solution;
    delete actualSolution;
}
static int pushed = 0; //ukládá kolik prvků bylo v průběhu výpočtu uloženo na zásobník

void Solver::expandTop() {
    int dept = myStack->back().getDepth() + 1;
    Board act = myStack->back().getBoard();

    Move lastMov = myStack->back().getMove();
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
                    //Board *b = new Board(act);
                    b.performMove(*m);
                    int lowBound = b.getDolniMez(targetTower);
                    if ((dept + lowBound) > bestSolutionsDepth) {//ověřím jestli krok může z definice dolní meze vést k řešení                         
                        delete m;
                        // cout<<b<<"D"<<b.getDolniMez(targetTower)<<"fik"<<bestSolutionsDepth<<endl;
                        //cout<<act<<act.getDolniMez(targetTower)<<dept<<endl;
                        continue;
                    }

                    StackItem *s = new StackItem(b, *m, dept);
                    //  cout << "inserting item: "  << *m <<" dep: "<< dept << endl;
                    myStack->push_back(*s);
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

int Solver::processTop() {

    //   if (solution->size() == dolniMez) {// pokud jsme nasli reseni rovne dolni mezi. už nemůžeme najít lepší
    //     return;
    //  }
    if (actualDepth > myStack->back().getDepth()) {//odstrani jiz expandovany stav ze zasobniku pri navratu do nej

        myStack->erase(myStack->end());
        actualSolution->pop_back();
        actualDepth -= 1;
        return 0;
    }
    if (myStack->back().getBoard().isTowerComplete(targetTower)) {//nasel sem reseni
        actualSolution->push_back(myStack->back().getMove());
        if ((solution->size() == 0) || (solution->size() > actualSolution->size())) {// reseni je lepsi nez nejlepsi zatim nalezene
            delete solution;
            solution = actualSolution;
            actualSolution = new vector<Move>;
            for (int i = 0; i < solution->size(); i++) {
                actualSolution->push_back((*solution)[i]);
            }
            bestSolutionsDepth = solution->size();
        }
        actualSolution->pop_back(); //
        int dep = myStack->back().getDepth();


        myStack->erase(myStack->end());

        return 0;
    }

    if (myStack->back().getDepth() >= bestSolutionsDepth) {// jsem ve vetsi hloubce nez moje nejlepsi


        myStack->erase(myStack->end());
        return 0;
    }
    actualSolution->push_back(myStack->back().getMove());
    actualDepth += 1;

    return 1;

}

vector<Move> Solver::solve() {

    if (myRank != MASTER_RANK) {
        //cekam az mi prijde prace
        //prvni rozdeleni se udela automaticky bez zadani
        
        
        //cekam dokud message neprijde melo by prijit prvni deleni prace
        //momentalne to prvni spocte takzee prijde pesek
        MPI_Status s;
        MPI_Probe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&s);
        
        processMessages();

    } else {
        //zvazit co je treba pokazde posilat...hloubka dolni mez??

        dolniMez = initState.getDolniMez(targetTower);
        //cout<<"dolniM: "<<dolniMez;
        if (initState.isTowerComplete(targetTower)) {//zadani je rovnou reseni
            return *solution;
        }
        bestSolutionsDepth = maxDepth;
        Move *foo = new Move(0, 0, 0);
        StackItem *s = new StackItem(initState, *foo, 0);
        delete foo;
        myStack->push_back(*s);
        delete s;
        expandTop();
    }
    int counter = 0;
 
    while (!finished) {
        if (!myStack->empty()) {
            int i = processTop();
            if (i == 1) {
                expandTop();
            }
        } else {
            //pozadam o praci ---zatim neumim
            sendPesek();
        }

        if(counter==150){//natipovat idealni honotu
            //sem prvni rozdeleni prace---jen MASTER
            counter=0;
            processMessages();
        }
        
        counter++;
    }

    //sem redukci reseni pripadne dalsi veci po vypoctu
    
    cout << "Pushed: " << pushed << endl; //výpis počtu uložených prvků
    return *solution;
}

