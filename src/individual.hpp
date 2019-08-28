#ifndef CLASSES_INDIVIDUAL_H
#define CLASSES_INDIVIDUAL_H
#include <vector>
#include <iostream>

class Individual {
    public:
        Individual();
        virtual ~Individual();
    private:
        std::vector<int> chromossome;
        int fitness = 0;
};
#endif