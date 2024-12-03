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

bool operator==(const Point& e1, const Point& e2){
    
    return (e1.getX()==e2.getX()) && (e1.getY() == e2.getY());
}

bool operator!=(const Point& e1, const Point& e2){
    
    return (e1.getX()!=e2.getX()) || (e1.getY() != e2.getY());
}

bool operator>(const Point& e1, const Point& e2){
    //std::cerr << "Debug: greater than" << std::endl;
    if(e1.getY()>e2.getY()){    
        //std::cout << "Debug: e1.getY() > e2.getY()" << std::endl;

        return true;
    } else if (e1.getY()==e2.getY()){
        //std::cout << "Debug: e1.getY() == e2.getY() and e1.getX() > e2.getX()" << std::endl;
        if(e1.getX()>e2.getX()){
            return true;
        } 
    } 



    return false;
}

bool operator<(const Point& e1, const Point& e2){
std::cerr << "Debug: less than" << std::endl;
    if(e1.getY()<e2.getY()){
        return true;
    } else if (e1.getY()==e2.getY()){
        if(e1.getX()<e2.getX()){
            return true;
        } 
    } 
    return false;
}

std::ostream& operator<<(std::ostream& os, 
const Point& point) {
    os << "(" << point.x << ", " 
    << point.y << ")";
    return os;
}

#endif
