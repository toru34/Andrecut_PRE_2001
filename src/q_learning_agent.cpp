#include "q_learning_agent.h"

QLearningAgent::QLearningAgent(int n_public_information_patterns, int n_strategies, float learning_rate, float discount_factor) {
    this->learning_rate = learning_rate;
    this->discount_factor = discount_factor;

    this->epsilon = 1;

    // Initalise strategies
    for (int i = 0; i < n_strategies; ++i) {
        this->strategies.emplace_back(MinorityGameStrategy(n_public_information_patterns));
    }

    // Initialise q table
    for (int i = 0; i < n_strategies; ++i) {
        this->q_table.emplace_back(std::vector<float>(n_strategies, 0.0));
    }

    // Initialise state
    std::uniform_int_distribution<int> uniform_int_dist(0, n_strategies - 1);
    this->state_t = uniform_int_dist(mt_engine);
}

int QLearningAgent::take_action(int public_information) {
    if (uniform_real_dist(mt_engine) < this->epsilon) { // Randomly pick strategy
        std::uniform_int_distribution<int> uniform_int_dist(0, this->q_table.size() - 1); // x ~ {0, 1, ..., S - 1}
        
        this->action_t = uniform_int_dist(mt_engine);
    } else { // Greedily pick strategy
        this->action_t = this->pick_best_strategy(this->state_t);
    }

    return this->strategies[this->action_t].pick_action(public_information);
}

void QLearningAgent::update_q_table(int excess_demand, int p) {
    float reward_t = - this->strategies[this->action_t].pick_action(p) * excess_demand;
    std::vector<float> q_values = this->q_table[this->action_t];
    float max_q_value = *std::max_element(std::begin(q_values), std::end(q_values));

    this->q_table[this->state_t][this->action_t] += this->learning_rate * (reward_t + this->discount_factor * max_q_value - this->q_table[this->state_t][this->action_t]);
}

void QLearningAgent::update_state(int step) {
    this->state_t = this->action_t;
    this->epsilon /= step + 2; // eps = 1 / t
}

int QLearningAgent::pick_best_strategy(int state) {
    int best_stategy = 0;
    int max_q_value = -1001001001;

    // TODO: argmax的なもので置き換える
    std::vector<float> q_values = this->q_table[this->state_t];
    for (int i = 0; i < q_values.size(); ++i) {
        if (q_values[i] > max_q_value) {
            best_stategy = i;
            max_q_value = q_values[i];
        }
    }

    return best_stategy;
}