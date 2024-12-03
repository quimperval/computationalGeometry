#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "AVL.h"
#include "EventPoint.h"
class EventQueue{
    private: 
        AVL<EventPoint, EventPoint*>* eventPoints = new AVL<EventPoint, EventPoint*>();

    public: 
        EventQueue(){
           
        }
        ~EventQueue(){
            
        }
        
        bool insertEvent(EventPoint*){
            //TODO
            return false;
        }

        EventPoint* getNextEvent(){
            EventPoint* nextEvent =  eventPoints->findMax();
            eventPoints->remove(*nextEvent);
            return nextEvent;
        }

        void addLine(Line* line){
            /**/
            std::cout << "Adding line "<< *line << "\n";
            Point* p1 = line->getP1();
            EventPoint* e1 = new EventPoint(*p1);
            std::cout << "Adding p1 "<< *p1 << "\n";
    
            std::cout << "@@@@@@ Trying to add " << *e1 << "\n";
            EventPoint* e1Temp = eventPoints->find(*e1);
            if(e1Temp!=nullptr){
                std::cout<< "The point e1 is already in the event queue\n";
                e1 = e1Temp;
                e1Temp= nullptr;
            } else {
                eventPoints->insert(*e1, e1);
            }
            

            
        
            Point* p2 = line->getP2();
            EventPoint* e2 = new EventPoint(*p2);
            std::cout << "Adding p2 "<< *p2 << "\n";

            std::cout << "@@@@@@ Trying to add " << *e2 << "\n";
            EventPoint* e2Temp = eventPoints->find(*e2);
            if(e2Temp!=nullptr){
                std::cout<< "The point e2 is already in the event queue\n";
                e2 = e2Temp;
                e2Temp= nullptr;
            } else {
                eventPoints->insert(*e2, e2);
            }
            
            std::cout << "Printing event queue\n";
            eventPoints->print();
           
                    
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

        void printEventPointsOrdered(){
            std::cout << "printEventPointsOrdered\n";
            auto orderedElements= eventPoints->getInOrderElementsAsNodes();
            for(auto elem : orderedElements){
                std::cout << *elem->element() << "\n";
                //For each event point print the lines starting at

                //For each event point print the lines ending at
            }
        }

        int getEventPointsCount(){
            if(eventPoints==nullptr){
                return 0;
            }
            return eventPoints->size();
        }

        EventPoint* getMaxEventPoint(){
            return eventPoints->findMax();
        }

        void printEventPointsOrdered() const{
            std::cout << "printEventPointsOrdered\n";
            auto orderedElements= eventPoints->getInOrderElementsAsNodes();
            for(auto elem : orderedElements){
                std::cout << *elem->element() << "\n";
            }
        }

        bool isEmpty(){
            return eventPoints->isEmpty();
        }
};


#endif //EVENT_QUEUE_H