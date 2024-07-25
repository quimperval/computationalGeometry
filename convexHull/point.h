#ifndef POINT_H
#define POINT_H

class Point{

    public: 
        float x, y, z=0;
        Point()  {
            x=0;
            y=0;
            z=0;    
        };
        Point(float x, float y): x(x), y(y){
            //std::cout << "Point constructor" << std::endl;
            //std::cout << "x: " << getX() << std::endl;
            //std::cout << "y: " << getY() << std::endl;
        }

        //Methods not marked as const cannot be called by a const object.
        float getX() const{
            return this->x;
        }

        float getY() const{
            return this->y;
        }

        float getZ() const{
            return this->z;
        }
};

std::ostream& operator<<(std::ostream& os, 
const Point& point) {
    os << "(" << point.x << ", " 
    << point.y << ")";
    return os;
}

#endif
