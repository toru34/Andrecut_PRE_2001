#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "config.h"
#include "q_learning_agent.h"

static const int n_agents = 101;
static const int n_strategies = 2;
static const float n_public_information_patterns = 128;
static const float learning_rate = 1 / n_public_information_patterns;
static const float discount_factor = 0.5;

static const int n_steps = 100;

std::uniform_int_distribution<int> uniform_int_dist(0, n_public_information_patterns - 1);

int main() {
    std::vector<QLearningAgent> agents;
    for (int i = 0; i < n_agents; ++i) {
        agents.emplace_back(QLearningAgent(n_public_information_patterns, n_strategies, learning_rate, discount_factor));
    }

    for (int step = 0; step < n_steps; ++step) {
        // Generate external information
        int public_information = uniform_int_dist(mt_engine);

        // Collect agents' actions
        std::vector<int> actions;
        for (auto& agent : agents) {
            actions.emplace_back(agent.take_action(public_information));
        }

        // Compute excess demand
        int buys = std::count(std::begin(actions), std::end(actions), BUY);
        int sells = std::count(std::begin(actions), std::end(actions), SELL);
        int excess_demand = buys - sells;

        // Update q functions
        for (auto& agent : agents) {
            agent.update_q_table(excess_demand, public_information);
        }

        // Update agents' states
        for (auto& agent : agents) {
            agent.update_state(step);
        }
    }

    return 0;
}