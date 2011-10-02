/* 
 * File:   Move.h
 * Author: adam
 *
 * Created on 26. září 2011, 21:06
 */

#ifndef Move_H
#define	Move_H

#include<iostream>
using namespace std;
class Move{
private: 
    int from;
    int to;  
public:
    inline const int getFrom() {return from;}
    inline const int getTo() {return to;}
    Move(int,int);
    const bool isReverse(const Move &);
    friend ostream& operator<< (ostream& ,const Move & );
};


#endif	/* Move_H */

