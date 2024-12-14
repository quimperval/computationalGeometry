#ifndef EVENT_POINT_H
#define EVENT_POINT_H

#include "point.h"
#include <bitset>
#include <unordered_set>


//#include "AVL.h"
#include "Line.h"
#include <iostream>
#include "LineHash.h"

class EventPoint : public Point{

    private: 
        
        
        std::unordered_set<Line, LineHash> linesStartingAtEventPoint;
        std::unordered_set<Line, LineHash> linesEndingAtEventPoint;
        std::unordered_set<Line, LineHash> linesWithEventPointInItsInterior;
    
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


        void addLineToListWithEventPointInItsInterior(Line* line){
            std::cout << "Adding line " << *line << " to the list of lines ending in this point " << *this << "\n";
            linesWithEventPointInItsInterior.insert(*line);
        }

        std::unordered_set<Line, LineHash> getLinesStartingAt(){
            return linesStartingAtEventPoint;
        }

        std::unordered_set<Line, LineHash> getLinesEndingAt(){
		return linesEndingAtEventPoint;
	}

	std::unordered_set<Line, LineHash> getLinesWithPointInItsInterior(){
		return linesWithEventPointInItsInterior;
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
