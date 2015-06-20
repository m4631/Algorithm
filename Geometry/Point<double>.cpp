double eps = 1e-9;
struct Point {
    double x,y;
    Point(double x=0,double y=0):x(x),y(y) {}
    Point operator-(const Point &P)const {
        return Point(x-P.x,y-P.y);
    }
    Point operator+(const Point &P)const {
        return Point(x+P.x,y+P.y);
    }
    double operator*(const Point &P)const {
        return x*P.x + y*P.y;
    }
    double distTo(const Point &P)const {
        Point v = *this-P;
        return sqrt(v*v);
    }
    Point operator*(const double f)const {
        return Point(x*f, y*f);
    }
    int operator^(const Point &P)const {
        return x*P.y - y*P.x;
    }
    bool operator<(const Point &a)const {
        if( abs(x-a.x) < eps ) {
            if( abs(y-a.y) < eps ) {
                return false;
            }
            return y < a.y;
        }
        return x < a.x;
    }

};
ostream& operator<< (ostream &out, const Point &P) {
    out << "(" << P.x << "," << P.y << ")" << endl;
    return out;
}
