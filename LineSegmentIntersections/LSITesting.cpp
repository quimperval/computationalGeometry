#include <gmock/gmock.h>

#include "BSTNode.h"
#include "BST.h"
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

        /*BSTNode<int, int>* root = new BSTNode<int, int>();*/
        BST<int, Integer*>* bstForIntInteger = new BST<int, Integer*>();
        Integer* myInt = new Integer(10);
        EventPoint* eventPoint = new EventPoint();
        IntersectionChecker* checker = new IntersectionChecker();
        StatusStructure* sSt = new StatusStructure();
        IntersectionFinder finder;
};

TEST_F(LSITesting, testEventPointNotNull){
        ASSERT_THAT(eventPoint,NotNull());
}

TEST_F(LSITesting, testEventPointGreaterThanTrue){
        EventPoint* e1 = new EventPoint(10,1);
        EventPoint* e2 = new EventPoint(9,1);
        //std::cout << "e1: "<< *e1 << std::endl;
        //std::cout << "e2: "<< *e2 << std::endl;
        bool comparison = *e1>*e2;
        ASSERT_THAT(comparison,true);
}

TEST_F(LSITesting, testCreateLine){
        /*
        25.0000;38.0000
        40.7500;66.2500
        */
        Line* line = new Line(new Point(25.0, 38.0), new Point(40.75, 66.25));
        std::cout << *line << "\n";
        

        Line* line2 = new Line(new Point(0, 0), new Point(100, 100));
        std::cout << *line2 << "\n";
        

        ASSERT_THAT(line,NotNull());
        IntersectionFinder* finder = new IntersectionFinder();
        ASSERT_THAT(finder, NotNull());
        finder->addLine(line);
        finder->addLine(line2);
        std::cout << "event point queue size: " << finder->getEventPointsCount() << "\n";
        ASSERT_THAT(4, finder->getEventPointsCount());

        std::cout << *(finder->getMaxEventPoint()) << "\n";
        std::cout << "Max is: " << *(finder->getMaxEventPoint())<<"\n";
        finder->printEventPointsOrdered();
        auto nextEvent = finder->getNextEvent();
        std::cout << *nextEvent << "\n";
        finder->printEventPointsOrdered();
}

TEST_F(LSITesting, testTwoEqualPoints){
        /*
        25.0000;38.0000
        40.7500;66.2500
        */
        Line* line = new Line(new Point(0, 0), new Point(40.75, 66.25));
        std::cout << *line << "\n";
        

        Line* line2 = new Line(new Point(0, 0), new Point(100, 100));
        std::cout << *line2 << "\n";
        

        Line* line3 = new Line(new Point(2, 35), new Point(25, 13));
        std::cout << *line3 << "\n";


        ASSERT_THAT(line,NotNull());
        IntersectionFinder* finder = new IntersectionFinder();
        ASSERT_THAT(finder, NotNull());
        finder->addLine(line);
        std::cout << "##########################################\n";
        std::cout << "Printing points after insertion of line 1\n";
        std::cout << "##########################################\n";
        finder->printEventPointsOrdered();
        
        finder->addLine(line2);
        
        std::cout << "event point queue size: " << finder->getEventPointsCount() << "\n";
        ASSERT_THAT(3, finder->getEventPointsCount());

        std::cout << *(finder->getMaxEventPoint()) << "\n";
        std::cout << "Max is: " << *(finder->getMaxEventPoint())<<"\n";
        finder->printEventPointsOrdered();
        auto nextEvent = finder->getNextEvent();
        std::cout << *nextEvent << "\n";
        finder->printEventPointsOrdered();
        ASSERT_THAT(2,finder->getEventPointsCount());
}

