#ifndef TG01_CODE_LIBRARY_H
#define TG01_CODE_LIBRARY_H
#include "boost/python.hpp"
#include "iostream"
#include "Cad_Data.h"
#include "CGAL_Setup.h"
#include "Genes_helpers.h"
#include "Genetic.h"
void hello();

template <class T>
boost::python::list toPythonList(std::vector<T> vector);
boost::python::list Point_3toPythonList(Point_3 point);
boost::python::list Point_3VectorPythonList(std::vector<Point_3> vector);
boost::python::list Point_2toPythonList(Point_2 point);
boost::python::list Point_2VectorPythonList(std::vector<Point_2> vector);
//boost::python::list QuaterniontoPythonList(std::vector<kernel_type> vector);
boost::python::list teste();
Cad_Data Create_Cad();

using namespace boost;
std::vector<Cad_Data> get_Cad_Data( python::list vertexes, python::list positions );
void teste2(python::list lista);
#endif //TG01_CODE_LIBRARY_H
