/* 
 * File:   main.cpp
 * Author: adam
 *
 * Created on 21. září 2011, 21:55
 */

#include <cstdlib>
#include <iostream>
#include "Move.h"
#include "Board.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cout<<"test"<<endl;
    Move *t =new Move(5,6);
    Move *r =new Move(6,7);
    
    cout<<*t<<endl;
    cout<<*r<<endl;
   
   
    Board *b = new Board(6); 
    b->pushItem(2,7);
    b->pushItem(2,5);
    b->pushItem(1,3);
   
    cout<<*b;
    (b->performMove(*(new Move(1,2))));
    cout<<*b;
    return 0;
}

