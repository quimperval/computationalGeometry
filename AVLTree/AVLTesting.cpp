#include <gmock/gmock.h>

#include "AVLNode.h"
#include "AVL.h"
#include "Integer.h"


using::testing::Eq;
using::testing::NotNull;

class AVLTesting : public testing::Test{ 
    public:
        int value = 10;
        AVL<int, Integer*>* avlForIntInt = new AVL<int, Integer*>();
};

TEST_F(AVLTesting, matchInt){
        ASSERT_THAT(value,10);
}

TEST_F(AVLTesting, avlNodeNotNull){
   // AVLNode<int, int>* avlNode = new AVLNode();      
   ASSERT_THAT(avlForIntInt, NotNull());
}

TEST_F(AVLTesting, testEventPointGreaterThanTrue){
    Integer* myInt15 = new Integer(15);  
    avlForIntInt->insert(myInt15->getValue(), myInt15);
    std::cout<<"######Printing AVL######"<< std::endl;
    avlForIntInt->print();
    ASSERT_THAT(1, avlForIntInt->size());
    Integer* myInt20 = new Integer(20);  
    avlForIntInt->insert(myInt20->getValue(), myInt20);
    std::cout<<"######Printing AVL######"<< std::endl;
    avlForIntInt->print();
    ASSERT_THAT(2, avlForIntInt->size());

    Integer* myInt11 = new Integer(11);  
    avlForIntInt->insert(myInt11->getValue(), myInt11);
    std::cout<<"######Printing AVL######"<< std::endl;
    avlForIntInt->print();
    ASSERT_THAT(3, avlForIntInt->size());

    Integer* myInt9 = new Integer(9);  
    avlForIntInt->insert(myInt9->getValue(), myInt9);
    std::cout<<"######Printing AVL######"<< std::endl;
    avlForIntInt->print();
    ASSERT_THAT(4, avlForIntInt->size());


    Integer* myInt8 = new Integer(8);  
    avlForIntInt->insert(myInt8->getValue(), myInt8);
    std::cout<<"######Printing AVL######"<< std::endl;
    avlForIntInt->print();
    ASSERT_THAT(5, avlForIntInt->size());

    Integer* myInt30 = new Integer(30);  
    avlForIntInt->insert(myInt30->getValue(), myInt30);
    std::cout<<"######Printing AVL######"<< std::endl;
    avlForIntInt->print();
    ASSERT_THAT(6, avlForIntInt->size());

    Integer* myInt35 = new Integer(35);  
    avlForIntInt->insert(myInt35->getValue(), myInt35);
    std::cout<<"######Printing AVL######"<< std::endl;
    avlForIntInt->print();
    ASSERT_THAT(7, avlForIntInt->size());

    Integer* myInt32 = new Integer(32);  
    avlForIntInt->insert(myInt32->getValue(), myInt32);
    std::cout<<"######Printing AVL######"<< std::endl;
    avlForIntInt->print();
    ASSERT_THAT(8, avlForIntInt->size());

    std::cout<<"######Removing node with key 8######"<< std::endl;
    avlForIntInt->remove(8);
    ASSERT_THAT(7, avlForIntInt->size());

    auto mStack = avlForIntInt->getInOrderElementsAsNodes();
    for(auto val : mStack){
        std::cout << "val: " << val->element()->getValue() << "\n";
    }
    ASSERT_THAT(7, mStack.size());
}

TEST_F(AVLTesting, testGetSuccessor){
	std::cout << "Testing getSuccesor\n";
	Integer* five = new Integer(5);
	Integer* six = new Integer(6);
	Integer* four = new Integer(4);

	AVL<int, Integer*>* avl = new AVL<int, Integer*>();
        avl->insert(five->getValue(), five);
	avl->insert(four->getValue(), four);
	avl->insert(six->getValue(), six);
        ASSERT_THAT(3,avl->size());
	auto succesor = avl->getSuccesor(five->getValue());
	if(succesor==nullptr)
	{
            std::cout<< "Succesor is null\n";

	}else {
            std::cout << "Succesor is: "<< succesor->getValue() << std::endl;
	}

	ASSERT_THAT(6, succesor->getValue());
        avl->print();
	auto predecesor  = avl->getPredecessor(five->getValue());

	if(predecesor== nullptr)
	{
	    std::cout << "Predecesor is null"<< std::endl;
	}else
	{
            std::cout << "Predecesor: " << predecesor->getValue() << std::endl ;
	}


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
