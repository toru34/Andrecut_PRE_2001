#ifndef MINORITY_GAME_H_
#define MINORITY_GAME_H_

#include <vector>

#include "config.h"

class MinorityGameStrategy {
private:
    std::vector<int> actions;
public:
    MinorityGameStrategy(int);
    int pick_action(int);
};

#endif