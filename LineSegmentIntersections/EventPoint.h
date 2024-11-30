#ifndef EVENT_POINT_H
#define EVENT_POINT_H

#include "point.h"
#include <bits/stdc++.h>
#include <unordered_set>


//#include "AVL.h"
#include "Line.h"
#include <iostream>

class EventPoint : public Point{

    struct LineHash{
        /**
         * without the const in this method operator() we would have the below error in compilation:
         * /usr/include/c++/11/bits/hashtable_policy.h:1217:23: error: 
         * /usr/include/c++/11/bits/hashtable_policy.h:1217:23: error: static assertion failed: hash function must be invocable with an argument of key type
         * 1217 |         static_assert(__is_invocable<const _Hash&, const _Key&>{},
         * 
         */
            std::size_t operator()(const Line& l) const {
                
                //^ - bitwise xor operator
                return std::hash<float>()(l.getP1()->getX()) ^
                    std::hash<float>()(l.getP1()->getX()) ^
                    std::hash<float>()(l.getP2()->getX()) ^
                    std::hash<float>()(l.getP2()->getX()) 
                    ;
            }
    };

    private: 
        
        
        std::unordered_set<Line, LineHash> linesStartingAtEventPoint;
        std::unordered_set<Line, LineHash> linesEndingAtEventPoint;
    
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
            std::cout << "Adding line " << *line << " to the list of lines starting in this point " << *this << "\n";
            linesStartingAtEventPoint.insert(*line);
        }

        void addLineToListEndingAtEventPoint(Line* line){
            std::cout << "Adding line " << *line << " to the list of lines ending in this point " << *this << "\n";
            linesEndingAtEventPoint.insert(*line);
        }

        

        friend bool operator ==(const EventPoint& e1, const EventPoint& e2);
        friend bool operator >(const EventPoint& e1, const EventPoint& e2);
        friend bool operator <(const EventPoint& e1, const EventPoint& e2);

        };

        
        


bool operator==(const EventPoint& e1, const EventPoint& e2){
    
    return (e1.getX()==e2.getX()) && (e1.getY() == e2.getY());
}

bool operator!=(const EventPoint& e1, const EventPoint& e2){
    
    return (e1.getX()!=e2.getX()) || (e1.getY() != e2.getY());
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
std::ostream& operator<<(std::ostream& os,const EventPoint& e) {
    os << "(" << e.getX() << ", " 
    << e.getY() << ")";
    return os;
}

#endif //EVENT_POINT_H
