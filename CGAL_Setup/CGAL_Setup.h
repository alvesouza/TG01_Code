//
// Created by pedro on 30/05/2021.
//

#ifndef TG01_CODE_CGAL_SETUP_H
#define TG01_CODE_CGAL_SETUP_H
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_2.h>
#include "CGAL/Polygon_with_holes_2.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/property_map.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_convex_set_2.h>
#include <CGAL/min_quadrilateral_2.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/aff_transformation_tags.h>
#include <CGAL/Segment_2.h>
//#include <CGAL/draw_polygon_2.h>
typedef float kernel_type;
typedef float angle_type;
typedef CGAL::Simple_cartesian<kernel_type> Kernel;
//typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;
typedef Kernel::Segment_2 Segment_2;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel> Polygon_with_holes_2;
typedef CGAL::Vector_2<Kernel> Vector_2;
typedef CGAL::Convex_hull_traits_adapter_2<Kernel,CGAL::Pointer_property_map<Point_2>::type > Convex_hull_traits_2;
typedef CGAL::Random_points_in_square_2<Point_2>  Generator;
typedef CGAL::Aff_transformation_2<Kernel> Transformation;
typedef CGAL::Min_quadrilateral_default_traits_2<Kernel> min_default;

#endif //TG01_CODE_CGAL_SETUP_H
