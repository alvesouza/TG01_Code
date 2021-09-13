//
// Created by pedro on 12/06/2021.
//

#include "Genes_helpers.h"
#include "iostream"
using namespace Genes_helpers;
typedef bit_parser_l1 bit_parser;
int main(){
    srand(time(NULL));
    boost::dynamic_bitset<> foo( sizeof( bit_parser )*8*4 ), foo1(sizeof( bit_parser )*8*4 );
    std::vector<State> Values;
    foo1.set();
    std::cout << "size foo = " << foo.size() << std::endl;
    std::cout << "foo0 tostring = " << foo <<std::endl;
    std::cout << "foo1 tostring = " << foo1 <<std::endl;
    convert_genes<bit_parser>( foo, Values );
    for ( size_t index_vector = 0, size_vector = Values.size(); index_vector < size_vector; ++index_vector) {
        std::cout << "Values[" << index_vector << "].Position = ( " << Values[index_vector].Position[0] << ", " <<
                                    Values[index_vector].Position[1] << ")\n";
        std::cout << "Values[" << index_vector << "].angle = " << Values[index_vector].angle << std::endl;
        std::cout << "////////////////" << std::endl;
    }
    std::cout << "Ended now cross" << std::endl;
    //foo[0] = 1;
    cross( foo, foo1);
    //cross( foo, foo1);
    mutation( foo, 10 );
    convert_genes<bit_parser>( foo, Values );
    std::cout << "end02" << std::endl;
    std::cout << "foo0 tostring = " << foo <<std::endl;
    std::cout << "foo1 tostring = " << foo1 <<std::endl;
    for ( size_t index_vector = 0, size_vector = Values.size(); index_vector < size_vector; ++index_vector) {
        std::cout << "Values[" << index_vector << "].Position = ( " << Values[index_vector].Position[0] << ", " <<
                  Values[index_vector].Position[1] << ")\n";
        std::cout << "Values[" << index_vector << "].angle = " << Values[index_vector].angle << std::endl;
        std::cout << "////////////////" << std::endl;
    }
    return 0;
}

