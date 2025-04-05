#ifndef EVENT_POINT_H
#define EVENT_POINT_H

#include "point.h"
#include <bitset>
#include <unordered_set>


//#include "AVL.h"
#include "Line.h"
#include <iostream>
#include "LinePtrHash.h"
#include "LinePtrEqual.h"
class EventPoint : public Point{

    private: 
        
        
        std::unordered_set<std::shared_ptr<Line>, LinePtrHash, LinePtrEqual> linesStartingAtEventPoint;
        std::unordered_set<std::shared_ptr<Line>, LinePtrHash, LinePtrEqual> linesEndingAtEventPoint;
        std::unordered_set<std::shared_ptr<Line>, LinePtrHash, LinePtrEqual> linesWithEventPointInItsInterior;
    
    public:
        EventPoint():Point(){
           
        }

        EventPoint(float x, float y):Point(x, y){
           
        }
        
        EventPoint(Point& p ):Point(p.getX(), p.getY()){
           //std::cout << "Initializing event point\n";
        }
        
        ~EventPoint(){
            
        }

        void addLineToListStartingAtEventPoint(Line& line){
            //std::cout << "Adding line " << *line << " to the list of lines starting in this point " << *this << "\n";
            auto l = std::make_shared<Line>(line);
            linesStartingAtEventPoint.insert(l);
        }

        void addLineToListEndingAtEventPoint(Line& line){
            //std::cout << "Adding line " << *line << " to the list of lines ending in this point " << *this << "\n";
            auto l = std::make_shared<Line>(line);
	    linesEndingAtEventPoint.insert(l);
        }


        void addLineToListWithEventPointInItsInterior(Line& line){
            //std::cout << "Adding line " << *line << " to the list of lines ending in this point " << *this << "\n";
	    auto l = std::make_shared<Line>(line);
            linesWithEventPointInItsInterior.insert(l);
        }

        std::unordered_set<std::shared_ptr<Line>, LinePtrHash, LinePtrEqual> getLinesStartingAt(){
            return linesStartingAtEventPoint;
        }

        std::unordered_set<std::shared_ptr<Line>, LinePtrHash, LinePtrEqual> getLinesEndingAt(){
		return linesEndingAtEventPoint;
	}

	std::unordered_set<std::shared_ptr<Line>, LinePtrHash, LinePtrEqual> getLinesWithPointInItsInterior(){
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
    //std::out << "Debug: less than" << std::endl;
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
