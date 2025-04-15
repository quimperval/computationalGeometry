#ifndef INTERSECTION_FINDER_H
#define INTERSECTION_FINDER_H

#include "EventQueue.h"
#include "StatusStructure.h"
#include "point.h"
#include "IntersectionChecker.h"

class IntersectionFinder{
    private:
        
        EventQueue eventQueue;
        StatusStructure statusStr;
        Point* minX = nullptr;
        Point* maxX = nullptr;
	IntersectionChecker checker;
	
    public:

        IntersectionFinder(){
        }

        ~IntersectionFinder(){
        }

        void addLine(std::shared_ptr<Line> line){
            eventQueue.addLine(line);
        }

        int getEventPointsCount(){
            return eventQueue.getEventPointsCount();
        }

	std::shared_ptr<EventPoint> getMaxEventPoint(){
            return eventQueue.getMaxEventPoint();
        }

        void printEventPointsOrdered() const{
            
            eventQueue.printEventPointsOrdered();
            
        }

	std::shared_ptr<EventPoint> getNextEvent(){
            return eventQueue.getNextEvent();
        }

        std::list<std::shared_ptr<Point>> findIntersections(){
            std::cout << "########################\n";
            std::cout << "########################\n";
            std::cout << "Finding intersections \n";
            std::cout << "########################\n";
            std::cout << "########################\n";
            std::list<std::shared_ptr<Point>> response;
            //Check if the event queue is empty
            if(eventQueue.getEventPointsCount()==0){
                std::cout << "event queue is empty \n";
                return response;
            }

            int counter = 0;

            while(!eventQueue.isEmpty()){
                counter++;
                if(counter>1000){
                    std::cout << "Breaking because of too many iterations during test phase";
                    break;
                }

                //Get the next event point p in the event queue, and delete it. 
		std::shared_ptr<EventPoint> p = eventQueue.getNextEvent();
                if(p==nullptr){
                    std::cout << "unhandle case for nullpointer\n";
                    continue;
                }

                std::cout << "Next point not null\n";
                //std::cout << nextPoint->elem();
        	std::cout << "**********" << std::endl;
		std::cout << "Processing point " << *p << std::endl;
                //TO-DO: print the lines associated to the event point  
		std::cout << "**********" << std::endl;
                //Create a temp sweep line basedon the event poin. Take its ycoordinate, and take the max a min x of all the event points.
		float minX = eventQueue.getMinX();
		float maxX = eventQueue.getMaxX();

		std::cout << "###### minX: " << minX << std::endl;
		std::cout << "###### maxX: " << maxX << std::endl;

		std::shared_ptr<Point> p1 = std::make_shared<Point>(Point(minX-10.0f, p->getY()));
		std::shared_ptr<Point> p2 = std::make_shared<Point>(Point(maxX+10.0f, p->getY()));
		std::shared_ptr<Line> sweepL = std::make_shared<Line>(Line(p1,p2));
		//handle event point

                handleEventPoint(p, sweepL, response);
                
                
            }
	    std::cout << "@@@@@@@@@@@@@" << std::endl;
            std::cout << " returning response with size: " << response.size() << std::endl; 
            return response;
            //
        }

       

