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

		std::cout << "**********" << std::endl;
                //handle event point
                handleEventPoint(p);
                
                
            }
            
            return response;
            //
        }

        

    private:
        void handleEventPoint(EventPoint* p){

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
	   for(auto l : Up){
               std::cout << "Checking line " << l << std::endl;
	       unionLpUpCp.insert(l);
	   }
           for(auto l : Lp){
               unionLpUpCp.insert(l);
	   }

	   for(auto l : Cp){
               unionLpUpCp.insert(l);
	    }

            std::cout << "Size of unionLpLpCp is: " << unionLpUpCp.size() << std::endl;
            //If the union contains more than one segment
	    if(unionLpUpCp.size()>1){


                //Then report p as an intersection, together with L(p), 
                //U(p) and C(p)
	    }
            
            //Delete the segments in L(p) union C(p) from 
            //the status structure

            //Insert the seguments that exist in the union of
            //U(p) and C(p) into the status structure, for this is necessary 
            //the sweep line
            //Deleting and re-inserting the segments of C(p) reverses their order

            //If the union of U(p) and C(p) is the empty set
                //Then let sj and sr be the left and right neighbors of p 
               //in the status structure.
                    //Execute the FindNewEvents(sl, sr, p)
                //Else: Let s' be the leftmost segment of U(p) union C(p) 
                //in the status structure
                    //Let sl be the left neighbor of s' in the status structure
                    //Execute FindNewEvents(sl, s', p)
                    //Let s'' be the rightmost segment of the union of U(p)
                    //and C(p) in the status structure.
                    //Let sr be the right neighbor of s'' in the status structure
                    //Execute FindNewEvents(s'', sr, p)


        }
        
};

#endif
