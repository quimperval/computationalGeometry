#ifndef INTERSECTION_FINDER_H
#define INTERSECTION_FINDER_H

#include "AVL.h"
#include "EventQueue.h"
#include "StatusStructure.h"

class IntersectionFinder{
    private:
        
        EventQueue* eventQueue=nullptr;
        StatusStructure* statusStr=nullptr;
        Point* minX = nullptr;
        Point* maxX = nullptr;
    
    public:

        IntersectionFinder(){
            eventQueue = new EventQueue();
        }


        void addLine(Line* line){
            eventQueue->addLine(line);
            
        }

        int getEventPointsCount(){
            return eventQueue->getEventPointsCount();
        }

        EventPoint* getMaxEventPoint(){
            return eventQueue->getMaxEventPoint();
        }

        void printEventPointsOrdered() const{
            
            eventQueue->printEventPointsOrdered();
            
        }

        EventPoint* getNextEvent(){
            return eventQueue->getNextEvent();
        }

        

    private:
        
};

#endif