    private:
	/*
	 * swl: sweepLine
	 */
        void handleEventPoint(std::shared_ptr<EventPoint> p, std::shared_ptr<Line> swl, std::list<std::shared_ptr<Point>>& intersections){
            std::cout << " Handle event Point " << *p << std::endl;
            //Find all segments stored in the status structure
            //that contain p
	    //U(p)
	    //Get the segments whose upper endpoint is p
            auto Up = p->getLinesStartingAt(); 
	    std::cout << "Count of lines starting at: " << Up.size() << std::endl;

            //L(p) the subset of segments found whose 
            //lower endpoint is p
	    auto Lp = p->getLinesEndingAt();
	    std::cout << "Count of lines ending at: " << Lp.size() << std::endl;

            //C(p) the subset of segments found that contain
            //in their interior
	    auto Cp = p->getLinesWithPointInItsInterior();
            std::cout << "Count of lines with P in its interior: " << Cp.size() << std::endl;

            //Get the union of L(p), U(p), C(p)
	    //i.e. the lines that are on the three sets
	   std::unordered_set<std::shared_ptr<Line>, LinePtrHash> unionLpUpCp;
	   std::unordered_set<std::shared_ptr<Line>, LinePtrHash> unionLpCp;
	   std::unordered_set<std::shared_ptr<Line>, LinePtrHash> unionUpCp;
	   for(auto l : Up){
               std::cout << "Checking line " << l << " and adding yo unionLpUpCp " << std::endl;
	       unionLpUpCp.insert(l);
	       unionUpCp.insert(l);
	   }
           for(auto l : Lp){
	
               std::cout << "Checking line " << l << " and adding yo unionLpUpCp and to unionLpCp " << std::endl;
               unionLpUpCp.insert(l);
	       unionLpCp.insert(l);
	   }

	   for(auto l : Cp){
               std::cout << "Checking line " << l << " and adding yo unionLpUpCp and to unionLpCp and to unionUpCp" << std::endl;
               unionLpUpCp.insert(l);
	       unionLpCp.insert(l);
	       unionUpCp.insert(l);
	    }

            std::cout << "Size of unionLpLpCp is: " << unionLpUpCp.size() << std::endl;
            //If the union contains more than one segment
	    if(unionLpUpCp.size()>1){


                //Then report p as an intersection, together with L(p), 
                //U(p) and C(p)
		    std::cout << *p << " is an intersection" << std::endl;
		    std::shared_ptr<Point> ip = std::make_shared<Point>(Point());
		    ip->setX(p->getX());
		    ip->setY(p->getY());
		    intersections.push_back(ip);
		    std::cout << "Intersections size: " << intersections.size() << std::endl;
		    
	    }
           for(auto elem : unionLpCp)
	   {
            //Delete the segments in L(p) union C(p) from 
            //the status structure
	       statusStr.removeLine(elem);
	   }
           
	   std::shared_ptr<Line> lmostLine = nullptr;
	   std::shared_ptr<Line> rmostLine = nullptr;

	   std::shared_ptr<Point> lmost= nullptr;
	   std::shared_ptr<Point> rmost = nullptr;

	   for(auto elem : unionUpCp)
	   {
            //personal comment: first remove them from the status structure, and then reinsert.
            std::cout << "@+@+@+@+@+@+@+@+@+ Status Structure size: " << statusStr.size() << std::endl;
	    std::cout << " Removing "<< *elem << std::endl;
	    statusStr.removeLine(elem);

            std::cout << "@+@+@+@+@+@+@+@+@+ Status Structure size after removal of element: " << statusStr.size() << std::endl;
            //Insert the seguments that exist in the union of
            //U(p) and C(p) into the status structure, for this is necessary 
            //the sweep line
            //Deleting and re-inserting the segments of C(p) reverses their order
	    std::cout << "Trying to add " << *elem << " to the status structure  based on the swl :" << *swl << std::endl;
            statusStr.addLine(elem,swl);
	    auto swlInt = statusStr.getSwpLineIntersection(elem);           
	    std::cout << "Line intersection: " << *swlInt << std::endl;
	    //check if the swlInt is min than the current min
	    //if yes, set it as min

	    if(lmost==nullptr)
	    {
                lmost= swlInt;
		lmostLine= elem;
	    }else if(*swlInt < *lmost)
	    {
                lmost = swlInt;
		lmostLine = elem;
	    }

	    //check if the swlInt is greater than the current max.
	    //if yes, then set it as the max.
	    if(rmost==nullptr)
	    {
                rmost = swlInt;
		rmostLine = elem;
	    } else if(*swlInt > *rmost)
	    {
                rmost = swlInt;
		rmostLine = elem;
	    }

	   }

	   if(unionUpCp.size()==0)
	    {
            //If the union of U(p) and C(p) is the empty set
                //Then let sj and sr be the left and right neighbors of p 
               //in the status structure.
               auto sj = statusStr.getSuccesor(*p);
              
                    //Execute the FindNewEvents(sl, sr, p)
	        std::cout << "unionUpCP size is zero" << std::endl;
		if(sj!=nullptr){
		    std::cout << "pointer to sj is not null: " << sj << std::endl;
                    std::cout << "sj is: " << *sj << std::endl;
		}

		auto sr = statusStr.getPredecessor(*p);
		if(sr!=nullptr)
		{
                    std::cout << "Pointer to sr is not null: " << sr << std::endl;
		    std::cout << "sr is: " << *sr << std::endl;
		}else
		{
                    std::cout << "Pointer to sr is null\n" ;
		}

		if(sr!=nullptr && sj!=nullptr)
		{
                    std::cout << "Calling FindNewEvents" << std::endl;
		}else{
                    std::cout << "Not Calling FindNewEvents\n"; 
		}

            }
	    else
	    {
		std::cout << "unionUpCp size is not zero" << std::endl;
                //Else: Let s' be the leftmost segment of U(p) union C(p) 
                //in the status structure
		std::shared_ptr<Line> sprime = lmostLine;

                    //Let sl be the left neighbor of s' in the status structure
                    std::shared_ptr<Line> sl = statusStr.getPredecessor(*lmost);
		    //Execute FindNewEvents(sl, s', p)
		if(sprime!=nullptr && sl!=nullptr)
		{
                    std::cout << "Calling FindnewEvents for sl, s', p"<< std::endl;
		    findNewEvent(sl, sprime, p, swl);
		}
                    //Let s'' be the rightmost segment of the union of U(p)
                    //and C(p) in the status structure.
		std::shared_ptr<Line> sbiprime = rmostLine;
                    //Let sr be the right neighbor of s'' in the status structure
                std::shared_ptr<Line> sr = statusStr.getSuccesor(*rmost);
		    //Execute FindNewEvents(s'', sr, p)
		if(sbiprime!=nullptr && sr!=nullptr)
		{
                    std::cout << "Calling FindNewEvents for sr, s', p" << std::endl;
		    findNewEvent(sr, sbiprime, p, swl);
		}

            }
	    std::cout << "Intersections size: " << intersections.size() << std::endl;
        }

