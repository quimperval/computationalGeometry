#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <map>
#include <memory>

//#include "BSTNode.h"
//#include "BST.h"
#include "Integer.h"
#include "point.h"
#include "EventPoint.h"
#include "Line.h"
#include "IntersectionFinder.h"
#include "IntersectionChecker.h"
#include "StatusStructure.h"

using::testing::Eq;
using::testing::NotNull;

class LSITesting : public testing::Test{ 
    public:
        /*std::function<bool(const int&, const int&)> intComp = [] (const int&a, const int& b)->bool{
            return a<b;
        };*/
/*
        BSTNode<int, int>* root = new BSTNode<int, int>();
        BST<int, Integer*>* bstForIntInteger = new BST<int, Integer*>();
        Integer* myInt = new Integer(10);
        EventPoint* eventPoint = new EventPoint();
        */
	IntersectionChecker* checker = new IntersectionChecker();
	std::shared_ptr<StatusStructure> sSt = std::make_shared<StatusStructure>(StatusStructure());
        IntersectionFinder finder;
	
};

TEST_F(LSITesting, mapWithPoints){
	std::map<int,Point> points;
	Point p(1,0);
	points[1] =p;
	std::cout << points[1] << std::endl;
	auto p1 = std::make_shared<Point>(points[1]);
	std::cout << "From pointer " << *p1 << std::endl;
	std::cout << "From map again: " << points[1] << std::endl;
	ASSERT_THAT(1, points.size());
        Point p2(2,0); 
	points[2] = p2;
	ASSERT_THAT(2, points.size());

	Point p3(3,0);
	points[3] = p3;

	ASSERT_THAT(3, points.size());
	std::map<int,Point>::iterator it;
	for(it= points.begin(); it!=points.end();it++)
	{
    std::cout << "it: " << (*it).first << ":"<< (*it).second << std::endl;
	}
}

TEST_F(LSITesting, testEventPointGreaterThanTrue){
        EventPoint* e1 = new EventPoint(10,1);
        EventPoint* e2 = new EventPoint(9,1);
        //std::cout << "e1: "<< *e1 << std::endl;
        //std::cout << "e2: "<< *e2 << std::endl;
        bool comparison = *e1>*e2;
	//in this case e2 goes first, as 9 is less than 10.
	//Then it will be analyzed first, from left to right
        ASSERT_THAT(comparison,false);
}

TEST_F(LSITesting, testCreateLine){
        
	std::shared_ptr<Line> line= std::make_shared<Line>(Line(std::make_shared<Point>(Point(25.0, 38.0)),std::make_shared<Point>( Point(40.75, 66.25))));
        //std::cout << *line << "\n";
        

	std::shared_ptr<Line> line2= std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, 0)),std::make_shared<Point>( Point(100, 100))));
        //std::cout << *line2 << "\n";
        

        //ASSERT_THAT(*line,NotNull());
        IntersectionFinder* finder = new IntersectionFinder();
        ASSERT_THAT(finder, NotNull());
        finder->addLine(line);
        finder->addLine(line2);
        //std::cout << "event point queue size: " << finder->getEventPointsCount() << "\n";
        ASSERT_THAT(4, finder->getEventPointsCount());

        //std::cout << *(finder->getMaxEventPoint()) << "\n";
        //std::cout << "Max is: " << *(finder->getMaxEventPoint())<<"\n";
        //finder->printEventPointsOrdered();
        auto nextEvent = finder->getNextEvent();
        std::cout << *nextEvent << "\n";
        //finder->printEventPointsOrdered();
}

