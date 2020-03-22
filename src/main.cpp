#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "config.h"
#include "q_learning_agent.h"
#include "minority_game_agent.h"

void run_simulation(int, int, int, int, float, float, int);

int main(int argc, char **argv) {
    std::vector<int> n_mg_agents_vec = {10, 11, 12, 14, 16, 18, 20, 22, 25, 28, 32, 36, 41, 46, 52, 58, 66, 74, 83, 94, 106, 119, 134, 151, 170, 191, 215, 242, 272, 307, 345, 388, 437, 492, 554, 623, 701, 789, 888, 1000};
    std::vector<int> n_q_agents_vec = {10, 11, 12, 14, 16, 18, 20, 22, 25, 28, 32, 36, 41, 46, 52, 58, 66, 74, 83, 94, 106, 119, 134, 151, 170, 191, 215, 242, 272, 307, 345, 388, 437, 492, 554, 623, 701, 789, 888, 1000};
    std::vector<int> n_strategies_vec = {2, 3, 4};
    int n_public_information_patterns = 128;
    float learning_rate = 1.0 / n_public_information_patterns;
    float discount_factor = 0.5;
    int n_steps = 100000; // 10^5

    // Q-learning agents
    for (auto n_q_agents : n_q_agents_vec) {
        for (auto n_strategies : n_strategies_vec) {
            run_simulation(
                n_q_agents,
                0,
                n_strategies,
                n_public_information_patterns,
                learning_rate,
                discount_factor,
                n_steps
            );
        }
    }

    // Minority game agents
    for (auto n_mg_agents : n_mg_agents_vec) {
        for (auto n_strategies : n_strategies_vec) {
            run_simulation(
                0,
                n_mg_agents,
                n_strategies,
                n_public_information_patterns,
                learning_rate,
                discount_factor,
                n_steps
            );
        }
    }

    return 0;
}

void run_simulation(
    int n_q_agents,
    int n_mg_agents,
    int n_strategies,
    int n_public_information_patterns,
    float learning_rate,
    float discount_factor,
    int n_steps) {
        // Open output file
        char file_path[1000];
        std::sprintf(file_path, "../results/q%04dmg%04ds%d.csv", n_q_agents, n_mg_agents, n_strategies);
        std::ofstream f(file_path);

        f << "public_information,excess_demand" << std::endl;

        std::uniform_int_distribution<int> uniform_int_dist(0, n_public_information_patterns - 1);

        // Instantiate agents
        std::vector<QLearningAgent> q_agents;
        for (int i = 0; i < n_q_agents; ++i) {
            q_agents.emplace_back(QLearningAgent(n_public_information_patterns, n_strategies, learning_rate, discount_factor));
        }

        std::vector<MinorityGameAgent> mg_agents;
        for (int i = 0; i < n_mg_agents; ++i) {
            mg_agents.emplace_back(MinorityGameAgent(n_public_information_patterns, n_strategies));
        }

        for (int step = 0; step < n_steps; ++step) {
            // Generate public information
            int public_information = uniform_int_dist(mt_engine);
            
            // Collect agents' actions
            std::vector<int> actions;
            for (auto& q_agent : q_agents) {
                actions.emplace_back(q_agent.take_action(public_information));
            }

            for (auto& mg_agent : mg_agents) {
                actions.emplace_back(mg_agent.take_action(public_information));
            }

            // Compute excess demand
            int buys = std::count(std::begin(actions), std::end(actions), BUY);
            int sells = std::count(std::begin(actions), std::end(actions), SELL);
            int excess_demand = buys - sells;

            // Update q tables
            for (auto& q_agent : q_agents) {
                q_agent.update_q_table(excess_demand, public_information);
            }

            // Update scores
            for (auto& mg_agent : mg_agents) {
                mg_agent.update_scores(excess_demand, public_information);
            }

            // Update agents' states
            for (auto& q_agent : q_agents) {
                q_agent.update_state(step);
            }
            
            // Output data to file
            f << public_information << "," << excess_demand << std::endl;
        }

        // Close output file
        f.close();
}