#include "fitness.hpp"

Fitness::Fitness() {}

Fitness::~Fitness() {}

int Fitness::sendMoreMoney(std::vector<int> chromossome) {
    int carryOn = 0, sum = 0, total;
    ///SEND + MORE = MONEY
    
    if(chromossome[3] + chromossome[1] >= 10) {//D+E
        carryOn = 1;
        sum += abs((chromossome[3] + chromossome[1] - 10) - chromossome[7]);
    } else {
        sum += abs((chromossome[3] + chromossome[1]) - chromossome[7]);
    }
    
    if((chromossome[2] + chromossome[6] + carryOn) >= 10) {//N+R
        sum += abs((chromossome[2] + chromossome[6] + carryOn - 10) - chromossome[1]);
        carryOn = 1;
    } else {
        sum += abs(chromossome[2] + chromossome[6] + carryOn - chromossome[1]);
        carryOn = 0;
    }

    if((chromossome[1] + chromossome[5] + carryOn) >= 10) {//E+O
        sum += abs((chromossome[1] + chromossome[5] + carryOn - 10) - chromossome[2]);
        carryOn = 1;
    } else {
        sum += abs(chromossome[1] + chromossome[5] + carryOn - chromossome[2]);
        carryOn = 0;
    }

    if((chromossome[0]+chromossome[4]+carryOn)>=10) {//S+M
        sum += abs((chromossome[0]+chromossome[4]+carryOn-10)-chromossome[5]);
        carryOn=1;
    } else {
        sum+=abs(chromossome[0]+chromossome[4]+carryOn-chromossome[5]);
        carryOn=0;
    }

    sum += abs(chromossome[4] - carryOn);

    return sum;
}