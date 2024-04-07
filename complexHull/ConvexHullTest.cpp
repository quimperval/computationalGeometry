#include <gmock/gmock.h>
#include "ConvexHullEngine.h"

using ::testing::Eq;
using ::testing::NotNull;

class ConvexHullTesting : public testing::Test{
    public: 
        ConvexHullEngine engine;
};

TEST_F(ConvexHullTesting, testNotNullEngine){
    ASSERT_THAT(engine, NotNull());
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}