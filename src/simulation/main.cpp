#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "config.h"
#include "q_learning_agent.h"

void run_simulation(int, int, int, float, float, int);

int main(int argc, char **argv) {
    std::vector<int> n_agents_vec = {10, 12, 16, 20, 26, 33, 42, 54, 69, 88, 112, 143, 183, 233, 297, 379, 483, 615, 784, 1000};
    std::vector<int> n_strategies_vec = {2, 3, 4};
    int n_public_information_patterns = 128;
    float learning_rate = 1.0 / n_public_information_patterns;
    float discount_factor = 0.5;
    int n_steps = 100000; // 10^5

    for (auto n_agents : n_agents_vec) {
        for (auto n_strategies : n_strategies_vec) {
            run_simulation(
                n_agents=n_agents,
                n_strategies=n_strategies,
                n_public_information_patterns=n_public_information_patterns,
                learning_rate=learning_rate,
                discount_factor=discount_factor,
                n_steps=n_steps
            );
        }
    }

    return 0;
}

void run_simulation(
    int n_agents,
    int n_strategies,
    int n_public_information_patterns,
    float learning_rate,
    float discount_factor,
    int n_steps) {
        // Open output file
        char file_path[1000];
        std::sprintf(file_path, "../../results/a%ds%d.csv", n_agents, n_strategies);
        std::ofstream f(file_path);

        f << "public_information, excess_demand" << std::endl;

        std::uniform_int_distribution<int> uniform_int_dist(0, n_public_information_patterns - 1);

        // Instantiate agents
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

            // Update q tables
            for (auto& agent : agents) {
                agent.update_q_table(excess_demand, public_information);
            }

            // Update agents' states
            for (auto& agent : agents) {
                agent.update_state(step);
            }
            
            // Output data to file
            f << public_information << ", " << excess_demand << std::endl;
        }

        // Close output file
        f.close();
}