TEST_F(LSITesting, testTwoEqualPoint){
	std::shared_ptr<Line> line= std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, 0)), std::make_shared<Point>(Point(40.75, 66.25))));
        //std::cout << *line << "\n";
        

	std::shared_ptr<Line> line2 = std::make_shared<Line>(Line(std::make_shared<Point>( Point(0, 0)), std::make_shared<Point>(Point(100, 100))));
        //std::cout << *line2 << "\n";
        

	std::shared_ptr<Line> line3 = std::make_shared<Line>(Line(std::make_shared<Point>( Point(2, 35)), std::make_shared<Point>(Point(25, 13))));
        //std::cout << *line3 << "\n";


        IntersectionFinder* finder = new IntersectionFinder();
        ASSERT_THAT(finder, NotNull());
        finder->addLine(line);
        //std::cout << "##########################################\n";
        //std::cout << "Printing points after insertion of line 1\n";
        //std::cout << "##########################################\n";
        //finder->printEventPointsOrdered();
        
        finder->addLine(line2);
        
        //std::cout << "event point queue size: " << finder->getEventPointsCount() << "\n";
        ASSERT_THAT(3, finder->getEventPointsCount());

        //std::cout << *(finder->getMaxEventPoint()) << "\n";
        //std::cout << "Max is: " << *(finder->getMaxEventPoint())<<"\n";
        //finder->printEventPointsOrdered();
        auto nextEvent = finder->getNextEvent();
        //std::cout << *nextEvent << "\n";
        //finder->printEventPointsOrdered();
        ASSERT_THAT(2,finder->getEventPointsCount());
	delete finder;
}

TEST_F(LSITesting, testThreeLines){
        
	std::shared_ptr<Line> line = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, 0)), std::make_shared<Point>(Point(40.75, 66.25))));
        //std::cout << *line << "\n";
        

	std::shared_ptr<Line> line2= std::make_shared<Line>(Line(std::make_shared<Point>( Point(0, 0)), std::make_shared<Point>(Point(100, 100))));
        //std::cout << *line2 << "\n";
        

	std::shared_ptr<Line> line3= std::make_shared<Line>(Line(std::make_shared<Point>( Point(2, 35)), std::make_shared<Point>( Point(25, 13))));
        //std::cout << *line3 << "\n";

        IntersectionFinder* finder = new IntersectionFinder();
        ASSERT_THAT(finder, NotNull());
        finder->addLine(line);
        //std::cout << "##########################################\n";
        //std::cout << "Printing points after insertion of line 1\n";
        //std::cout << "##########################################\n";
        //finder->printEventPointsOrdered();
        
        finder->addLine(line2);
        //std::cout << "##########################################\n";
        //std::cout << "Printing points after insertion of line 1\n";
        //std::cout << "##########################################\n";
        //finder->printEventPointsOrdered();
        finder->addLine(line3);
        //std::cout << "event point queue size: " << finder->getEventPointsCount() << "\n";
        ASSERT_THAT(5, finder->getEventPointsCount());

        //std::cout << *(finder->getMaxEventPoint()) << "\n";
        //std::cout << "Max is: " << *(finder->getMaxEventPoint())<<"\n";
        //finder->printEventPointsOrdered();
        auto nextEvent = finder->getNextEvent();
        //std::cout << *nextEvent << "\n";
        //finder->printEventPointsOrdered();
        ASSERT_THAT(4,finder->getEventPointsCount());
	delete finder;
}

TEST_F(LSITesting, testIntersectionExists0){
        ASSERT_THAT(checker,NotNull());
	std::shared_ptr<Line>  line1 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, 0)), std::make_shared<Point>(Point(10, 10))));
        std::shared_ptr<Line> line2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, -1)), std::make_shared<Point>(Point(10, -10))));

        ASSERT_FALSE(checker->existIntersection(line1,line2));
        ASSERT_FALSE(checker->existIntersection(line2,line1));
}

/*

TEST_F(LSITesting, testIntersectionExists1){
        ASSERT_THAT(checker,NotNull());
        Line* line1 = new Line(new Point(0, 0), new Point(10, 10));
        Line* line2 = new Line(new Point(0, 10), new Point(10, 0));

        ASSERT_TRUE(checker->existIntersection(line1,line2));
        ASSERT_TRUE(checker->existIntersection(line2,line1));
}
*/

TEST_F(LSITesting, testIntersectionExists2){
        ASSERT_THAT(checker,NotNull());
	std::shared_ptr<Line> line1 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, 0)), std::make_shared<Point>(Point(0, 10))));
	std::shared_ptr<Line> line2 = std::make_shared<Line>(Line( std::make_shared<Point>(Point(1, 0)), std::make_shared<Point>(Point(1, 10))));

        ASSERT_FALSE(checker->existIntersection(line1,line2));
}

