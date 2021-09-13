PROJECT(Genes_helpers)
SET(GCC_COVERAGE_COMPILE_FLAGS "-fPIC -Wl,--no-undefined")
SET(GCC_COVERAGE_LINK_FLAGS    "")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_library( Genes_helpers Genes_helpers.h Genes_helpers.cpp)
#ADD_SUBDIRECTORY(../CGAL_Setup)
#target_link_libraries(Cad_Data INTERFACE ../CGAL_Setup)
target_include_directories ( Genes_helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories( Genes_helpers PUBLIC "${CGAL_helpers_SOURCE_DIR}")
target_link_libraries(Genes_helpers LINK_PUBLIC CGAL_helpers)

PROJECT(Test_Genes_helpers)

#target_link_libraries(Test_Genes_helpers LINK_PUBLIC Genes_helpers)
add_executable(Test_Genes_helpers test.cpp )
target_link_libraries(Test_Genes_helpers LINK_PUBLIC Genes_helpers)