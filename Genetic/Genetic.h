//
// Created by pedro on 13/06/2021.
//

#ifndef TG01_CODE_GENETIC_H
#define TG01_CODE_GENETIC_H

#include "Genes_helpers.h"
#include "CGAL_helpers.h"
namespace Genetic {
    typedef struct Score_struct Score_struct;

    struct Score_struct{
        kernel_type score, intersection;
        CGAL_helpers::Rect_info info;
    };

    template <class T>
    extern std::vector<boost::dynamic_bitset<>> Create_Genetic_Population_V01(std::size_t population_size,
                                                                              std::size_t n_states);

    inline void Input_State_2_Polygon( Polygon_2 &p, Genes_helpers::State *state );

    std::vector<Polygon_2> Input_State_2_Vec_Polygon(std::vector<Polygon_2> polygons,
                                                     std::vector<Genes_helpers::State> &states);

    float Score_V01(std::vector<Polygon_2> &p, const float multiply_intersection_area);

    std::size_t Generation_Algo_V01(std::vector<Polygon_2> &p, std::vector<boost::dynamic_bitset<>> &genes_population,
                    std::vector<Genes_helpers::State> &values,std::vector<float> &scores, float intersection_weight);

    std::vector<boost::dynamic_bitset<>> selection_V01(std::vector<boost::dynamic_bitset<>> &genes_population,
                                                       std::vector<float> &scores, std::size_t best);
    template <class T>
    void next_generation_V01(std::vector<boost::dynamic_bitset<>> &genes_population);

    template <class T>
    void next_generation_V02(std::vector<boost::dynamic_bitset<>> &genes_population);

    template <class T>
    void next_generation_V03(std::vector<boost::dynamic_bitset<>> &genes_population);

    template <class T>
    void next_generation_V04(std::vector<boost::dynamic_bitset<>> &genes_population);

    typedef struct geneticReturn{
        std::vector<std::size_t> index;
        std::vector<float> scoresFinal;
        std::vector<float> area;
        std::vector<float> scores;
        std::vector<float> time;
        std::vector<Genes_helpers::State> values;
    } geneticReturn;

    template <class T>
    geneticReturn Genetic_Algo_V01(std::vector<Polygon_2> &p,
                               std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations);

    template <class T>
    geneticReturn Genetic_Algo_V02(std::vector<Polygon_2> &p,
                                                       std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations);
    template <class T>
    geneticReturn Genetic_Algo_V03(std::vector<Polygon_2> &p,
                                                       std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations);

    template<class T>
    geneticReturn Genetic_Algo_knolling_V01(std::vector<Polygon_2> &p, Polygon_2 &board,
                                            std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations);
}


#endif //TG01_CODE_GENETIC_H
