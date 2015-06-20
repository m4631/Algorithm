Point incenter(Point A,Point B,Point C) {
    double a = B.distTo(C), b = A.distTo(C), c = A.distTo(B);
    return (A*a + B*b + C*c) * (1/(a+b+c));
}

// http://recursostic.educacion.es/descartes/web/materiales_didacticos/OrtoCircun/Ortocentro.htm
Point orthocenter(Point A, Point B, Point C) {
    Point CA = A-C, AB = B-A, BC = C-B;
    Point pBC(-BC.y, BC.x);
    double t = -(CA*AB)/(pBC*AB);
    return A + pBC * t;
}

//http://recursostic.educacion.es/descartes/web/materiales_didacticos/OrtoCircun/Circuncentro.htm
Point circuncenter(Point A, Point B, Point C) {
    Point mAB = (B-A)*0.5 + A, mAC = (C-A)*0.5 + A, mBC = (C-B)*0.5 + B;
    return orthocenter(mAB,mAC,mBC);
}
