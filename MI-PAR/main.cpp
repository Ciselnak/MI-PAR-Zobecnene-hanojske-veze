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
  
 //   cout<<*t<<endl;
   // cout<<*r<<endl;
   
   //sem implantovat tabulku empirickejch hloubek
    Board *b = new Board(3); 
    b->pushItem(0,2);
   // b->pushItem(1,9); 
   // b->pushItem(1,6);
   // b->pushItem(2,4); 
    b->pushItem(1,5); 
    b->pushItem(2,3); 
   
    cout<<*b<<endl;
    
            
    
    Solver *s = new Solver(*b,0,30);
    vector<Move> sol=s->solve();
    if(sol.size()==0){
      cout<<"Reseni v pozadovane hloubce nenalezeno."<<endl;  
    }else{
    cout<<"Solution:"<<endl;
    for ( vector<Move>::iterator it=sol.begin() ; it < sol.end(); it++ ){
    cout <<  *it<<endl;}
    cout<<"Celkem tahu: "<<sol.size()<<endl;
    }
    
    delete s;
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

