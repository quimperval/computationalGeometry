#ifndef STATUS_STRUCTURE_H
#define STATUS_STRUCTURE_H

#include "AVL.h"
#include "point.h"
#include "Line.h"
#include "IntersectionChecker.h"

class StatusStructure{
    
    private:
        //iswl: Intersections With Sweep Line
        AVL<Point, Line*>* iswl = new AVL<Point, Line*>();
        IntersectionChecker* checker = new IntersectionChecker();

    public:
        StatusStructure(){

        }
        
        ~StatusStructure(){
            //delete iswl;
            //delete checker;
        }

        void updateIntersections(Line* sweepLine){
            //Use the sweep line to calculate the intersections with the
            //first get the content of the iswl
            std::cout << "Getting in order elements \n";
            auto elements = iswl->getInOrderElements();
            /*if(elements!=nullptr){
                std::cout << "elements variable is not nullptr";
            }*/
            //Clear the iswl
            std::cout << "Clearing iswl \n";
            iswl->clear();
            //for each element that was previously retrieved 
            //calculate the intersection point
            //with the sweep line
            std::cout << "elements: " << elements.size() << std::endl;
            std::cout << "Iterating over all elements \n";
            
            for(Line* line : elements){
                std::cout << *line << std::endl;
                /*if(item==nullptr){
                    std::cout << "item is null\n";
                } else {
                    std::cout << "item is Not null\n";
                }
                Line* line = item->element();*/
                /*
                if(line==nullptr){
                    std::cout <<" line is null\n";
                } else {
                    std::cout <<" line is NOT null\n";
                }*/
                addLine(line, sweepLine);
            }
        }

        void removeLine(Line* toRemove) const{
            if(toRemove->getIntersectionwithSweepLine()!=nullptr){
                iswl->remove(*(toRemove->getIntersectionwithSweepLine()));
                toRemove->setIntersectionwithSweepLine(nullptr);
            }
            
        }

        void addLine(Line* line, Line* sweepLine){
            std::cout << "Add line method\n";
            //Calculate the intersection
            
            std::cout << *line << "\n";
            auto intersection = checker->calculateIntersection(line, sweepLine);
            if(intersection!=nullptr){
                //Set the intersection in the line
                line->setIntersectionwithSweepLine(intersection);
                std::cout << "Adding line "<< *line << " that intersects at " << *intersection << std::endl;
                iswl->insert(*intersection, line);
            } else {
                line->setIntersectionwithSweepLine(nullptr);
            }
            
        } 

        int size(){
            return iswl->size();
        }

};

#endif //STATUS_STRUCTURE_H