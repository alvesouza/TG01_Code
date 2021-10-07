//
// Created by pedro on 13/06/2021.
//

#include "Genetic.h"
#include "Genes_helpers.h"
#include "iostream"
using namespace Genes_helpers;

typedef bit_parser_l1 bit_parser;
void Test_Create_Population(){
    srand(time(NULL));
    std::vector<boost::dynamic_bitset<>> foo =
            Genetic::Create_Genetic_Population_V01<Genes_helpers::bit_parser_l1>(1000, 10);
    std::vector<State> Values;
    boost::dynamic_bitset<> test = foo[0];
    std::cout << "test tostring = " << test <<std::endl;
    foo[0][0] ^= 1;
    std::cout << "test tostring = " << test <<std::endl;
    std::cout << "foo tostring = " << foo[0] <<std::endl;
    std::cout << "continue?\n";
    for (std::size_t i = 0, size_pop = foo.size(); i < size_pop; ++i) {
        Genes_helpers::convert_genes<Genes_helpers::bit_parser_l1>( foo[i], Values);
        std::cout << "size foo = " << foo[i].size() << std::endl;
        std::cout << "foo tostring = " << foo[i] <<std::endl;
        std::cout << "Convertion to Value\n************************************" <<std::endl;
        for ( size_t index_vector = 0, size_vector = Values.size(); index_vector < size_vector; ++index_vector) {
            std::cout << "Values[" << index_vector << "].Position = ( " << Values[index_vector].Position[0] << ", " <<
                      Values[index_vector].Position[1] << ")\n";
            std::cout << "Values[" << index_vector << "].angle = " << Values[index_vector].angle << std::endl;
            std::cout << "///////////////////////////////////" << std::endl;
        }
        std::cout << "Ended\n/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*" <<std::endl;
    }
}

Polygon_2 Square( kernel_type w, kernel_type h){
    Point_2 points[] = {Point_2(0,0), Point_2(w,0), Point_2(w,h), Point_2(0,h)};
    return Polygon_2(points, points+4);
}

Polygon_2 Square_triangle_hole( kernel_type r){
    Point_2 points[] = {Point_2(0,0), Point_2(r/2,r* tan(CGAL_PI/3)/2), Point_2(r,0), Point_2(r,r), Point_2(0,r)};
    return Polygon_2(points, points+5);
}

Polygon_2 Hexagon( kernel_type r ){
    Point_2 points[] = {
            Point_2(0,0),
            Point_2(2*r*sin(M_PI/6),0),
            Point_2(r*(sin(M_PI/6)+1),r*cos(M_PI/6)),
            Point_2(2*r*sin(M_PI/6),2*r*cos(M_PI/6)),
            Point_2(0,2*r*cos(M_PI/6)),
            Point_2(r*(sin(M_PI/6)-1),r*cos(M_PI/6))
    };
    return Polygon_2(points, points+6);
}

Polygon_2 Triangle( kernel_type r ){
    Point_2 points[] = {
            Point_2(0,0),
            Point_2(2*r*sin(M_PI/3),0),
            Point_2(r*sin(M_PI/3),r*(1+cos(M_PI/3)))
    };
    return Polygon_2(points, points+3);
}

