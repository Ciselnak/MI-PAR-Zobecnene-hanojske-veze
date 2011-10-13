#include "Board.h"

Board::Board(int number) {
    if (number <= 0) throw"zaporny pocet vezi!!";

    towers = new vector < vector<int>*>;
    for (int i = 0; i < number; i++) {
        towers->push_back(new vector<int>);
    }
    this->items = 0;
}

Board::Board(const Board& param) {
    towers = new vector < vector<int>*>;
    for (int i = 0; i < param.towers->size(); i++) {
        towers->push_back(new vector<int>);
    }
    int i = -1;
    for (vector< vector<int>* >::iterator it = param.towers->begin(); it != param.towers->end(); ++it) {
        i++;
        for (vector<int>::iterator iter = (*it)->begin(); iter != (*it)->end(); ++iter) {
            (*towers)[i]->push_back(*iter);
        }
    }
    this->items = param.items;
}

Board::~Board() {
    for (vector< vector<int>* >::iterator it = towers->begin(); it != towers->end(); ++it) {
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
    this->items++;
}

int Board::getDolniMez(int tower) const{
    if((*towers)[tower]->size()==0){
        return items;
    }
    
    int dobre=0;
    for(int i = items;i>0;i--){
       // (*(*b.towers)[i])[j] 
        if((*(*towers)[tower])[items-i]==i){
            dobre+=1;
        }
    }
    return ((*towers)[tower]->size()-dobre)*2 + items-(*towers)[tower]->size();
  
}

bool Board::isTowerComplete(int tower) const {
    return (*towers)[tower]->size() == items; 

}

int Board::getTowerTop(int tower) const{
    if((*towers)[tower]->size()==0){
        return 0;
    }
    else{
    return *(*towers)[tower]->rbegin();
    }
    //return 2;
}

int Board::size() const {
    return this->towers->size();
}

/*overi zda je dany tah mozny 
 */
bool Board::isMoveCorrect(Move& m) const {
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

void Board::performMove(Move& move) {
    int item = (*this->towers)[move.getFrom()]->back();
    (*this->towers)[move.getFrom()]->pop_back();
    (*this->towers)[move.getTo()]->push_back(item);
}

/*
 vypise veze po radcich...slo by upravit aby vypadalo lepe
 */
ostream& operator<<(ostream& os, const Board &b) {

    for (int i = 0; i < b.size(); i++) {
        cout << i << ". vez:  ";
        for (int j = 0; j < (*b.towers)[i]->size(); j++) {
            os << (*(*b.towers)[i])[j] << "  ";
        }
        os << endl;
    }
    return os;
}

bool Board::operator==(const Board & param) {
    throw "dodelat operator== pokud ho budeme pouzivat";
}
