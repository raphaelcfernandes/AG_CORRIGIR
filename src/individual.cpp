#include "individual.hpp"

Individual::Individual(std::vector<int> c, int f) {
    chromossome = c;
    fitness = f;
}

Individual::~Individual() {}

void Individual::getChromossome() {
    for (std::vector<int>::iterator it = chromossome.begin() ; it != chromossome.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}