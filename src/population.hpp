#ifndef CLASSES_POPULATION_H
#define CLASSES_POPULATION_H
#include <vector>
#include <iostream>
#include "individual.hpp"
#include <random>
#include <algorithm>
#include <ctime>

class Population {
    std::vector<Individual> population;
    int size;
    public:
        Population(int);
        virtual ~Population();
        int getSize();
        void createInitialPopulation();
};
#endif