#include "library.h"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
#include <iostream>

void hello() {
    std::cout << "Hello, World!" << std::endl;
}
template <class T>
boost::python::list toPythonList(std::vector<T> vector) {
    typename std::vector<T>::iterator iter;
    boost::python::list list;
    for (iter = vector.begin(); iter != vector.end(); ++iter) {
        list.append(*iter);
    }
    return list;
}

boost::python::list Point_3toPythonList(Point_3 point){
    boost::python::list list;
    list.append(point[0]);
    list.append(point[1]);
    list.append(point[2]);

    return list;
}
boost::python::list Point_3VectorPythonList(std::vector<Point_3> vector){
    typename std::vector<Point_3>::iterator iter;
    boost::python::list list;
    for (iter = vector.begin(); iter != vector.end(); ++iter) {
        list.append(Point_3toPythonList(*iter));
    }
    return list;
}

boost::python::list Point_2toPythonList(Point_2 point){
    boost::python::list list;
    list.append(point[0]);
    list.append(point[1]);

    return list;
}
boost::python::list Point_2VectorPythonList(std::vector<Point_2> vector){
    typename std::vector<Point_2>::iterator iter;
    boost::python::list list;
    for (iter = vector.begin(); iter != vector.end(); ++iter) {
        list.append(Point_2toPythonList(*iter));
    }
    return list;
}

boost::python::list QuaterniontoPythonList(std::vector<kernel_type> vector){
    return toPythonList<kernel_type>(vector);
}
boost::python::list teste(){
    std::vector<int> a = {1,2,3};

    return toPythonList(a);
}

void teste2(boost::python::list lista){
    ssize_t size_lista = len(lista);
    ssize_t i = 0;
    std::cout << "size = " << size_lista << std::endl;
    while ( i < size_lista){
        std::cout << boost::python::extract<int>(lista[i]) << " ";
        i++;
    }
    std::cout << "\n";
}

void teste3(){
    Cad_Data n;
    n.printa();
}
using namespace boost;
std::vector<Cad_Data> get_Cad_Data( python::list vertexes, python::list positions, python::list quaternion){
    Cad_Data cad_new;
    std::vector<Cad_Data> vec_data;

    ssize_t size_list = len(vertexes);
    ssize_t i = 0;
    python::list pos, vertex_list;
    while ( i < size_list ){
        cad_new = Cad_Data();
        pos = python::extract<python::list>(positions[i] );
        cad_new.position = Point_3(
                python::extract<kernel_type>(pos[0]),
                python::extract<kernel_type>(pos[1]),
                python::extract<kernel_type>(pos[2])
        );

        ssize_t j = 0;
        ssize_t size_vertexes = len( vertexes[i] );

        pos = python::extract<python::list>(vertexes[i] );
        while ( j < size_vertexes ){
            vertex_list = python::extract<python::list>(pos[j] );
            cad_new.vertexes.push_back( Point_3(
                    python::extract<kernel_type>(vertex_list[0]) - cad_new.position[0],
                    python::extract<kernel_type>(vertex_list[1]) - cad_new.position[1],
                    python::extract<kernel_type>(vertex_list[2]) - cad_new.position[2]
                    ) );
            j++;
        }

        pos = python::extract<python::list>(quaternion[i] );
        cad_new.quaternion[0] = python::extract<kernel_type>(pos[0]);
        cad_new.quaternion[1] = python::extract<kernel_type>(pos[1]);
        cad_new.quaternion[2] = python::extract<kernel_type>(pos[2]);
        cad_new.quaternion[3] = python::extract<kernel_type>(pos[3]);

        vec_data.push_back(cad_new);
        i++;
    }

    return vec_data;

}
Cad_Data Create_Cad(){
    Cad_Data n;
    n.quaternion = {1,2,3,7};

    n.position = Point_3(3,4,5);
    n.vertexes = {Point_3(7,4,5)};
    return n;
}

void Module_Add_CGAL_Point_3(){
    python::class_<Point_3>("Point_3"
    );
    //.def("x", &Point_3::x)
    //.def("y", &Point_3::y)
    //.def("z", &Point_3::z);
    //.def("__getitem__", &Point_3::operator[]);
}
void Module_Add_CGAL_Point_2(){
    python::class_<Point_2>("Point_2"
    );
    //.def("x", &Point_3::x)
    //.def("y", &Point_3::y)
    //.def("z", &Point_3::z);
    //.def("__getitem__", &Point_3::operator[]);
}

void Module_Add_CGAL(){
    Module_Add_CGAL_Point_3();
    Module_Add_CGAL_Point_2();
}

void Module_Add_Cad_Data(){
    python::class_<Cad_Data>("Cad_Data"
            )
            .def_readwrite("vertexes", &Cad_Data::vertexes)
            .def_readwrite("position", &Cad_Data::position)
            .def_readwrite("quaternion", &Cad_Data::quaternion)
            .def("projection_XY", &Cad_Data::projection_XY)
            .def("printa", &Cad_Data::printa);
}

void Module_Add_Cad_Data_XY(){
    python::class_<Cad_Data_XY>("Cad_Data_XY"
    )
            .def_readwrite("vertexes", &Cad_Data_XY::vertexes)
            .def_readwrite("position", &Cad_Data_XY::position)
            .def_readwrite("angle", &Cad_Data_XY::angle);
}

template <class T>
void Module_Add_Vector_Template(const char* name){
    python::class_<std::vector<T>>(name
            )
            .def(python::vector_indexing_suite<std::vector<T> >());
}

void Module_Add_Vectors(){
    //python::implicitly_convertible<std::string, Cad_Data>();
    Module_Add_Vector_Template<Cad_Data>("Cad_DataVec");
    Module_Add_Vector_Template<Cad_Data_XY>("Cad_Data_XYVec");
    Module_Add_Vector_Template<Point_3>("Point3Vec");
    Module_Add_Vector_Template<Point_2>("Point2Vec");
    Module_Add_Vector_Template<bool>("BoolVec");
    Module_Add_Vector_Template<float>("FloatVec");
    Module_Add_Vector_Template<kernel_type>("Kernel_TypeVec");
}

void Module_Add_List_Converter(){
    using namespace boost::python;
    def("Point_3toPythonList", Point_3toPythonList, args("point"));
    def("Point_3VectorPythonList", Point_3VectorPythonList, args("vector"));
    def("Point_2toPythonList", Point_2toPythonList, args("point"));
    def("Point_2VectorPythonList", Point_2VectorPythonList, args("vector"));
    def("QuaterniontoPythonList", QuaterniontoPythonList, args("vector"));
}

void Add_Cad_Data(){
    Module_Add_Cad_Data();
    Module_Add_Cad_Data_XY();
    using namespace boost::python;
    def("Project_Cad_Data_Vector", Project_Cad_Data_Vector, args("vector"));
}

BOOST_PYTHON_MODULE(TG01_Code)
{
    using namespace boost::python;
    def("hello", hello);
    def("teste", teste);
    def("teste2", teste2, args("lista"));
    def("teste3", teste3);
    Add_Cad_Data();
    Module_Add_CGAL();
    Module_Add_Vectors();
    Module_Add_List_Converter();
    def("Create_Cad", Create_Cad);
    def("get_Cad_Data", get_Cad_Data, args("vertexes"), args("positions"), args("quaternions"));

}
