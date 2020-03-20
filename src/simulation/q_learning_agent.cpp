#include "q_learning_agent.h"

QLearningAgent::QLearningAgent(int n_strategies, float learning_rate, float discount_factor) {
    this->learning_rate = learning_rate;
    this->discount_factor = discount_factor;

    this->epsilon = 1;

    for (int i = 0; i < n_strategies; ++i) {
        this->q_table.emplace_back(std::vector<float>(n_strategies, 0.0));
    }

    // Initialise state
    std::uniform_int_distribution<int> uniform_int_dist(0, n_strategies - 1);
    this->state_t = uniform_int_dist(mt_engine);
}

int QLearningAgent::take_action() {
    if (uniform_real_dist(mt_engine) < this->epsilon) { // Randomly pick strategy
        std::uniform_int_distribution<int> uniform_int_dist(0, this->q_table.size() - 1); // x ~ {0, 1, ..., S - 1}
        
        this->action_t = uniform_int_dist(mt_engine);
    } else { // Greedily pick strategy
        int best_strategy = -1;
        float max_q_value = -1001001001;
        
        std::vector<float> q_values = this->q_table[this->state_t];

        for (int i = 0; i < q_values.size(); ++i) {
            if (q_values[i] > max_q_value) {
                best_strategy = i;
                max_q_value = q_values[i];
            }
        }

        this->action_t = best_strategy;
    }

    return this->action_t;
}

void QLearningAgent::update_q_table(int excess_demand) {
    // TODO
}

void QLearningAgent::update_state(int step) {
    this->state_t = this->action_t;
    this->epsilon /= step + 2;
}