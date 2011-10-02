#include "Board.h"

Board::Board(int number) {
    towers = new vector < vector<int>*>;
    for (int i = 0; i < number; i++) {
        towers->push_back(new vector<int>);
    }
}

Board::Board(const Board& param){
    throw "dodelat";    
} 


Board::~Board(){
    for (vector< vector<int>* >::iterator it = towers->begin(); it!=towers->end(); ++it) {
    delete *it;
}
    delete towers;
    
}

/*
 Metoda nekontroluje jestli po vlozeni prvku bude vez v pripustnem stavu
 je treba to kontrolovat pri vytvareni
 */
void Board::pushItem(int tower, int value) {
    (*towers)[tower]->push_back(value);
}

const int Board::size() {
    return this->towers->size();
}

/*overi zda je dany tah mozny
 
 */
const bool Board::isMoveCorrect(Move& m) {
  //  if(this->size)
    
    if ((*this->towers)[m.getFrom()]->empty()) {//beru z prazdne veze
        return false;
    }
    if ((*this->towers)[m.getTo()]->empty()) {//davam na prazdnou vez
        return true;
    }

    if ((*this->towers)[m.getFrom()]->back()>(*this->towers)[m.getTo()]->back()) {//na obouv vezich neco je
        return false;
    } else {
        return true;
    }
}

void Board::performMove(Move& move){
    int item = (*this->towers)[move.getFrom()]->back();
    (*this->towers)[move.getFrom()]->pop_back();
    (*this->towers)[move.getTo()]->push_back(item);
}

/*
 vypise veze po radcich...slo by upravit aby vypadalo lepe
 */
ostream& operator<<(ostream& os, Board &b) {

    for (int i = 0; i < b.size(); i++) {
        cout << i << ". vez:  ";
        for (int j = 0; j < (*b.towers)[i]->size(); j++) {
            os << (*(*b.towers)[i])[j] << "  ";
        }
        os << endl;
    }
    return os;
}

bool Board::operator==(const Board & param){
    throw "dodelat";
}
