//
// Created by pedro on 13/06/2021.
//

#include "Genetic.h"
#include <ctime>

namespace Genetic {
    template <class T>
    extern std::vector<boost::dynamic_bitset<>> Create_Genetic_Population_V01(std::size_t population_size, std::size_t n_states){
        std::vector<boost::dynamic_bitset<>> Population = std::vector<boost::dynamic_bitset<>>(population_size);//foo( sizeof( bit_parser )*8*4 ), foo1(sizeof( bit_parser )*8*4 );
        const u_char prob_step_groups = 5;
        const u_char number_groups = 100/prob_step_groups - 2;//0% and 100% are out of the equation
        const std::size_t structure_size_bits = sizeof( T )*8;
        std::size_t group_sizes = ceil(float (population_size/number_groups));

        u_char prob = prob_step_groups;
        for (std::size_t i = 1; i < population_size; ) {
            for (std::size_t j = 0; j < group_sizes && i < population_size; ++i, ++j){
                Population[i] = boost::dynamic_bitset<>(structure_size_bits*n_states);

                Genes_helpers::mutation(Population[i], prob);
            }
            prob += prob_step_groups;
        }

        return Population;
    }

    template std::vector<boost::dynamic_bitset<>> Create_Genetic_Population_V01<Genes_helpers::bit_parser_l1>(
            std::size_t population_size, std::size_t n_states);

    template std::vector<boost::dynamic_bitset<>> Create_Genetic_Population_V01<Genes_helpers::bit_parser_l3>(
            std::size_t population_size, std::size_t n_states);

    inline void Input_State_2_Polygon( Polygon_2 &p, Genes_helpers::State *state ){
        Vector_2 v( state->Position[0], state->Position[1]);
        CGAL_helpers::Rotate_Polygon_degree( p, state->angle);
        CGAL_helpers::Translate_Polygon( p, v);
    }

    std::vector<Polygon_2> Input_State_2_Vec_Polygon(std::vector<Polygon_2> polygons,
                                                     std::vector<Genes_helpers::State> &states){
        for (std::size_t i = 0, size_polygons = polygons.size(); i < size_polygons; ++i) {
            Input_State_2_Polygon(polygons[i], &states[i]);
        }

        return polygons;
    }

    float Score_V01(std::vector<Polygon_2> &p, const float multiply_intersection_area){
        kernel_type area_rect = CGAL_helpers::Min_Rect_XY_Area_V01(p);
        kernel_type intersection_areas = CGAL_helpers::All_Intersection_Area(p);
        return area_rect + intersection_areas*multiply_intersection_area;
    }

    Score_struct Score_V02(std::vector<Polygon_2> &p, const float multiply_intersection_area){
        CGAL_helpers::Rect_info rect_inf = CGAL_helpers::Min_Rect_XY_Area_V02(p);
        kernel_type intersection_areas = CGAL_helpers::All_Intersection_Area(p);
        kernel_type score;

        score = rect_inf.x_max*rect_inf.y_max;

        return {score + intersection_areas*multiply_intersection_area, intersection_areas, rect_inf};
    }

    std::size_t Generation_Algo_V01(std::vector<Polygon_2> &p, std::vector<boost::dynamic_bitset<>> &genes_population,
                 std::vector<Genes_helpers::State> &values,std::vector<float> &scores, float intersection_weight){
        std::vector<Polygon_2> poly_aux;
        std::size_t size_population = genes_population.size(), best_index_score = 0;
        std::vector<Genes_helpers::State> values_aux;
        for (std::size_t i = 0; i < size_population; ++i) {
            Genes_helpers::convert_genes<Genes_helpers::bit_parser_l1>(genes_population[i], values_aux);
            if ( i == 0 ) values = values_aux;
            poly_aux = Input_State_2_Vec_Polygon(p, values_aux);
            scores[i] = Score_V01(poly_aux, intersection_weight);
            if (scores[best_index_score] > scores[i]) {
                best_index_score = i;
                values = values_aux;
            }
        }

        return best_index_score;
    }

