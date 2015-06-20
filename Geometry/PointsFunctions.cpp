bool collinear(Point A, Point B, Point C){
    return ( ( (B-A)^(C-A) ) == 0 );
}
