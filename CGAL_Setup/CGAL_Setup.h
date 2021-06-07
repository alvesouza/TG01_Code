//
// Created by pedro on 30/05/2021.
//

#ifndef TG01_CODE_CGAL_SETUP_H
#define TG01_CODE_CGAL_SETUP_H
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_2.h>
#include "CGAL/Polygon_with_holes_2.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2_algorithms.h>

typedef float kernel_type;
typedef float angle_type;
typedef CGAL::Simple_cartesian<float> Kernel;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel> Polygon_with_holes_2;
typedef CGAL::Vector_2<Kernel> Vector_2;

#endif //TG01_CODE_CGAL_SETUP_H
