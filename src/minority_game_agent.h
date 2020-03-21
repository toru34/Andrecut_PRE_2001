#ifndef MINORITY_GAME_AGENT_H_
#define MINORITY_GAME_AGENT_H_

#include <vector>

#include "config.h"
#include "minority_game_strategy.h"

class MinorityGameAgent {
private:
    std::vector<MinorityGameStrategy> strategies;
    std::vector<float> scores;
public:
    MinorityGameAgent(int, int);
};

#endif