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
        
        Point* calculateIntersection(Line* line1, Line* line2) const{
            //Considering the first line has the equation A1*x+B1*y = C1
            //Delta y of line 1 (L1)
            float deltaYL1 = line1->getP2()->getY() - line1->getP1()->getY();
            //std::cout<<"deltaYL1: " << deltaYL1 << std::endl;
            float deltaXL1 = line1->getP1()->getX() - line1->getP2()->getX();
            //std::cout<<"deltaXL1: " << deltaXL1 << std::endl;
            float compL1 = deltaYL1*(line1->getP1()->getX())+deltaXL1*(line1->getP1()->getY());
            //std::cout<<"compL1: " << compL1 << std::endl;
            //Considering the first line has the equation A1*x+B1*y = C1
            //Delta y of line 2 (L2)
            float deltaYL2 = line2->getP2()->getY() - line2->getP1()->getY();
            //std::cout<<"deltaYL2: " << deltaYL2 << std::endl;
            float deltaXL2 = line2->getP1()->getX() - line2->getP2()->getX();
            //std::cout<<"deltaXL2: " << deltaXL2 << std::endl;
            float compL2 = deltaYL2*(line2->getP1()->getX())+deltaXL2*(line2->getP1()->getY());
            //std::cout<<"compL2: " << compL2 << std::endl;

            float determinant = deltaYL1*deltaXL2-deltaYL2*deltaXL1;

            if(determinant==0){
                //std::cout<<"These are parallel lines\n";
                return nullptr;
            } else {
                //std::cout<<"Calculating intersection point\n";
                float x = ((deltaXL2*compL1) - (deltaXL1*compL2) ) / determinant;
                float y = ((deltaYL1*compL2) - (deltaYL2*compL1) ) / determinant;
                Point* p = new Point(x,y);
                //std::cout << "Returning "<< *p << std::endl;
                return p;
            }

            return nullptr;
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