void Test_Square_Genetics_V01(){
    srand(time(NULL));
    std::vector<Polygon_2> polygons = {
            Square(10, 10),
            Square(10, 20),
            Square(30, 20),
            Square(30, 50),
            Square(180, 50),
            Square(80, 30),
            Square(50, 70),
            Square(40, 55)
    };

    std::cout << "flag01\n";
    std::vector<boost::dynamic_bitset<>> genes = Genetic::Create_Genetic_Population_V01<Genes_helpers::bit_parser_l1>(
            1000, polygons.size());

    std::cout << "flag02\n";
    std::vector<Genes_helpers::State> values = Genetic::Genetic_Algo_V01<Genes_helpers::bit_parser_l1>(polygons,genes, 10000);

    std::cout << "flag03\n";
    std::vector<Polygon_2> polygons_end = Genetic::Input_State_2_Vec_Polygon(polygons, values);
    std::cout << "flag04\n";
    std::cout << "Area = " << CGAL_helpers::Min_Rect_XY_Area(polygons_end) << std::endl;
    std::cout << "Intersect = " << CGAL_helpers::All_Intersection_Area(polygons_end) << std::endl;
    for (std::size_t i = 0, size = polygons_end.size(); i < size;) {
        if (i == 0)std::cout << "[\n";
        for (std::size_t j = 0, size_poly = polygons_end[i].size(); j < size_poly; ){
            if (j == 0)std::cout << "\"";
            std::cout << polygons_end[i][j].x() << "," << polygons_end[i][j].y();
            j++;
            if (j != size_poly)
                std::cout << " ";
            else
                std::cout << "\",\n";
        }
        i++;
        if (i == size)
            std::cout << "]\n";
    }
}
void Test_Square_Genetics_V02(){
    srand(time(NULL));
    std::vector<Polygon_2> polygons = {
            Square(10, 10),
            Square(10, 20),
            Square(30, 20),
            Square(30, 50),
            Square(180, 50),
            Square(80, 30),
            Square(50, 70),
            Square(40, 55)
    };

    std::cout << "flag01\n";
    std::vector<boost::dynamic_bitset<>> genes = Genetic::Create_Genetic_Population_V01<Genes_helpers::bit_parser_l1>(
            1000, polygons.size());

    std::cout << "flag02\n";
    std::vector<Genes_helpers::State> values = Genetic::Genetic_Algo_V02<Genes_helpers::bit_parser_l1>(polygons,genes, 1000000);

    std::cout << "flag03\n";
    std::vector<Polygon_2> polygons_end = Genetic::Input_State_2_Vec_Polygon(polygons, values);
    std::cout << "flag04\n";
    std::cout << "Area = " << CGAL_helpers::Min_Rect_XY_Area(polygons_end) << std::endl;
    std::cout << "Intersect = " << CGAL_helpers::All_Intersection_Area(polygons_end) << std::endl;
    for (std::size_t i = 0, size = polygons_end.size(); i < size;) {
        if (i == 0)std::cout << "[\n";
        for (std::size_t j = 0, size_poly = polygons_end[i].size(); j < size_poly; ){
            if (j == 0)std::cout << "\"";
            std::cout << polygons_end[i][j].x() << "," << polygons_end[i][j].y();
            j++;
            if (j != size_poly)
                std::cout << " ";
            else
                std::cout << "\",\n";
        }
        i++;
        if (i == size)
            std::cout << "]\n";
    }
}
void Test_Square_Genetics_V03(){
    srand(time(NULL));
    std::vector<Polygon_2> polygons = {
            Square(10, 10),
            Square(10, 20),
            Triangle(10),
            Triangle(50),
            Triangle(45),
            Hexagon(20),
            Hexagon(30),
            Hexagon(45),
            Hexagon(20),
            Square(40, 55)
    };

    std::cout << "flag01\n";
    std::vector<boost::dynamic_bitset<>> genes = Genetic::Create_Genetic_Population_V01<Genes_helpers::bit_parser_l1>(
            1000, polygons.size());

    std::cout << "flag02\n";
    std::vector<Genes_helpers::State> values = Genetic::Genetic_Algo_V02<Genes_helpers::bit_parser_l1>(polygons,genes, 10000);

    std::cout << "flag03\n";
    std::vector<Polygon_2> polygons_end = Genetic::Input_State_2_Vec_Polygon(polygons, values);
    std::cout << "flag04\n";
    std::cout << "Area = " << CGAL_helpers::Min_Rect_XY_Area(polygons_end) << std::endl;
    std::cout << "Intersect = " << CGAL_helpers::All_Intersection_Area(polygons_end) << std::endl;
    for (std::size_t i = 0, size = polygons_end.size(); i < size;) {
        if (i == 0)std::cout << "[\n";
        for (std::size_t j = 0, size_poly = polygons_end[i].size(); j < size_poly; ){
            if (j == 0)std::cout << "\"";
            std::cout << polygons_end[i][j].x() << "," << polygons_end[i][j].y();
            j++;
            if (j != size_poly)
                std::cout << " ";
            else
                std::cout << "\",\n";
        }
        i++;
        if (i == size)
            std::cout << "]\n";
    }
}
void Test_Genetic_V04(){
    srand(time(NULL));

    std::vector<Polygon_2> polygons = {
            Square(10, 10),
            Square(10, 20),
            Square(30, 20),
            Square(30, 50),
            Square(180, 50),
            Square(80, 30),
            Square(50, 70),
            Square(40, 55)
    };/*
    std::vector<Polygon_2> polygons = {
            Square(10, 10),
            Square(10, 20),
            Triangle(10),
            Triangle(50),
            Triangle(45),
            Hexagon(20),
            Hexagon(30),
            Hexagon(45),
            Hexagon(20),
            Square(40, 55),
            Square_triangle_hole(50),
            Square_triangle_hole(65),
            Square_triangle_hole(60),
    };*/

    std::cout << "flag01\n";
    std::vector<boost::dynamic_bitset<>> genes = Genetic::Create_Genetic_Population_V01<Genes_helpers::bit_parser_l1>(
            1000, polygons.size());

    std::cout << "flag02\n";
    std::vector<Genes_helpers::State> values = Genetic::Genetic_Algo_V03<Genes_helpers::bit_parser_l1>(polygons,genes, 2000);

    std::cout << "flag03\n";
    std::vector<Polygon_2> polygons_end = Genetic::Input_State_2_Vec_Polygon(polygons, values);
    std::cout << "flag04\n";
    std::cout << "Area = " << CGAL_helpers::Min_Rect_XY_Area(polygons_end) << std::endl;
    std::cout << "Intersect = " << CGAL_helpers::All_Intersection_Area(polygons_end) << std::endl;
    for (std::size_t i = 0, size = polygons_end.size(); i < size;) {
        if (i == 0)std::cout << "[\n";
        for (std::size_t j = 0, size_poly = polygons_end[i].size(); j < size_poly; ){
            if (j == 0)std::cout << "\"";
            std::cout << polygons_end[i][j].x() << "," << polygons_end[i][j].y();
            j++;
            if (j != size_poly)
                std::cout << " ";
            else
                std::cout << "\",\n";
        }
        i++;
        if (i == size)
            std::cout << "]\n";
    }
}

