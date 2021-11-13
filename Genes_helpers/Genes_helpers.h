//
// Created by pedro on 12/06/2021.
//

#ifndef TG01_CODE_GENES_HELPERS_H
#define TG01_CODE_GENES_HELPERS_H
#include "bitset"
#include "cstring"
#include "string.h"
#include "boost/dynamic_bitset.hpp"
#include "iostream"
#include "CGAL_helpers.h"
namespace Genes_helpers {

    typedef struct bit_parser_l3 bit_parser_l3;
    struct bit_parser_l3{
        ushort Position_2[4];//x and y are 0 and 2 where 1 and 3 are their decimal(2x)
        ushort angle;
    };
    typedef struct bit_parser_l1 bit_parser_l1;
    struct bit_parser_l1{
        uint value; //first 14 bits will be x(0-16383, but then limited by 10000 and divided by 10.0f), than the next 14
        //will be for y, with the same in mind. for the last 4 bits(0-15) then multiplied by 12 will be the angle
    };
    struct State{
        float Position[2];
        float angle;
    };
    typedef struct State State;

    void mutation(boost::dynamic_bitset<> &a, const uint rate);

    template<class T>
    void mutationV02(boost::dynamic_bitset<> &a, const uint rate);

    template<class T>
    void mutationV03(boost::dynamic_bitset<> &a, const uint rate, const uint object_rate );

    template<class T>
    void mutationV04(boost::dynamic_bitset<> &a, const uint rate );

    State Convert_Bits( bit_parser_l3 *bits );

    State Convert_Bits( bit_parser_l1 *bits );

    State Convert_Bits_V02( bit_parser_l1 *bits, CGAL_helpers::Rect_info *rect );

    void cross(boost::dynamic_bitset<> &a, boost::dynamic_bitset<> &b);

    template<class T>
    void crossV02(boost::dynamic_bitset<> &a, boost::dynamic_bitset<> &b);

    template<class T>
    void crossV03(boost::dynamic_bitset<> &a, boost::dynamic_bitset<> &b, const uint cross_odds );

    template<class T>
    void crossV04(boost::dynamic_bitset<> &a, boost::dynamic_bitset<> &b );

    template<class T>
    extern void convert_genes(boost::dynamic_bitset<> &genes, std::vector<State> &Values){
        const boost::dynamic_bitset<>::size_type size_structure = sizeof( T );
        const boost::dynamic_bitset<>::size_type size_structure_bits = size_structure*8;
        Values.resize(genes.size()/size_structure_bits);
        T aux_parser;
        std::bitset<size_structure_bits> aux;
        State aux_transform;

        for ( size_t index_vector = 0, size_vector = Values.size(); index_vector < size_vector; ++index_vector) {
            for (boost::dynamic_bitset<>::size_type i = 0; i < size_structure_bits; ++i) {
                aux[i] = genes[index_vector*size_structure + i];
            }
            memcpy( &aux_parser, &aux, size_structure );
            Values[ index_vector ] = Convert_Bits(&aux_parser);

        }
    }

    template<class T>
    extern void convert_genes_V02(boost::dynamic_bitset<> &genes, std::vector<State> &Values, CGAL_helpers::Rect_info *rect){
        const boost::dynamic_bitset<>::size_type size_structure = sizeof( T );
        const boost::dynamic_bitset<>::size_type size_structure_bits = size_structure*8;
        Values.resize(genes.size()/size_structure_bits);
        T aux_parser;
        std::bitset<size_structure_bits> aux;
        State aux_transform;
        for ( size_t index_vector = 0, size_vector = Values.size(); index_vector < size_vector; ++index_vector) {
            for (boost::dynamic_bitset<>::size_type i = 0; i < size_structure_bits; ++i) {
                aux[i] = genes[index_vector*size_structure + i];
            }

            memcpy( &aux_parser, &aux, size_structure );

            Values[ index_vector ] = Convert_Bits_V02(&aux_parser, rect);

        }
    }
}


#endif //TG01_CODE_GENES_HELPERS_H
