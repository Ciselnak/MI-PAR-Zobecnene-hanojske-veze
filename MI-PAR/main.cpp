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
#include "Input.h"
#include "mpi.h"


using namespace std;

/*
 * Vstupni bod programu.
 */
int main(int argc, char** argv) {
    try {
        
        MPI_Init(&argc,&argv);
      


        
        // sem implementovat tabulku empirickejch hloubek
        // dodat výpočet horní meze pro stanovení hloubky prohledávání

        // Nacteni dat ze souboru.
//        Input input;
//        input.parseArguments(argc, argv);
//
//        if (!input.getFileName().empty()) {
//            // Bylo zadano nacteni ze souboru.
//            cout << "Nacitam data ze souboru: " << input.getFileName() << endl;
//            input.parseFile();
//        } else {
//            // Nenacita se ze souboru.
//            input.generateBoard();          
//        }
//        
        Board *b = new Board(4);
        int targetTower = 2;
        int maxDepth = 20;

        //Board *b = new Board(4);

         b->pushItem(0,3);
         b->pushItem(0,1);
       
            
     //   b->pushItem(1, 6);
       b->pushItem(1, 5);
           b->pushItem(1,2);

     
    
     //   b->pushItem(3, 7);
    //    b->pushItem(2, 8);
        b->pushItem(2, 4);
        cout<<*b<<endl;
//        if (input.getFileName().empty()) {
//            cout << "Pocet tokenu: " << input.getTokensCount() << endl;
//        }
//        cout << "Pocet vezi: " << input.getTowersCount() << endl;
//        cout << "Cilova vez: " << input.getTargetTower() << endl;
//        cout << "Maximalni hloubka: " << input.getMaxDepth() << endl;       
//        cout << *b << endl;

        Solver *s = new Solver(*b, targetTower, maxDepth );
         s->init();
       vector<Move> sol = s->solve();
      
       
       //tady neni treba vypisovat to pokazdz ale jen pro mastra...mozna nebudeme vypisovat vubec
        if (sol.size() == 0) {
            cout << "Reseni v pozadovane hloubce nenalezeno." << endl;
        } else {
            cout << "Solution:" << endl;
            for (vector<Move>::iterator it = sol.begin(); it < sol.end(); it++) {
                cout << *it << endl;
            }
            cout << "Celkem tahu: " << sol.size() << endl;
        }
        
        delete s;
        delete b;

        MPI_Finalize();
        return 0;
    } catch (const char* ch) {
        cout << ch << endl;
    }

}

