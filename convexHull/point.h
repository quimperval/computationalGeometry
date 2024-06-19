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
        Point(float x, float y): x(x), y(y){}

};

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

#endif
