#include <gmock/gmock.h>

#include "BSTNode.h"
#include "BST.h"
#include "Integer.h"

using::testing::Eq;
using::testing::NotNull;

class BSTTesting : public testing::Test{ 
    public:
        /*std::function<bool(const int&, const int&)> intComp = [] (const int&a, const int& b)->bool{
            return a<b;
        };*/

        /*BSTNode<int, int>* root = new BSTNode<int, int>();
        BST<int, int>* bst = new BST<int, int>();*/
        Integer* myInt = new Integer(1);
};

TEST_F(BSTTesting, testOneEqualsOne){
        ASSERT_THAT(1,testing::Eq(1));
}

TEST_F(BSTTesting, testNotNullEngine){
    std::cout<< "Integer value: " << myInt->getValue()  << std::endl;
    ASSERT_THAT(myInt, NotNull());

    /*ASSERT_THAT(root, NotNull());*/
    /*root->setCompare(intComp);
    root->setElement(10);
    root->traverse(root);
    root->insert(9,9);
    root->traverse(root);
    root->insert(15,15);
    root->traverse(root);*/
}

TEST_F(BSTTesting, testNotNullBST){
/*    ASSERT_THAT(bst, NotNull());
*/
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}