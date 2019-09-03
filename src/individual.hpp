#ifndef CLASSES_INDIVIDUAL_H
#define CLASSES_INDIVIDUAL_H
#include <vector>
#include <iostream>

class Individual {
    std::vector<int> chromossome;
    int fitness = 0;

    public:
        Individual(std::vector<int>, int);
        virtual ~Individual();    
        void getChromossome();
};
#endif