    std::vector<std::size_t> Generation_Algo_V02(std::vector<Polygon_2> &p, std::vector<boost::dynamic_bitset<>> &genes_population,
                                                 std::vector<Genes_helpers::State> &values,std::vector<float> &scores, float intersection_weight){
        std::vector<Polygon_2> poly_aux;
        std::size_t size_population = genes_population.size(), best_index_score = 0;
        std::size_t size_best = 0.2*size_population, num_index = 0;
        std::vector<std::size_t> best_indexes(size_best);
        std::priority_queue <std::pair<float, std::size_t>, std::vector<std::pair<float, std::size_t>>,
                std::greater<std::pair<float, std::size_t>>  > pq;
        float worst_score = std::numeric_limits<float>::max();
        for (std::size_t i = 0; i < size_population; ++i) {
            Genes_helpers::convert_genes<Genes_helpers::bit_parser_l1>(genes_population[i], values);
            poly_aux = Input_State_2_Vec_Polygon(p, values);
            scores[i] = Score_V01(poly_aux, intersection_weight);
            if (num_index < size_best ) {
                num_index++;
                pq.push(std::pair<float, std::size_t>(scores[i], i));
                if (scores[i] > worst_score) worst_score = scores[i];
            }else if(scores[i] < worst_score){
                pq.push(std::pair<float, std::size_t>(scores[i], i));
            }
        }

        for (std::size_t i = 0; i < size_best; ++i) {
            best_indexes[i] = pq.top().second;
            pq.pop();
        }
        Genes_helpers::convert_genes<Genes_helpers::bit_parser_l1>(genes_population[best_indexes[0]], values);
        return best_indexes;
    }
    typedef struct Generation_Algo_V03_struct Generation_Algo_V03_struct;
    struct Generation_Algo_V03_struct{
        std::vector<std::size_t> best_indexes;
        CGAL_helpers::Rect_info rect;
    };

    Generation_Algo_V03_struct Generation_Algo_V03(std::vector<Polygon_2> &p, std::vector<boost::dynamic_bitset<>> &genes_population,
                 std::vector<Genes_helpers::State> &values,std::vector<float> &scores, float intersection_weight, CGAL_helpers::Rect_info rect, float best_score, bool change_rect){
        std::vector<Polygon_2> poly_aux;
        std::size_t size_population = genes_population.size(), best_index_score = 0;
        std::size_t size_best = 0.2*size_population, num_index = 0;
        std::vector<std::size_t> best_indexes(size_best);
        std::priority_queue <std::pair<float, std::size_t>, std::vector<std::pair<float, std::size_t>>,
                std::greater<std::pair<float, std::size_t>>  > pq;
        float worst_score = std::numeric_limits<float>::max();
        Score_struct score_aux;
        CGAL_helpers::Rect_info best_rect;
        best_rect = rect;
        //std::cout << "Flag02_01" << std::endl;
        for (std::size_t i = 0; i < size_population; ++i) {
            Genes_helpers::convert_genes_V02<Genes_helpers::bit_parser_l1>(genes_population[i], values, &rect);
            poly_aux = Input_State_2_Vec_Polygon(p, values);

            score_aux = Score_V02(poly_aux, intersection_weight);
            if ( change_rect && best_rect.area > score_aux.info.area && score_aux.intersection == 0 && score_aux.score < best_score) {
                best_rect = score_aux.info;
                best_score = score_aux.score;
                std::cout << "Flag02_05" << std::endl;
            }
            scores[i] = score_aux.score;
            if (num_index < size_best ) {
                num_index++;
                pq.push(std::pair<float, std::size_t>(scores[i], i));
                if (scores[i] > worst_score) worst_score = scores[i];
            }else if(scores[i] < worst_score){
                pq.push(std::pair<float, std::size_t>(scores[i], i));
            }
        }

        for (std::size_t i = 0; i < size_best; ++i) {
            best_indexes[i] = pq.top().second;
            pq.pop();
        }
        Genes_helpers::convert_genes<Genes_helpers::bit_parser_l1>(genes_population[best_indexes[0]], values);
        return {best_indexes, best_rect};
    }

    std::vector<boost::dynamic_bitset<>> selection_V01(std::vector<boost::dynamic_bitset<>> &genes_population, std::vector<float> &scores, std::size_t best){
        std::size_t size_vector = genes_population.size();
        std::vector<boost::dynamic_bitset<>> new_population(size_vector);
        new_population[0] = genes_population[best];
        std::size_t index_01, index_02;
        for (std::size_t i = 1; i < size_vector; ++i) {
            index_01 = rand()%size_vector;
            index_02 = rand()%size_vector;
            if (scores[index_01] < scores[index_02] )
                new_population[i] = genes_population[index_01];
            else
                new_population[i] = genes_population[index_02];
        }

        return new_population;

    }

