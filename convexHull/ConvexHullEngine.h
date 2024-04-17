#ifndef CONVEX_HULL_ENGINE_H
#define CONVEX_HULL_ENGINE_H
#include <algorithm>
#include <vector>
#include "point.h"

class ConvexHullEngine{

    public: 
        ConvexHullEngine(){

        }

        void orderPoints(std::vector<Point>& inputVector) {
            std::sort(inputVector.begin(),inputVector.end(), comparePoints );
        }

        bool isValidVector(std::vector<Point>& inputVector){
            if(inputVector.size()<=2){
                return false;
            } 
            return true;
        }

        std::unique_ptr<std::vector<Point>> getConvexHull(std::vector<Point>& inputVector){
            //First get the inputVector Ordered
            //std::cout << "###### Printing unordered vector\n";
            ///this->printVector(inputVector);
            this->orderPoints(inputVector);
            
            std::unique_ptr<std::vector<Point>> upperHullList = std::make_unique<std::vector<Point>>();
            //std::cout << "###### Printing ORDERED vector\n";
            //this->printVector(inputVector);
            
            upperHullList->push_back(inputVector.at(0));
            upperHullList->push_back(inputVector.at(1));
            //std::cout << "###### Printing printing temp vector\n";
            //this->printVector(upperHullList);
            int counter=0;
            for(int i=2; i < inputVector.size(); i++){
                //std::cout<< "@@@@@@ Iteration in algorithm: "<< ++counter << std::endl;
                
                upperHullList->push_back(inputVector.at(i));
                //std::cout<< "@@@@@@ Printing current vector" << std::endl;
                //this->printVector(upperHullList);
                while(upperHullList->size()>2 && 
                this->getTurn(
                    std::make_unique<Point>(upperHullList->at(upperHullList->size()-3)), 
                    std::make_unique<Point>(upperHullList->at(upperHullList->size()-2)),
                    std::make_unique<Point>(upperHullList->at(upperHullList->size()-1)))!=-1){
                    //std::cout<< "Removing element at: " << (upperHullList->size()-2) << std::endl;
                    upperHullList->erase(upperHullList->begin() + upperHullList->size()-2);
                }
            }
            //std::cout << "###### Printing upper hull\n";
            //this->printVector(upperHullList);
            std::vector<Point> lowerHullList;

            lowerHullList.push_back(inputVector.at(inputVector.size()-1));
            lowerHullList.push_back(inputVector.at(inputVector.size()-2));
            //std::cout << "###### Calculating the lower hull\n";
            counter=0;
            for(int i=inputVector.size()-3; i>=0; i--){
                //std::cout<< "@@@@@@ Iteration in algorithm: "<< ++counter << std::endl;
                lowerHullList.push_back(inputVector.at(i));
                //std::cout<< "@@@@@@ Printing current vector" << std::endl;
                while(lowerHullList.size()>2 && 
                this->getTurn(
                    std::make_unique<Point>(lowerHullList.at(lowerHullList.size()-3)), 
                    std::make_unique<Point>(lowerHullList.at(lowerHullList.size()-2)),
                    std::make_unique<Point>(lowerHullList.at(lowerHullList.size()-1)))!=-1 ){
                        //std::cout<< "Removing element at: " << (lowerHullList.size()-2) << std::endl;
                        lowerHullList.erase(lowerHullList.begin() + lowerHullList.size()-2);
                }
            }

            ///std::cout << "###### Printing lower hull\n";
            //this->printVector(lowerHullList);
            mergeVectors(upperHullList, lowerHullList);
            //this->printVector(upperHullList);
            return upperHullList;
        }

        int getTurn (const std::unique_ptr<Point>& refPoint, const std::unique_ptr<Point>& p1, const std::unique_ptr<Point>& p2){
            //Let generate a vector, in the sense of the geometry, not in the sense of c++
            // u  = u_1* i + u_2*j + u_3*k;
            // v  = v_1* i + v_2*j + v_3*k;
            //Where i, j, k are the unit vectors 
            
            auto u_x = p1->x - refPoint->x;
            auto u_y = p1->y - refPoint->y;
            Point u(u_x, u_y);

            auto v_x = p2->x - p1->x;
            auto v_y = p2->y - p1->y;
            Point v(v_x, v_y);
            
            //Get the component of the u x v resultant vector over the k axis.
            auto kComp = u.x*v.y - u.y*v.x;
            //The other two components are zero, because the z component of the inputs is zero.
            if(kComp>0){
                //Left turn
                return 1;
            } else if (kComp<0){
                //Right turn
                return -1;
            }
            return 0;
        }
    
    private:
        static bool comparePoints(const Point& p1,  const Point& p2) {
            if(p1.x != p2.x)
                return p1.x < p2.x;
            return p1.x < p2.y;
        }

        void printVector(std::unique_ptr<std::vector<Point>>& mVector){
            for(int pos=0; pos< mVector->size(); pos++){
                std::cout <<"pos: " << pos << ", x:" <<mVector->at(pos).x << ", y: " << mVector->at(pos).y << std::endl;                    
            }
        }

        //std::vector<Point>& inputVector
        void printVector(std::vector<Point> mVector){
            for(int pos=0; pos< mVector.size(); pos++){
                std::cout <<"pos: " << pos << ", x:" <<mVector.at(pos).x << ", y: " << mVector.at(pos).y << std::endl;                    
            }
        }

        void mergeVectors(std::unique_ptr<std::vector<Point>>& upperHullList, std::vector<Point> lowerHullList){
            //std::cout<<"Merging vectors" << std::endl;   
            Point* lastPoint = &upperHullList->at(upperHullList->size()-1);
            //std::cout << "Last upper point, x:" << lastPoint->x << "; y: " << lastPoint->y << std::endl; 
            Point* firstPoint = &lowerHullList.at(0);
            //std::cout << "Fist lower point, x:" << firstPoint->x << "; y: " << firstPoint->y << std::endl; 
            bool areEqual = (lastPoint->x == firstPoint->x) && (lastPoint->y == firstPoint->y) ;
            //std::cout << "areEqual: " << areEqual << std::endl;
            if(areEqual){
                upperHullList->insert(upperHullList->end(), lowerHullList.begin()+1, lowerHullList.end());
            } else {
                upperHullList->insert(upperHullList->end(), lowerHullList.begin(), lowerHullList.end());
            }
            
        }
};
#endif
