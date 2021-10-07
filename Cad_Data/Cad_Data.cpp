//
// Created by pedro on 30/05/2021.
//

#include "Cad_Data.h"
Polygon_2 Cad_Data_XY::Get_Convex_Hull_Polygon(){
    std::vector<std::size_t> indices(vertexes.size()), out;
    std::iota(indices.begin(), indices.end(),0);

    CGAL::convex_hull_2(indices.begin(), indices.end(), std::back_inserter(out),
                        Convex_hull_traits_2( CGAL::make_property_map(vertexes) ));

    std::vector<Point_2> points;

    for (std::size_t i : out) {
        points.push_back(vertexes[i]);
    }

    return Polygon_2(points.begin(), points.end());
}
void Cad_Data::printa() {

    std::cout << "Position = " << this->position << std::endl;

    std::cout << "Quaternion = ( ";
    for (std::size_t i = 0; i < 4; i++) {
        std::cout << this->quaternion[i];
        if( i < 3 )std::cout << ", ";
    }

    std::cout << ")" << std::endl;

    std::cout << "Vertexes = [ " << std::endl;
    std::size_t len = this->vertexes.size();
    for (std::size_t j = 0; j < len; j++) {
        std::cout << "  ( ";
        for (std::size_t i = 0; i < 3; i++) {
            std::cout << this->vertexes[j][i];
            if( i < 2 )std::cout << ", ";
        }
        std::cout << "),\n";
    }

    std::cout << "]" << std::endl;
}

Cad_Data_XY Cad_Data::projection_XY() {
    Cad_Data_XY new_xy;
    Point_2  p;
    new_xy.position = Point_2(position[0], position[1]);

    for (std::size_t i = 0, size = vertexes.size(); i < size; ++i) {
        p = Point_2(vertexes[i][0], vertexes[i][1]);
        if (std::find(new_xy.vertexes.begin(), new_xy.vertexes.end(), p)==new_xy.vertexes.end())
            new_xy.vertexes.push_back(p);
    }

    new_xy.angle = 0;

    return new_xy;
}

std::vector<Cad_Data_XY> Project_Cad_Data_Vector( std::vector<Cad_Data> vector){
    std::vector<Cad_Data_XY> projection_cad;

    for (std::size_t i = 0, size = vector.size(); i < size; i++)
        projection_cad.push_back(vector[i].projection_XY());

    return projection_cad;
}