TEST_F(LSITesting, testThreeLines){
        /*
        25.0000;38.0000
        40.7500;66.2500
        */
        Line* line = new Line(new Point(0, 0), new Point(40.75, 66.25));
        std::cout << *line << "\n";
        

        Line* line2 = new Line(new Point(0, 0), new Point(100, 100));
        std::cout << *line2 << "\n";
        

        Line* line3 = new Line(new Point(2, 35), new Point(25, 13));
        std::cout << *line3 << "\n";


        ASSERT_THAT(line,NotNull());
        IntersectionFinder* finder = new IntersectionFinder();
        ASSERT_THAT(finder, NotNull());
        finder->addLine(line);
        std::cout << "##########################################\n";
        std::cout << "Printing points after insertion of line 1\n";
        std::cout << "##########################################\n";
        finder->printEventPointsOrdered();
        
        finder->addLine(line2);
        std::cout << "##########################################\n";
        std::cout << "Printing points after insertion of line 1\n";
        std::cout << "##########################################\n";
        finder->printEventPointsOrdered();
        finder->addLine(line3);
        std::cout << "event point queue size: " << finder->getEventPointsCount() << "\n";
        ASSERT_THAT(5, finder->getEventPointsCount());

        std::cout << *(finder->getMaxEventPoint()) << "\n";
        std::cout << "Max is: " << *(finder->getMaxEventPoint())<<"\n";
        finder->printEventPointsOrdered();
        auto nextEvent = finder->getNextEvent();
        std::cout << *nextEvent << "\n";
        finder->printEventPointsOrdered();
        ASSERT_THAT(4,finder->getEventPointsCount());
}

TEST_F(LSITesting, testIntersectionExists0){
        ASSERT_THAT(checker,NotNull());
        Line* line1 = new Line(new Point(0, 0), new Point(10, 10));
        Line* line2 = new Line(new Point(0, -1), new Point(10, -10));

        ASSERT_FALSE(checker->existIntersection(line1,line2));
        ASSERT_FALSE(checker->existIntersection(line2,line1));
}

TEST_F(LSITesting, testIntersectionExists1){
        ASSERT_THAT(checker,NotNull());
        Line* line1 = new Line(new Point(0, 0), new Point(10, 10));
        Line* line2 = new Line(new Point(0, 10), new Point(10, 0));

        ASSERT_TRUE(checker->existIntersection(line1,line2));
        ASSERT_TRUE(checker->existIntersection(line2,line1));
}

TEST_F(LSITesting, testIntersectionExists2){
        ASSERT_THAT(checker,NotNull());
        Line* line1 = new Line(new Point(0, 0), new Point(0, 10));
        Line* line2 = new Line(new Point(1, 0), new Point(1, 10));

        ASSERT_FALSE(checker->existIntersection(line1,line2));
}

TEST_F(LSITesting, testIntersectionExists3){
        ASSERT_THAT(checker,NotNull());
        Line* line1 = new Line(new Point(0, 10), new Point(0, 0));
        Line* line2 = new Line(new Point(1, 10), new Point(1, 0));

        ASSERT_FALSE(checker->existIntersection(line1,line2));
}

TEST_F(LSITesting, testIntersectionWithSweepLine0){
	std::cout << "testIntersectionWithSweepLine0\n";
	ASSERT_THAT(checker,NotNull());
        Line* line1 = new Line(new Point(1, 1), new Point(4, 4));
        Line* line2 = new Line(new Point(1, 8), new Point(2, 4));
        //Intersection at 1,0
        ASSERT_THAT(sSt, NotNull());
        Point* mInter = checker->calculateIntersection(line1, line2);
	std::cout << mInter << std::endl;
        ASSERT_THAT(mInter, NotNull());
        ASSERT_THAT(2.4f, mInter->getX());
        ASSERT_THAT(2.4f, mInter->getY());
}

TEST_F(LSITesting, testIntersectionWithSweepLine1){
        ASSERT_THAT(checker,NotNull());
        Line* line1 = new Line(new Point(0, 0), new Point(50, 0));
        Line* line2 = new Line(new Point(1, 10), new Point(1, -1));
        //Intersection at 1,0
        ASSERT_THAT(sSt, NotNull());
        Point* mInter = checker->calculateIntersection(line1, line2);
        ASSERT_THAT(mInter, NotNull());
        ASSERT_THAT(1, mInter->getX());
        ASSERT_THAT(0, mInter->getY());
}

