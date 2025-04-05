#ifndef INTERSECTION_CHECKER_H
#define INTERSECTION_CHECKER_H

#include "iostream"
#include "cmath"
#include "Line.h"

class IntersectionChecker{

    public:
	//returns true if the point is above the line, 
	//returns false if the point is on the line or below
	bool isPointBelowLine(std::shared_ptr<Point> p, std::shared_ptr<Line> l)
	{

	      auto dX = l->getP2()->getX()-l->getP1()->getX();
	      auto dY = l->getP2()->getY()-l->getP1()->getY();
	      //rect equation: y=mx+b
	      auto m = dY/dX;
              //resolving b
	      //b = y - mx
	      auto b = l->getP1()->getY() - m* l->getP1()->getX();
	     //now get the x from the point we want to check
	     auto y = m*p->getX()+b;
             auto diff = y-p->getY();
	     if(diff<0)
	     {
                 diff = -1*diff;
	     }

	     if(p->getY()< y)
	     {
                 return true;
	     }

	     return false;
	}

        bool isPointInLine(std::shared_ptr<Point> p, std::shared_ptr<Line> l)
        {
              auto dX = l->getP2()->getX()-l->getP1()->getX();
	      auto dY = l->getP2()->getY()-l->getP1()->getY();
	      //rect equation: y=mx+b
	      auto m = dY/dX;
              //resolving b
	      //b = y - mx
	      auto b = l->getP1()->getY() - m* l->getP1()->getX();
	     //now get the x from the point we want to check
	     auto y = m*p->getX()+b;
             auto diff = y-p->getY();
	     if(diff<0)
	     {
                 diff = -1*diff;
	     }

	     if(p->getY()==y || diff < 0.001)
	     {
                 return true;
	     } 

	     return false;
	}
        bool existIntersection(std::shared_ptr<Line> l1, std::shared_ptr<Line> l2) const {
            
            int mOrient1 = getOrientation(l1->getP1(), l1->getP2(), l2->getP1());
            int mOrient2 = getOrientation(l1->getP1(), l1->getP2(), l2->getP2());
            int mOrient3 = getOrientation(l2->getP1(), l2->getP2(), l1->getP1());
            int mOrient4 = getOrientation(l2->getP1(), l2->getP2(), l1->getP2());

            if(mOrient1!=mOrient2 && mOrient3!=mOrient4){
                return true;
            }

            if(mOrient1==0 && liesOnSegment(l1->getP1(), l1->getP2(), l2->getP1())){
                return true;
            }

            if(mOrient2==0 && liesOnSegment(l1->getP1(), l2->getP2(), l2->getP1())){
                return true;
            }

            if(mOrient3==0 && liesOnSegment(l1->getP2(), l1->getP1(), l2->getP2())){
                return true;
            }

            if(mOrient4==0 && liesOnSegment(l1->getP2(), l2->getP1(), l2->getP2())){
                return true;
            }

            return false;
        }
        
	std::shared_ptr<Point> calculateIntersection(std::shared_ptr<Line> line1, std::shared_ptr<Line> line2) const {
    float deltaYL1 = line1->getP2()->getY() - line1->getP1()->getY();
    float deltaXL1 = line1->getP1()->getX() - line1->getP2()->getX();
    float compL1 = deltaYL1 * (line1->getP1()->getX()) + deltaXL1 * (line1->getP1()->getY());

    float deltaYL2 = line2->getP2()->getY() - line2->getP1()->getY();
    float deltaXL2 = line2->getP1()->getX() - line2->getP2()->getX();
    float compL2 = deltaYL2 * (line2->getP1()->getX()) + deltaXL2 * (line2->getP1()->getY());

    float determinant = deltaYL1 * deltaXL2 - deltaYL2 * deltaXL1;
    
    if (fabs(determinant) < EPSILON) {
        // These are parallel lines
	    //std::cout << "these are parallel lines \n";
        return nullptr;
    } else {
        // Calculate intersection point
        float x = ((deltaXL2 * compL1) - (deltaXL1 * compL2)) / determinant;
        float y = ((deltaYL1 * compL2) - (deltaYL2 * compL1)) / determinant;
        
	std::shared_ptr<Point> intersection = std::make_shared<Point>( Point(x, y));
        //std::cout << "Checking if point "<< *intersection << " lines on both lines" << std::endl;
        // Check if the intersection point lies on both segments
        if (liesOnSegment(line1->getP1(), intersection, line1->getP2()) &&
            liesOnSegment(line2->getP1(), intersection, line2->getP2())) {
            return intersection;
        } else {
	    //std::cout << "returning null\n";
            
            return nullptr;
        }
    }
}


    private:
        const float EPSILON = 1e-6;
        //p1, p2, and p3 are collinear points.
        //Check if p2 lies on the segment p1-p3
        bool liesOnSegment(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2, std::shared_ptr<Point> p3) const{
    //std::cout << "Checking if point " << *p2 << " lies in linw dwfined.by " << *p1 << " and " << *p3 << std::endl;
    bool condition1 = p2->getX() < minValue(p1->getX(), p3->getX()) - EPSILON;
    //std::cout << "condition 1 (p2->getX() < minValue(p1->getX(), p3->getX()) - EPSILON) is " << condition1 << std::endl;

    bool condition2 = p2->getX() > maxValue(p1->getX(), p3->getX()) + EPSILON;
    //std::cout << "condition 2 ( p2->getX() > maxValue(p1->getX(), p3->getX()) + EPSILON ) is: " << condition2 << std::endl;
    bool condition3 = p2->getY() < minValue(p1->getY(), p3->getY()) - EPSILON;
    //std::cout << "condition 3 ( p2->getY() < minValue(p1->getY(), p3->getY()) - EPSILON ) is " << condition3 << std::endl;
    bool condition4 = p2->getY() > maxValue(p1->getY(), p3->getY()) + EPSILON;
    //std::cout << " condition 4 ( p2->getY() > maxValue(p1->getY(), p3->getY()) + EPSILON ) is " << condition4 << std::endl;
        // Check if p2 is within the bounding box of p1 and p3
    if (condition1 ||
        condition2 ||
        condition3 ||
        condition4) {
	//std::cout << "liesOnSegment returning false because of lying outside of the bounding box" << std::endl;
        return false;
    }

    // Ensure collinearity within precision limits
    float crossProduct = (p2->getY() - p1->getY()) * (p3->getX() - p1->getX()) -
                         (p2->getX() - p1->getX()) * (p3->getY() - p1->getY());
    if (fabs(crossProduct) > EPSILON) {
	//std::cout << "liesOnSegment returning false because of cross product indicates there is collinearity" << std::endl;
        return false;
    }

    return true;
        }

        int getOrientation(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2, std::shared_ptr<Point> p3) const{
            int response = (p2->getY() - p1->getY()) *(p3->getX()-p2->getX()) - 
                        (p2->getX()-p1->getX()) * (p3->getY()-p2->getY());
            if(response==0){
                return 0;
            }

            return (response>0) ? 1 : 2;
        }

        float maxValue(float v1, float v2) const{
            if(v1>v2){
                return v1;
            } else {
                return v2;
            }
        }

        float minValue(float v1, float v2) const{
            if(v1>v2){
                return v2;
            } else {
                return v1;
            }
        }

        

};

#endif //INTERSECTION_CHECKER
