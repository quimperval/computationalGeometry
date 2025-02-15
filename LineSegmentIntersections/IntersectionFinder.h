#ifndef INTERSECTION_FINDER_H
#define INTERSECTION_FINDER_H

#include "AVL.h"
#include "EventQueue.h"
#include "StatusStructure.h"
#include "point.h"

class IntersectionFinder{
    private:
        
        EventQueue* eventQueue=nullptr;
        StatusStructure* statusStr=nullptr;
        Point* minX = nullptr;
        Point* maxX = nullptr;
    public:

        IntersectionFinder(){
            eventQueue = new EventQueue();
            statusStr = new StatusStructure();
        }

        ~IntersectionFinder(){
            if(eventQueue!=nullptr){
                delete eventQueue;
            }
            if(statusStr!=nullptr){
                delete statusStr;
            }
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

        std::list<Point> findIntersections(){
            std::cout << "########################\n";
            std::cout << "########################\n";
            std::cout << "Finding intersections \n";
            std::cout << "########################\n";
            std::cout << "########################\n";
            std::list<Point> response;
            //Check if the event queue is empty
            if(eventQueue->getEventPointsCount()==0){
                std::cout << "event queue is empty \n";
                return response;
            }

            int counter = 0;

            while(!eventQueue->isEmpty()){
                counter++;
                if(counter>1000){
                    std::cout << "Breaking because of too many iterations during test phase";
                    break;
                }

                //Get the next event point p in the event queue, and delete it. 
                EventPoint* p = eventQueue->getNextEvent();
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
		float minX = eventQueue->getMinX();
		float maxX = eventQueue->getMaxX();

		std::cout << "###### minX: " << minX << std::endl;
		std::cout << "###### maxX: " << maxX << std::endl;

		Point* p1 = new Point(minX-10.0f, p->getY());
		Point* p2 = new Point(maxX+10.0f, p->getY());
		Line* sweepL = new Line(p1,p2);
		//handle event point

                handleEventPoint(p, sweepL);
                
                
            }
            
            return response;
            //
        }

        

    private:
	/*
	 * swl: sweepLine
	 */
        void handleEventPoint(EventPoint* p, Line* swl){

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
	   std::unordered_set<Line, LineHash> unionLpUpCp;
	   std::unordered_set<Line, LineHash> unionLpCp;
	   std::unordered_set<Line, LineHash> unionUpCp;
	   for(auto l : Up){
               std::cout << "Checking line " << l << std::endl;
	       unionLpUpCp.insert(l);
	       unionUpCp.insert(l);
	   }
           for(auto l : Lp){
               unionLpUpCp.insert(l);
	       unionLpCp.insert(l);
	   }

	   for(auto l : Cp){
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
	    }
           for(auto elem : unionLpCp)
	   {
            //Delete the segments in L(p) union C(p) from 
            //the status structure
	    statusStr->removeLine(&elem);
	   }

	   for(auto elem : unionUpCp)
	   {
            //personal comment: first remove them from the status structure, and then reinsert.
            std::cout << "@+@+@+@+@+@+@+@+@+ Status Structure size: " << statusStr->size() << std::endl;
	    statusStr->removeLine(&elem);

            std::cout << "@+@+@+@+@+@+@+@+@+ Status Structure size after removal of element: " << statusStr->size() << std::endl;
            //Insert the seguments that exist in the union of
            //U(p) and C(p) into the status structure, for this is necessary 
            //the sweep line
            //Deleting and re-inserting the segments of C(p) reverses their order
            statusStr->addLine(&elem,swl);
            }

	   if(unionUpCp.size()==0)
	    {
            //If the union of U(p) and C(p) is the empty set
                //Then let sj and sr be the left and right neighbors of p 
               //in the status structure.
               auto sj = statusStr->getSuccesor(*p);
              
                    //Execute the FindNewEvents(sl, sr, p)
	        std::cout << "unionUpCP size is zero" << std::endl;
		if(sj!=nullptr){
		    std::cout << "pointer to sj is not null: " << sj << std::endl;
                    std::cout << "sj is: " << *sj << std::endl;
		}
            }
	    else
	    {
		std::cout << "unionUpCp size is not zero" << std::endl;
                //Else: Let s' be the leftmost segment of U(p) union C(p) 
                //in the status structure
                    //Let sl be the left neighbor of s' in the status structure
                    //Execute FindNewEvents(sl, s', p)
                    //Let s'' be the rightmost segment of the union of U(p)
                    //and C(p) in the status structure.
                    //Let sr be the right neighbor of s'' in the status structure
                    //Execute FindNewEvents(s'', sr, p)

            }
        }
        
};

#endif
