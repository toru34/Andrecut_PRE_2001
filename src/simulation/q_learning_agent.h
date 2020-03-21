#ifndef Q_LEARNING_AGENT_H_
#define Q_LEARNING_AGENT_H_

#include <vector>
#include <random>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "config.h"
#include "minority_game_strategy.h"

class QLearningAgent {
private:
    float learning_rate;
    float discount_factor;
    float epsilon;

    int state_t;
    int action_t;

    std::vector<MinorityGameStrategy> strategies;
    std::vector<std::vector<float>> q_table;
public:
    QLearningAgent(int, int, float, float);
    int take_action(int);
    void update_q_table(int, int);
    void update_state(int);
    int pick_best_strategy(int);
};

#endif