#include <gmock/gmock.h>

#include "BSTNode.h"
#include "BST.h"
#include "Integer.h"
#include "point.h"

using::testing::Eq;
using::testing::NotNull;

class BSTTesting : public testing::Test{ 
    public:
        /*std::function<bool(const int&, const int&)> intComp = [] (const int&a, const int& b)->bool{
            return a<b;
        };*/

        /*BSTNode<int, int>* root = new BSTNode<int, int>();*/
        BST<int, Integer*>* bstForIntInteger = new BST<int, Integer*>();
        Integer* myInt = new Integer(10);    
};

TEST_F(BSTTesting, testOneEqualsOne){
        ASSERT_THAT(10,testing::Eq(10));
}

TEST_F(BSTTesting, testEngineForIntegerClass){
    std::function<int const(const int&, const int&)> intComp = [](const int&a, const int& b)->int{
        int response = 0;
        std::cout<< "a: "<< a << std::endl;
        std::cout<< "b: "<< b << std::endl;
        if(a==b){
            std::cout<<"returning: " << response <<std::endl;
            return response;
        } else if (a<b){
            std::cout<< "a<b" << std::endl;
            response = -1;
        }  else {
            std::cout<< "last case, a>b" <<std::endl;
            response = 1;
        }
        std::cout << "Returning: " << response << std::endl;
        return response;
    };
    bstForIntInteger->setCompare(intComp);
    std::cout<< "Integer value: " << myInt->getValue()  << std::endl;
    ASSERT_THAT(myInt, NotNull());
    ASSERT_THAT(bstForIntInteger, NotNull());
    bstForIntInteger->insert(myInt->getValue(), myInt);
    std::cout<<"######Printing bst######"<< std::endl;
    bstForIntInteger->print();
    Integer* myInt15 = new Integer(15);  
    bstForIntInteger->insert(myInt15->getValue(), myInt15);
    std::cout<<"######Printing bst######"<< std::endl;
    bstForIntInteger->print();

    Integer* myInt5 = new Integer(5);  
    bstForIntInteger->insert(myInt5->getValue(), myInt5);
    std::cout<<"######Printing bst######"<< std::endl;
    bstForIntInteger->print();
    Integer* myInt1 = new Integer(1);  
    bstForIntInteger->insert(myInt1->getValue(), myInt1);
    std::cout<<"######Printing bst######"<< std::endl;
    bstForIntInteger->print();
    Integer* myInt25 = new Integer(25);  
    bstForIntInteger->insert(myInt25->getValue(), myInt25);
    std::cout<<"######Printing bst######"<< std::endl;
    bstForIntInteger->print();
    Integer* myInt13 = new Integer(13);  
    bstForIntInteger->insert(myInt13->getValue(), myInt13);
    std::cout<<"######Printing bst######"<< std::endl;
    bstForIntInteger->print();
    Integer* myInt6 = new Integer(6);  
    bstForIntInteger->insert(myInt6->getValue(), myInt6);
    std::cout<<"######Printing bst######"<< std::endl;
    bstForIntInteger->print();
}

TEST_F(BSTTesting, testingEngineForPoint){
    std::cout<< "testingEngineForPoint" << std::endl;
    std::function<int const(const Point&, const Point&)> pointComp = [](const Point&a, const Point& b)->int{
        //return a<b;
        if(a.y < b.y ){
            std::cout<< b << "  has precedence over " << a << std::endl;
            return -1;
        } else if (a.y > b.y ){
            std::cout<< a << " has precedence over " << b << std::endl;
            return 1;
        } else{
            //In this case a.y == b.y
            if(a.x > b.x){
                std::cout<< b << " has precedence over " << a << std::endl;
                return -1;
            } else if (a.x < b.x){
                std::cout<< a << " has precedence over " << b << std::endl;
                return 1;
            }else {
                std::cout<< a << " is equal to " << b << std::endl;
                return 0;
            }
        }
    };
   
    
    BST<Point, Point*>* bstForPoint = new BST<Point, Point*>();
    bstForPoint->setCompare(pointComp);
    Point* p1 = new Point(5,5);
    bstForPoint->insert(*p1, p1);
    bstForPoint->print();
    Point* p105 = new Point(10,5);
    bstForPoint->insert(*p105, p105);
    bstForPoint->print();
    Point* p25 = new Point(2,5);
    bstForPoint->insert(*p25, p25);
    bstForPoint->print();
    /*Point* p24 = new Point(2,4);
    bstForPoint->insert(*p24, p24);
    bstForPoint->print();*/
    Point* max = bstForPoint->getMax();

    
    std::cout << "Max is : " << *max << std::endl;

    Point* p1_55 = new Point(1.5,5);
    bstForPoint->insert(*p1_55, p1_55);
    bstForPoint->print();

    Point* p48 = new Point(4,8);
    bstForPoint->insert(*p48, p48);
    bstForPoint->print();


    Point* p15 = new Point(1,5);
    bstForPoint->insert(*p15, p15);
    bstForPoint->print();

    ASSERT_THAT(bstForPoint, NotNull());
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}