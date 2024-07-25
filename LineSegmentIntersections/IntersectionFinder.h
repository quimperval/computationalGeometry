#ifndef INTERSECTION_FINDER_H
#define INTERSECTION_FINDER_H

#include "AVL.h"

class IntersectionFinder{
    private: 
        AVL<EventPoint, EventPoint*>* eventPoints = nullptr;
        
    
    public: 
        IntersectionFinder(){
            eventPoints = new AVL<EventPoint, EventPoint*>();    
        }

        void addLine(Line* line){
            std::cout << "Adding line "<< *line << "\n";
            Point* p1 = line->getP1();
            EventPoint* e1 = new EventPoint(*p1);
            std::cout << "Adding p1 "<< *p1 << "\n";
    
            eventPoints->insert(*e1, e1);
            Point* p2 = line->getP2();
            EventPoint* e2 = new EventPoint(*p2);
            std::cout << "Adding p2 "<< *p2 << "\n";

            eventPoints->insert(*e2, e2);
        }

        int getEventPointsCount(){
            return eventPoints->size();
        }
};

#endif