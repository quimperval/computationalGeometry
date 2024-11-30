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
        ASSERT_THAT(checker,NotNull());
        Line* sweep = new Line(new Point(1, 1), new Point(4, 4));
        Line* line2 = new Line(new Point(1, 8), new Point(2, 4));
        //Intersection at 1,0
        ASSERT_THAT(sSt, NotNull());
        Point* mInter = checker->calculateIntersection(sweep, line2);
        ASSERT_THAT(mInter, NotNull());
        ASSERT_THAT(2.4f, mInter->getX());
        ASSERT_THAT(2.4f, mInter->getY());
}

TEST_F(LSITesting, testIntersectionWithSweepLine1){
        ASSERT_THAT(checker,NotNull());
        Line* sweep = new Line(new Point(0, 0), new Point(50, 0));
        Line* line2 = new Line(new Point(1, 10), new Point(1, -1));
        //Intersection at 1,0
        ASSERT_THAT(sSt, NotNull());
        Point* mInter = checker->calculateIntersection(sweep, line2);
        ASSERT_THAT(mInter, NotNull());
        ASSERT_THAT(1, mInter->getX());
        ASSERT_THAT(0, mInter->getY());
}

TEST_F(LSITesting, testIntersectionWithSweepLine2){
        ASSERT_THAT(checker,NotNull());
        Line* sweep = new Line(new Point(0, 0), new Point(0, 50));
        Line* line2 = new Line(new Point(1, 10), new Point(1, -1));
        
        Point* mInter = checker->calculateIntersection(sweep, line2);
        ASSERT_TRUE(mInter == nullptr);
     
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