#ifndef LINE_H
#define LINE_H

#include <memory>
#include "point.h"

class Line{

    

    public:
        Line(){

        }

        Line(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2): p1(p1), p2(p2){

        }

        ~Line(){
           std::cout << "Line being destroyed\n";    
        }

	std::shared_ptr<Point> getP1() const{
            return p1;
        }

	std::shared_ptr<Point> getP2() const{
            return p2;
        }

	std::shared_ptr<Point> getIntersectionwithSweepLine(){
            //TO-DO
            return intersectionWithSweepLine;
        }

        void setIntersectionwithSweepLine(std::shared_ptr<Point> intersection){
            //TO-DO
            intersectionWithSweepLine = intersection;
        }

        void resetIntersectionwithSweepLine(){
            intersectionWithSweepLine = nullptr;
        }
        
        

    private:
	std::shared_ptr<Point> p1 = nullptr;
	std::shared_ptr<Point> p2= nullptr;
	std::shared_ptr<Point> intersectionWithSweepLine = nullptr;

    friend bool operator==(const Line& line1, const Line& line2);
};


std::ostream& operator<<(std::ostream& os, 
const Line& line){
    os << "[p1("<< line.getP1()->getX() << ", " 
    << line.getP1()->getY() << ")" 
    << ", p1("<< line.getP2()->getX() << ", " 
    << line.getP2()->getY() << ")]";
    return os;
}

bool operator==(const Line& line1, const Line& line2){
    if(line1.getP1()==line2.getP1() && line1.getP2()==line2.getP2()){
        return true;
    }
    return false;
}

bool operator>(const Line& l1, const Line& l2){
    //use the same logic to compare that we use for event points
    //the line with greater "y" is the greater, if both "y" are
    //equal, then the line with lower "x" is greater.
    float l1MaxY = l1.getP1()->getY() > l1.getP2()->getY() ? l1.getP1()->getY() : l1.getP2()->getY();
    float l2MaxY = l2.getP1()->getY() > l2.getP2()->getY() ? l2.getP1()->getY() : l2.getP2()->getY();

    float l1MinX = l1.getP1()->getX() < l1.getP2()->getX() ? l1.getP1()->getX() : l1.getP2()->getX();

    float l2MinX = l2.getP1()->getX() < l2.getP2()->getX() ? l2.getP1()->getX() : l2.getP2()->getX();

    if(l1MaxY>l2MaxY ){
        //std::cout << "Debug: e1.getY() > e2.getY()" << std::endl;

        return true;
    } else if (l1MaxY==l2MaxY){
        //std::cout << "Debug: e1.getY() == e2.getY() and e1.getX() > e2.getX()" << std::endl;
        if(l1MinX<l2MinX){
            return true;
        }
    }



    return false;
}


bool operator<(const Line& l1, const Line& l2){
    //use the same logic to compare that we use for event points
    //the line with greater "y" is the greater, if both "y" are
    //equal, then the line with lower "x" is greater. 
    float l1MaxY = l1.getP1()->getY() > l1.getP2()->getY() ? l1.getP1()->getY() : l1.getP2()->getY();                                 
    float l2MaxY = l2.getP1()->getY() > l2.getP2()->getY() ? l2.getP1()->getY() : l2.getP2()->getY();

    float l1MinX = l1.getP1()->getX() < l1.getP2()->getX() ? l1.getP1()->getX() : l1.getP2()->getX();

    float l2MinX = l2.getP1()->getX() < l2.getP2()->getX() ? l2.getP1()->getX() : l2.getP2()->getX();

    if(l1MaxY<l2MaxY ){
        //std::cout << "Debug: e1.getY() > e2.getY()" << std::endl;

        return true;
    } else if (l1MaxY==l2MaxY){
        //std::cout << "Debug: e1.getY() == e2.getY() and e1.getX() > e2.getX()" << std::endl;
        if(l1MinX>l2MinX){
            return true;
        }
    }



    return false;
}

#endif //LINE_H
