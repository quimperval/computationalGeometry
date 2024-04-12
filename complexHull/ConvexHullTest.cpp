#include <gmock/gmock.h>
#include "ConvexHullEngine.h"

using ::testing::Eq;
using ::testing::NotNull;

class ConvexHullTesting : public testing::Test{
    public: 
        ConvexHullEngine*    engine;
};

TEST_F(ConvexHullTesting, testNotNullEngine){
    ASSERT_THAT(engine, NotNull());
}

TEST_F(ConvexHullTesting, testArrayOrdering){
    std::vector<Point> points = { {1, 3}, {2, 2}, {1, 2}, {3, 1} };
    std::vector<Point> expected_sorted = { {1, 2}, {1, 3}, {2, 2}, {3, 1} };
    engine->orderPoints(points);
    ASSERT_EQ(points.size(), expected_sorted.size());
    for (size_t i = 0; i < points.size(); ++i) {
        ASSERT_EQ(points[i].x, expected_sorted[i].x);
        ASSERT_EQ(points[i].y, expected_sorted[i].y);
    }
}

TEST_F(ConvexHullTesting, testNotHavingMinLengthA){
    std::vector<Point> points = { {1, 3}, {2, 2}};
    ASSERT_FALSE(engine->isValidVector(points)) ;
}

TEST_F(ConvexHullTesting, testHavingMinLengthB){
    std::vector<Point> points = { {1, 3}};
    ASSERT_FALSE(engine->isValidVector(points));
}

TEST_F(ConvexHullTesting, DISABLED_getConvexHull){
    std::vector<Point> points = { {1, 3}, {2, 2}, {1, 2}, {3, 1} };
    ASSERT_TRUE(engine->getConvexHull(points).size()>=3);
}

TEST_F(ConvexHullTesting, turnRightTestA){
    std::unique_ptr<Point> p1 = std::make_unique<Point>(1,2);
    std::unique_ptr<Point> p2 = std::make_unique<Point>(1,3);
    std::unique_ptr<Point> p3 = std::make_unique<Point>(2,2);
    ASSERT_EQ(-1, engine->getTurn(p1, p2, p3));
}

TEST_F(ConvexHullTesting, turnLeftTestA){
    std::unique_ptr<Point> p1 = std::make_unique<Point>(1,2);
    std::unique_ptr<Point> p2 = std::make_unique<Point>(1,3);
    std::unique_ptr<Point> p3 = std::make_unique<Point>(0,2);
    ASSERT_EQ(1, engine->getTurn(p1, p2, p3));
}

TEST_F(ConvexHullTesting, noTurnTestA){
    std::unique_ptr<Point> p1 = std::make_unique<Point>(0,0);
    std::unique_ptr<Point> p2 = std::make_unique<Point>(1,1);
    std::unique_ptr<Point> p3 = std::make_unique<Point>(2,2);
    ASSERT_EQ(0, engine->getTurn(p1, p2, p3));
}

TEST_F(ConvexHullTesting, testHavingRequiredLength){
    std::vector<Point> points = { {1, 3}, {2, 2}, {1, 2},};
    ASSERT_TRUE(engine->isValidVector(points));
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}