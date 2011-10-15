/* 
 * File:   Input.cpp
 * Author: Tomáš Čerevka
 * 
 * Created on October 15, 2011, 5:16 PM
 */

#include <string>
#include <sstream>
#include "Input.h"

Input::Input() {
}

Input::~Input() {

}

void Input::parseFile(const char* fileName) {
    ifstream file(fileName);

    string line;
    getline(file, line);
    stringstream config(line);

    // Pocet vezi, cilova vez, omezeni hloubky.
    config >> this->towerCount >> this->targetTower >> this->maxDepth;

    // Vytvori se deska.
    this->board = new Board(this->towerCount);

    // Na jednotlive veze se nasazi tokeny.
    for (int i = 0; i < this->towerCount; ++i) {        
        getline(file, line);
        stringstream tokens(line);       
        
        while (tokens.good()) {
            int token;
            tokens >> token;
            this->board->pushItem(i, token);
            //cout << i;
        }
    }
    file.close();
}

Board* Input::getBoard() {
    return this->board;
}

int Input::getTargetTower() {
    return this->targetTower;
}

int Input::getMaxDepth() {
    return this->maxDepth;
}

