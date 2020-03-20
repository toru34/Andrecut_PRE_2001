#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "config.h"
#include "q_learning_agent.h"

static const int n_agents = 101;
static const int n_strategies = 2;
static const float n_histories = 128;
static const float learning_rate = 1 / n_histories;
static const float discount_factor = 0.5;

static const int n_steps = 100;

int main() {
    std::vector<QLearningAgent> agents;
    for (int i = 0; i < n_agents; ++i) {
        agents.emplace_back(QLearningAgent(n_strategies, learning_rate, discount_factor));
    }

    for (int step = 0; step < n_steps; ++step) {
        // Collect agents' actions
        std::vector<int> actions;
        for (auto& agent : agents) {
            actions.emplace_back(agent.take_action());
        }

        // Compute excess demand
        int buys = std::count(std::begin(actions), std::end(actions), BUY);
        int sells = std::count(std::begin(actions), std::end(actions), SELL);
        int excess_demand = buys - sells;

        // Update q functions
        for (auto& agent : agents) {
            agent.update_q_table(excess_demand);
        }

        // Update agents' states
        for (auto& agent : agents) {
            agent.update_state(step);
        }
    }

    return 0;
}