TEST_F(LSITesting, testIntersectionExists3){
        ASSERT_THAT(checker,NotNull());
	std::shared_ptr<Line> line1 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, 10)), std::make_shared<Point>(Point(0, 0))));
	std::shared_ptr<Line> line2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(1,10)),std::make_shared<Point>(Point(1, 0))));

        ASSERT_FALSE(checker->existIntersection(line1,line2));
}

TEST_F(LSITesting, testIntersectionWithSweepLine0){
	//std::cout << "testIntersectionWithSweepLine0\n";
	ASSERT_THAT(checker,NotNull());
	std::shared_ptr<Line> line1 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(1, 1)), std::make_shared<Point>(Point(4, 4))));
	std::shared_ptr<Line> line2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(1, 8)), std::make_shared<Point>(Point(2, 4))));
        //Intersection at 1,0
	std::shared_ptr<Point> mInter = checker->calculateIntersection(line1, line2);
	//std::cout << mInter << std::endl;
        ASSERT_TRUE(mInter == nullptr);
        
}

TEST_F(LSITesting, testIntersectionWithSweepLine1){
	std::shared_ptr<Line> line1 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, 0)), std::make_shared<Point>(Point(50, 0))));
	std::shared_ptr<Line> line2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(1, 10)), std::make_shared<Point>( Point(1, -1))));
        //Intersection at 1,0
	std::shared_ptr<Point> mInter = checker->calculateIntersection(line1, line2);
        ASSERT_THAT(mInter, NotNull());
        ASSERT_THAT(1, mInter->getX());
        ASSERT_THAT(0, mInter->getY());
}

TEST_F(LSITesting, testIntersectionWithSweepLine2){
        ASSERT_THAT(checker,NotNull());
	std::shared_ptr<Line> line1 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, 0)), std::make_shared<Point>(Point(0, 50))));
	std::shared_ptr<Line> line2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(1, 10)), std::make_shared<Point>(Point(1, -1))));
	std::shared_ptr<Point> mInter = checker->calculateIntersection(line1, line2);
        ASSERT_TRUE(mInter == nullptr);
}


TEST_F(LSITesting, testIntersectionWithSweepLine3){
	std::shared_ptr<Line> line2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(1, 8)), std::make_shared<Point>(Point(2, 4))));
	std::shared_ptr<Line> swp2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0,1)), std::make_shared<Point>(Point(6,0))));

	std::shared_ptr<Point> mInter = checker->calculateIntersection(line2, swp2);
        //std::cout << "mInter: " << *mInter << std::endl;
        ASSERT_TRUE(mInter == nullptr);
}


TEST_F(LSITesting, testStatusStructure0){
	std::cout << "test Status Structure0" << std::endl;
	std::shared_ptr<Line> sweepLine = std::make_shared<Line>(Line(std::make_shared<Point>(Point(1, 1)), std::make_shared<Point>(Point(4, 4))));
	std::shared_ptr<Line> line2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(1, 8)), std::make_shared<Point>(Point(2, 4))));
        //Intersection at 1,0
        ASSERT_THAT(0, sSt->size());
        //Add one line
        std::cout << "Sweep line: " << *sweepLine << std::endl;
        sSt->addLine(line2, sweepLine);
	std::cout << "testint sst size equal to 1" << std::endl;
        ASSERT_THAT(0, sSt->size());
	ASSERT_THAT(0, sSt->getMirrorSize());
        sweepLine = std::make_shared<Line>(Line(std::make_shared<Point>(Point(1, 2)), std::make_shared<Point>( Point(4, 2))));
        //std::cout << "Sweep line: " << *sweepLine << std::endl;
        sSt->updateIntersections(sweepLine);
	std::cout << "sst size"  << std::endl;
        ASSERT_THAT(0, sSt->size());
	std::shared_ptr<Line> swp2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0,1)), std::make_shared<Point>(Point(6,0))));
	sSt->updateIntersections(swp2);
	std::cout << "Testing sst size:"  << std::endl;
	ASSERT_THAT(0, sSt->size());
}