TEST_F(LSITesting, testIntersectionWithSweepLine2){
        ASSERT_THAT(checker,NotNull());
        Line* line1 = new Line(new Point(0, 0), new Point(0, 50));
        Line* line2 = new Line(new Point(1, 10), new Point(1, -1));
        Point* mInter = checker->calculateIntersection(line1, line2);
        ASSERT_TRUE(mInter == nullptr);
}


TEST_F(LSITesting, testIntersectionWithSweepLine3){
        Line* line2 = new Line(new Point(1, 8), new Point(2, 4));
	Line* swp2 = new Line(new Point(0,1), new Point(6,0));

	Point* mInter = checker->calculateIntersection(line2, swp2);
        std::cout << "mInter: " << *mInter << std::endl;
        ASSERT_TRUE(mInter == nullptr);
}


TEST_F(LSITesting, testStatusStructure0){
        ASSERT_THAT(checker,NotNull());
        Line* sweepLine = new Line(new Point(1, 1), new Point(4, 4));
        Line* line2 = new Line(new Point(1, 8), new Point(2, 4));
        //Intersection at 1,0
        ASSERT_THAT(sSt, NotNull());
        ASSERT_THAT(0, sSt->size());
        //Add one line
        std::cout << "Sweep line: " << *sweepLine << std::endl;
        sSt->addLine(line2, sweepLine);
        ASSERT_THAT(1, sSt->size());
	ASSERT_THAT(1, sSt->getMirrorSize());
        sweepLine = new Line(new Point(1, 2), new Point(4, 2));
        std::cout << "Sweep line: " << *sweepLine << std::endl;
        sSt->updateIntersections(sweepLine);
        ASSERT_THAT(1, sSt->size());
	Line* swp2 = new Line(new Point(0,1), new Point(6,0));
	sSt->updateIntersections(swp2);
	ASSERT_THAT(0, sSt->size());
}

TEST_F(LSITesting, testEmtpyEventQueue){
        std::cout << "#######################################\n";
        std::cout << "#######################################\n";
        std::cout << "Testing emtpy event queue\n";
        std::cout << "#######################################\n";
        std::cout << "#######################################\n";
        ASSERT_THAT(checker,NotNull());
        Line* line1 = new Line(new Point(1, 1), new Point(4, 4));
        Line* line2 = new Line(new Point(1, 8), new Point(2, 4));
        std::list intersections = finder.findIntersections();
        ASSERT_THAT(0, intersections.size());
}

TEST_F(LSITesting, testIntersections1Line){
        std::cout << "#######################################\n";
        std::cout << "#######################################\n";
        std::cout << "Testing 1 line intersections\n";
        std::cout << "#######################################\n";
        std::cout << "#######################################\n";
        ASSERT_THAT(checker,NotNull());
        Line* line1 = new Line(new Point(1, 1), new Point(4, 4));
        Line* line2 = new Line(new Point(1, 8), new Point(2, 4));
        std::list intersections = finder.findIntersections();
        finder.addLine(line1);
        ASSERT_THAT(0, intersections.size());
}

TEST_F(LSITesting, testIntersections2Lines){
        std::cout << "#######################################\n";
        std::cout << "#######################################\n";
        std::cout << "Testing intersection between 2 lines\n";
        std::cout << "#######################################\n";
        std::cout << "#######################################\n";
        Line* line1 = new Line(new Point(0, 0), new Point(50, 0));
        Line* line2 = new Line(new Point(1, 10), new Point(1, -1));
        //Intersection is expected at 1,0        
        
        finder.addLine(line1);
        std::list<Point> intersections = finder.findIntersections();
        ASSERT_THAT(1, intersections.size());
}

/*
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
