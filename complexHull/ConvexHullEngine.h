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

        std::vector<Point> getConvexHull(std::vector<Point>& inputVector){
            //First get the inputVector Ordered
            this->orderPoints(inputVector);
            
            auto response = std::vector<Point>();

            for(int i=0; i< inputVector.size(); i++){
                std::cout <<"i: " << i << ", x:" <<inputVector.at(i).x << ", y: " << inputVector.at(i).y << std::endl;
            }
            return std::vector<Point>();
        }

        int getTurn(std::unique_ptr<Point>& refPoint, std::unique_ptr<Point>& p1, std::unique_ptr<Point>& p2){
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
                return 1;
            } else if (kComp<0){
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

};
#endif