    std::vector<boost::dynamic_bitset<>> selection_V02(std::vector<boost::dynamic_bitset<>> &genes_population, std::vector<float> &scores, std::vector<std::size_t> &best){
        std::size_t size_vector = genes_population.size(), size_best = best.size(), i = 0;
        std::vector<boost::dynamic_bitset<>> new_population(size_vector);
        std::size_t index_01, index_02;
        for (; i < size_best; ++i) {
            new_population[i] = genes_population[best[i]];
        }
        for (; i < 0.7*size_vector; ++i) {
            index_01 = rand()%size_best;
            new_population[i] = genes_population[best[index_01]];
        }
        for (; i < size_vector; ++i) {
            index_01 = rand()%size_vector;
            index_02 = rand()%size_vector;
            if (scores[index_01] < scores[index_02] )
                new_population[i] = genes_population[index_01];
            else
                new_population[i] = genes_population[index_02];
        }
        return new_population;

    }

    template <class T>
    void next_generation_V01(std::vector<boost::dynamic_bitset<>> &genes_population){
        //keeps the best result untouched
        std::size_t i = 1;
        for (std::size_t size_vector = 0.2*genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 5 && i + 1 < size_vector ) {
                Genes_helpers::cross(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 5 ) {
                Genes_helpers::mutation(genes_population[i], (1000 * i) / size_vector );
            }
        }

        for (std::size_t size_vector = 0.5*genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 10 && i + 1 < size_vector ) {
                Genes_helpers::cross(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 10 ) {
                Genes_helpers::mutation(genes_population[i], (2000 * i) / size_vector);
            }
        }

        for (std::size_t size_vector = 0.75*genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 40 && i + 1 < size_vector ) {
                Genes_helpers::cross(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 50 ) {
                Genes_helpers::mutation(genes_population[i], (10000 * i) / size_vector);
            }
        }

        for (std::size_t size_vector = genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 80 && i + 1 < size_vector ) {
                Genes_helpers::cross(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 90 ) {
                Genes_helpers::mutation(genes_population[i], (50000 * i) / size_vector);
            }
        }
    }

    template void next_generation_V01<Genes_helpers::bit_parser_l1>(std::vector<boost::dynamic_bitset<>> &genes_population);
    template void next_generation_V01<Genes_helpers::bit_parser_l3>(std::vector<boost::dynamic_bitset<>> &genes_population);

    template <class T>
    void next_generation_V02(std::vector<boost::dynamic_bitset<>> &genes_population){
        //keeps the best result untouched
        std::size_t i = 0.2*genes_population.size();

        for (std::size_t size_vector = 0.5*genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 0 && i + 1 < size_vector ) {
                Genes_helpers::cross(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 100 ) {
                Genes_helpers::mutation(genes_population[i], 400);
            }
        }

        for (std::size_t size_vector = 0.75*genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 75 && i + 1 < size_vector ) {
                Genes_helpers::cross(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 90 ) {
                Genes_helpers::mutation(genes_population[i], 1000);
            }
        }

        for (std::size_t size_vector = genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 30 && i + 1 < size_vector ) {
                Genes_helpers::cross(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 100 ) {
                Genes_helpers::mutation(genes_population[i], 3000);
            }
        }
    }

    template void next_generation_V02<Genes_helpers::bit_parser_l1>(std::vector<boost::dynamic_bitset<>> &genes_population);
    template void next_generation_V02<Genes_helpers::bit_parser_l3>(std::vector<boost::dynamic_bitset<>> &genes_population);

    template <class T>
    void next_generation_V03(std::vector<boost::dynamic_bitset<>> &genes_population){
        //keeps the best result untouched
        std::size_t i = 1;
        for (std::size_t size_vector = 0.2*genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 5 && i + 1 < size_vector ) {
                Genes_helpers::crossV02<T>(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 5 ) {
                Genes_helpers::mutationV02<T>(genes_population[i], (1000 * i) / size_vector );
            }
        }

        for (std::size_t size_vector = 0.5*genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 10 && i + 1 < size_vector ) {
                Genes_helpers::crossV02<T>(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 10 ) {
                Genes_helpers::mutationV02<T>(genes_population[i], (2000 * i) / size_vector);
            }
        }

        for (std::size_t size_vector = 0.75*genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 40 && i + 1 < size_vector ) {
                Genes_helpers::crossV02<T>(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 50 ) {
                Genes_helpers::mutationV02<T>(genes_population[i], (10000 * i) / size_vector);
            }
        }

        for (std::size_t size_vector = genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 80 && i + 1 < size_vector ) {
                Genes_helpers::crossV02<T>(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 90 ) {
                Genes_helpers::mutationV02<T>(genes_population[i], (50000 * i) / size_vector);
            }
        }
    }

