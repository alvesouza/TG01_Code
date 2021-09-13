//
// Created by pedro on 11/06/2021.
//

#include "CGAL_helpers.h"

void test_All_Intersection(){
    Point_2 points[] = { Point_2(0,0), Point_2(1,0), Point_2(1,1), Point_2(0,1)};
    Point_2 points2[] = { Point_2(0.5,0.5), Point_2(1.5,0.5), Point_2(1.5,1.5), Point_2(0.5,1.5)};
    Point_2 points3[] = { Point_2(0.5,0.5), Point_2(1.5,0.5), Point_2(1.5,1.5), Point_2(0.5,1.5)};

    Polygon_2 poly1(points, points+4);
    Polygon_2 poly2(points2, points2+4);
    Polygon_2 poly3(points3, points3+4);

    std::vector<Polygon_2> polys = {poly1, poly2, poly3};
    //float area = CGAL_helpers::Calculate_Intersection_Area( poly1, poly2 );
    float area = CGAL_helpers::All_Intersection_Area(polys);
    std::cout << "Area = " << area << std::endl;
}

int main(){
    test_All_Intersection();
    return 0;
}
