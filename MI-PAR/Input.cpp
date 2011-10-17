
/* 
 * File:   Input.cpp
 * Author: Tomáš Čerevka
 * 
 * Created on October 15, 2011, 5:16 PM
 */

#include <string>
#include <sstream>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include "Input.h"

Input::Input() {
        
}

Input::~Input() {

}

void Input::parseFile() {
    ifstream file(this->fileName.c_str());
    
    string line;
    getline(file, line);
    stringstream config(line);

    // Pocet vezi, cilova vez, omezeni hloubky.
    config >> this->towersCount >> this->targetTower >> this->maxDepth;

    // Vytvori se deska.   
    this->board = new Board(this->towersCount);

    // Na jednotlive veze se nasazi tokeny.
    for (int i = 0; i < this->towersCount; ++i) {
        getline(file, line);
        stringstream tokens(line);

        while (tokens.good()) {
            int token;
            tokens >> token;
            this->board->pushItem(i, token);           
        }
    }
    file.close();
}

void Input::parseArguments(int count, char** args) {  
    // Argumentu musi byt lichy pocet - v nule je cesta k binarce.
    if (count % 2 == 0) {
        throw "Argumentu musi byt sudy pocet.";
    }

    for (int i = 1; i < (count); i = i + 2) { 
        if (strcmp(args[i], "-h") == 0) {
            // Napoveda
            printHelp();
            break;
        } else if (strcmp(args[i], "-n") == 0) {
            // Pocet tokenu.
            this->tokensCount = atoi(args[i + 1]);            
        } else if (strcmp(args[i], "-s") == 0) {
            // Pocet vezi.
            this->towersCount = atoi(args[i + 1]);
        } else if (strcmp(args[i], "-r") == 0) {
            // Cilova vez.
            this->targetTower = atoi(args[i + 1]);
        } else if (strcmp(args[i], "-d") == 0) {
            // Maximalni hloubka.
            this->maxDepth = atoi(args[i + 1]);
        } else if (strcmp(args[i], "-f") == 0) {
            // Nazev souboru.
            //string temp(args[i + 1]);
            this->fileName = args[i + 1];
            cout << "nacteny soubor " << this->fileName << endl;
        } else {            
            throw "Neznamy prepinac!";
        }
    }    
}

void Input::generateBoard() {    
    this->board = new Board(this->towersCount);
    
    // Inicializuje randomizer.
    srand(time(NULL));
    
    for (int i = (this->tokensCount - 1); i >= 0; --i) {
        // Nahodne se urci vez.
        int tower = rand() % this->towersCount;
        this->board->pushItem(tower, i);
    }
}

void Input::printHelp() {
    cout << "Napoveda" << endl;
    cout << "A) Nacteni ze souboru:" << endl;
    cout << "   -f cesta k souboru" << endl;
    cout << "B) Generovani zadani:" << endl;
    cout << "   -s pocet vezi" << endl;
    cout << "   -n pocet tokenu" << endl;
    cout << "   -r cilova vez <0, pocet vezi)" << endl;
    cout << "   -d maximalni hloubka" << endl;
}

Board* Input::getBoard() {
    return this->board;
}

int Input::getTowersCount() {
    return this->towersCount;
}

int Input::getTokensCount() {
    return this->tokensCount;
}

int Input::getTargetTower() {
    return this->targetTower;
}

int Input::getMaxDepth() {
    return this->maxDepth;
}

string Input::getFileName() {
    return this->fileName;
}

