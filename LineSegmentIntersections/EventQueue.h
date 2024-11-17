#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "AVL.h"
#include "EventPoint.h"
class EventQueue{
    private: 
         AVL<EventPoint, EventPoint*>* eventPoints = new AVL<EventPoint, EventPoint*>();

    public: 
        EventQueue(){
           // eventPoints = ;
        }
        ~EventQueue(){
            
        }
        
        void addLine(Line* line){
            /**/
            std::cout << "Adding line "<< *line << "\n";
            Point* p1 = line->getP1();
            EventPoint* e1 = new EventPoint(*p1);
            std::cout << "Adding p1 "<< *p1 << "\n";
    
            std::cout << "@@@@@@ Trying to add " << *e1 << "\n";
            if (!eventPoints) {
                std::cerr << "eventPoints is null before accessing!\n";
            }
             if(eventPoints==nullptr){
                std::cout << "@@@@@@ eventPoints is null \n";
            }
            eventPoints->insert(*e1, e1);
            Point* p2 = line->getP2();
            EventPoint* e2 = new EventPoint(*p2);
            std::cout << "Adding p2 "<< *p2 << "\n";

            std::cout << "@@@@@@ Trying to add " << *e2 << "\n";
            if(eventPoints==nullptr){
                std::cout << "@@@@@@ eventPoints is null \n";
            }
            eventPoints->insert(*e2, e2);
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
            auto orderedElements= eventPoints->getInOrderElements();
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
            auto orderedElements= eventPoints->getInOrderElements();
            for(auto elem : orderedElements){
                std::cout << *elem->element() << "\n";
            }
        }
};


#endif //EVENT_QUEUE_H