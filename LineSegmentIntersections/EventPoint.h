#ifndef EVENT_POINT_H
#define EVENT_POINT_H

#include "point.h"
//#include "AVL.h"
#include "Line.h"
#include <iostream>

class EventPoint : public Point{

    private: 
        //AVL<Line&,Line*> linesStartingAtEventPoint =  new AVL<Line&, Line*>; 
        //AVL<Line&,Line*> linesEndingAtEventPoint =  new AVL<Line&, Line*>; 
    
    public:
        EventPoint():Point(){
           
        }

        EventPoint(float x, float y):Point(x, y){
           
        }
        
        EventPoint(Point& p ):Point(p.getX(), p.getY()){
           std::cout << "Initializing event point\n";
        }
        
        ~EventPoint(){
            
        }

        void addLineToListStartingAtEventPoint(Line* line){
            std::cout << "Addling " << line << " to the list of lines starting in this point \n";
        }

        void addLineToListEndingAtEventPoint(Line* line){
            std::cout << "Addling " << line << " to the list of lines ending in this point \n";
        }

        void addLine(Line* line){
            EventPoint p1(*line->getP1());
            EventPoint p2(*line->getP2());
            if(*this==p1){
                std::cout << "P1 is equal to " << *this << "\n";
            }/* else if(*this==p2){
                std::cout << "P2 is equal to " << *this << "\n";
            }*/ 
        }

        friend bool operator ==(const EventPoint& e1, const EventPoint& e2);
        friend bool operator >(const EventPoint& e1, const EventPoint& e2);
        friend bool operator <(const EventPoint& e1, const EventPoint& e2);
        

};
bool operator==(const EventPoint& e1, const EventPoint& e2){
    
    return (e1.getX()==e2.getX()) && (e1.getY() == e2.getY());
}

bool operator>(const EventPoint& e1, const EventPoint& e2){
    //std::cerr << "Debug: greater than" << std::endl;
    if(e1.getY()>e2.getY()){    
        //std::cout << "Debug: e1.getY() > e2.getY()" << std::endl;

        return true;
    } else if (e1.getY()==e2.getY()){
        //std::cout << "Debug: e1.getY() == e2.getY() and e1.getX() > e2.getX()" << std::endl;
        if(e1.getX()>e2.getX()){
            return true;
        } 
    } 



    return false;
}

bool operator<(const EventPoint& e1, const EventPoint& e2){
std::cerr << "Debug: less than" << std::endl;
    if(e1.getY()<e2.getY()){
        return true;
    } else if (e1.getY()==e2.getY()){
        if(e1.getX()<e2.getX()){
            return true;
        } 
    } 
    return false;
}
std::ostream& operator<<(std::ostream& os, 
const EventPoint& e) {
    os << "(" << e.getX() << ", " 
    << e.getY() << ")";
    return os;
}

#endif //EVENT_POINT_H
