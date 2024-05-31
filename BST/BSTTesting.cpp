#include <gmock/gmock.h>

#include "BSTNode.h"

using::testing::Eq;
using::testing::NotNull;

class BSTTesting : public testing::Test{ 
    public:
        std::function<bool(const int&, const int&)> intComp = [] (const int&a, const int& b)->bool{
            return a<b;
        };

        BSTNode<int, int>* root = new BSTNode<int, int>();
};

TEST_F(BSTTesting, testOneEqualsOne){
        ASSERT_THAT(1,testing::Eq(1));
}

TEST_F(BSTTesting, testNotNullEngine){
    ASSERT_THAT(root, NotNull());
    root->setCompare(intComp);
    root->setElement(10);
    root->traverse(root);
    root->insert(9,9);
    root->traverse(root);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}