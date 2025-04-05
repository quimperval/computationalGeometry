#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H


#include "EventPoint.h"
#include <map>
#include <list>

class EventQueue{
    private: 
	std::map<Point, std::shared_ptr<EventPoint>> eventPoints;
        float minX = 0;
	float maxX = 0;
    public: 
        EventQueue(){
           
        }
        ~EventQueue(){
            
        }
        
        bool insertEvent(std::shared_ptr<EventPoint> ep){
            //TODO
		std::cout << "insert Event is not yet implemented" << std::endl;

	    Point p (ep->getX(), ep->getY());
	    auto it = eventPoints.find(p);
	    if(it == eventPoints.end())
	    {
                eventPoints[p] = ep;
	    }
            return false;
        }

	std::shared_ptr<EventPoint> getNextEvent(){
		//add a call to the end method of the map
            auto maxPair =  eventPoints.rbegin();
	    std::shared_ptr<EventPoint> e = maxPair->second;
            eventPoints.erase(maxPair->first);
            return e;
        }

        void addLine(Line line){
            /**/
            //std::cout << "Adding line "<< *line << "\n";
            Point p1 = *(line.getP1());
	    std::shared_ptr<EventPoint> e1 = std::make_shared<EventPoint>(EventPoint(p1));
            //std::cout << "Adding p1 "<< *p1 << "\n";
    
            //std::cout << "@@@@@@ Trying to add " << *e1 << "\n";
            //find by id in the map, by using p1
	    std::shared_ptr<EventPoint> e1Temp = nullptr;
	    auto it = eventPoints.find(p1);
	    if(it != eventPoints.end())
	    {
                e1Temp = it->second;
	    }
	    
            if(e1Temp!=nullptr){
                std::cout<< "The point e1 is already in the event queue\n";
                e1 = e1Temp;
                e1Temp= nullptr;
            } else {
                eventPoints[p1] = e1;
            }
            
            setMinAndMaxX(std::make_shared<EventPoint>(p1));
        
            Point p2 = *(line.getP2());
	    std::shared_ptr<EventPoint> e2 = std::make_shared<EventPoint>(EventPoint(p2));
            
	    //std::cout << "Adding p2 "<< *p2 << "\n";

            //std::cout << "@@@@@@ Trying to add " << *e2 << "\n";
	    std::shared_ptr<EventPoint> e2Temp = nullptr;
	    //find by id in the map, by using p2
	    auto it2 = eventPoints.find(p2);
	    if(it2!= eventPoints.end())
	    {
                e2Temp = it2->second;
	    }

            if(e2Temp!=nullptr){
                //std::cout<< "The point e2 is already in the event queue\n";
                e2 = e2Temp;
                e2Temp= nullptr;
            } else {
                eventPoints[p2] = e2;
            }
       
            setMinAndMaxX(std::make_shared<Point>(p2));

            //std::cout << "Printing event queue\n";
            //eventPoints->print();
           
                    
            //if the p1.y is greater than the p2.y, then add the line to the list of linesStartingAtEventPoint of p1. 
            if(p1.getY()>p2.getY()){
                e1->addLineToListStartingAtEventPoint(line);
                //and therefore add the line to the list of linesEndingAtEventPoint of p2
                e2->addLineToListEndingAtEventPoint(line);
            }else if (p1.getY()<p2.getY()){
                //if the p2.y is greater than the p1.y then add the line to the list of linesStartingAtEventPoint of p2. 
                e2->addLineToListStartingAtEventPoint(line);
                //and therefore add the line to the list of linesEndingAtEventPoint of p2
                e1->addLineToListEndingAtEventPoint(line);
            } else if (p1.getY()==p2.getY()){
                //if both p2.y and p1.y are equal
                if(p1.getX()<p2.getX()){
                    //if p1.x is lower than p2.x then add the line to the list of linesStartingAtEventPoint of p1.
                    e1->addLineToListStartingAtEventPoint(line);
                    //and therefore add the line to the list of linesEndingAtEventPoint of p2
                    e2->addLineToListEndingAtEventPoint(line);
                } else if(p1.getX()>p2.getX()) {
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

        void setMinAndMaxX(std::shared_ptr<Point> p)
	{
		std::cout<< "Setting min and max based on: " << *p << std::endl;
	

		    std::cout << "Current minX: " << minX << std::endl;
                    if(minX > p->getX())
		    {
                        minX = p->getX();
		    }


		    std::cout << "Current maxX: " << maxX << std::endl;
                    if(maxX < p->getX())
		    {
                        maxX = p->getX();
		    }

	}

	void printEventPointsOrdered(){
            std::cout << "printEventPointsOrdered\n";
            auto orderedElements= getInOrderElements();
            for(auto elem : orderedElements){
                std::cout << *elem << "\n";
                //For each event point print the lines starting at

                //For each event point print the lines ending at
            }
        }

        int getEventPointsCount(){
            return eventPoints.size();
        }

	std::shared_ptr<EventPoint> getMaxEventPoint(){
            return eventPoints.rbegin()->second;
        }

        void printEventPointsOrdered() const{
            std::cout << "printEventPointsOrdered\n";
            auto orderedElements = getInOrderElements();
            for(auto elem : orderedElements){
                std::cout << *elem << "\n";
            }
        }

        bool isEmpty(){
            return eventPoints.empty();
        }

	float getMinX()
	{
	    return minX;
	}

	float getMaxX()
	{
            return maxX;
	}
	std::list<std::shared_ptr<EventPoint>> getInOrderElements() const
	{
            std::list<std::shared_ptr<EventPoint>> response;
            for(auto it= eventPoints.begin(); it!=eventPoints.end();it++)
	    {
	        std::cout << "it: " << (*it).first << ":"<< (*it).second << std::endl;
		response.push_back(it->second);
	    }

	    return response;
	}

};


#endif //EVENT_QUEUE_H