	void findNewEvent(std::shared_ptr<Line> sl, std::shared_ptr<Line> sr, std::shared_ptr<Point> p, std::shared_ptr<Line> swl){
	    std::cout << "Find new event: " << std::endl;
	    std::cout << "sl is: " << *sl << std::endl;

	    std::cout << "sr is: " << *sr << std::endl;
            if(checker.existIntersection(sl,sr)){
		std::cout << "There exists an intersection" << std::endl;
	        auto intsct = checker.calculateIntersection(sl,sr);
		bool toBeAdded = false;
		if(checker.isPointBelowLine(intsct,swl))
		{
		    std::cout << "The point is below the swl or is in the swl" << std::endl;
		    toBeAdded = true;
		}else if ( checker.isPointInLine(intsct, swl)){
		    std::cout << "The point is over the sweep linr" << std::endl;
                        if(intsct->getX() > p->getX())
			{
			    toBeAdded = true;
			}
		}
	       if(toBeAdded)
	       {
			std::cout << "The intersection is to the right of p " << std::endl;
			std::shared_ptr<EventPoint> ep = std::make_shared<EventPoint>(EventPoint(intsct->getX(), intsct->getY()));
                        ep->addLineToListWithEventPointInItsInterior(*sl);
			ep->addLineToListWithEventPointInItsInterior(*sr);
			eventQueue.insertEvent(ep); 
			
		}
	    }else 
	    {
                std::cout << " There is no intersection? " << std::endl;
	    }
	}

};

#endif