    template void next_generation_V03<Genes_helpers::bit_parser_l1>(std::vector<boost::dynamic_bitset<>> &genes_population);
    template void next_generation_V03<Genes_helpers::bit_parser_l3>(std::vector<boost::dynamic_bitset<>> &genes_population);


    template <class T>
    void next_generation_V04(std::vector<boost::dynamic_bitset<>> &genes_population){
        //keeps the best result untouched
        std::size_t i = 0.2*genes_population.size();

        for (std::size_t size_vector = 0.5*genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 0 && i + 1 < size_vector ) {
                Genes_helpers::crossV02<T>(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 100 ) {
                Genes_helpers::mutationV02<T>(genes_population[i], 400);
            }
        }

        for (std::size_t size_vector = 0.75*genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 75 && i + 1 < size_vector ) {
                Genes_helpers::crossV02<T>(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 90 ) {
                Genes_helpers::mutationV02<T>(genes_population[i], 1000);
            }
        }

        for (std::size_t size_vector = genes_population.size(); i < size_vector; ++i) {
            if ( rand()%100 < 30 && i + 1 < size_vector ) {
                Genes_helpers::crossV02<T>(genes_population[i], genes_population[i + 1]);
            }
            if ( rand()%100 < 100 ) {
                Genes_helpers::mutationV02<T>(genes_population[i], 3000);
            }
        }
    }

    template void next_generation_V04<Genes_helpers::bit_parser_l1>(std::vector<boost::dynamic_bitset<>> &genes_population);
    template void next_generation_V04<Genes_helpers::bit_parser_l3>(std::vector<boost::dynamic_bitset<>> &genes_population);

    template<class T>
    geneticReturn Genetic_Algo_V01(std::vector<Polygon_2> &p,
                                                       std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations){

        geneticReturn results;
        std::vector<Polygon_2> polygons_aux;
        std::size_t size_population = genes_population.size();
        std::vector<Genes_helpers::State> values;
        //std::vector<std::size_t> selected_indexes(size_population);
        std::vector<float> scores(size_population);
        std::size_t best_index;
        float area_aux;
        float intersection_weight_max = std::numeric_limits<float>::max();
        std::clock_t start;

        for (std::size_t i = 0; i < generations; ++i) {
            if ( i < 0.75*generations )
                best_index = Generation_Algo_V01(p, genes_population, values, scores, 10 + (4000000.0*(i+1))/generations );
            else
                best_index = Generation_Algo_V01(p, genes_population, values, scores, intersection_weight_max);
            if( i % 10 == 0 || i == (generations - 1) ) {
                results.index.push_back(i);
                results.scores.push_back(scores[best_index]);
                polygons_aux = Input_State_2_Vec_Polygon(p, values);
                area_aux = CGAL_helpers::Min_Rect_XY_Area(polygons_aux);
                results.area.push_back(area_aux);
                results.scoresFinal.push_back( area_aux +
                    intersection_weight_max*CGAL_helpers::All_Intersection_Area(polygons_aux) );

                results.time.push_back((std::clock() - start) / (float)(CLOCKS_PER_SEC / 1000));
                if( i == (generations - 1) ){
                    results.values = values;
                    break;
                }

            }
            genes_population = selection_V01(genes_population, scores, best_index);
            next_generation_V01<T>(genes_population);
        }

        return results;
    }

    template geneticReturn Genetic_Algo_V01<Genes_helpers::bit_parser_l1>(std::vector<Polygon_2> &p,
                                                                                              std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations = 1000);
    template geneticReturn Genetic_Algo_V01<Genes_helpers::bit_parser_l3>(std::vector<Polygon_2> &p,
                                                                                              std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations = 1000);

