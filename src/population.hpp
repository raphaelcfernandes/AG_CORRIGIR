#ifndef CLASSES_POPULATION_H
#define CLASSES_POPULATION_H
#include "individual.hpp"
#include <iostream>

class Population {
    public:
        Population();
        virtual ~Population();
    private:
        std::vector<Individual> chromossome;
};
#endif
