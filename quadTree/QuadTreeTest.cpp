#include <gmock/gmock.h>
#include "point.h"

using ::testing::Eq;
using ::testing::NotNull;

class QuadTreeTest : public testing::Test{
    public:
        int i=1;
        std::unique_ptr<Point> point = std::make_unique<Point>();
};

TEST_F(QuadTreeTest, testOne){
    ASSERT_THAT(1,i);
}

TEST_F(QuadTreeTest, pointNotNull){
    ASSERT_THAT(point, NotNull());
}

int main(int argc, char**argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
