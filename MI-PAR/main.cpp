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
#include "StackItem.h"
#include "Solver.h"
using namespace std;

/*
 * main
 */
int main(int argc, char** argv) {
    try{
    cout<<"test"<<endl;
    Move *t =new Move(5,6);
    Move *r =new Move(6,7);
    
 //   cout<<*t<<endl;
   // cout<<*r<<endl;
   
   
    Board *b = new Board(5); 
    b->pushItem(0,1);
    b->pushItem(0,4);
    b->pushItem(0,7);
    b->pushItem(0,8);
    b->pushItem(0,9); 
  // Solver *s = new Solver(*b,5,2);
   // s->solve();
    cout<<b->isTowerComplete(2);
   // delete s;
    delete b;
  /*  
   StackItem *s = new StackItem(*b,*r,1);
   // (b->performMove(*(new Move(1,2))));
   cout<<s->getDepth()<<endl;
   cout<<s->getBoard()<<endl;
  
    Board bor = *b;
        bor.pushItem(5,7);
        cout<<b->getItems()<<endl;
        cout<<bor.getItems()<<endl;*/
    return 0;
    }catch (const char* ch) {
        cout<<ch<<endl;
    }
    
    }

