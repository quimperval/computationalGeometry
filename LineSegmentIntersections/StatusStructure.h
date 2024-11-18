#ifndef STATUS_STRUCTURE_H
#define STATUS_STRUCTURE_H

#include "AVL.h"
#include "point.h"
#include "Line.h"

class StatusStructure{
    
    //iswl: Intersections With Sweep Line
    AVL<Point, Line*>* iswl = new AVL<Point, Line*>();

    public:
        StatusStructure(){

        }

        void updateIntersections(Line* sweepLine){
            //Use the sweep line to calculate the intersections with the
            //first get the content of the iswl
            auto elements = iswl->getInOrderElements();
            //Clear the iswl
            iswl->clear();
            //for each element that was previously retrieved 
            //calculate the intersection point
            //with the sweep line
            for(auto elem : elements){
                std::cout << elem << "\n";
            }
        }

        void removeLine(Line* toRemove) const{
            if(toRemove->getIntersectionwithSweepLine()!=nullptr){
                iswl->remove(*(toRemove->getIntersectionwithSweepLine()));
            }
            
        }

        void addIntersectionWithLine(Line* line, Line* sweepLine){

        }

    private:

};

#endif //STATUS_STRUCTURE_H