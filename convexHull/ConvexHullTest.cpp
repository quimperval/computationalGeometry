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

TEST_F(ConvexHullTesting, getConvexHullA){
    std::vector<Point> points = { {1, 3}, {2, 1}, {2, 2}, {3, 2}, {1,0},{2,0},{1,1} };

    std::vector<Point> expectedPoints = { {1, 0}, {1, 3}, {3, 2}, {2,0},{1,0}};
    ASSERT_THAT(expectedPoints.size(), engine->getConvexHull(points)->size());
}


TEST_F(ConvexHullTesting, getConvexHullB){
    std::vector<Point> points = { {41.7500,59.7500},{65.2500,74.7500},{101.5000,57.7500},
        {48.0000,37.2500},{62.2500,62.5000},{58.7500,32.0000},{82.0000,41.5000},{78.2500,55.0000},
        {60.7500,45.2500},{41.0000,47.7500},{36.2500,26.7500},{47.2500,20.5000},{57.5000,19.7500},
        {69.5000,24.5000},{69.2500,35.0000},{76.2500,34.0000},{90.2500,25.5000},{105.2500,30.7500},
        {98.5000,43.7500},{92.5000,55.0000},{101.0000,73.7500},{122.5000,62.5000},{116.7500,48.7500},
        {120.2500,35.0000},{114.0000,19.0000},{85.5000,4.5000},{78.7500,14.2500},{80.7500,19.0000},
        {67.7500,12.5000},{57.2500,5.7500},{50.2500,5.7500},{40.7500,11.0000},{28.5000,18.2500},
        {24.2500,29.5000},{29.5000,36.7500},{33.7500,40.0000},{29.5000,53.2500},{34.7500,60.7500},
        {44.2500,71.5000},{62.5000,77.5000},{82.0000,77.0000},{94.2500,57.0000} };

    std::vector<Point> expectedPoints = {{24.2500,29.5000},{29.5000,53.2500},{34.7500,60.7500},
        {44.2500,71.5000},{62.5000,77.5000},{82.0000,77.0000},{101.0000,73.7500},{122.5000,62.5000},
        {120.2500,35.0000},{114.0000,19.0000},{85.5000,4.5000},{50.2500,5.7500},{40.7500,11.0000},
        {28.5000,18.2500},{24.2500,29.5000}};
    ASSERT_THAT(expectedPoints.size(), engine->getConvexHull(points)->size());
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

TEST_F(ConvexHullTesting, testVectorHavingRequiredLength){
    std::vector<Point> points = { {1, 3}, {2, 2}, {1, 2}};
    ASSERT_TRUE(engine->isValidVector(points));
}

TEST_F(ConvexHullTesting, testVectorNotHavingRequiredLength){
    std::vector<Point> points = { {1, 3}, {2, 2}};
    ASSERT_FALSE(engine->isValidVector(points));
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}