TEST_F(LSITesting, testWithEmptyEventQueue){
        //std::cout << "#######################################\n";
        //std::cout << "#######################################\n";
        //std::cout << "Testing emtpy event queue\n";
        //std::cout << "#######################################\n";
        //std::cout << "#######################################\n";
	std::shared_ptr<Line> line1 = std::make_shared<Line>(std::make_shared<Point>(Point(0, 0)), std::make_shared<Point>(Point(2, 2)));
	std::shared_ptr<Line> line2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, 2)), std::make_shared<Point>(Point(2, 0))));
        auto intersections = finder.findIntersections();

        ASSERT_THAT(0, intersections.size());
}

TEST_F(LSITesting, testEventPointOrder)
{
    EventPoint ep1(0,0);

    EventPoint ep2(0,2);
    ASSERT_TRUE( ep1 < ep2);

    EventPoint ep3(1,3);
    EventPoint ep4(4,3);

    ASSERT_TRUE( ep3 > ep4);

    std::map<EventPoint, EventPoint> mmap;
    mmap[ep1] = ep1;

    mmap[ep4] = ep4;
    mmap[ep2] = ep2;
    mmap[ep3] = ep3;
    for ( auto it= mmap.begin(); it!=mmap.end(); it++)
    {
        std::cout << it->first << std::endl;
    }
}

TEST_F(LSITesting, testIntersections1Line){
        std::cout << "#######################################\n";
        std::cout << "#######################################\n";
        std::cout << "Testing 1 line intersections\n";
        std::cout << "#######################################\n";
        std::cout << "#######################################\n";
        ASSERT_THAT(checker,NotNull());
        

	std::shared_ptr<Line> line1 = std::make_shared<Line>(std::make_shared<Point>(Point(0, 0)), std::make_shared<Point>(Point(2, 2)));
	std::cout << " Line 1 is :" << *line1 << std::endl;

	std::shared_ptr<Line> line2 = std::make_shared<Line>(Line(std::make_shared<Point>(Point(0, 2)), std::make_shared<Point>(Point(2, 0))));
        std::cout << " Line 2 is: " << *line2 << std::endl;
        finder.addLine(line1);
	finder.addLine(line2);
	finder.printEventPointsOrdered();
	auto intersections = finder.findIntersections();
	std::cout << "Intersections size: " << intersections.size() << std::endl;
        //finder.addLine(line1);
        ASSERT_THAT(1, intersections.size());
	for( auto item : intersections)
	{
            std::cout << "intersection: " << item << std::endl;
	}
}
/*
TEST_F(LSITesting, testIntersections2Lines){
        std::cout << "#######################################\n";
        std::cout << "#######################################\n";
        std::cout << "Testing intersection between 2 lines\n";
        std::cout << "#######################################\n";
        std::cout << "#######################################\n";
        Line* line1 = new Line(new Point(0, 0), new Point(50, 0));
        Line* line2 = new Line(new Point(1, 10), new Point(1, -1));
        //Intersection is expected at 1,0        
	std::cout << "Adding line1" << std::endl;
        finder.addLine(line1);
	std::cout << "Adding lin2" << std::endl;
	finder.addLine(line2);
        std::list<Point*>* intersections = finder.findIntersections();
        if(intersections==nullptr)
	{
            std::cout << "intersections is null\n";
	}

	ASSERT_THAT(1, intersections->size());
}

TEST_F(LSITesting, testEventPointLessThanFalse){
        ASSERT_THAT(eventPoint,NotNull());
}

TEST_F(LSITesting, testEventPointEqualTrue){
        ASSERT_THAT(eventPoint,NotNull());
}

TEST_F(LSITesting, testEventPointEqualFalse){
        ASSERT_THAT(eventPoint,NotNull());
}

TEST_F(LSITesting, testOneEqualsOne){
        ASSERT_THAT(10,testing::Eq(10));
}*/


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
