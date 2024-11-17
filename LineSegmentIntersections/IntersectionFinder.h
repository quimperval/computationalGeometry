#ifndef INTERSECTION_FINDER_H
#define INTERSECTION_FINDER_H

#include "AVL.h"

class IntersectionFinder{
    private:
        AVL<EventPoint, EventPoint*>* eventQueue = nullptr;
        
    
    public:

        IntersectionFinder(){
            eventQueue = new AVL<EventPoint, EventPoint*>();
        }

        void printEventQueue(){
            eventQueue->print();
        }

        void addLine(Line* line){
            
            std::cout << "Adding line "<< *line << "\n";
            Point* p1 = line->getP1();
            EventPoint* e1 = new EventPoint(*p1);
            std::cout << "Adding p1 "<< *p1 << "\n";
    
            std::cout << "@@@@@@ Trying to add " << *e1 << "\n";
            eventQueue->insert(*e1, e1);
            Point* p2 = line->getP2();
            EventPoint* e2 = new EventPoint(*p2);
            std::cout << "Adding p2 "<< *p2 << "\n";

            std::cout << "@@@@@@ Trying to add " << *e2 << "\n";
            eventQueue->insert(*e2, e2);
            std::cout << "Printing event queue\n";
            eventQueue->print();
           
                    
            //if the p1.y is greater than the p2.y, then add the line to the list of linesStartingAtEventPoint of p1. 
            if(p1->getY()>p2->getY()){
                e1->addLineToListStartingAtEventPoint(line);
                //and therefore add the line to the list of linesEndingAtEventPoint of p2
                e2->addLineToListEndingAtEventPoint(line);
            }else if (p1->getY()<p2->getY()){
                //if the p2.y is greater than the p1.y then add the line to the list of linesStartingAtEventPoint of p2. 
                e2->addLineToListStartingAtEventPoint(line);
                //and therefore add the line to the list of linesEndingAtEventPoint of p2
                e1->addLineToListEndingAtEventPoint(line);
            } else if (p1->getY()==p2->getY()){
                //if both p2.y and p1.y are equal
                if(p1->getX()<p2->getX()){
                    //if p1.x is lower than p2.x then add the line to the list of linesStartingAtEventPoint of p1.
                    e1->addLineToListStartingAtEventPoint(line);
                    //and therefore add the line to the list of linesEndingAtEventPoint of p2
                    e2->addLineToListEndingAtEventPoint(line);
                } else if(p1->getX()>p2->getX()) {
                    //if p2.x is lower than p1.x then add the line to the list of linesStartingAtEventPoint of p2.
                    e2->addLineToListStartingAtEventPoint(line);
                    //and therefore add the line to the list of linesEndingAtEventPoint of p1
                    e1->addLineToListEndingAtEventPoint(line);
                } else {
                    e1->addLineToListStartingAtEventPoint(line);
                    e2->addLineToListEndingAtEventPoint(line);
                }
            }
            
        }

        int getEventPointsCount(){
            return eventQueue->size();
        }

        EventPoint* getMaxEventPoint(){
            return eventQueue->findMax();
        }

        void printLinesByEventPoint() const{
            std::cout << "printLinesByEventPoint\n";
            auto orderedElements= eventQueue->getInOrderElements();
            for(auto elem : orderedElements){
                std::cout << *elem->element() << "\n";
            }
        }

    private:
        
};

#endif