#ifndef Q_LEARNING_AGENT_H_
#define Q_LEARNING_AGENT_H_

#include <vector>
#include <random>
#include <iostream>

#include "config.h"

class QLearningAgent {
private:
    float learning_rate;
    float discount_factor;
    float epsilon;

    int state_t;
    int action_t;

    std::vector<std::vector<float>> q_table;
public:
    QLearningAgent(int, float, float);
    int take_action();
    void update_q_table(int);
    void update_state(int);
};

#endif