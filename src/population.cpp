#include "population.hpp"

Population::Population(int s){
    size = s;
}

Population::~Population(){}

int Population::getSize() {
    return size;
}

void Population::createInitialPopulation() {
    std::vector<int> values;
    for(int v = 0; v < 10; v++) 
        values.push_back(v);
    for(int x = 0; x < size; x++) {
        std::random_shuffle(values.begin(), values.end());
        //Helps prevent duplicate individuals
        std::next_permutation(values.begin(), values.end());
        Individual i(values, 0);
        population.push_back(i);
    }
}
