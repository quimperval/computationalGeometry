#ifndef INTERSECTION_CHECKER_H
#define INTERSECTION_CHECKER_H

#include "Line.h"

class IntersectionChecker{

    public:

        bool existIntersection(Line* l1, Line* l2) const {
            
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

    private:
        //p1, p2, and p3 are collinear points.
        //Check if p2 lies on the segment p1-p3
        bool liesOnSegment(Point* p1, Point* p2, Point* p3) const{
            bool condition1 = p2->getX()<=maxValue(p1->getX(), p3->getX());
            
            bool condition2 = p2->getX()>=minValue(p1->getX(), p3->getX());

            bool condition3 = p2->getY()<=maxValue(p1->getY(), p3->getY());

            bool condition4 = p2->getX()>=minValue(p1->getY(), p3->getY());
           

            if(condition1 && condition2 && condition3 && condition4){
                return true;
            }
            return false;
        }

        int getOrientation(Point* p1, Point* p2, Point* p3) const{
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