void Test_Intersection(){
    //p1 = 4 0 0 3 0 3 5 0 5
    //p2 = 4 0 0 10.9215 -14.308 14.896 -11.2743 3.97445 3.03376
}

int main(){
    //Test_Create_Population();
    /*
    int a;
    std::cout << "0 eh sair\n";
    std::cout << "1 eh Test_Create_Population\n";
    std::cout << "2 eh Test_Square_Genetics_V01\n";
    std::cout << "3 eh Test_Square_Genetics_V02\n";
    std::cout << "4 eh Test_Square_Genetics_V03\n";
    std::cout << "5 eh Test_Genetic_V04\n";
    std::cin >> a;
    while (a != 0){
        switch (a) {
            case 1:
                Test_Create_Population();
                break;
            case 2:
                Test_Square_Genetics_V01();
                break;
            case 3:
                Test_Square_Genetics_V02();
                break;
            case 4:
                Test_Square_Genetics_V03();
                break;
            case 5:
                Test_Genetic_V04();
                break;
        }

        std::cout << "0 eh sair\n";
        std::cout << "1 eh Test_Create_Population\n";
        std::cout << "2 eh Test_Square_Genetics_V01\n";
        std::cout << "3 eh Test_Square_Genetics_V02\n";
        std::cout << "4 eh Test_Square_Genetics_V03\n";
        std::cout << "5 eh Test_Genetic_V04\n";
        std::cin >> a;
    }
    */
    float angle = 3.14*45/180.0;
    Point_2 p(1,0);
    Transformation rotate(CGAL::ROTATION, sin(angle), cos(angle));
    p = rotate( p );
    printf( "( %f, %f )", p[0], p[1] );
    return 0;
}