//
// Created by pedro on 06/06/2021.
//

#ifndef TG01_CODE_CGAL_HELPERS_H
#define TG01_CODE_CGAL_HELPERS_H

#include "CGAL_Setup.h"
namespace CGAL_helpers{
    typedef struct Rect_info Rect_info;
    struct Rect_info{
        kernel_type x_max, y_max, area;
    };
    inline float angle_radian( const Vector_2 &v, const Vector_2 &u );
    void Rotate_Polygon_radian(Polygon_2 &p, const float angle);

    kernel_type Polygons_Area( std::vector<Polygon_2> &polygons );

    void Rotate_Polygon_degree(Polygon_2 &p, const float angle);

    void Translate_Polygon( Polygon_2 &p, const Vector_2 Movement);

    kernel_type Calculate_Intersection_Area( Polygon_2 &p1, Polygon_2 &p2 );

    Polygon_2 Get_Convex_Hull( std::vector<Point_2> &points );

    kernel_type All_Intersection_Area( std::vector<Polygon_2> &polygons );
    kernel_type All_Intersection_Inside_Board_Area( std::vector<Polygon_2> &polygons, Polygon_2 &board );

    kernel_type Min_Rect_XY_Area( std::vector<Polygon_2> &polygons );
    kernel_type Min_Rect_XY_Area_V01( std::vector<Polygon_2> &polygons );

    Rect_info Min_Rect_XY_Area_V02( std::vector<Polygon_2> &polygons );
}

#endif //TG01_CODE_CGAL_HELPERS_H
