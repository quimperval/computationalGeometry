#include <gmock/gmock.h>

#include "BSTNode.h"
#include "BST.h"
#include "Integer.h"
#include "point.h"
#include "EventPoint.h"
#include "Line.h"
#include "IntersectionFinder.h"

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
        EventPoint* e1 = new EventPoint(*line->getP1());
        std::cout << *e1 << "\n";

        ASSERT_THAT(line,NotNull());
        IntersectionFinder* finder = new IntersectionFinder();
        ASSERT_THAT(finder, NotNull());
        finder->addLine(line);
        std::cout << "event point queue size: " << finder->getEventPointsCount() << "\n";
        ASSERT_THAT(2, finder->getEventPointsCount());

        std::cout << *(finder->getMaxEventPoint()) << "\n";
        std::cout << "Max is: " << *(finder->getMaxEventPoint())<<"\n";
        finder->printEventPointsOrdered();
}
/*
TEST_F(LSITesting, testEventPointLessThanTrue){
        ASSERT_THAT(eventPoint,NotNull());
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