    template<class T>
    geneticReturn Genetic_Algo_V02(std::vector<Polygon_2> &p,
                                                       std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations){
        geneticReturn results;
        std::size_t size_population = genes_population.size();
        std::vector<Genes_helpers::State> values;
        //std::vector<std::size_t> selected_indexes(size_population);
        std::vector<float> scores(size_population);
        std::vector<std::size_t> best_indexes;
        float area_aux;
        float intersection_weight_max = std::numeric_limits<float>::max();
        std::clock_t start;
        std::vector<Polygon_2> polygons_aux;
        for (std::size_t i = 0; i < generations; ++i) {
            if ( i < 0.75*generations )
                best_indexes = Generation_Algo_V02(p, genes_population, values, scores, 10+(4000000.0*(i+1))/generations);
            else
                best_indexes = Generation_Algo_V02(p, genes_population, values, scores, std::numeric_limits<float>::max());

            if( i % 10 == 0 || i == (generations - 1) ) {
                results.index.push_back(i);
                results.scores.push_back(scores[best_indexes[0]]);
                polygons_aux = Input_State_2_Vec_Polygon(p, values);
                area_aux = CGAL_helpers::Min_Rect_XY_Area(polygons_aux);
                results.area.push_back(area_aux);
                results.scoresFinal.push_back( area_aux +
                                               intersection_weight_max*CGAL_helpers::All_Intersection_Area(polygons_aux) );

                results.time.push_back((std::clock() - start) / (float)(CLOCKS_PER_SEC / 1000));
                if( i == (generations - 1) ){
                    results.values = values;
                    break;
                }

            }
            genes_population = selection_V02(genes_population, scores, best_indexes);
            next_generation_V02<T>(genes_population);
        }
        std::cout << "Best Score = " << scores[best_indexes[0]] << std::endl;
        Genes_helpers::convert_genes<Genes_helpers::bit_parser_l1>(genes_population[best_indexes[0]], values);
        return results;
    }

    template geneticReturn Genetic_Algo_V02<Genes_helpers::bit_parser_l1>(std::vector<Polygon_2> &p,
                                                                                              std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations = 1000);
    template geneticReturn Genetic_Algo_V02<Genes_helpers::bit_parser_l3>(std::vector<Polygon_2> &p,
                                                                                              std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations = 1000);

    template<class T>
    geneticReturn Genetic_Algo_V03(std::vector<Polygon_2> &p,
                                                       std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations){
        geneticReturn results;
        std::size_t size_population = genes_population.size();
        std::vector<Genes_helpers::State> values;
        //std::vector<std::size_t> selected_indexes(size_population);
        std::vector<float> scores(size_population);
        float best_score = std::numeric_limits<float>::max();
        CGAL_helpers::Rect_info best_rect = {
                                             500,
                                             500,
                                             500*500};
        Generation_Algo_V03_struct info;
        kernel_type area_aux;
        float intersection_weight_max = std::numeric_limits<float>::max();
        std::clock_t start;
        std::vector<Polygon_2> polygons_aux;
        for (std::size_t i = 0; i < generations; ++i) {
            if ( i < 0.75*generations )
                info = Generation_Algo_V03(p, genes_population, values, scores, 10+(4000000.0*(i+1))/generations, best_rect, best_score, true);
            else
                info = Generation_Algo_V03(p, genes_population, values, scores, std::numeric_limits<float>::max(), best_rect, best_score, i < 0.8*generations);

            best_rect = info.rect;
            if( i % 10 == 0 || i == (generations - 1) ) {
                results.index.push_back(i);
                results.scores.push_back(scores[info.best_indexes[0]]);
                area_aux = info.rect.area;
                results.area.push_back(area_aux);
                polygons_aux = Input_State_2_Vec_Polygon(p, values);
                results.scoresFinal.push_back( area_aux +
                                               intersection_weight_max*CGAL_helpers::All_Intersection_Area(polygons_aux) );

                results.time.push_back((std::clock() - start) / (float)(CLOCKS_PER_SEC / 1000));
                if( i == (generations - 1) ){
                    results.values = values;
                    break;
                }

            }
            genes_population = selection_V02(genes_population, scores, info.best_indexes);
            next_generation_V02<T>(genes_population);
            best_score = scores[info.best_indexes[0]];
        }
        std::cout << "Best Score = " << scores[info.best_indexes[0]] << std::endl;
        std::cout << "best_rect.area = " << best_rect.area << std::endl;
        std::cout << "best_rect.x_max = " << best_rect.x_max << std::endl;
        std::cout << "best_rect.y_max = " << best_rect.y_max << std::endl;
        return results;
    }

    template geneticReturn Genetic_Algo_V03<Genes_helpers::bit_parser_l1>(std::vector<Polygon_2> &p,
                                                                                              std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations = 1000);
    template geneticReturn Genetic_Algo_V03<Genes_helpers::bit_parser_l3>(std::vector<Polygon_2> &p,
                                                                                              std::vector<boost::dynamic_bitset<>> &genes_population, std::size_t generations = 1000);
}