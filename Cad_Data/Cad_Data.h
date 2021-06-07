//
// Created by pedro on 30/05/2021.
//

#ifndef TG01_CODE_CAD_DATA_H
#define TG01_CODE_CAD_DATA_H
#include "stdio.h"
#include "iostream"
#include "CGAL_Setup.h"

class Cad_Data_XY{
public:
    std::vector<Point_2> vertexes;
    Point_2 position;
    angle_type angle;
    bool operator==(const Cad_Data_XY& other) {return false;}
    bool operator!=(const Cad_Data_XY& other) {return true;}
};

class Cad_Data {
public:
    std::vector<Point_3> vertexes;
    Point_3 position;
    std::vector<kernel_type> quaternion = std::vector<kernel_type>(4);
    void printa();
    bool operator==(const Cad_Data& other) {return false;}
    bool operator!=(const Cad_Data& other) {return true;}
    Cad_Data_XY projection_XY();
};

class Vector_Cad_Data{
public:
    std::vector<Cad_Data> vector;

};


#endif //TG01_CODE_CAD_DATA_H
