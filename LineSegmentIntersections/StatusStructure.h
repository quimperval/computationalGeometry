#ifndef STATUS_STRUCTURE_H
#define STATUS_STRUCTURE_H


#include "point.h"
#include "Line.h"
#include "LinePtrHash.h"
#include "IntersectionChecker.h"
#include <unordered_set>
#include <list>
#include <map>
#include <memory>

class StatusStructure{
    
    private:
        //iswl: Intersections With Sweep Line
	std::map<Point, std::shared_ptr<Line>> iswl;
	std::map<Line, std::shared_ptr<Point>> mirror;

        IntersectionChecker* checker = new IntersectionChecker();

        //Get a set that contains all the lines 
        //in the status structure
	std::unordered_set<std::shared_ptr<Line>, LinePtrHash, LinePtrEqual> getContent(){
            std::unordered_set<std::shared_ptr<Line>, LinePtrHash,LinePtrEqual> response;
	    if(iswl.empty()){
	        return response;
	    }
	    std::map<Point, std::shared_ptr<Line>>::iterator it;
	    for(it= iswl.begin(); it != iswl.end(); it ++)
	    {
                auto value = (*it).second;
		response.insert(value);
	    }
	    return response;
	}

	

    public:
        StatusStructure(){

        }
        
        ~StatusStructure(){
            //delete iswl;
            //delete checker;
        }
        
	std::shared_ptr<Point> getSwpLineIntersection(std::shared_ptr<Line> l)
	{
	    auto it = mirror.find(*l);
	    if(it!=mirror.end())
	    {
                return it->second;
	    }
            return nullptr;
	}

        void getIntersectionByLine(std::shared_ptr<Line> l)
	{
            auto intersection = mirror.find(*l);
	    std::cout << intersection->first << std::endl;
	}

	int getMirrorSize()
        {
            return mirror.size();
	}

        void updateIntersections(std::shared_ptr<Line> sweepLine){
		std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@\n";
	    std::cout << "@@@@@@@@@@@ updateIntersectionsMethod\n";
            //Use the sweep line to calculate the intersections with the
            //first get the content of the iswl
            std::cout << "Getting in order elements \n";
            auto elements = getContent();
            
            //Clear the iswl
            std::cout << "Clearing iswl \n";
            iswl.clear();
            //for each element that was previously retrieved 
            //calculate the intersection point
            //with the sweep line
            std::cout << "*****************\n";
	    std::cout << "elements: " << elements.size() << std::endl;
            std::cout << "Iterating over all elements \n";
            std::cout << "*****************\n";
            std::cout << "*****************\n";
            
            for(std::shared_ptr<Line> line : elements){
                std::cout << "checking: " << *line << std::endl;
		std::cout << "The sweep line is: " << *sweepLine << std::endl;
                addLine(line, sweepLine);
            }
        }

        void removeLine(std::shared_ptr<Line> toRemove){
	    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	    std::cout << "@@@@@@@@@@ Removing Line@@@@@@\n";
            if(toRemove->getIntersectionwithSweepLine()!=nullptr){
	    auto intersct = toRemove->getIntersectionwithSweepLine();
	    std::cout << *toRemove << " has an interswction with the sweep line " << std::endl;   
	    std::cout << "Interswction: " << intersct << std::endl;
            auto it = iswl.find(*intersct);
	    if(it!=iswl.end())
	    {
                iswl.erase(it);
	    
                toRemove->setIntersectionwithSweepLine(nullptr);
	    }
            }
            
        }

        void addLine(std::shared_ptr<Line> line, std::shared_ptr<Line> sweepLine){
            std::cout << "Add line method\n";
            //Calculate the intersection
            
            std::cout << *line << "\n";
            auto intersection = checker->calculateIntersection(line, sweepLine);
	    std::cout << "Intersection: " << intersection << std::endl;
            if(intersection!=nullptr){
                //Set the intersection in the line
                line->setIntersectionwithSweepLine(intersection);
                std::cout << "Adding line "<< *line << "(" << line<< ") that intersects at " << *intersection << " with " << *sweepLine << std::endl;
                iswl[*intersection]= line;
		mirror[*line]= intersection;
            } else {
		std::cout << "Case intersection is null"<< std::endl ;
                line->setIntersectionwithSweepLine(nullptr);
            }
            
        }
/*
        //Create a method that checks if a Line is stored in the status
        //structure
        bool containsLine(Line* l){
            bool response = false;
            //If the line is in the set of elements contained in the
            //status structure
	    std::unordered_set<Line*, LinePtrHash> content = getContent();
            if( auto search= content.find(l); search!=content.end()){
                std::cout << *l << " is in the status strucrure\n";
	    }
            return false;
        }
*/
        int size(){
            return iswl.size();
        }

	std::shared_ptr<Line> getSuccesor(Point p){
	    auto it = iswl.upper_bound(p);
	    if(it!=iswl.end())
	    {
                return it->second;
	    }
            return nullptr;
	}

	std::shared_ptr<Line> getPredecessor(Point p){
	    auto it = iswl.lower_bound(p);
	    if(it!=iswl.begin())
	    {
                --it;
		return it->second;
	    }
            return nullptr;
	}
	

};

#endif //STATUS_STRUCTURE_H
