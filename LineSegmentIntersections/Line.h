#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line{
    public:
        Line(){

        }

        Line(Point* p1, Point* p2): p1(p1), p2(p2){

        }

        ~Line(){
            
        }

        Point* getP1() const{
            return p1;
        }

        Point* getP2() const{
            return p2;
        }

    private: 
        Point* p1 = nullptr;
        Point* p2= nullptr;

};


std::ostream& operator<<(std::ostream& os, 
const Line& line){
    os << "[p1("<< line.getP1()->getX() << ", " 
    << line.getP1()->getY() << ")" 
    << ", p1("<< line.getP2()->getX() << ", " 
    << line.getP2()->getY() << ")]";
    return os;
}

#endif //LINE_H