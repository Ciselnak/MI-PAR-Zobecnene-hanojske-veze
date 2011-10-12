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
    int value;
public:
    Move(int,int, int);
    inline int getFrom() const {return from;}
    inline int getTo() const {return to;}    
    bool isReverse(const Move &) const;
    friend ostream& operator<< (ostream& ,const Move & );
};

#endif	/* Move_H */

